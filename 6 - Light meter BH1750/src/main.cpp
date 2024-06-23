/*
 *	BH1750 - Sensor de luz
 *	Autor: Luis Ángel Cruz Díaz
 *	Fecha:  17/11/2023
 *
 *	Este programa lee el sensor de luz BH1750 y lo muestra en el monitor serial.
 *	Hace uso de la librería BH1750.
 * 
 *	BH1750		ESP8266
 *	VCC---------VIN
 *	GND---------GND
 *	SDA---------GPIO4 (D2)
 *	SCL---------GPIO5 (D1)
 *
 *  BH1750  ESP32
 *  VCC---------VIN
 *  GND---------GND
 *  SDA---------GPIO21
 *  SCL---------GPIO22
 */

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

/*
 *	El BH1750 tiene dos direcciones I2C posibles, 0x23 y 0x5c.
 *	La dirección 0x23 es la dirección por defecto, pero si se conecta el pin ADDR a VCC, 
 *	la dirección pasa a ser 0x5c.
*/
BH1750 luxometro(0x23);             // Dirección I2C del sensor de luz
unsigned int delayTime = 2000;      // Tiempo de espera entre lecturas
unsigned long tiempoAnterior = 0;


void setup(){
	Serial.begin(9600);
	Wire.begin();
/*
 *	El sensor tiene dos modos de funcionamiento:
 *		- Modo de medición continua	
 *			- Modo de medición continua de alta resolución (CONTINUOUS_HIGH_RES_MODE)
 *			- Modo de medición continua de alta resolución 2 (CONTINUOUS_HIGH_RES_MODE_2)
 *			- Modo de medición continua de baja resolución (CONTINUOUS_LOW_RES_MODE)
 *		- Modo de medición única
 *			- Modo de medición única de alta resolución (ONE_TIME_HIGH_RES_MODE)
 *			- Modo de medición única de alta resolución 2 (ONE_TIME_HIGH_RES_MODE_2)
 *			- Modo de medición única de baja resolución (ONE_TIME_LOW_RES_MODE)
 */
	luxometro.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);    // Inicializa el sensor en modo de medición continua de alta resolución 2
}

void loop(){
    unsigned long tiempoActual = millis();
    if(tiempoActual - tiempoAnterior >= delayTime){
        tiempoAnterior = tiempoActual;
        uint16_t lux = luxometro.readLightLevel();
        Serial.println("Luz: " + String(lux) + " lx");
    }
}