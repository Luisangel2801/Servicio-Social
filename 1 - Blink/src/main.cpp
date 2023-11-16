/* Blink ESP8266
 * Autor: Luis Angel Cruz Diaz
 * Fecha: 16/11/2023
 * 
 * Este programa realiza el parpadep del LED integrado del ESP8266
 * para prueba de funcionamiento del IDE PlatformIO
 *
 */

/*  ESP8266
 *  Pin 16 = Led integrado rojo
 *  Pin 2 = Led integrado azul
 */

#include <Arduino.h>

const int led = 2; // GPIO 2
// const int led = 16; 

void setup() { 
  pinMode(led, OUTPUT);  // inicializar GPIO 2 como salida 
} 

void loop() { 
  digitalWrite(led, HIGH); // enciende el LED (HIGH es ALTO y es el nivel de voltaje)
  delay(1000);                // espera 1000 milisegundos = un segundo
  digitalWrite(led, LOW);  // apaga el LED (LOW es BAJO y es el nivel de voltaje)
  delay(1000);                // espera 1000 miliasegundos = un segundo
}
