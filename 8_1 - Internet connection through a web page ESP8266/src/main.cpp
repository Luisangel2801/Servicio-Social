/*
 * Conexión a red WiFi a través de una página web con ESP8266
 * Autor: Luis Ángel Cruz Díaz
 * Fecha: 2 de Diciembre de 2023
 * 
 * El siguiente código crea un punto de acceso WiFi temporal en caso de que no se haya
 * configurado una red WiFi previamente. A continuación, el usuario debe conectarse a 
 * esta red temporal e ingresar las credenciales de la red WiFi a la que desea conectar 
 * el ESP8266. Una vez que el ESP8266 se haya conectado a la red WiFi seleccionada, se mostrará 
 * la dirección IP asignada al dispositivo.
 *
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

Ticker ticker;          // Objeto para el manejo de interrupciones
int statusLedPin = 2;	// Led azul del ESP8266
int errorLedPin = 16;   // Led rojo del ESP8266

// Función para el parpadeo del led
void parpadeo(){
    byte estado = digitalRead(errorLedPin);
    digitalWrite(errorLedPin, !estado);
}

void setup() {
    Serial.begin(115200);
    pinMode(errorLedPin, OUTPUT);
    pinMode(statusLedPin, OUTPUT);
    digitalWrite(statusLedPin, HIGH);
    ticker.attach(0.2, parpadeo);   // Inicialización del ticker
    WiFiManager wifiManager;        // Inicialización de la conexión a la red WiFi
    //wifiManager.resetSettings();  // Descomenta esta línea si quieres resetear la configuración de WiFi
    // Conexión a la red WiFi
    if (!wifiManager.autoConnect("ESP8266_temporal","12345678")){
        Serial.println("Fallo en la conexión (timeout)");
        ESP.reset();                // Reiniciar el ESP8266
        delay(1000);
    }
    // Detener el ticker
    ticker.detach();
    digitalWrite(errorLedPin, HIGH);
    digitalWrite(statusLedPin, LOW);
    Serial.println("Conectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
}