/*
 *  Conexión a red WiFi con ESP32
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha: 18 de noviembre de 2023
 *
 * Se requiere de la librería Wifi.h para la conexión a la red WiFi en el ESP32
 * Se requiere de la librería ESP8266WiFi.h para la conexión a la red WiFi en el ESP8266
 * 
 * En este código se muestra la secuencia de conexión a una red WiFi con un ESP32
 * o un ESP8266. Se muestra el uso de los leds para indicar el estado de la conexión.
 */

#include <Arduino.h>

#ifdef ESP8266_BOARD
    #include <ESP8266WiFi.h>
    int errorLedPin = 16;
    bool ledEncendido = false;
    bool ledApagado = true;
#elif defined(ESP32_BOARD)
    #include <WiFi.h>
    int errorLedPin = 21;
    bool ledEncendido = true;
    bool ledApagado = false;
#endif

// Variables de configuración de red
const char *ssid = "SSID";          // Nombre de la red
const char *password = "PASSWORD";  // Contraseña de la red

// Variables para el manejo de errores
byte cont = 0;
byte max_intentos = 50;
int statusLedPin = 2;
bool ledState = false;

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
        ledState = !ledState;
        digitalWrite(statusLedPin, ledState);
        delay(500);
        ledState = !ledState;
        digitalWrite (statusLedPin, ledState);
        Serial.print(".");  // Indicador de progreso
        delay (100); // Espera asimetrica para dar la sensación de parpadeo al led
    }

    // Esta función mejora los resultados de las funciones aleatorias y toma como semilla el contador de tiempo
    randomSeed(micros());

    // Mensajes de confirmación
    if(cont < max_intentos){
        Serial.println("\n*************************");
        digitalWrite(statusLedPin, ledEncendido);
        digitalWrite(errorLedPin, ledApagado);
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
        digitalWrite (statusLedPin, ledApagado);
        digitalWrite (errorLedPin, ledEncendido);
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