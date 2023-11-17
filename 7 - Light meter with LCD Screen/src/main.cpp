/*
 *  Mostrar valores del BH1750 en una pantalla LCD 
 *  Autor: Luis Ángel Cruz Díaz
 *  Fecha:  16/11/2023
 *
 *  Este programa muestra los valores de iluminación en una pantalla LCD
 *
 *  El programa utiliza la librería LiquidCrystal_I2C para controlar la pantalla LCD
 *  y la librería BH1750 para controlar el sensor de iluminación
 *  
 *  El sensor de luz se conecta de la siguiente manera:
 *	
 *  BH1750   ESP8266
 *  VCC------VIN
 * 	GND------GND
 * 	SDA------GPIO4 (D2)
 * 	SCL------GPIO5 (D1)
 *  ADDR-----VCC resitencia 10K
 * 
 *  La pantalla LCD se conecta de la siguiente manera:
 *  LCD		ESP8266
 *  VCC------VIN
 *  GND------GND
 *  SDA------GPIO4 (D2)
 *  SCL------GPIO5 (D1)
 */
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

// La dirección I2C de la pantalla LCD es 0x27
LiquidCrystal_I2C lcd(0x27,16,2);

// La dirección I2C del sensor de iluminación es 0x23
BH1750 luxometro(0x23);

void setup(){
    Wire.begin();
    luxometro.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
    lcd.init();
	lcd.backlight();
}

void loop(){
    if (millis() % 2000 == 0) {
        uint16_t lux = luxometro.readLightLevel();
    	lcd.clear();
    	lcd.setCursor(0,0);
    	lcd.print("Luz: " + String(lux) + " lx");
  	}
}