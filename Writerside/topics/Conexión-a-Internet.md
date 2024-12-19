---
switcher-label: Placa
---
# Enviar Mensaje por MQTT

## Descripción

En el ecosistema del Internet de las Cosas (IoT), el protocolo MQTT se utiliza ampliamente por su ligereza y eficiencia, especialmente en dispositivos con recursos limitados como el ESP8266 y el ESP32. Estos microcontroladores con wifi integrado permiten la conexión a Internet y, a su vez, la comunicación con un broker MQTT como EMQX. Con ello se pueden enviar datos de sensores, estados o configuraciones en formato JSON para su posterior procesamiento en la nube, dashboards u otros servicios IoT.

## Requisitos

- **Hardware**
    - Placa ESP8266 o ESP32
- **Software**:
    - PlatformIO instalado en Visual Studio Code, o Arduino IDE con las bibliotecas requeridas.
- **Información de Red**:
    - SSID (nombre de la red Wi-Fi).
    - Contraseña de la red.

## Conexión a Internet (Wi-Fi)

Antes de enviar mensajes MQTT, el dispositivo debe conectarse a Internet. A continuación, se presenta el código base para la conexión wifi en ambas plataformas. En el ejemplo se emplean macros (ESP8266_BOARD, ESP32_BOARD) para compilar el código según la placa a utilizar.

### Código para la Conexión a Internet

Este ejemplo muestra el código base para la conexión a Internet en un ESP8266 y ESP32. Se emplean las bibliotecas `WiFi.h` y `ESP8266WiFi` para la conexión wifi. Además, se utilizan los pines `statusLedPin` y `errorLedPin` para indicar el estado de la conexión.

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
            #include &lt;Arduino.h&gt;
            &emsp;
            #ifdef ESP8266_BOARD
                #include &lt;ESP8266WiFi.h&gt;
                int errorLedPin = 16;
                bool ledEncendido = false;
                bool ledApagado = true;
            #elif defined(ESP32_BOARD)
                #include &lt;WiFi.h&gt;
                int errorLedPin = 21;
                bool ledEncendido = true;
                bool ledApagado = false;
            #endif
            &emsp;
            // Variables de configuración de red
            const char *ssid = &quot;SSID&quot;;          // Nombre de la red
            const char *password = &quot;PASSWORD&quot;;  // Contraseña de la red
            &emsp;
            // Variables para el manejo de errores
            byte cont = 0;
            byte max_intentos = 50;
            int statusLedPin = 2;
            bool ledState = false;
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
                    ledState = !ledState;
                    digitalWrite(statusLedPin, ledState);
                    delay(500);
                    ledState = !ledState;
                    digitalWrite(statusLedPin, ledState);
                    Serial.print(&quot;.&quot;);  // Indicador de progreso
                    delay (100); // Espera para dar la sensación de parpadeo al led
                }
                &emsp;
                randomSeed(micros());
                &emsp;
                // Mensajes de confirmación
                if(cont &lt; max_intentos) {
                    Serial.println(&quot;\n*************************&quot;);
                    digitalWrite(statusLedPin, ledEncendido);
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
                    digitalWrite (statusLedPin, ledApagado);
                    digitalWrite (errorLedPin, ledEncendido);
                    Serial.println(&quot;-------------------------------&quot;);
                }
            }
            &emsp;
            void setup() {
                Serial.begin(115200);
                pinMode(statusLedPin, OUTPUT);
                pinMode(errorLedPin, OUTPUT);
                digitalWrite(statusLedPin, ledApagado);
                digitalWrite(errorLedPin, ledApagado);
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
            framework = arduino
            monitor_speed = 115200
            build_flags = -D ESP32_BOARD
            &emsp;
            [env:esp8266]
            platform = espressif8266
            board = esp12e
            framework = arduino
            monitor_speed = 115200
            build_flags = -D ESP8266_BOARD
        </code-block>
    </tab>
</tabs>

## Enviar Mensajes JSON por MQTT (ESP8266) {switcher-key="ESP8266"}

Para enviar mensajes por MQTT en un ESP8266, es necesario de un broker MQTT. En este caso, se utiliza el broker público de EMQX. En ese ejemplo se tomó los datos del [broker público que ofrece EMQX](https://www.emqx.com/en/mqtt/public-mqtt5-broker) para configurar el cliente MQTT. Los datos requeridos para realizar la conexión son:

- **Broker MQTT**: broker.emqx.io
- **Puerto MQTT**: 8883
- **Tema MQTT**: tema a suscribir
- **Usuario MQTT**: nombre del dispositivo
- **Contraseña MQTT**: public
- **Certificado**: [Certificate Authority](https://assets.emqx.com/data/broker.emqx.io-ca.crt "Descargar certificado")

> **Nota**: Cuando se utiliza el broker público la contraseña por defecto es `public`. Podemos utilizar un broker privado visto en la [guía de instalación de EMQX](Instalar-MQTTX.md), para ello se debe cambiar el certificado de la CA y las credenciales de acceso en el código.
> {style="note"}

![mqtt_broker](mqtt_broker.png) {border-effect="rounded" width="400" thumbnail="true"}

### Código para enviar un mensaje por MQTT en ESP8266

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
            #include &lt;Arduino.h&gt;
            #include &lt;ESP8266WiFi.h&gt;
            #include &lt;PubSubClient.h&gt;
            #include &lt;time.h&gt;
            #include &lt;Ticker.h&gt;
            &emsp;
            Ticker timer;   // Objeto para manejar el tiempo no bloqueante
            &emsp;
            // Variables de configuración de red
            const char* ssid = &quot;SSID&quot;;        // Nombre de la red WiFi
            const char* password = &quot;PASSWORD&quot;;// Contraseña de la red WiFi
            const char* device_name = &quot;nombre_dispositivo&quot;; // Nombre del dispositivo
            &emsp;
            // Variables para el manejo de errores
            byte cont = 0;
            byte max_intentos = 50;
            int statusLedPin = 2;   // Led azul del ESP8266
            int errorLedPin = 16;   // Led rojo del ESP8266
            &emsp;
            // Variable para el manejo de tiempo
            unsigned int msgTime = 10000;       // Tiempo de espera entre mensajes
            &emsp;
            // Configuración del broker MQTT
            const int mqtt_port = 8883;                 // Puerto del broker MQTT
            const char *mqtt_broker = &quot;broker.emqx.io&quot;; // Broker MQTT
            const char *mqtt_topic = &quot;temperatura/cuarto&quot;;// Tema MQTT
            const char *mqtt_username = device_name;    // MQTT usuario
            const char *mqtt_password = &quot;public&quot;;
            &emsp;
            // NTP Server settings
            const char *ntp_server = &quot;pool.ntp.org&quot;;    // Server NTP
            // -6 horas * 3600 segundos para obtener el offset para México
            const long gmt_offset_sec = -21600;
            // En mexico no se usa horario de verano
            const int daylight_offset_sec = 0;
            &emsp;
            BearSSL::WiFiClientSecure espClient;
            PubSubClient mqtt_client(espClient);
            &emsp;
            // Certificado de la CA
            static const char ca_cert[]
            PROGMEM = R&quot;EOF(
            -----BEGIN CERTIFICATE-----
            MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
            MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
            d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
            QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
            MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
            b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
            9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
            CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
            nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
            43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
            T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
            gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
            BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
            TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
            DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
            hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
            06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
            PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
            YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
            CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
            -----END CERTIFICATE-----
            )EOF&quot;;
            &emsp;
            void setup_wifi() {
                delay(10);
                // Mensajes de intento de conexión
                Serial.println();
                Serial.print(&quot;Conectando a: &quot;);
                Serial.print(ssid);
                Serial.print(&quot; &quot;);
                &emsp;
                // Conexión a la red WiFi
                WiFi.begin(ssid, password);
                &emsp;
                // Secuencia que hace parpadear los leds durante el intento de conexión.
                while (WiFi.status() != WL_CONNECTED and cont &lt; max_intentos) {
                    cont++;
                    digitalWrite (statusLedPin, HIGH);
                    delay(500);
                    digitalWrite (statusLedPin, LOW);
                    Serial.print(&quot;.&quot;);  // Indicador de progreso
                    delay (5); // Espera asimetrica para dar la sensación de parpadeo al led
                }
                &emsp;
                randomSeed(micros());
                &emsp;
                // Mensajes de confirmación
                if(cont &lt; max_intentos){
                    Serial.println(&quot;\n*************************&quot;);
                    Serial.print(&quot;Conectado a la red WiFi: &quot;);
                    Serial.println(WiFi.SSID());
                    Serial.print(&quot;IP: &quot;);
                    Serial.println(WiFi.localIP());
                    Serial.println(&quot;*************************&quot;);
                }else{
                    Serial.println(&quot;-------------------------------&quot;);
                    Serial.println(&quot;Error de conexión&quot;);
                    digitalWrite (statusLedPin, HIGH);
                    digitalWrite (errorLedPin, LOW);
                    Serial.println(&quot;-------------------------------&quot;);
                }
            }
            &emsp;
            void syncTime() {
                configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
                Serial.print(&quot;\nSincronizando la hora &quot;);
                while (time(nullptr) &lt; 1510644967) {
                    delay(1000);
                    Serial.print(&quot;.&quot;);
                }
                Serial.println(&quot;\n*************************&quot;);
                Serial.println(&quot;Hora sincronizada&quot;);
                struct tm timeinfo;
                if(getLocalTime(&timeinfo)){
                    Serial.print(&quot;Horario Actual: &quot;);
                    Serial.print(asctime(&timeinfo));
                    Serial.println(&quot;*************************&quot;);
                }else{
                    Serial.println(&quot;Error al sincronizar la hora&quot;);
                    Serial.println(&quot;*************************&quot;);
                }
            }
            &emsp;
            void connectToMQTT() {
                BearSSL::X509List serverTrustedCA(ca_cert);
                espClient.setTrustAnchors(&serverTrustedCA);
                while(!mqtt_client.connected()){
                    // Crea un ID de cliente único
                    String clientId = String(device_name);
                    clientId += &quot;_&quot; + String(random(0xffff), HEX);
                    Serial.println(&quot;Conectando al broker MQTT como &quot; + String(clientId.c_str()));
                    if(mqtt_client.connect(clientId.c_str(), mqtt_username, mqtt_password)){
                        Serial.println(&quot;Broker MQTT conectado&quot;);
                        mqtt_client.subscribe(mqtt_topic);          // Se suscribe al topic
                    }else{
                        char err_buff[128];
                        espClient.getLastSSLError(err_buff, sizeof(err_buff));
                        Serial.println(&quot;Error al conectar al broker MQTT:: Estado:&quot;);
                        Serial.println(mqtt_client.state());
                        Serial.print(err_buff);
                        delay(5000);
                    }
                }
            }
            &emsp;
            // Función que se ejecuta cada cierto tiempo
            void enviarJSON(){
                String json = &quot;{\&quot;id\&quot;:\&quot;&quot;+ String(device_name) + &quot;\&quot;,\&quot;temp\&quot;:&quot;+ String(25.4) + &quot;,\&quot;hum\&quot;:&quot;+String(60)+&quot;}&quot;;
                // Serial.println(json); ¡
                int str_len = json.length() + 1;    // Calcula la longitud del string
                char char_array[str_len];
                json.toCharArray(char_array, str_len);// Convierte el string a un array de char
                mqtt_client.publish(mqtt_topic, char_array);// Publica el mensaje en el topic
            }
            &emsp;
            void setup() {
                Serial.begin(115200);
                pinMode(statusLedPin, OUTPUT);
                pinMode(errorLedPin, OUTPUT);
                digitalWrite (statusLedPin, HIGH);
                digitalWrite (errorLedPin, HIGH);
                setup_wifi();                                   // Conexión a la red WiFi
                syncTime();                                     // Sincronización de la hora
                mqtt_client.setServer(mqtt_broker, mqtt_port);  // Configuración del broker MQTT
                connectToMQTT();                                // Conexión al broker MQTT
                timer.attach_ms(msgTime, enviarJSON);           // Configura la interrupción
            }
            &emsp;
            void loop() {
                if(!mqtt_client.connected()){
                    connectToMQTT();
                }else{
                    mqtt_client.loop();
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
            monitor_speed = 115200
            lib_deps = knolleary/PubSubClient@^2.8
        </code-block>
    </tab>
</tabs>

> **Resultado** Se realizó la conexión a Internet y el envío de mensajes por MQTT en un ESP8266. Se empleó el broker público de EMQX para la conexión MQTT. El código base se adaptó para enviar mensajes JSON con la temperatura y humedad simuladas. El mensaje se publicó en el tema `temperatura/cuarto`, el cual es un dato configurable en el código.

## Enviar Mensajes JSON por MQTT (ESP32) {switcher-key="ESP32"}

Para enviar mensajes por MQTT en un ESP32, es necesario de un broker MQTT. En este caso, se utiliza el broker público de EMQX. En ese ejemplo se tomó los datos del [broker público que ofrece EMQX](https://www.emqx.com/en/mqtt/public-mqtt5-broker) para configurar el cliente MQTT. Los datos requeridos para realizar la conexión son:

- **Broker MQTT**: broker.emqx.io
- **Puerto MQTT**: 8883
- **Tema MQTT**: tema a suscribir
- **Usuario MQTT**: nombre del dispositivo
- **Contraseña MQTT**: public
- **Certificado**: [Certificate Authority](https://assets.emqx.com/data/broker.emqx.io-ca.crt "Descargar certificado")

> **Nota**: Cuando se utiliza el broker público la contraseña por defecto es `public`. Podemos utilizar un broker privado visto en la [guía de instalación de EMQX](Instalar-MQTTX.md), para ello se debe cambiar el certificado de la CA y las credenciales de acceso en el código.
> {style="note"}

![mqtt_broker](mqtt_broker.png) {border-effect="rounded" width="400" thumbnail="true"}

### Código para enviar un mensaje por MQTT en ESP32

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
            #include &lt;Arduino.h&gt;
            #include &lt;WiFi.h&gt;
            #include &lt;PubSubClient.h&gt;
            #include &lt;WiFiClientSecure.h&gt;
            #include &lt;Ticker.h&gt;
            &emsp;
            Ticker timer;   // Objeto para manejar el tiempo no bloqueante
            &emsp;
            // Variables de configuración de red
            const char *ssid = &quot;SSID&quot;;                      // Remplazar con el nombre de tu red WiFi
            const char *password = &quot;Password&quot;;              // Remplazar con la contraseña de tu red WiFi
            const char* device_name = &quot;nombre_dispositivo&quot;; // Nombre del dispositivo
            &emsp;
            // Variables para el manejo de errores
            byte cont = 0;
            byte max_intentos = 50;
            int statusLedPin = 2;   // Led interno del ESP32
            int errorLedPin = 21;   // Led conectado al puerto D21
            &emsp;
            unsigned int msgTime = 5000;    // Tiempo de espera entre mensajes
            &emsp;
            // Variables de configuración de MQTT
            const char *mqtt_broker = &quot;broker.emqx.io&quot;;     // Remplazar con la dirección de tu broker MQTT
            const char *mqtt_topic = &quot;temperatura/cuarto&quot;;  // Remplazar con el topic de tu broker MQTT
            const char *mqtt_username = device_name;
            const char *mqtt_password = &quot;public&quot;;
            const int mqtt_port = 8883;
            &emsp;
            WiFiClientSecure esp_client;
            PubSubClient mqtt_client(esp_client);
            &emsp;
            const char *ca_cert = R&quot;EOF(
            -----BEGIN CERTIFICATE-----
            MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
            MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
            d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
            QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
            MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
            b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
            9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
            CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
            nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
            43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
            T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
            gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
            BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
            TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
            DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
            hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
            06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
            PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
            YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
            CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
            -----END CERTIFICATE-----
            )EOF&quot;;
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
                    Serial.println(&quot;Error de conexión&quot;);
                    digitalWrite(statusLedPin, LOW);
                    digitalWrite(errorLedPin, HIGH);
                    Serial.println(&quot;-------------------------------&quot;);
                }
            }
            &emsp;
            void connectToMQTT() {
                while (!mqtt_client.connected()) {
                    String clientId = String(device_name);
                    clientId += &quot;_&quot; + String(random(0xffff), HEX);
                    Serial.println(&quot;Conectando al broker MQTT como &quot; + String(clientId.c_str()));
                    if (mqtt_client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
                        Serial.println(&quot;Broker MQTT conectado&quot;);
                        mqtt_client.subscribe(mqtt_topic);
                    } else {
                        Serial.print(&quot;Error al conectar al broker MQTT:: Estado:&quot;);
                        Serial.print(mqtt_client.state());
                        Serial.println(&quot;Intentando de nuevo en 5 segundos&quot;);
                        delay(5000);
                    }
                }
            }
            &emsp;
            void enviarJSON(){
                String json = &quot;{\&quot;id\&quot;:\&quot;&quot;+ String(device_name) + &quot;\&quot;,\&quot;temp\&quot;:&quot;+ String(25.4) + &quot;,\&quot;hum\&quot;:&quot;+String(60)+&quot;}&quot;;
                // Serial.println(json); ¡
                int str_len = json.length() + 1;            // Calcula la longitud del string
                char char_array[str_len];
                json.toCharArray(char_array, str_len);      // Convierte el string a un array de char
                mqtt_client.publish(mqtt_topic, char_array);// Publica el mensaje en el topic
            }
            &emsp;
            void setup() {
                Serial.begin(115200);
                pinMode(statusLedPin, OUTPUT);
                pinMode(errorLedPin, OUTPUT);
                setup_wifi();                                   // Conecta a la red WiFi
                esp_client.setCACert(ca_cert);                  // Configura el certificado de seguridad
                mqtt_client.setServer(mqtt_broker, mqtt_port);  // Configura el broker MQTT
                mqtt_client.setKeepAlive(60);                   // Configura el tiempo de espera
                connectToMQTT();                                // Conecta al broker MQTT
                timer.attach_ms(msgTime, enviarJSON);           // Configura el tiempo de las interrupciones
            }
            &emsp;
            void loop() {
                if(!mqtt_client.connected()){
                    connectToMQTT();
                }else{
                    mqtt_client.loop();
                }
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
            lib_deps = knolleary/PubSubClient@^2.8
        </code-block>
    </tab>
</tabs>

> **Resultado** Se realizó la conexión a Internet y el envío de mensajes por MQTT en un ESP32. Se empleó el broker público de EMQX para la conexión MQTT. El código base se adaptó para enviar mensajes JSON con la temperatura y humedad simuladas. El mensaje se publicó en el tema `temperatura/cuarto`, el cual es un dato configurable en el código.