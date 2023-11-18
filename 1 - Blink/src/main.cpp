/*	Blink ESP8266
 *	Autor: Luis Angel Cruz Diaz
 *	Fecha: 16/11/2023
 * 
 *	Este programa realiza el parpadep del LED integrado del ESP8266
 *	para prueba de funcionamiento del IDE PlatformIO
 *
 *	ESP8266
 *	Led integrado rojo = Pin 16 (GPIO 2)
 *	Led integrado azul = Pin 2 (GPIO 16)
 */

#include <Arduino.h>

//const int led = 2;
const int led = 16; 

void setup() {
	Serial.begin(9600);		// iniciar puerto serial
	pinMode(led, OUTPUT);	// inicializar GPIO 2 como salida 
} 

void loop() { 
	digitalWrite(led, HIGH);	// apaga el LED (HIGH es ALTO y es el nivel de voltaje)
	Serial.println("LED OFF");
	delay(10000);				// espera 1000 milisegundos = un segundo
	digitalWrite(led, LOW);		// enciende el LED (LOW es BAJO y es el nivel de voltaje)
	Serial.println("LED ON");
	delay(10000);				// espera 1000 miliasegundos = un segundo
}
