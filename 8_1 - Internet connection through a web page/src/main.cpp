/*
 *  Conexión a red WiFi a través de una página web
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha: 2 de Diciembre de 2023
 *
 *  El siguiente código crea un punto de acceso WiFi temporal en caso de que no se haya
 *  configurado una red WiFi previamente. A continuación, el usuario debe conectarse a 
 *  esta red temporal e ingresar las credenciales de la red WiFi a la que desea conectar 
 *  el ESP32. Una vez que el ESP32 se haya conectado a la red WiFi seleccionada, se mostrará 
 *  la dirección IP asignada al dispositivo.
 * 
 * Es necesario de agregar las siguientes librerías:
 * - WiFiManager.h by tzapu
 * - DNSServer.h
 * - Ticker.h
 * - ESP8266WiFi.h (para ESP8266)
 * - ESP8266WebServer.h (para ESP8266)
 * - WiFi.h (para ESP32)
 * - WebServer.h (para ESP32)
 */
#include <Arduino.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <Ticker.h>

#ifdef ESP8266_BOARD
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    int errorLedPin = 16;
    bool ledEncendido = false;
    bool ledApagado = true;
#elif defined(ESP32_BOARD)
    #include <WiFi.h>
    #include <WebServer.h>
    int errorLedPin = 21;
    bool ledEncendido = true;
    bool ledApagado = false;
#endif

Ticker ticker;          // Objeto para el manejo de interrupciones
int statusLedPin = 2;   // Led integrado en el ESP32

// Función para el parpadeo del led
void parpadeo() {
    int estado = digitalRead(statusLedPin);
    digitalWrite(statusLedPin, !estado);
}

void setup() {
    Serial.begin(115200);
    pinMode(statusLedPin, OUTPUT);
    pinMode(errorLedPin, OUTPUT);
    digitalWrite(errorLedPin, ledApagado);
    digitalWrite(statusLedPin, ledApagado);
    ticker.attach(0.2, parpadeo);   // Inicialización del ticker
    WiFiManager wifiManager;        // Inicialización de la conexión a la red WiFi
    //wifiManager.resetSettings();    // Descomenta esta línea si quieres resetear la configuración de WiFi
    // Conexión a la red WiFi
    if (!wifiManager.autoConnect("ESP32_temporal", "12345678")) {
        Serial.println("Fallo en la conexión (timeout)");
        ESP.restart();
        delay(1000);
    }
    // Detener el ticker
    ticker.detach();
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Fallo en la conexión");
        digitalWrite(errorLedPin, ledEncendido);
        digitalWrite(statusLedPin, ledApagado);
        delay(1000);
        ESP.restart();
    }else{
        digitalWrite(errorLedPin, ledApagado);
        digitalWrite(statusLedPin, ledEncendido);
        Serial.println("Conectado a WiFi");
        Serial.print("Dirección IP: ");
        Serial.println(WiFi.localIP());
    }
}

void loop() {
}