/*
 *  Programa para enviar mensajes MQTT con el ESP32
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha: 15 de Diciembre de 2023
 *
 *  Se requiere de la librería WiFi.h, WiFiManager.h, DNSServer.h, WebServer.h, PubSubClient.h, WiFiClientSecure.h y Ticker.h
 * 
 *  El siguiente código crea un punto de acceso WiFi temporal en caso de que no se haya
 *  configurado una red WiFi previamente. A continuación, el usuario debe conectarse a 
 *  esta red temporal e ingresar las credenciales de la red WiFi a la que desea conectar 
 *  el ESP32. Una vez que el ESP32 se haya conectado a la red WiFi seleccionada, se podrá
 *  enviar mensajes MQTT al broker MQTT configurado en el código.
 *
 *  El broker MQTT de EMQX es un broker público y gratuito, por lo que no se requiere
 *  de un usuario y contraseña para conectarse, sin embargo, se requiere de un certificado
 *  de seguridad para la conexión, el certificado se encuentra en la variable ca_cert.
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <Ticker.h>

Ticker timer;                                   // Objeto para manejar el tiempo no bloqueante

int statusLedPin = 2;                           // Led integrado en el ESP32
unsigned int msgTime = 5000;                    // Modificar el tiempo de envío de mensajes

// Variables de configuración de MQTT
const char *mqtt_broker = "broker.emqx.io";     // Remplazar con la dirección de tu broker MQTT
const char *mqtt_topic = "tema/tema";           // Remplazar con el topic de tu broker MQTT
const char *device_name = "nombre_dispositivo"; // Remplazar con el nombre de tu dispositivo
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

void connectToMQTT() {
    while (!mqtt_client.connected()) {
        String clientId = String(device_name);
        clientId += "_" + String(random(0xffff), HEX);
        Serial.println("Conectando al broker MQTT como " + String(clientId.c_str()));
        if (mqtt_client.connect(clientId.c_str(), device_name, mqtt_password)) {
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

// Función para el parpadeo del led
void parpadeo() {
    int estado = digitalRead(statusLedPin);
    digitalWrite(statusLedPin, !estado);
}

void setup() {
    Serial.begin(115200);
    pinMode(statusLedPin, OUTPUT);
    timer.attach(0.2, parpadeo);            // Configura el tiempo de las interrupciones para el parpadeo del led
    WiFiManager wifiManager;                // Inicialización de la conexión a la red WiFi
    //wifiManager.resetSettings();          // Descomenta esta línea si quieres resetear la configuración de WiFi
    // Conexión a la red WiFi
    if (!wifiManager.autoConnect("ESP32_temporal", "12345678")) {
        Serial.println("Fallo en la conexión (timeout)");
        ESP.restart();                      // Reinicia el ESP32
        delay(1000);
    }
    timer.detach();                         // Detiene el parpadeo del led
    digitalWrite(statusLedPin, LOW);
    Serial.println("Conectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
    esp_client.setCACert(ca_cert);          // Configura el certificado de seguridad
    mqtt_client.setServer(mqtt_broker, mqtt_port);  // Configura el broker MQTT
    mqtt_client.setKeepAlive(60);           // Configura el tiempo de espera
    connectToMQTT();                        // Conecta al broker MQTT
    timer.attach_ms(msgTime, enviarJSON);   // Configura el tiempo de las interrupciones
}

void loop() {
    if(!mqtt_client.connected()){
        connectToMQTT();
    }else{
        mqtt_client.loop();
    }
}