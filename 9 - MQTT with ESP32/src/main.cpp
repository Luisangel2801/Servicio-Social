/*
 *  Envio de mensajes a un broker MQTT publico de EMQX
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha: 20 de noviembre de 2023
 *
 *  Se requiere de la librería WiFi.h, PubSubClient.h y WiFiClientSecure.h
 *  para el manejo de la conexión a la red WiFi y el envío de mensajes MQTT,
 *  también se requiere de la librería Ticker.h para el manejo del tiempo no bloqueante
 * 
 *  En este ejemplo se envía un mensaje JSON con la temperatura y humedad simulada
 *  de un sensor, el mensaje se envía cada 5 segundos al broker MQTT de EMQX, también
 *  se conectó un led al puerto D21 para indicar un error de conexión.
 *
 *  El broker MQTT de EMQX es un broker público y gratuito, por lo que no se requiere
 *  de un usuario y contraseña para conectarse, sin embargo, se requiere de un certificado
 *  de seguridad para la conexión, el certificado se encuentra en la variable ca_cert.
 */

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <Ticker.h>

Ticker timer;   // Objeto para manejar el tiempo no bloqueante

// Variables de configuración de red
const char *ssid = "SSID";                      // Remplazar con el nombre de tu red WiFi
const char *password = "Password";              // Remplazar con la contraseña de tu red WiFi
const char* device_name = "nombre_dispositivo"; // Nombre del dispositivo

// Variables para el manejo de errores
byte cont = 0;
byte max_intentos = 50;
int statusLedPin = 2;   // Led interno del ESP32
int errorLedPin = 21;   // Led conectado al puerto D21

unsigned int msgTime = 5000;    // Tiempo de espera entre mensajes

// Variables de configuración de MQTT
const char *mqtt_broker = "broker.emqx.io";     // Remplazar con la dirección de tu broker MQTT
const char *mqtt_topic = "prueba/temperatura";  // Remplazar con el topic de tu broker MQTT
const char *mqtt_username = device_name;
const char *mqtt_password = "public";
const int mqtt_port = 8883;

WiFiClientSecure esp_client;
PubSubClient mqtt_client(esp_client);

const char *ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
-----END CERTIFICATE-----
)EOF";

void setup_wifi() {
    delay(10);
    // Mensajes de intento de conexión
    Serial.println();
    Serial.print("Conectando a: ");
    Serial.print(ssid);
    Serial.print(" ");

    // Funciones de conexión
    WiFi.begin(ssid, password);

    // Secuencia que hace parpadear los leds durante el intento de conexión.
    while (WiFi.status() != WL_CONNECTED and cont < max_intentos) {
        cont++;
        digitalWrite (statusLedPin, HIGH);
        delay(500);
        digitalWrite (statusLedPin, LOW);
        Serial.print(".");  // Indicador de progreso
        delay (100); // Espera asimetrica para dar la sensación de parpadeo al led
    }

    // Esta función mejora los resultados de las funciones aleatorias y toma como semilla el contador de tiempo
    randomSeed(micros());

    // Mensajes de confirmación
    if(cont < max_intentos){
        Serial.println("\n*************************");
        digitalWrite(statusLedPin, HIGH);
        digitalWrite(errorLedPin, LOW);
        Serial.print("Conectado a la red WiFi: ");
        Serial.println(WiFi.SSID());
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("macAddress: ");
        Serial.println(WiFi.macAddress());
        Serial.println("*************************");
    }else{
        Serial.println("-------------------------------");
        Serial.println("Error de conexion");
        digitalWrite (statusLedPin, LOW);
        digitalWrite (errorLedPin, HIGH);
        Serial.println("-------------------------------");
    }
}

void connectToMQTT() {
    while (!mqtt_client.connected()) {
        String clientId = String(device_name);
        clientId += "_" + String(random(0xffff), HEX);
        Serial.println("Conectando al broker MQTT como " + String(clientId.c_str()));
        if (mqtt_client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Broker MQTT conectado");
            mqtt_client.subscribe(mqtt_topic);
        } else {
            Serial.print("Error al conectar al broker MQTT:: Estado:");
            Serial.print(mqtt_client.state());
            Serial.println("Intentando de nuevo en 5 segundos");
            delay(5000);
        }
    }
}

void enviarJSON(){
    String json = "{\"id\":\""+ String(device_name) + "\",\"temp\":"+ String(25.4) + ",\"hum\":"+String(60)+"}";
    // Serial.println(json); ¡
    int str_len = json.length() + 1;            // Calcula la longitud del string
    char char_array[str_len];                   // Crea un array de char con la longitud calculada
    json.toCharArray(char_array, str_len);      // Convierte el string a un array de char
    mqtt_client.publish(mqtt_topic, char_array);// Publica el mensaje en el topic 
}

void setup() {
    Serial.begin(115200);
    pinMode(statusLedPin, OUTPUT);
    pinMode(errorLedPin, OUTPUT);
    setup_wifi();                                   // Conecta a la red WiFi
    esp_client.setCACert(ca_cert);                  // Configura el certificado de seguridad
    mqtt_client.setServer(mqtt_broker, mqtt_port);  // Configura el broker MQTT
    mqtt_client.setKeepAlive(60);                   // Configura el tiempo de espera
    connectToMQTT();                                // Conecta al broker MQTT
    timer.attach_ms(msgTime, enviarJSON);           // Configura el tiempo de las interrupciones
}

void loop() {
    if(!mqtt_client.connected()){
        connectToMQTT();
    }else{
        mqtt_client.loop();
    }
}