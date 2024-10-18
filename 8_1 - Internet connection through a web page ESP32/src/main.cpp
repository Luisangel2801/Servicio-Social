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
 *  Es necesario de agregar las siguientes librerías:
 *  - WiFi.h
 *  - WiFiManager.h by tzapu
 *  - DNSServer.h
 *  - WebServer.h
 *  - Ticker.h
 */
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <Ticker.h>

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
    ticker.attach(0.2, parpadeo);   // Inicialización del ticker
    WiFiManager wifiManager;        // Inicialización de la conexión a la red WiFi
    //wifiManager.resetSettings();  // Descomenta esta línea si quieres resetear la configuración de WiFi
    // Conexión a la red WiFi
    if (!wifiManager.autoConnect("ESP32_temporal", "12345678")) {
        Serial.println("Fallo en la conexión (timeout)");
        ESP.restart();
        delay(1000);
    }
    // Detener el ticker
    ticker.detach();
    digitalWrite(statusLedPin, LOW);
    Serial.println("Conectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
}