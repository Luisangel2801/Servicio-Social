# Proyecto IoT


<tabs>
    <tab title="main.cpp">
        <code-block lang="c++" collapsible="true" collapsed-title="Person">
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
            delay(1000);               // espera 1000 milisegundos = un segundo
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

![](proyecto_hostpot.png) {border-effect="rounded" width="400" thumbnail="true"}

![](proyecto_wifiManager.png) {border-effect="rounded" width="400" thumbnail="true"}

![](proyecto_credenciales.png) {border-effect="rounded" width="400" thumbnail="true"}


## Crear base de datos en influxDB

Para comenzar, debemos ingresar a la terminal de influxDB dentro de Docker. Para ello, ejecutamos el siguiente comando:

```bash
docker exec -it influxdb influx
```

Una vez que se tiene acceso a la terminal de influxDB, se debe crear una base de datos para almacenar las lecturas de los sensores. Para ello, se debe ejecutar el siguiente comando:

```sql
CREATE DATABASE nombre_base_datos
```
Posteriormente, se debe verificar que la base de datos se haya creado correctamente. Para ello, se debe ejecutar el siguiente comando:

```sql
SHOW DATABASES
```

Posteriormente, se debe seleccionar la base de datos creada. Para ello, se debe ejecutar el siguiente comando:

```sql
USE nombre_base_datos
```

## Crear base de datos para almacenar los usuarios

Para comenzar, debemos instalar mysql en nuestra Raspberry Pi, para ello, podemos hacer uso de la [imagen oficial de mysql en Docker](https://hub.docker.com/_/mysql). Para ello, ejecutamos el siguiente comando:

```bash 
docker run --name mysql -e MYSQL_ROOT_PASSWORD=contraseña -d mysql:tag
```

> **Nota:** Reemplazar `tag` por la versión de mysql que se desea instalar y `contraseña` por la contraseña que se desea asignar al usuario root.
> {sytle="warning"}

Una vez que se tiene instalado mysql, se debe crear una base de datos para almacenar los usuarios. Para ello, se debe ejecutar el siguiente comando:

```sql
CREATE DATABASE nombre_base_datos;
```

![Crear base de datos](proyecto_crearBD.png) {border-effect="rounded" width="400" thumbnail="true"}

Para agilizar el proceso de administración de la base de datos, se recomienda instalar [DataGrip](https://www.jetbrains.com/datagrip/?source=google&medium=cpc&campaign=AMER_en_AMER_DataGrip_Branded&term=datagrip&content=555122603991&gad_source=1&gclid=CjwKCAiApY-7BhBjEiwAQMrrEXxBHBWMDPdgYmyyVZftG1WWbMyfBuKvH8f98yE2wgFBdh6xcQhYVRoCRu4QAvD_BwE), un IDE de JetBrains que permite la conexión a bases de datos MySQL, PostgreSQL, SQLite, entre otros.

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

## Crear tabla para almacenar los usuarios

Una vez que se tiene la base de datos creada y la conexión establecida, se debe crear una tabla para almacenar los usuarios. Para ello, se debe ejecutar el siguiente comando:

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

## Insertar usuarios en la tabla

Para insertar usuarios en la tabla `usuarios`, se debe ejecutar el siguiente comando:

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
Para visualizar los registros de la tabla `usuarios`, se debe ejecutar el siguiente comando:

```sql
SELECT * FROM usuarios;
```

![Insertar usuarios](proyecto_insertarUsuarios.png) {border-effect="rounded" width="400" thumbnail="true"}

Una vez creada la tabla y los registros, se puede proceder a realizar la conexión con la base de datos en Node-RED el cual creará un flujo para agregar, modificar, eliminar y consultar los registros de la tabla `usuarios` utilizando el nodo de Telegram bot.

## Flow en Node-RED

Antes de empezar, es necesario realizar la instalación de los siguientes nodos en Node-RED:

- [Nodo de MySQL](https://flows.nodered.org/node/node-red-node-mysql)
- [Nodo de InfluxDB](https://flows.nodered.org/node/node-red-contrib-influxdb)
- [Nodo de Telegram bot](https://flows.nodered.org/node/node-red-contrib-telegrambot)
- [Nodo de Telegram sender](https://flows.nodered.org/node/node-red-contrib-telegrambot-home)

### Guardar lecturas de los sensores en InfluxDB

El flujo de Node-RED para guardar las lecturas de los sensores en InfluxDB se muestra a continuación:

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

El flujo de Node-RED para enviar alertas por Telegram se muestra a continuación:

![Node-Red-FlowTelegram](flow_telegram.png) {border-effect="rounded" width="400" thumbnail="true"}

El flujo para importar en Node-RED el flujo de alertas por Telegram se muestra a continuación:

<code-block lang="JSON" src="nodeRed_telegram.json" collapsible="true" collapsed-title="Alertas por Telegram"/>

Una vez que el flujo haya sido ejecutado, podremos unirnos al bot de Telegram, al ingresar el comando `/start` el bot nos enviará un mensaje de bienvenida y posteriormente debemos agregar los datos requeridos por el bot, para enlazar nuestro usuario de Telegram con el dispositivo IoT para recibir únicamente las alertas de nuestro dispositivo.

![Telegram](proyecto_telegram.png) {border-effect="rounded" width="400" thumbnail="true"}

### Visualizar datos en Grafana

Una vez que los datos se encuentran en InfluxDB, se pueden visualizar en Grafana. Para ello, es necesario configurar un nuevo origen de datos en Grafana con los siguientes parámetros: