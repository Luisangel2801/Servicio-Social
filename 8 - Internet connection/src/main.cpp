/*
 *	Conexión a red WiFi con ESP8266
 *	Autor: Luis Ángel Cruz Díaz
 *	Fecha: 18 de noviembre de 2023
 *
 *	Se requiere de la librería ESP8266WiFi
 *	para el manejo de la conexión a red WiFi
 */
#include <ESP8266WiFi.h>

// Variables de configuración de red
const char* ssid = "********";
const char* password = "********";

byte cont = 0;
byte max_intentos = 50;
int statusLedPin = 2;	// Led azul del ESP8266
int errorLedPin = 16; // Led rojo del ESP8266

void setup_wifi() {
	delay(10);
	// Mensajes de intento de conexión
	Serial.println();
	Serial.print("Conectando a: ");
	Serial.println(ssid);
    
	// Funciones de conexión
	WiFi.begin(ssid, password); // Proporcionar características de red
	
	// Secuencia que hace parpadear los leds durante el intento de conexión. Logica Inversa
	while (WiFi.status() != WL_CONNECTED and cont < max_intentos) {
		cont++;
		digitalWrite (statusLedPin, HIGH);
		delay(500); // Dado que es de suma importancia esperar a la conexión, debe usarse espera bloqueante
		digitalWrite (statusLedPin, LOW);
		Serial.print(".");  // Indicador de progreso
		delay (5); // Espera asimetrica para dar la sensación de parpadeo al led
  }

	randomSeed(micros());

	// Mensajes de confirmación
    if(cont < max_intentos){
		Serial.println("*************************");
		Serial.print("Conectado a la red WiFi: ");
		Serial.println(WiFi.SSID());
		Serial.print("IP: ");
		Serial.println(WiFi.localIP());
		Serial.print("macAddress: ");
		Serial.println(WiFi.macAddress());
		Serial.println("*************************");
	}else{
		Serial.println("-------------------------------");
		Serial.println("Error de conexion");
		digitalWrite (statusLedPin, HIGH);
		digitalWrite (errorLedPin, LOW);
		Serial.println("-------------------------------");
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(statusLedPin, OUTPUT);
	pinMode(errorLedPin, OUTPUT);
	digitalWrite (statusLedPin, HIGH);
	digitalWrite (errorLedPin, HIGH);
	setup_wifi();
}

void loop() {

}