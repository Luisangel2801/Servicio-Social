---
switcher-label: Placa
---

# Pantalla LCD

## Descripción

La pantalla LCD (Liquid Crystal Display) 16x2 es un dispositivo capaz de mostrar información en forma de texto, muy utilizado en proyectos IoT. Gracias a su interfaz I2C, la conexión con microcontroladores como el ESP8266 y el ESP32 se simplifica, reduciendo el número de pines necesarios para la comunicación.

### ¿Qué es I2C?

I2C (Inter-Integrated Circuit) es un protocolo de comunicación serial síncrono que utiliza únicamente dos líneas: SDA (datos) y SCL (reloj). Este protocolo permite conectar múltiples dispositivos en un mismo bus, identificándolos mediante direcciones únicas. Su simplicidad y bajo consumo de pines lo hace ideal para pantallas LCD, sensores y otros periféricos.

![I2C](i2c.jpeg) {width="700"}

## Características de la pantalla LCD

* **Tamaño de pantalla:** 16x2 caracteres
* **Voltaje de operación:** 5 V
* **Interfaz de comunicación:** I2C
* **Dirección I2C:** 0x27
* **Retroiluminación:** LED azul


## Esquema de conexión para el ESP8266 {switcher-key="ESP8266"}

Para la conexión de la pantalla LCD a la placa de desarrollo ESP8266 se utiliza la interfaz I2C. A continuación se muestra el esquema de conexión de la pantalla LCD a la placa de desarrollo ESP8266.

- VCC → 5 V (Fuente de alimentación externa)
- GND → GND
- SDA → GPIO4 (D2)
- SCL → GPIO5 (D1)

![LCD ESP8266](LCD_ESP8266.png) {border-effect="rounded" width="500" thumbnail="true"}

> **Nota:** Conectar la pantalla LCD a la salida de 5 V de una fuente de alimentación externa es recomendable. La pantalla puede requerir más corriente de la que la placa de desarrollo puede suministrar directamente.

## Esquema de conexión para el ESP32 {switcher-key="ESP32"}

Para la conexión de la pantalla LCD a la placa de desarrollo ESP32 se utiliza la interfaz I2C. A continuación se muestra el esquema de conexión de la pantalla LCD a la placa de desarrollo ESP32.

- VCC → 5 V (Fuente de alimentación externa)
- GND → GND
- SDA → GPIO21 (D21)
- SCL → GPIO22 (D22)

![LCD ESP32](LCD_ESP32.png) {border-effect="rounded" width="500" thumbnail="true"}

> **Nota:** Conectar la pantalla LCD a la salida de 5 V de una fuente de alimentación externa es recomendable. La pantalla puede requerir más corriente de la que la placa de desarrollo puede suministrar directamente.

## Código

En el siguiente código se muestra como inicializar la pantalla LCD y mostrar un mensaje en la pantalla.

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
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
        &emsp;
        #include &lt;Arduino.h&gt;
        #include &lt;Wire.h&gt;
        #include &lt;LiquidCrystal_I2C.h&gt;
        &emsp;
        LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección 0x27, pantalla con 16 columnas y 2 filas
        &emsp;
        void setup() {
            lcd.init();             // Inicializa la pantalla
            lcd.backlight();        // Enciende la luz de la pantalla
            lcd.setCursor(0, 0);    // Coloca el cursor en la columna 0, fila 0
            lcd.print(&quot;Hola Mundo&quot;);// Imprime el mensaje en la pantalla
            lcd.setCursor(0, 1);    // Coloca el cursor en la columna 0, fila 1
            lcd.print(&quot;LCD I2C&quot;);   // Imprime el mensaje en la pantalla
        }
        &emsp;
        void loop() {
        }
        </code-block>
    </tab>
    <tab title="platformio.ini">
        <code-block lang="Plain Text">
            [env:esp8266]
            platform = espressif8266
            board = esp12e
            framework = arduino
            lib_deps = marcoschwartz/LiquidCrystal_I2C@^1.1.4
            &emsp;
            [env:esp32]
            platform = espressif32
            board = esp32dev
            framework = arduino
            lib_deps = marcoschwartz/LiquidCrystal_I2C@^1.1.4
        </code-block>
    </tab>
</tabs>

> **Resultado:** Se realizó la conexión de la pantalla LCD a la placa de desarrollo ESP8266 y ESP32 mediante la interfaz I2C. Se programó un mensaje en la pantalla LCD que muestra el texto "Hola Mundo" en la primera fila y "LCD I2C" en la segunda fila.