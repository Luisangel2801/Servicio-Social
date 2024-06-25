---
switcher-label: Placa
---
# Sensor DHT con la pantalla LCD

## Descripción

El sensor DHT es un sensor que permite medir la temperatura y humedad del ambiente en el que se encuentre. Este sensor es muy utilizado en proyectos de domótica y automatización de hogares.
El sensor DHT se conecta a la placa de desarrollo a través de un pin digital y se puede utilizar con la pantalla LCD para mostrar la temperatura y humedad en tiempo real. A continuación se muestra el esquema de conexión del sensor DHT a la placa de desarrollo y la pantalla LCD.

## Esquema de conexión para el ESP8266 {switcher-key="ESP8266"}

Esquema de conexión del sensor DHT y la pantalla LCD a la placa ESP8266.

<tabs>
    <tab title="DHT11">
        <img src="dht11_LCD_ESP8266.png" alt="dht11_LCD_ESP8266" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
    <tab title="DHT22">
        <img src="dht22_LCD_ESP8266.png" alt="dht22_LCD_ESP8266" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
</tabs>

## Esquema de conexión para el  ESP32 {switcher-key="ESP32"}

Esquema de conexión del sensor DHT y la pantalla LCD a la placa ESP32.

<tabs>
    <tab title="DHT11">
        <img src="dht11_LCD_ESP32.png" alt="dht11_LCD_ESP32" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
    <tab title="DHT22">
        <img src="dht22_LCD_ESP32.png" alt="dht22_LCD_ESP32" width="500" border-effect="rounded" thumbnail="true"/>
    </tab>
</tabs>

## Código

El siguiente código muestra la lectura de la temperatura y humedad del sensor DHT y la muestra en la pantalla LCD.

> En una carpeta se debe agregar un archivo llamado `platformio.ini` con la configuración de la tarjeta de desarrollo que se va a utilizar, además del archivo `main.cpp` con el código, este irá dentro de la carpeta `src`.
> {style="warning"}

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
        /*
         *	Humidity Sensor with LCD
         *	Autor: Luis Ángel Cruz Díaz
         *	Fecha:  16/11/2023
         *
         *	Este programa muestra la temperatura y humedad en la pantalla LCD
         *
         *	El programa utiliza la librería LiquidCrystal_I2C para controlar la pantalla LCD
         *	y la librería DHT para controlar el sensor de humedad y temperatura
         *  
         *	El sensor de humedad y temperatura DHT11 o el DHT22 se conecta con el ESP8266 de la siguiente manera:
         *
         *  DHT11   ESP8266         LCD     Power Supply
         *  DATA----GPIO14 (D5)
         *  VCC-----VIN-------------VCC-----5V
         *  GND-----GND-------------GND-----GND
         *          GPIO4 (D2)------SDA
         *          GPIO5 (D1)------SCL
         * 
         * El sensor de humedad y temperatura DHT11 o el DHT22 se conecta con el ESP32 de la siguiente manera:
         * 
         *  DHT11   ESP32           LCD     Power Supply
         *  DATA----GPIO 5 (D5)
         *  VCC-----VIN-------------VCC-----5V
         *  GND-----GND-------------GND-----GND
         *          GPIO21 (D21)----SDA
         *          GPIO22 (D22)----SCL
         */
        &emsp;
        #include &lt;Arduino.h&gt;
        #include &lt;LiquidCrystal_I2C.h&gt;
        #include &lt;Wire.h&gt;
        #include &lt;DHT.h&gt;
        #include &lt;DHT_U.h&gt;
        &emsp;
        // Pin del sensor según el modelo de placa
        #ifdef ESP8266_BOARD
            int sensor = 14;
        #elif defined(ESP32_BOARD)
            int sensor = 5;
        #endif
        &emsp;
        // Si queremos usar el DHT11 en lugar del DHT22, cambiamos el tipo de sensor a DHT11
        DHT dht(sensor,DHT22);
        LiquidCrystal_I2C lcd(0x27,16,2);
        &emsp;
        double tempF,tempC;
        int humedad;
        float tiempoAnterior = 0;
        int pausa = 2000;
        &emsp;
        void setup() {
            Serial.begin(9600);
            dht.begin();
            lcd.init();
            lcd.backlight();
        }
        &emsp;
        void loop() {
            // Si han pasado 2 segundos, leemos la temperatura y humedad
            int tiempoActual = millis();
            if (tiempoActual - tiempoAnterior >= pausa) {
                tiempoAnterior = tiempoActual;
                // Lectura de la temperatura y humedad
                tempC = dht.readTemperature();    // Temperatura en grados centígrados
                tempF = dht.readTemperature(true);// Temperatura en grados Fahrenheit
                humedad = dht.readHumidity();     // Humedad relativa
                // Mostramos la temperatura y humedad en el LCD
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Temp: " + String(tempC) + " "+ (char)223 +"C");
                lcd.setCursor(0,1);
                lcd.print("Humedad: " + String(humedad) + " %");
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
            lib_deps = 
                adafruit/DHT sensor library@^1.4.6
                marcoschwartz/LiquidCrystal_I2C@^1.1.4
            &emsp;
            [env:esp8266]
            platform = espressif8266
            board = esp12e
            framework = arduino
            build_flags = -D ESP8266_BOARD
            lib_deps = 
                adafruit/DHT sensor library@^1.4.6
                marcoschwartz/LiquidCrystal_I2C@^1.1.4
        </code-block>
    </tab>
</tabs>

> Se realizó una adaptación del código del sensor DHT para mostrar la temperatura y humedad en una pantalla LCD. Se utilizó la librería LiquidCrystal_I2C para controlar la pantalla LCD y la librería DHT para controlar el sensor de humedad y temperatura. 
> En la documentación se muestra el código y la conexión del sensor DHT a la placa de desarrollo.
> Se utilizó la placa ESP8266 y ESP32 para realizar el proyecto.
> {style="note"}