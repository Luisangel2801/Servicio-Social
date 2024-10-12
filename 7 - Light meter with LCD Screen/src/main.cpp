/*
 *	Mostrar valores del BH1750 en una pantalla LCD 
 *	Autor: Luis Ángel Cruz Díaz
 *	Fecha:  16/11/2023
 *
 *	Este programa muestra los valores de iluminación en una pantalla LCD
 *
 *	El programa utiliza la librería LiquidCrystal_I2C para controlar la pantalla LCD
 *	y la librería BH1750 para controlar el sensor de iluminación
 *  
 ************************************************************************************
 *	El sensor de luz y la pantalla LCD se conectan al ESP8266 de la siguiente manera:
 *	
 *  BH1750      ESP8266         LCD     Power Supply
 *	VCC---------------------------------3.3V
 *	GND---------GND-------------GND-----GND
 *	SDA---------GPIO4 (D2)------SDA
 *	SCL---------GPIO5 (D1)------SCL
 *              VIN-------------VCC-----5V
 ************************************************************************************
 *	El sensor de luz y la pantalla LCD se conectan al ESP32 de la siguiente manera:
 *	
 *  BH1750      ESP32           LCD     Power Supply
 *	VCC---------------------------------3.3V
 *	GND---------GND-------------GND-----GND
 *	SDA---------GPIO21 (D21)----SDA
 *	SCL---------GPIO22 (D22)----SCL
 *              VIN-------------VCC-----5V
 */
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

// La dirección I2C de la pantalla LCD es 0x27
LiquidCrystal_I2C lcd(0x27,16,2);

// La dirección I2C del sensor de iluminación es 0x23
BH1750 luxometro(0x23);

int tiempoAnterior = 0;
int pausa = 2000;

void setup(){
	Wire.begin();
	luxometro.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
	lcd.init();
	lcd.backlight();
}

void loop(){
    int tiempoActual = millis();
	if (tiempoActual - tiempoAnterior >= pausa) {
        tiempoAnterior = tiempoActual;
		uint16_t lux = luxometro.readLightLevel();
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Luz: " + String(lux) + " lx");
	}
}