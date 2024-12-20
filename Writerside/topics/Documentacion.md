# Proyecto IoT

Este proyecto busca la monitorización de un cubículo en la universidad utilizando dispositivos IoT (Internet de las Cosas). Para ello, se emplean sensores conectados a un ESP8266 que envía datos a un broker MQTT, los cuales son posteriormente almacenados en InfluxDB y visualizados en Grafana. Además, se integra un flujo en Node-RED para enviar alertas por Telegram y gestionar información en una base de datos MySQL.

## Componentes Principales

- **ESP8266**
- **Sensores:**
    - Temperatura y humedad (DHT22)
    - Luz (BH1750)
    - Calidad del aire (MQ135)
- **Pantalla LCD I2C**
- **Raspberry Pi** (Servidor con Docker)
- **Broker MQTT** (ej. EMQX)
- **Bases de datos:** InfluxDB (para datos de sensores) y MySQL (para información de usuarios)
- **Visualización y Control:** Node-RED, Grafana, Telegram

## Código para ESP8266

El ESP8266 se encarga de leer las mediciones de los sensores DHT22, BH1750 y MQ135, mostrar algunos datos en la pantalla LCD, y enviar periódicamente la información al broker MQTT.

<tabs>
    <tab title="main.cpp">
        <code-block lang="c++">
        #include &lt;Arduino.h&gt;
        #include &lt;ESP8266WiFi.h&gt;
        #include &lt;WiFiManager.h&gt;
        #include &lt;DNSServer.h&gt;
        #include &lt;ESP8266WebServer.h&gt;
        #include &lt;PubSubClient.h&gt;
        #include &lt;time.h&gt;
        #include &lt;Ticker.h&gt;
        #include &lt;Wire.h&gt;
        #include &lt;Adafruit_Sensor.h&gt;
        #include &lt;DHT.h&gt;
        #include &lt;BH1750.h&gt;
        #include &lt;LiquidCrystal_I2C.h&gt;
        &emsp;
        #define PIN_ANALOG A0
        const int statusLedPin = 2;	// Led azul del ESP8266
        const int errorLedPin = 16;   // Led rojo del ESP8266
        const int sensorDHTPin = 14;  // Pin del sensor DHT
        const int analog_PIN = A0;          // Pin analógico del ESP8266
        const int adc_resolution = 1024 - 1;// La resolución del ADC es de 10 bits
        &emsp;
        float tempC;
        float humidity;
        float ppm;
        uint16 lux;
        &emsp;
        Ticker timer;   // Objeto para manejar el tiempo no bloqueante
        DHT dht(sensorDHTPin, DHT22);
        BH1750 luxometro(0x23);
        LiquidCrystal_I2C lcd(0x27, 16, 2);
        &emsp;
        // Variables para el manejo de tiempo
        unsigned int timeNow, timeLast; // Variables para el control de tiempo no bloqueante
        unsigned int timeRead = 2000; // Tiempo de espera entre lecturas
        unsigned int mqttPublishInterval = 10000;   // Variable para el tiempo de envío de mensajes
        const char *edificio = "W"; // Agrega la ubicación del dispositivo
        const char *cubiculo = "312"; // Agrega el número de cubículo
        String device_name = "ESP8266_" + String(edificio) + String(cubiculo); 
        const char *wifiName = "ESP8266_wifi"; // Agrega el nombre del punto de acceso
        &emsp;
        // Configuración del broker MQTT
        const int mqtt_port = 8883;                 // Puerto del broker MQTT
        const char *mqttBroker = "broker.emqx.io"; // Broker MQTT
        const char *mqttTopic = "w/312";       // Agrerga el topic al que se va a publicar
        const char *mqtt_username = "emqx";
        const char *mqttPassword = "public";
        &emsp;
        // NTP Server settings
        const char *ntp_server = "pool.ntp.org";    // Server NTP
        const long gmt_offset_sec = -21600;         // -6 horas * 3600 segundos para obtener el offset para México
        const int daylight_offset_sec = 0;          // En mexico no se usa horario de verano
        &emsp;
        // Variables para el sensor MQ135
        const float VCC = 5;            // Voltaje de alimentación conectado al sensor MQ135
        const float RL = 0.750;         // Resistencia de carga en ohmios (1 kΩ) del sensor MQ135
        const float air_factor = 3.8;   // Factor de aire limpio (RS/Ro en aire limpio) obtenido de la hoja de datos
        float RO = 7.70;                // Resistencia del sensor en aire limpio
        &emsp;
        #define A 116.6020682           // Coeficiente A de la ecuación de correlación
        #define B 2.769034857           // Coeficiente B de la ecuación de correlación
        #define CORA .00035
        #define CORB .02718
        #define CORC 1.39538
        #define CORD .0018
        #define CORE -.003333333
        #define CORF -.001923077
        #define CORG 1.130128205
        &emsp;
        BearSSL::WiFiClientSecure espClient;
        PubSubClient mqttClient(espClient);
        &emsp;
        // Certificado de la CA
        static const char caCert[] PROGMEM = R"EOF(
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
        )EOF";
        &emsp;
        // Función para sincronizar la hora
        void syncTime() {
            configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
            Serial.print("\nSincronizando la hora ");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Sincronizando");
            lcd.setCursor(0, 1);
            lcd.print("la hora");
            while (time(nullptr) &lt; 1510644967) {
                delay(1000);
                Serial.print(".");
            }
            Serial.println("\n*************************");
            Serial.println("Hora sincronizada");
            struct tm timeinfo;
            if(getLocalTime(&timeinfo)){
                Serial.print("Horario Actual: ");
                Serial.print(asctime(&timeinfo));
                Serial.println("*************************");
            }else{
                Serial.println("Error al sincronizar la hora");
                Serial.println("*************************");
            }
        }
        &emsp;
        // Función la conexión con el broker MQTT
        void connectToMQTT() {
            BearSSL::X509List serverTrustedCA(caCert);
            espClient.setTrustAnchors(&serverTrustedCA);
            while(!mqttClient.connected()){
                String clientId = String(device_name);          // Crea un ID de cliente único
                clientId += "_" + String(random(0xffff), HEX);  // Agrega un ID aleatorio
                Serial.println("Conectando al broker MQTT como " + String(clientId.c_str()));
                if(mqttClient.connect(clientId.c_str(), mqtt_username, mqttPassword)){
                    //Serial.println("Broker MQTT conectado");
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Conexion fallida");
                    lcd.setCursor(0, 1);
                    lcd.print("(timeout)");
                    mqttClient.subscribe(mqttTopic);          // Se suscribe al topic
                }else{
                    char err_buff[128];
                    espClient.getLastSSLError(err_buff, sizeof(err_buff));
                    Serial.println("Error al conectar al broker MQTT:: Estado:");
                    Serial.println(mqttClient.state());        // Muestra el estado de la conexión
                    Serial.print(err_buff);
                    delay(5000);
                }
            }
        }
        &emsp;
        // Función para enviar un mensaje JSON al broker MQTT
        void publishJSON(){
            String json = "{\"ID\":\"" + String(device_name) + 
              "\",\"temp\":" + String(tempC) + 
              ",\"hum\":" + String(humidity) + 
              ",\"luz\":" + String(lux) + 
              ",\"CO2\":" + String(ppm) + 
              ",\"edificio\":\"" + String(edificio) + 
              "\",\"cubiculo\":\"" + String(cubiculo) + 
              "\"}";
            //Serial.println(json);
            mqttClient.publish(mqttTopic, json.c_str());
        }
        &emsp;
        // Función para el parpadeo del led
        void blinkLED(){
            digitalWrite(errorLedPin, !digitalRead(errorLedPin));
        }
        &emsp;
        // Función para obtener el factor de corrección en función de la temperatura y humedad
        float getCorrectionFactor(float tem, float hum) {
            if(tem &lt; 20){
                return CORA * tem * tem - CORB * tem + CORC - (hum-33.)*CORD;
            } else {
                return CORE * tem + CORF * hum + CORG;
            }
        }
        &emsp;
        // Función para obtener la resistencia del sensor MQ135
        float getRS(int samples){
            float avgReadings = 0;
            for (int i = 0; i &lt; samples; i++) {
                avgReadings += analogRead(analog_PIN);  // Leer el valor del sensor del pin analógico
                delay(10);
            }
            avgReadings /= samples;                     // Promedio de las lecturas de calibración
            float voltage = avgReadings * (VCC / adc_resolution);// Conversión de lectura a voltaje
            float RS = (VCC / voltage - 1) * RL;                 // Cálculo de resistencia RS
            return RS;
        }
        &emsp;
        void calibrateRO() {
            RO = getRS(10000) / air_factor;             // Obtener resistencia RO en aire limpio
            Serial.printf("RO calibrado: %.2f Ω\n", RO);// Imprimir resistencia RO calibrada
        }
        &emsp;
        float readCO2PPM() {
            float RS = getRS(100);                      // Obtener resistencia RS del sensor
            float RSCorrected = RS / getCorrectionFactor(tempC, humidity);// Corregir la resistencia RS
            float ppm = A * pow((RSCorrected/RO), -B);  // Calcular la concentración de CO2 en ppm
            return ppm;
        }
        &emsp;
        void setup() {
            Serial.begin(115200);
            Wire.begin();
            lcd.init();
            lcd.backlight();
            &emsp;
            pinMode(statusLedPin, OUTPUT);
            pinMode(errorLedPin, OUTPUT);
            digitalWrite (statusLedPin, HIGH);
            timer.attach(0.2, blinkLED);   // Inicialización del ticker
            WiFiManager wifiManager;        // Inicialización de la conexión a la red WiFi
            //wifiManager.resetSettings();  // Descomenta esta línea si quieres resetear la configuración de WiFi
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Conectarse a:");
            lcd.setCursor(0, 1);
            lcd.print(String(wifiName));
            if (!wifiManager.autoConnect(wifiName)){
                //Serial.println("Fallo en la conexión (timeout)");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Conexion fallida");
                ESP.reset();                // Reiniciar el ESP8266
                delay(5000);
            }
            timer.detach();                  // Detiene el ticker de parpadeo
            digitalWrite(errorLedPin, HIGH);
            digitalWrite(statusLedPin, LOW);
            &emsp;
            Serial.println("Conectado a WiFi");
            Serial.print("Dirección IP: ");
            Serial.println(WiFi.localIP());
            &emsp;
            dht.begin();
            luxometro.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
            &emsp;
            syncTime();                                     // Sincronización de la hora
            mqttClient.setServer(mqttBroker, mqtt_port);  // Configuración del broker MQTT
            connectToMQTT();                                // Conexión al broker MQTT
            timer.attach_ms(mqttPublishInterval, publishJSON);           // Inicialización del ticker para enviar mensajes
        }
        &emsp;
        void loop() {
            timeNow = millis();
            if(!mqttClient.connected()){
                connectToMQTT();
            }
            mqttClient.loop();
            if(timeNow - timeLast &gt;= timeRead){
                timeLast = timeNow;
                float avgtempC = 0;
                float avghumidity = 0;
                for (int i = 0; i &lt; 100; i++){
                    float readTemp = dht.readTemperature();
                    float readHumidity = dht.readHumidity();
                    lux = luxometro.readLightLevel();
                    avgtempC += readTemp;
                    avghumidity += readHumidity;
                }
                avgtempC = avgtempC / 100;
                avghumidity = avghumidity / 100;
                tempC = avgtempC;
                humidity = avghumidity;
                ppm = readCO2PPM();
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print(String(tempC, 1) + " "+ (char)223 + "C "+ String(lux) + " lux");
                lcd.setCursor(0, 1);
                lcd.print(String(humidity,1) + "% "+ String(ppm) + " ppm");
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
            lib_deps = 
                knolleary/PubSubClient@^2.8
                tzapu/WiFiManager @ ^2.0.17
                adafruit/DHT sensor library@^1.4.6
                claws/BH1750@^1.3.0
                marcoschwartz/LiquidCrystal_I2C@^1.1.4
        </code-block>
    </tab>
</tabs>

## Conexión del ESP8266 a Internet

Una vez subido el firmware al ESP8266, el dispositivo creará un punto de acceso wifi llamado `ESP8266_wifi` si no encuentra una red conocida. Para configurarlo:

1. Buscar la red WiFi `ESP8266_wifi`. Esta red se crea automáticamente cuando el ESP8266 no se ha conectado a ninguna red WiFi conocida, no tiene contraseña y se puede conectar a ella para configurar la red WiFi a la que se desea conectar el ESP8266.
    
    ![](proyecto_hostpot.png) {border-effect="rounded" width="400" thumbnail="true"}

2. Cuando se haya conectado a la red WiFi `ESP8266_wifi`, se abrirá una página web para configurar la red WiFi a la que se desea conectar el ESP8266. Para esto debemos seleccionar `Configure WiFi`.

    ![](proyecto_wifiManager.png) {border-effect="rounded" width="400" thumbnail="true"}

3. Seleccionar la red WiFi a la que se desea conectar el ESP8266 e ingresar la contraseña de la red WiFi. Posteriormente, seleccionar `Save`.

    ![](proyecto_credenciales.png) {border-effect="rounded" width="400" thumbnail="true"}

4. Una vez que se haya configurado la red WiFi, el ESP8266 se conectará automáticamente a la red WiFi seleccionada. Después de un rato en la pantalla LCD se mostrarán las lecturas de los sensores, en ese momento empezará a enviar las lecturas a un broker MQTT y podremos visualizarlas utilizando MQTTX CLI.

    ![](proyecto_mqttx.png) {border-effect="rounded" width="400" thumbnail="true"}

> Esta configuración se realiza una sola vez, ya que el ESP8266 recordará la red WiFi a la que se conectó y se conectará automáticamente a ella cuando se reinicie.

## Almacenamiento de Datos en InfluxDB

Para almacenar las lecturas de los sensores, se utiliza InfluxDB dentro de un contenedor Docker en la Raspberry Pi.

1. Acceder a la terminal de InfluxDB:

    ```bash
    docker exec -it influxdb influx
    ```

2. Crear una base de datos:

    ```sql
    CREATE DATABASE nombre_base_datos
    ```

3. Verificar bases de datos:

    ```sql
    SHOW DATABASES
    ```

4. Seleccionar la base de datos a usar:
   ```sql
   USE nombre_base_datos;
   ```

Los datos enviados por MQTT y procesados por Node-RED quedarán almacenados en InfluxDB.

## Base de Datos MySQL para Usuarios

Se implementa una base de datos MySQL (también en Docker) para gestionar información de usuarios.

1. Ejecutar un contenedor MySQL:

   ```bash
   docker run --name mysql -e MYSQL_ROOT_PASSWORD=contraseña -d mysql:tag
   ```

    > **Nota:** Reemplazar `tag` por la versión de mysql que se desea instalar y `contraseña` por la contraseña que se desea asignar al usuario root.
    > {sytle="warning"}

2. Crear la base de datos:

   ```sql
   CREATE DATABASE nombre_base_datos;
   ```

    ![Crear base de datos](proyecto_crearBD.png) {border-effect="rounded" width="400" thumbnail="true"}

3. Para agilizar el proceso de administración de la base de datos, se recomienda instalar [DataGrip](https://www.jetbrains.com/datagrip/?source=google&medium=cpc&campaign=AMER_en_AMER_DataGrip_Branded&term=datagrip&content=555122603991&gad_source=1&gclid=CjwKCAiApY-7BhBjEiwAQMrrEXxBHBWMDPdgYmyyVZftG1WWbMyfBuKvH8f98yE2wgFBdh6xcQhYVRoCRu4QAvD_BwE), un IDE de JetBrains que permite la conexión a bases de datos MySQL, PostgreSQL, SQLite, entre otros.

    Tras instalar DataGrip y crear la base de datos, debes configurar una conexión. Para ello:

   - Haz clic en el botón `+`.
   - Selecciona `MySQL`.
   - Introduce los datos de conexión correspondientes:
       - Host: `Dirección IP de la Raspberry Pi`.
       - Port: `3306`.
       - User: `root`.
       - Password: `contraseña`.
       - Database: `nombre_base_datos (creada anteriormente)`.

    > **Nota:** Antes de aplicar los cambios, es necesario verificar que la conexión se haya establecido correctamente.
    
    ![Configurar conexión](proyecto_conecBD.png) {border-effect="rounded" width="400" thumbnail="true"}

4. Una vez que se tiene la base de datos creada y la conexión establecida, se debe crear una tabla para almacenar los usuarios. Para ello, se debe ejecutar el siguiente comando:

    ```sql
    CREATE TABLE usuarios (
        id INT PRIMARY KEY AUTO_INCREMENT,
        nombres VARCHAR(100) NOT NULL,
        apellido_paterno VARCHAR(50) NOT NULL,
        apellido_materno VARCHAR(50),
        cubiculo VARCHAR(50),
        numero_cubiculo VARCHAR(10),
        id_telegram BIGINT UNIQUE,
        fecha_creacion TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        fecha_actualizacion TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
    );
    ```

    El comando anterior crea una tabla llamada `usuarios` con los siguientes campos:
    
    - `id`: Identificador único de cada usuario.
    - `nombres`: Nombres del usuario.
    - `apellido_paterno`: Apellido paterno del usuario.
    - `apellido_materno`: Apellido materno del usuario.
    - `cubiculo`: Cubículo asignado al usuario.
    - `numero_cubiculo`: Número de cubículo asignado al usuario.
    - `id_telegram`: Identificador único de Telegram del usuario.
    - `fecha_creacion`: Fecha de creación del registro.
    - `fecha_actualizacion`: Fecha de actualización del registro.

    ![Crear tabla](proyecto_crearTabla.png) {border-effect="rounded" width="400" thumbnail="true"}

5. Insertar registros en la tabla `usuarios`:

    ```sql
    INSERT INTO usuarios (
        nombres, 
        apellido_paterno, 
        apellido_materno, 
        cubiculo, 
        numero_cubiculo, 
        id_telegram
    )VALUES(
        'Juan Carlos', 
        'González', 
        'Pérez', 
        'A', 
        '101', 
        '3242342545'
    );
    ```

6. Para visualizar los registros de la tabla `usuarios`, se debe ejecutar el siguiente comando:

    ```sql
    SELECT * FROM usuarios;
    ```
    
    ![Insertar usuarios](proyecto_insertarUsuarios.png) {border-effect="rounded" width="400" thumbnail="true"}

Una vez creada la tabla y los registros, se puede proceder a realizar la conexión con la base de datos en Node-RED el cual creará un flujo para agregar, modificar, eliminar y consultar los registros de la tabla `usuarios` utilizando el nodo de Telegram bot.

## Integración con Node-RED

**Objetivos:**

- Guardar lecturas de sensores en InfluxDB.
- Enviar alertas y mensajes por Telegram.
- Integrar MySQL para gestionar información de usuarios.

### Guardar Lecturas en InfluxDB

Node-RED recibe los datos del MQTT, los transforma de ser necesario y los escribe en InfluxDB. Importar el flujo `nodeRed_bd.json` en Node-RED para implementar esta funcionalidad. Luego, desde el terminal de InfluxDB se pueden consultar los datos almacenados.

![Node-Red-FlowBD](flow_baseDatos.png) {border-effect="rounded" width="400" thumbnail="true"}

El flujo para importar en Node-RED el flujo de guardar lecturas en InfluxDB se muestra a continuación:

<code-block lang="JSON" src="nodeRed_bd.json" collapsible="true" collapsed-title="Guardar lecturas en InfluxDB"/>

Posteriormente, ingresamos a influxDB dentro de Docker con el siguiente comando:

```bash
docker exec -it influxdb influx
```

Y ejecutamos el siguiente comando para visualizar los datos almacenados en la base de datos:

```sql
USE nombre_base_datos
```

```sql
SELECT * FROM nombre_medida
```

Podemos observar que los mensajes enviados por MQTT han sido almacenados en la base de datos.

### Alertas por Telegram

Se configura un bot de Telegram en Node-RED para enviar alertas sobre los datos del cubículo. Importar el flujo `nodeRed_telegram.json` en Node-RED. Tras iniciar el bot con `/start`, se pueden registrar usuarios y enlazar sus cuentas de Telegram al dispositivo IoT, recibiendo alertas personalizadas.

![Node-Red-FlowTelegram](flow_telegram.png) {border-effect="rounded" width="400" thumbnail="true"}

El flujo para importar en Node-RED el flujo de alertas por Telegram se muestra a continuación:

<code-block lang="JSON" src="nodeRed_telegram.json" collapsible="true" collapsed-title="Alertas por Telegram"/>

Una vez que el flujo haya sido ejecutado, el bot de telegram enviará un mensaje de bienvenida al momento de ingresar.

![Telegram](proyecto_telegram.png) {border-effect="rounded" width="400" thumbnail="true"}

Podremos visualizar los usuarios que se han registrado en la base de datos, para ello, se deben abrir nuevamente DataGrip y ejecutar el siguiente comando:

```sql
SELECT * FROM usuarios;
```

### Visualización de Datos con Grafana

Una vez que InfluxDB está almacenando las lecturas, Grafana se utiliza para visualizar los datos en paneles y gráficas. Configurar una fuente de datos InfluxDB en Grafana y crear dashboards según las necesidades del proyecto.

![Grafana](proyecto_grafana.png) {border-effect="rounded" width="400" thumbnail="true"}