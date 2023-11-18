/*
 *	MQ135 - Sensor de calidad de aire
 *	Autor: Luis Ángel Cruz Díaz
 *	Fecha:  17/11/2023
 *
 *	Este programa lee el valor del sensor MQ135 y lo muestra en el monitor serial
 *	El sensor MQ135 se conecta al pin A0 del ESP8266
 * 
 *	ESP8266      MQ135
 *	VCC----------VCC
 *	GND----------GND
 *	A0-----------A0
 */

#include <Arduino.h>
#include <MQ135.h>

#define PIN_ANALOG A0

MQ135 mq135_sensor(PIN_ANALOG);
unsigned long tiempoActual = 0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	if (millis() % 1000 == 0){
		int ppm = mq135_sensor.getPPM();
		Serial.print("CO2: " + String(ppm) + " ppm\n");
	}
}