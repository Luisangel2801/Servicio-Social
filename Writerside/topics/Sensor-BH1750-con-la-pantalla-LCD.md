---
switcher-label: Placa
---

# Sensor BH1750 con la pantalla LCD

## Descripción

El sensor BH1750 es un sensor de iluminación digital que permite medir la intensidad de la luz en el ambiente. Este sensor es muy utilizado en proyectos de domótica y automatización de hogares. El sensor BH1750 se conecta a la placa de desarrollo a través de los pines SDA y SCL y se puede utilizar con la pantalla LCD para mostrar la intensidad de la luz en tiempo real. A continuación se muestra el esquema de conexión del sensor BH1750 a la placa de desarrollo y la pantalla LCD.

## Esquema de conexión para el ESP8266 {switcher-key="ESP8266"}

Esquema de conexión del sensor BH1750 y la pantalla LCD a la placa ESP8266.

![BH1750_LCD_ESP8266](BH1750_LCD_ESP8266.png) {border-effect="rounded" width="500" thumbnail="true"}

## Esquema de conexión para el  ESP32 {switcher-key="ESP32"}

Esquema de conexión del sensor BH1750 y la pantalla LCD a la placa ESP32.

![BH1750_LCD_ESP32](BH1750_LCD_ESP32.png) {border-effect="rounded" width="500" thumbnail="true"}

## Código

El siguiente código muestra la lectura de la intensidad de la luz del sensor BH1750 y la muestra en la pantalla LCD.

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
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
             *	BH1750      ESP32           LCD     Power Supply
             *	VCC---------------------------------3.3V
             *	GND---------GND-------------GND-----GND
             *	SDA---------GPIO21 (D21)----SDA
             *	SCL---------GPIO22 (D22)----SCL
             *              VIN-------------VCC-----5V
             */
            #include &lt;Arduino.h&gt;
            #include &lt;Wire.h&gt;
            #include &lt;BH1750.h&gt;
            #include &lt;LiquidCrystal_I2C.h&gt;
            &emsp;
            // La dirección I2C de la pantalla LCD es 0x27
            LiquidCrystal_I2C lcd(0x27,16,2);
            &emsp;
            // La dirección I2C del sensor de iluminación es 0x23
            BH1750 luxometro(0x23);
            &emsp;
            int tiempoAnterior = 0;
            int pausa = 2000;
            &emsp;
            void setup(){
                Wire.begin();
                luxometro.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
                lcd.init();
                lcd.backlight();
            }
            &emsp;
            void loop(){
                int tiempoActual = millis();
                if (tiempoActual - tiempoAnterior >= pausa) {
                    tiempoAnterior = tiempoActual;
                    uint16_t lux = luxometro.readLightLevel();
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print(&quot;Luz: &quot; + String(lux) + &quot; lx&quot;);
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
            lib_deps = 
                marcoschwartz/LiquidCrystal_I2C@^1.1.4
                claws/BH1750@^1.3.0
            &emsp;
            [env:esp32]
            platform = espressif32
            board = esp32dev
            framework = arduino
            lib_deps =
                marcoschwartz/LiquidCrystal_I2C@^1.1.4
                claws/BH1750@^1.3.0
        </code-block>
    </tab>
</tabs>

> Se realizó una adaptación del código del sensor BH1750 para mostrar la intensidad de la luz en una pantalla LCD. Se utilizó la librería LiquidCrystal_I2C para controlar la pantalla LCD y la librería BH1750 para controlar el sensor de iluminación.
> En la documentación se muestra el código y la conexión del sensor BH1750 y la pantalla LCD a la placa de desarrollo.
> {style="note"}