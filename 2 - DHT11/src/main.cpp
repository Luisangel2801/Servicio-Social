/*
 *  Humidity Sensor
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha:  16/11/2023
 *
 *  Este programa lee la humedad y temperatura de un sensor DHT22
 *  y lo muestra por el puerto serial.
 *
 *  El sensor DHT22 se conecta al pin 14 (D5) del ESP8266
 *
 * ESP8266      DHT22
 * VCC----------VCC
 * GND----------GND
 * 14-----------DATA
 *
 */

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

int sensor = 14;
float temperatura;
float humedad;
unsigned long tiempoActual = 0;

// Si queremos usar el DHT22 en lugar del DHT11, cambiamos el tipo de sensor a DHT22
DHT dht(sensor, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  if (millis() % 2000 == 0) {
    tiempoActual = millis();
    temperatura = dht.readTemperature();
    humedad = dht.readHumidity();
    Serial.print("Temperatura: " + String(temperatura) + " Humedad: " + String(humedad) + "\n");
  }
}