/*
 *	LCD I2C
 *	Autor: Luis Ángel Cruz Díaz
 *	Fecha:  16/11/2023
 *
 *	Este programa muestra cáracteres en una pantalla LCD 16x2
 *
 *	El programa utiliza la librería LiquidCrystal_I2C
 *
 *	LCD     ESP8266         Power Supply
 *	VCC---------------------5V
 *	GND-----GND-------------GND
 *	SDA-----GPIO4 (D2)
 *	SCL-----GPIO5 (D1)
 *
 *  LCD     ESP32           Power Supply
 *  VCC---------------------5V
 *  GND-----GND-------------GND
 *  SDA-----GPIO21 (D21)
 *  SCL-----GPIO22 (D22)
 */

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección 0x27, pantalla con 16 columnas y 2 filas

void setup() {
	lcd.init();             // Inicializa la pantalla
	lcd.backlight();        // Enciende la luz de la pantalla
	lcd.setCursor(0, 0);    // Coloca el cursor en la columna 0, fila 0
	lcd.print("Hola Mundo");// Imprime el mensaje en la pantalla
	lcd.setCursor(0, 1);    // Coloca el cursor en la columna 0, fila 1
	lcd.print("LCD I2C");   // Imprime el mensaje en la pantalla
}

void loop() {
}