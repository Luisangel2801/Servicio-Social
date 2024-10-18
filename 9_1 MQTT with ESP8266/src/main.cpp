/*
 *  Envio de mensajes a un broker MQTT publico de EMQX
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha: 10 de Diciembre de 2023
 *
 *  Se requiere la librería PubSubClient.h, ESP8266WiFi.h y time.h para el manejo 
 *  de la conexión a la red WiFi, el protocolo MQTT y la sincronización de la hora,
 *  también se requiere la librería Ticker.h para el manejo del tiempo no bloqueante.
 *
 *  En este ejemplo envía mensajes a un broker MQTT público de EMQX. El código se conecta 
 *  a la red WiFi, sincroniza la hora con un servidor NTP, se conecta al broker MQTT y envía 
 *  un mensaje cada cierto tiempo. Se utiliza los leds del ESP8266 para indicar el estado de 
 *  la conexión a la red WiFi.
 *
 *  El broker MQTT de EMQX es un broker público y gratuito, por lo que no se requiere
 *  de un usuario y contraseña para conectarse, sin embargo, se requiere de un certificado
 *  de seguridad para la conexión, el certificado se encuentra en la variable ca_cert.
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <time.h>
#include <Ticker.h>

Ticker timer;   // Objeto para manejar el tiempo no bloqueante
int statusLedPin = 2;	// Led azul del ESP8266
int errorLedPin = 16;   // Led rojo del ESP8266

unsigned int msgTime = 10000;                   // Variable para el tiempo de envío de mensajes
const char* device_name = "nombre_dispositivo"; // Agrega el nombre del dispositivo

// Configuración del broker MQTT
const int mqtt_port = 8883;                 // Puerto del broker MQTT
const char *mqtt_broker = "broker.emqx.io"; // Broker MQTT
const char *mqtt_topic = "tema/tema";       // Agrerga el topic al que se va a publicar
const char *mqtt_username = device_name;    // MQTT usuario
const char *mqtt_password = "public";

// NTP Server settings
const char *ntp_server = "pool.ntp.org";    // Server NTP
const long gmt_offset_sec = -21600;         // -6 horas * 3600 segundos para obtener el offset para México
const int daylight_offset_sec = 0;          // En mexico no se usa horario de verano

BearSSL::WiFiClientSecure espClient;
PubSubClient mqtt_client(espClient);

// Certificado de la CA
static const char ca_cert[]
PROGMEM = R"EOF(
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

// Función para sincronizar la hora
void syncTime() {
    configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
    Serial.print("\nSincronizando la hora ");
    while (time(nullptr) < 1510644967) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\n*************************");
    Serial.println("Hora sincronizada");
    struct tm timeinfo;
    if(getLocalTime(&timeinfo)){
        Serial.print("Horario Actual: ");
        Serial.print(asctime(&timeinfo));
        Serial.println("*************************");
    }else{
        Serial.println("Error al sincronizar la hora");
        Serial.println("*************************");
    }
}

// Función la conexión con el broker MQTT
void connectToMQTT() {
    BearSSL::X509List serverTrustedCA(ca_cert);
    espClient.setTrustAnchors(&serverTrustedCA);
    while(!mqtt_client.connected()){
        String clientId = String(device_name);          // Crea un ID de cliente único
        clientId += "_" + String(random(0xffff), HEX);  // Agrega un ID aleatorio
        Serial.println("Conectando al broker MQTT como " + String(clientId.c_str()));
        if(mqtt_client.connect(clientId.c_str(), mqtt_username, mqtt_password)){
            Serial.println("Broker MQTT conectado");
            mqtt_client.subscribe(mqtt_topic);          // Se suscribe al topic
        }else{
            char err_buff[128];
            espClient.getLastSSLError(err_buff, sizeof(err_buff));
            Serial.println("Error al conectar al broker MQTT:: Estado:");
            Serial.println(mqtt_client.state());        // Muestra el estado de la conexión
            Serial.print(err_buff);
            delay(5000);
        }
    }
}

// Función para enviar un mensaje JSON al broker MQTT
void enviarJSON(){
    String json = "{\"id\":\""+ String(device_name) + "\",\"temp\":"+ String(25.4) + ",\"hum\":"+String(60)+"}";
    // Serial.println(json); ¡
    int str_len = json.length() + 1;            // Calcula la longitud del string
    char char_array[str_len];                   // Crea un array de char con la longitud calculada
    json.toCharArray(char_array, str_len);      // Convierte el string a un array de char
    mqtt_client.publish(mqtt_topic, char_array);// Publica el mensaje en el topic 
}

// Función para el parpadeo del led
void parpadeo(){
    byte estado = digitalRead(errorLedPin);
    digitalWrite(errorLedPin, !estado);
}

void setup() {
    Serial.begin(115200);
    pinMode(statusLedPin, OUTPUT);
    pinMode(errorLedPin, OUTPUT);
    digitalWrite (statusLedPin, HIGH);
    timer.attach(0.2, parpadeo);   // Inicialización del ticker
    WiFiManager wifiManager;        // Inicialización de la conexión a la red WiFi
    //wifiManager.resetSettings();  // Descomenta esta línea si quieres resetear la configuración de WiFi
    // Conexión a la red WiFi
    if (!wifiManager.autoConnect("ESP8266_temporal","12345678")){
        Serial.println("Fallo en la conexión (timeout)");
        ESP.reset();                // Reiniciar el ESP8266
        delay(1000);
    }
    timer.detach();                  // Detiene el ticker de parpadeo
    digitalWrite(errorLedPin, HIGH);
    digitalWrite(statusLedPin, LOW);
    Serial.println("Conectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
    syncTime();                                     // Sincronización de la hora
    mqtt_client.setServer(mqtt_broker, mqtt_port);  // Configuración del broker MQTT
    connectToMQTT();                                // Conexión al broker MQTT
    timer.attach_ms(msgTime, enviarJSON);           // Inicialización del ticker para enviar mensajes
}

void loop() {
    if(!mqtt_client.connected()){
        connectToMQTT();
    }else{
        mqtt_client.loop();
    }
}