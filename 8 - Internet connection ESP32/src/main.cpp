/*
 *  Conexión a red WiFi con ESP32
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha: 18 de noviembre de 2023
 *
 *  Se requiere de la librería Wifi.h
 *  para el manejo de la conexión a red WiFi
 */

#include <Arduino.h>
#include <WiFi.h>

// Variables de configuración de red
const char *ssid = "SSID";          // Nombre de la red
const char *password = "PASSWORD";  // Contraseña de la red

// Variables para el manejo de errores
byte cont = 0;
byte max_intentos = 50;
int statusLedPin = 2;
int errorLedPin = 21;

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

void setup() {
    Serial.begin(115200);
    pinMode(statusLedPin, OUTPUT);
    pinMode(errorLedPin, OUTPUT);
    setup_wifi();
}

void loop() {
}