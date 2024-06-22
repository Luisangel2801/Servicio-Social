/*
 *	Humidity Sensor
 *	Autor: Luis Ángel Cruz Díaz
 *	Fecha:  16/11/2023
 *
 *  Este programa lee la humedad y temperatura de un sensor DHT22 o un DHT11
 *  y muestra los valores en el puerto serial.
 *
 *  El sensor DHT22 o el DHT 11 se conecta al pin 14 (D5) del ESP8266
 *  DHT22       ESP8266
 *  VCC---------VCC
 *  GND---------GND
 *  DATA--------GPIO 14 (D5)
 *
 * El sensor DHT22 o el DHT 11 se conecta al pin 5 (D5) del ESP32
 * DHT22        ESP32
 * VCC----------VCC
 * GND----------GND
 * DATA---------GPIO 5 (D5)
 */

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#ifdef ESP8266_BOARD
    int sensor = 14;
#elif defined(ESP32_BOARD)
    int sensor = 5;
#endif

float temperatura;
float humedad;
float tiempoAnterior = 0;

// Si queremos usar el DHT11 en lugar del DHT22, cambiamos el tipo de sensor a DHT22
DHT dht(sensor, DHT22);

void setup() {
	Serial.begin(9600);
	dht.begin();
}

void loop() {
    float tiempo = millis();
    if (tiempo - tiempoAnterior > 2000) {
        tiempoAnterior = tiempo;
        temperatura = dht.readTemperature();
        humedad = dht.readHumidity();
        Serial.println("Temperatura: " + String(temperatura) + " Humedad: " + String(humedad) +"%");
    }
}