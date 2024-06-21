---
switcher-label: Placa
---
# Blink

Documentación para realizar el parpadeo de un LED integrado en la placa ESP8266 y ESP32.

## Conexión para el ESP8266 {switcher-key="ESP8266"}

![esp8266](ESP8266.png) {border-effect="rounded" width="500" thumbnail="true"}

## Conexión para el  ESP32 {switcher-key="ESP32"}

![esp32](ESP32.png) {border-effect="rounded" width="500" thumbnail="true"}

## Código

El siguiente código funciona para ambas tarjetas de desarrollo, se define el pin del led integrado y se realiza el parpadeo del mismo. 

> En una carpeta se debe agregar un archivo llamado `platformio.ini` con la configuración de la tarjeta de desarrollo que se va a utilizar, además del archivo `main.cpp` con el código, este irá dentro de la carpeta `src`.
> {style="warning"}


<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
        /*  Blink ESP8266
         *  Autor: Luis Angel Cruz Diaz
         *
         *  Este programa realiza el parpadeo de un LED integrado en la placa ESP8266 y ESP32.
         *  para prueba de funcionamiento del IDE PlatformIO
         *
         *  ESP8266
         *  Led integrado rojo = Pin 16 (GPIO 2)
         *  Led integrado azul = Pin 2 (GPIO 16)
         *
         *  ESP32
         *  Led integrado = Pin 2 (D2)
         */
        &emsp;
        #include &lt;Arduino.h &gt;
        #ifdef ESP8266_BOARD
            int led = 16;
        #elif defined(ESP32_BOARD)
            int led = 2;
        #endif
        &emsp;
        void setup() {
            Serial.begin(9600);     // iniciar puerto serial
            pinMode(led, OUTPUT);   // inicializar GPIO 2 como salida
        }
        &emsp;
        void loop() {
            digitalWrite(led, HIGH);    // apaga el LED en el ESP8266 y enciende el LED en el ESP32
            Serial.println(&quot;LED OFF&quot;);
            delay(1000);               // espera 1000 milisegundos = un segundo
            digitalWrite(led, LOW);     // enciende el LED en el ESP8266 y apaga el LED en el ESP32
            Serial.println(&quot;LED ON&quot;);
            delay(1000);               // espera 1000 miliasegundos = un segundo
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
            &emsp;
            [env:esp8266]
            platform = espressif8266
            board = esp12e
            framework = arduino
            build_flags = -D ESP8266_BOARD
        </code-block>
    </tab>
</tabs>

> Se realizó un proyecto en PlatformIO para encender y apagar un LED integrado en la placa ESP8266 y ESP32, en la documentación se muestra el código y la conexión de los pines de la placa.
> {style="note"}

