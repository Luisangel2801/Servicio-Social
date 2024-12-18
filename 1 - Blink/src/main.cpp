/*	Blink ESP8266
 *	Autor: Luis Angel Cruz Diaz
 *	Fecha: 16/11/2023
 * 
 *	Este programa realiza el parpadeo de un LED integrado en la placa ESP8266 y ESP32.
 *	para prueba de funcionamiento del IDE PlatformIO
 *
 *  ESP8266
 *  Led integrado rojo = Pin 16 (GPIO 2) - enciende con LOW
 *  Led integrado azul = Pin 2 (GPIO 16) - enciende con LOW
 *
 *  ESP32
 *  Led integrado azul = Pin 2 (D2) - enciende con HIGH
 */

#include <Arduino.h>

#ifdef ESP8266_BOARD
    int led = 2;
    bool ledState = false;
#elif defined(ESP32_BOARD)
    int led = 2;
    bool ledState = true;
#endif

void setup() {
    Serial.begin(9600);     // iniciar puerto serial
    pinMode(led, OUTPUT);   // inicializar pin de salida
} 

void loop() {
    digitalWrite(led, ledState);
    Serial.println("LED ON");
    delay(5000);                // Tiempo de espera de 1 segundo
    bool state = !ledState;
    digitalWrite(led, state);
    Serial.println("LED OFF");
    delay(5000);
}
