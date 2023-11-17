/*
 *  Humidity Sensor with LCD
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha:  16/11/2023
 *
 *  Este programa muestra cáracteres en una pantalla LCD la temperatura y humedad
 *
 *  El programa utiliza la librería LiquidCrystal_I2C para controlar la pantalla LCD
 *  y la librería DHT para controlar el sensor de humedad y temperatura
 *  
 * El sensor de humedad y temperatura DHT11 se conecta de la siguiente manera:
 * DHT11    ESP8266
 * VCC------VIN
 * GND------GND
 * DATA-----GPIO14 (D5)
 * 
 * La pantalla LCD se conecta de la siguiente manera:
 * LCD		ESP8266
 * VCC------VIN
 * GND------GND
 * SDA------GPIO4 (D2)
 * SCL------GPIO5 (D1)
 */
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int sensor = 14;
double tempF,tempC;
int humedad;
DHT dht(sensor,DHT11); // Si queremos usar el DHT22 en lugar del DHT11, cambiamos el tipo de sensor a DHT22

unsigned long tiempoActual = 0; // Variable para almacenar el tiempo actual

void setup() {
	Serial.begin(9600);
	dht.begin();
	lcd.init();
	lcd.backlight();
}

void loop() {
  	// Si han pasado 2 segundos, leemos la temperatura y humedad
	if (millis() % 2000 == 0) {
		tiempoActual = millis();
    	// Lectura de la temperatura y humedad
    	tempC = dht.readTemperature();    // Temperatura en grados centígrados
    	tempF = dht.readTemperature(true);// Temperatura en grados Fahrenheit
    	humedad = dht.readHumidity();     // Humedad relativa
    	// Mostramos la temperatura y humedad en el LCD
    	lcd.clear();
    	lcd.setCursor(0,0);
    	lcd.print("Temp: " + String(tempC) + " C");
    	lcd.setCursor(0,1);
    	lcd.print("Humedad: " + String(humedad) + " %");
  	}
}