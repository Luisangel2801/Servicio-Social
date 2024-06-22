---
switcher-label: Placa
---

# Sensor DHT

## Descripción

El sensor DHT es un sensor que permite medir la temperatura y humedad del ambiente en el que se encuentre. Este sensor es muy utilizado en proyectos de domótica y automatización de hogares.

## Características del sensor DHT
<tabs>
    <tab title="DHT11">
    <list>
        <li> Rango de medición de temperatura: 0 a 50 °C </li>
        <li> Precisión de medición de temperatura: ±2 °C </li>
        <li> Rango de medición de humedad: 20 a 80% </li>
        <li> Precisión de medición de humedad: ±5% </li>
        <li> Voltaje de operación: 3 a 5 V </li>
        <li> Muestra de datos: 1 vez por segundo </li>
    </list>
    </tab>
    <tab title="DHT22">
    <list>
        <li> Rango de medición de temperatura: -40 a 125 °C </li>
        <li> Precisión de medición de temperatura: ±0.5 °C </li>
        <li> Rango de medición de humedad: 0 a 100% </li>
        <li> Precisión de medición de humedad: ±2% </li>
        <li> Voltaje de operación: 3 a 5 V </li>
        <li> Muestra de datos: 2 veces por segundo </li>
    </list>
    </tab>
</tabs>


## Esquema de conexión para el ESP8266 {switcher-key="ESP8266"}

El sensor DHT se conecta a la placa de desarrollo ESP8266 a través de un pin digital. A continuación se muestra el esquema de conexión del sensor DHT a la placa de desarrollo ESP8266.

<tabs>
    <tab title="DHT11">
        <img src="dht11_ESP8266.png" alt="DHT11 ESP8266" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
    <tab title="DHT22">
        <img src="dht22_ESP8266.png" alt="DHT22 ESP8266" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
</tabs>


## Esquema de conexión para el  ESP32 {switcher-key="ESP32"}

El sensor DHT se conecta a la placa de desarrollo ESP32 a través de un pin digital. A continuación se muestra el esquema de conexión del sensor DHT a la placa de desarrollo ESP32.

<tabs>
    <tab title="DHT11">
        <img src="dht11_ESP32.png" alt="DHT11 ESP8266" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
    <tab title="DHT22">
        <img src="dht22_ESP32.png" alt="DHT22 ESP8266" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
</tabs>

## Código

El siguiente código permite leer la temperatura y humedad del sensor DHT y mostrar los valores en el monitor serial.

> En una carpeta se debe agregar un archivo llamado `platformio.ini` con la configuración de la tarjeta de desarrollo que se va a utilizar, además del archivo `main.cpp` con el código, este irá dentro de la carpeta `src`.
> {style="warning"}

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
        /*
         *  Humidity Sensor
         *  Autor: Luis Ángel Cruz Díaz
         *
         *  Este programa lee la humedad y temperatura de un sensor DHT22 o un DHT11
         *  y muestra los valores en el puerto serial.
         *
         *  El sensor DHT22 o el DHT 11 se conecta al pin 14 (D5) del ESP8266
         *  DHT22       ESP8266
         *  VCC---------VCC
         *  GND---------GND
         *  DATA--------GPIO 14 (D5)
         *
         *  El sensor DHT22 o el DHT 11 se conecta al pin 5 (D5) del ESP32
         *  DHT22        ESP32
         *  VCC----------VCC
         *  GND----------GND
         *  DATA---------GPIO 5 (D5)
         */
        &emsp;
        #include &lt;Arduino.h&gt;
        #include  &lt;Adafruit_Sensor.h&gt;
        #include  &lt;DHT.h&gt;
        #include  &lt;DHT_U.h&gt;
        &emsp;
        #ifdef ESP8266_BOARD
            int sensor = 14;
        #elif defined(ESP32_BOARD)
            int sensor = 5;
        #endif
        &emsp;
        float temperatura;
        float humedad;
        float tiempoAnterior = 0;
        &emsp;
        // Si queremos usar el DHT11 en lugar del DHT22, cambiamos el tipo de sensor a DHT22
        DHT dht(sensor, DHT22);
        &emsp;
        void setup() {
            Serial.begin(9600);
            dht.begin();
        }
        &emsp;
        void loop() {
            float tiempo = millis();
            if (tiempo - tiempoAnterior > 2000) {   // Lee la temperatura y humedad cada 2 segundos
                tiempoAnterior = tiempo;
                temperatura = dht.readTemperature();
                humedad = dht.readHumidity();
                Serial.println(&quot;Temperatura: &quot; + String(temperatura) + &quot; Humedad: &quot; + String(humedad) + &quot;%&quot;);
            }
        }
        </code-block>
    </tab>
    <tab title="platformio.ini">
        <code-block lang="Plain Text">
            [env:esp32]
            platform = espressif32
            board = esp32dev
            framework = arduino
            build_flags = -D ESP32_BOARD
            lib_deps = adafruit/DHT sensor library@^1.4.6
            &emsp;
            [env:esp8266]
            platform = espressif8266
            board = esp12e
            framework = arduino
            build_flags = -D ESP8266_BOARD
            lib_deps = adafruit/DHT sensor library@^1.4.6
        </code-block>
    </tab>
</tabs>

> Se realizó un proyecto en PlatformIO para leer la temperatura y humedad de un sensor DHT11 y DHT22, en la documentación se muestra el código y la conexión del sensor DHT a la placa de desarrollo.
> {style="note"}