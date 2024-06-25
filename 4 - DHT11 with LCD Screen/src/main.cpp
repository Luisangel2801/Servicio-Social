/*
 *	Humidity Sensor with LCD
 *	Autor: Luis Ángel Cruz Díaz
 *	Fecha:  16/11/2023
 *
 *	Este programa muestra la temperatura y humedad en la pantalla LCD
 *
 *	El programa utiliza la librería LiquidCrystal_I2C para controlar la pantalla LCD
 *	y la librería DHT para controlar el sensor de humedad y temperatura
 *  
 *	El sensor de humedad y temperatura DHT11 o el DHT22 se conecta con el ESP8266 de la siguiente manera:
 *
 *  DHT11   ESP8266         LCD     Power Supply
 *  DATA----GPIO14 (D5)
 *  VCC-----VIN-------------VCC-----5V
 *  GND-----GND-------------GND-----GND
 *          GPIO4 (D2)------SDA
 *          GPIO5 (D1)------SCL
 * 
 * El sensor de humedad y temperatura DHT11 o el DHT22 se conecta con el ESP32 de la siguiente manera:
 * 
 *  DHT11   ESP32           LCD     Power Supply
 *  DATA----GPIO 5 (D5)
 *  VCC-----VIN-------------VCC-----5V
 *  GND-----GND-------------GND-----GND
 *          GPIO21 (D21)----SDA
 *          GPIO22 (D22)----SCL
 */

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>

// Pin del sensor según el modelo de placa
#ifdef ESP8266_BOARD
    int sensor = 14;
#elif defined(ESP32_BOARD)
    int sensor = 5;
#endif

// Si queremos usar el DHT11 en lugar del DHT22, cambiamos el tipo de sensor a DHT11
DHT dht(sensor,DHT22);
LiquidCrystal_I2C lcd(0x27,16,2);

double tempF,tempC;
int humedad;
float tiempoAnterior = 0;

void setup() {
	Serial.begin(9600);
	dht.begin();
	lcd.init();
	lcd.backlight();
}

void loop() {
	// Si han pasado 2 segundos, leemos la temperatura y humedad
	int tiempoActual = millis();
    if (tiempoActual - tiempoAnterior >= 2000) {
		tiempoAnterior = tiempoActual;
		// Lectura de la temperatura y humedad
		tempC = dht.readTemperature();    // Temperatura en grados centígrados
		tempF = dht.readTemperature(true);// Temperatura en grados Fahrenheit
		humedad = dht.readHumidity();     // Humedad relativa
		// Mostramos la temperatura y humedad en el LCD
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Temp: " + String(tempC) + " "+ (char)223 +"C");
		lcd.setCursor(0,1);
		lcd.print("Humedad: " + String(humedad) + " %");
	}
}