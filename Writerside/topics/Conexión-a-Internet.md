---
switcher-label: Placa
---
# Conexión a Internet

## Descripción ESP8266 {switcher-key="ESP8266"}

El módulo ESP8266 es un módulo de bajo costo que permite la conexión a Internet a través de Wi-Fi. Este módulo es muy utilizado en proyectos de IoT, ya que permite la comunicación con otros dispositivos a través de Internet.

### Código para la placa ESP8266

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
            #include &lt;Arduino.h&gt;
            #include &lt;ESP8266WiFi.h&gt;
            &emsp;
            // Variables de configuración de red
            const char* ssid = &quot;Nombre SSDI&quot;;
            const char* password = &quot;Password&quot;;
            &emsp;
            // Variables para el manejo de errores
            byte cont = 0;
            byte max_intentos = 50;
            int statusLedPin = 2;	// Led azul del ESP8266
            int errorLedPin = 16; // Led rojo del ESP8266
            &emsp;
            void setup_wifi() {
                delay(10);
                // Mensajes de intento de conexión
                Serial.println();
                Serial.print(&quot;Conectando a: &quot;);
                Serial.print(ssid);
                Serial.print(&quot; &quot;);
                &emsp;
                // Funciones de conexión
                WiFi.begin(ssid, password); // Proporcionar características de red
                &emsp;
                // Secuencia que hace parpadear los leds durante el intento de conexión.
                while (WiFi.status() != WL_CONNECTED and cont &lt; max_intentos) {
                    cont++;
                    digitalWrite(statusLedPin, HIGH);
                    delay(500);
                    digitalWrite(statusLedPin, LOW);
                    Serial.print(&quot;.&quot;);  // Indicador de progreso
                    delay(5); // Espera asimétrica para dar la sensación de parpadeo al led
                }
                &emsp;
                // Esta función mejora los resultados de las funciones aleatorias y toma como semilla el contador de tiempo
                randomSeed(micros());
                &emsp;
                // Mensajes de confirmación
                if(cont &lt; max_intentos) {
                    Serial.println(&quot;\n*************************&quot;);
                    Serial.print(&quot;Conectado a la red WiFi: &quot;);
                    Serial.println(WiFi.SSID());
                    Serial.print(&quot;IP: &quot;);
                    Serial.println(WiFi.localIP());
                    Serial.print(&quot;macAddress: &quot;);
                    Serial.println(WiFi.macAddress());
                    Serial.println(&quot;*************************&quot;);
                } else {
                    Serial.println(&quot;-------------------------------&quot;);
                    Serial.println(&quot;Error de conexion&quot;);
                    digitalWrite(statusLedPin, HIGH);
                    digitalWrite(errorLedPin, LOW);
                    Serial.println(&quot;-------------------------------&quot;);
                }
            }
            &emsp;
            void setup() {
                Serial.begin(9600);
                pinMode(statusLedPin, OUTPUT);
                pinMode(errorLedPin, OUTPUT);
                digitalWrite(statusLedPin, HIGH);
                digitalWrite(errorLedPin, HIGH);
                setup_wifi();
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
        </code-block>
    </tab>
</tabs>

## Descripción ESP32 {switcher-key="ESP32"}

El módulo ESP32 es una placa de bajo costo que permite la conexión a Internet a través de Wi-Fi. Este módulo es muy utilizado en proyectos de IoT, ya que permite la comunicación con otros dispositivos a través de Internet. Una de las ventajas del ESP32 es que tiene muchos más GPIO que el ESP8266, además de tener bluetooth.

### Código para la placa ESP32

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
            #include &lt;Arduino.h&gt;
            #include &lt;WiFi.h&gt;
            &emsp;
            // Variables de configuración de red
            const char* ssid = &quot;Nombre SSDI&quot;;
            const char* password = &quot;Password&quot;;
            &emsp;
            // Variables para el manejo de errores
            byte cont = 0;
            byte max_intentos = 50;
            int statusLedPin = 2;
            int errorLedPin = 21;
            &emsp;
            void setup_wifi() {
                delay(10);
                // Mensajes de intento de conexión
                Serial.println();
                Serial.print(&quot;Conectando a: &quot;);
                Serial.print(ssid);
                Serial.print(&quot; &quot;);
                &emsp;
                // Funciones de conexión
                WiFi.begin(ssid, password);
                &emsp;
                // Secuencia que hace parpadear los leds durante el intento de conexión.
                while (WiFi.status() != WL_CONNECTED and cont &lt; max_intentos) {
                    cont++;
                    digitalWrite(statusLedPin, HIGH);
                    delay(500);
                    digitalWrite(statusLedPin, LOW);
                    Serial.print(&quot;.&quot;);  // Indicador de progreso
                    delay(100); // Espera asimétrica para dar la sensación de parpadeo al led
                }
                &emsp;
                // Esta función mejora los resultados de las funciones aleatorias y toma como semilla el contador de tiempo
                randomSeed(micros());
                &emsp;
                // Mensajes de confirmación
                if (cont &lt; max_intentos) {
                    Serial.println(&quot;\n*************************&quot;);
                    digitalWrite(statusLedPin, HIGH);
                    digitalWrite(errorLedPin, LOW);
                    Serial.print(&quot;Conectado a la red WiFi: &quot;);
                    Serial.println(WiFi.SSID());
                    Serial.print(&quot;IP: &quot;);
                    Serial.println(WiFi.localIP());
                    Serial.print(&quot;macAddress: &quot;);
                    Serial.println(WiFi.macAddress());
                    Serial.println(&quot;*************************&quot;);
                } else {
                    Serial.println(&quot;-------------------------------&quot;);
                    Serial.println(&quot;Error de conexion&quot;);
                    digitalWrite(statusLedPin, LOW);
                    digitalWrite(errorLedPin, HIGH);
                    Serial.println(&quot;-------------------------------&quot;);
                }
            }
            &emsp;
            void setup() {
                Serial.begin(115200);
                pinMode(statusLedPin, OUTPUT);
                pinMode(errorLedPin, OUTPUT);
                setup_wifi();
            }
            &emsp;
            void loop() {
            }
        </code-block>
    </tab>
    <tab title="platformio.ini">
        <code-block lang="Plain Text">
            [env:esp32]
            platform = espressif32
            board = esp32dev
            monitor_speed = 115200
            framework = arduino
        </code-block>
    </tab>
</tabs>

> Se realizó un proyecto en PlatformIO para conectar a Internet una placa ESP8266 y ESP32, en la documentación se muestra el código para cada placa y la configuración de PlatformIO. 
> {style="note"}