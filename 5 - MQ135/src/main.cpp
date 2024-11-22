/*
 * MQ135 - Sensor de calidad de aire
 * Autor: Luis Ángel Cruz Díaz
 * Fecha:  17/11/2023
 *
 * Programa para medir la concentración de CO2 en el aire con un sensor MQ135
 * y evaluar la calidad del aire en función de la concentración de CO2. Este 
 * programa utiliza la curva característica del sensor MQ135 para calibrar el
 * sensor y obtener la concentración de CO2 en partes por millón (ppm).
 * 
 * El sensor MQ135 se conecta con el ESP8266 de la siguiente manera:
 * 
 * ESP8266      MQ135       Power Supply
 * A0-----------A0
 * GND----------GND---------GND
 *              VCC---------5V
 * 
 * El sensor MQ135 se conecta con el ESP32 de la siguiente manera:
 * 
 * ESP32        MQ135       Power Supply
 * D34----------A0
 * GND----------GND---------GND
 *              VCC---------5V
 */

#include <Arduino.h>

#ifdef ESP8266_BOARD
    const int analog_PIN = A0;          // Pin analógico del ESP8266
    const int adc_resolution = 1024 - 1;// La resolución del ADC es de 10 bits
#elif defined(ESP32_BOARD)
    const int analog_PIN = 34;          // Pin analógico del ESP32
    const int adc_resolution = 4096 - 1;// La resolución del ADC es de 12 bits 
#endif

const float VCC = 5;            // Voltaje de alimentación conectado al sensor MQ135
const float RL = 0.750;         // Resistencia de carga en ohmios (1 kΩ) del sensor MQ135
const float air_factor = 3.8;   // Factor de aire limpio (RS/Ro en aire limpio) obtenido de la hoja de datos
float RO = 7.70;                // Resistencia del sensor en aire limpio

float temperature = 25;         // Temperatura en grados Celsius
float humidity = 50;            // Humedad relativa en porcentaje

#define A 116.6020682           // Coeficiente A de la ecuación de correlación
#define B 2.769034857           // Coeficiente B de la ecuación de correlación

#define CORA .00035
#define CORB .02718
#define CORC 1.39538
#define CORD .0018
#define CORE -.003333333
#define CORF -.001923077
#define CORG 1.130128205

String evaluateAirQuality(float ppm) {
    if (ppm < 400) return "Excelente";
    else if (ppm < 1000) return "Buena";
    else if (ppm < 2000) return "Moderada";
    else if (ppm < 5000) return "Mala";
    else return "Peligrosa";
}

// Función para obtener el factor de corrección en función de la temperatura y humedad
float getCorrectionFactor(float tem, float hum) {
    if(tem < 20){
        return CORA * tem * tem - CORB * tem + CORC - (hum-33.)*CORD;
    } else {
        return CORE * tem + CORF * hum + CORG;
    }
}

// Función para obtener la resistencia del sensor MQ135
float getRS(int samples){
    float avgReadings = 0;
    for (int i = 0; i < samples; i++) {
        avgReadings += analogRead(analog_PIN);  // Leer el valor del sensor del pin analógico
        delay(10);
    }
    avgReadings /= samples;                     // Promedio de las lecturas de calibración
    float voltage = avgReadings * (VCC / adc_resolution);// Conversión de lectura a voltaje
    float RS = (VCC / voltage - 1) * RL;                 // Cálculo de resistencia RS
    return RS;
}

void calibrateRO() {
    RO = getRS(10000) / air_factor;             // Obtener resistencia RO en aire limpio
    Serial.printf("RO calibrado: %.2f Ω\n", RO);// Imprimir resistencia RO calibrada
}

float readCO2PPM() {
    float RS = getRS(100);                      // Obtener resistencia RS del sensor
    float RSCorrected = RS / getCorrectionFactor(temperature, humidity);// Corregir la resistencia RS
    float ppm = A * pow((RSCorrected/RO), -B);  // Calcular la concentración de CO2 en ppm
    return ppm;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando sensor MQ135...");
    delay(10000);
    Serial.println("Calibrando sensor MQ135...");
    //calibrateRO();
}

void loop() {
    float ppm = readCO2PPM();
    if (ppm > 0) {
        Serial.printf("Concentración de CO2: %.2f ppm\n", ppm);
        String airQuality = evaluateAirQuality(ppm);
        Serial.printf("Calidad del aire: %s\n", airQuality.c_str());
    }
    Serial.println("--------------------");
    delay(500);
}