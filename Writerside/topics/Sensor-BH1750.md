---
switcher-label: Placa
---

# Sensor BH1750

## Descripción

El sensor BH1750 es un sensor de luz digital que permite medir la intensidad de luz en un ambiente. Este sensor es muy utilizado en proyectos de domótica y automatización de hogares.

> El lux es la unidad de medida de la intensidad de luz, y el sensor BH1750 es capaz de medir la intensidad de luz en lux. La diferencia entre el lux y el lumen es que el lux mide la cantidad de luz que llega a una superficie, mientras que el lumen mide la cantidad de luz emitida por una fuente de luz.

- 0,01 lx Cielo nocturno despejado
- 1 lx Cielo nocturno con luna
- 300 lx Sala de reuniones
- 500 lx Oficina bien iluminada
- 1000 lx Iluminación en un estudio de televisión
- 32000 lx Luz solar en un día medio

## Características del sensor BH1750

- Rango de medición de intensidad de luz: 0 a 65535 lux
- Precisión de medición de intensidad de luz: ±20%
- Voltaje de operación: 3.3 a 5 V
- Interfaz de comunicación: I2C
- Dirección I2C: **0x23** (dirección predeterminada) o **0x5C** (dirección al administrar voltaje en el pin ADDR)

## Esquema de conexión para el ESP8266 {switcher-key="ESP8266"}

El sensor BH1750 se conecta a la placa de desarrollo ESP8266 a través de la interfaz I2C. A continuación se muestra el esquema de conexión del sensor BH1750 a la placa de desarrollo ESP8266.

![esp8266](BH1750_ESP8266.png) {border-effect="rounded" width="500" thumbnail="true"}


## Esquema de conexión para el  ESP32 {switcher-key="ESP32"}

El sensor BH1750 se conecta a la placa de desarrollo ESP32 a través de la interfaz I2C. A continuación se muestra el esquema de conexión del sensor BH1750 a la placa de desarrollo ESP32.

![esp32](BH1750_ESP32.png) {border-effect="rounded" width="500" thumbnail="true"}

## Código

El siguiente código funciona para ambas tarjetas de desarrollo, se lee la intensidad de luz del sensor BH1750 y se muestra por el monitor serial.

> En una carpeta se debe agregar un archivo llamado `platformio.ini` con la configuración de la tarjeta de desarrollo que se va a utilizar, además del archivo `main.cpp` con el código, este irá dentro de la carpeta `src`.
> {style="warning"}

El sensor tiene dos modos de funcionamiento:
1. Modo de medición continua - Realiza mediciones continuas de la intensidad de luz
    - `CONTINUOUS_LOW_RES_MODE` resolucion de 4 lux toma 16ms hacer una lectura
    - `CONTINUOUS_HIGH_RES_MODE` resolucion de 1 lux toma 120ms hacer una lectura
    - `CONTINUOUS_HIGH_RES_MODE_2` resolucion de 0.5 lux toma 120ms hacer una lectura
2. Modo de medición única - Realiza una sola medición de la intensidad de luz y después se apaga
    - `ONE_TIME_LOW_RES_MODE` resolucion de 4 lux toma 16ms hacer una lectura
    - `ONE_TIME_HIGH_RES_MODE` resolucion de 1 lux toma 120ms hacer una lectura
    - `ONE_TIME_HIGH_RES_MODE_2` resolucion de 0.5 lux toma 120ms hacer una lectura

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
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
         *  BH1750		ESP32
         *  VCC---------VIN
         *  GND---------GND
         *  SDA---------GPIO21
         *  SCL---------GPIO22
         */
        &emsp;
        #include &lt;Arduino.h&gt;
        #include &lt;Wire.h&gt;
        #include &lt;BH1750.h&gt;
        &emsp;
        BH1750 luxometro(0x23);             // Dirección I2C del sensor de luz
        unsigned int delayTime = 2000;      // Tiempo de espera entre lecturas
        unsigned long tiempoAnterior = 0;
        &emsp;
        void setup(){
            Serial.begin(9600);
            Wire.begin();
            luxometro.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
        }
        &emsp;
        void loop() {
            unsigned long tiempoActual = millis();
            if(tiempoActual - tiempoAnterior >= delayTime){
                tiempoAnterior = tiempoActual;
                uint16_t lux = luxometro.readLightLevel();
                Serial.println(&quot;Luz: &quot; + String(lux) + &quot; lx&quot;);
            }
        }
        </code-block>
    </tab>
    <tab title="platformio.ini">
        <code-block lang="Plain Text">
            [env:esp8266]
            platform = espressif8266
            board = esp12e
            framework = arduino
            lib_deps = claws/BH1750@^1.3.0
            &emsp;
            [env:esp32]
            platform = espressif32
            board = esp32dev
            framework = arduino
            lib_deps = claws/BH1750@^1.3.0
        </code-block>
    </tab>
</tabs>

> Se realizó un proyecto en PlatformIO para leer la intensidad de luz de un sensor BH1750, en la documentación se muestra el código y la conexión del sensor BH1750 a la placa de desarrollo.
> {style="note"}