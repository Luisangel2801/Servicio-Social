# Instalar EMQX

**EMQX** es un broker MQTT (Message Queuing Telemetry Transport) de código abierto y altamente escalable, llegando a soportar 100 millones de conexiones simultáneas de dispositivos IoT por cluster. MQTT es un protocolo ligero y eficiente para la comunicación máquina a máquina (M2M) y el Internet de las Cosas (IoT).

![MQTTX](emqx.png) {width="700"}

## Características de EMQX

- **Alto rendimiento y escalabilidad**:
	- **Millones de conexiones simultáneas**: EMQX puede gestionar fácilmente millones de dispositivos conectados, lo que lo hace ideal para grandes despliegues IoT.
	- **Baja latencia**: Garantiza una comunicación rápida y eficiente entre dispositivos y aplicaciones.
	- **Clústering**: Permite escalar horizontalmente para manejar cargas de trabajo aún mayores.
    ![EMQX_Cluster](emqx_cluster.png) {width="700"}
- **Compatibilidad con MQTT 5.0, MQTT 3.1.1**: Ofrece soporte total para las últimas especificaciones del protocolo MQTT y versiones anteriores.
- **Seguridad Robusta**:
	- **Autenticación y autorización**: Protege tus datos mediante múltiples mecanismos de autenticación y autorización.
	- **Cifrado**: Garantiza la confidencialidad de los datos en tránsito.
    ![EMQX_seguridad](emqx_seguridad.png) {width="700"}
- **Amplio conjunto de características**:
	- **Retención de mensajes**: Permite a los clientes recibir mensajes antiguos cuando se suscriben a un nuevo tema. Los mensajes se almacenan en el servidor para que los nuevos suscriptores puedan recibirlos.
	- **QoS (Quality of Service)**: Ofrece tres niveles de QoS para garantizar la entrega de mensajes.
	- **Temas wildcard**: Facilita la creación de suscripciones flexibles.

![EMQX_Features](emqx_arquitectura.png) {width="700"}

## Instalación de MQTTX CLI

MQTTX CLI es un cliente MQTT 5.0 de código abierto que opera desde la línea de comandos. Está diseñado para agilizar el desarrollo y la depuración de servicios y aplicaciones MQTT, eliminando la necesidad de utilizar una interfaz gráfica.

### 1. Descargar el archivo de instalación

Primero, descargamos el archivo de instalación de EMQX desde la [página oficial de descargas de EMQX](https://mqttx.app/downloads "Página oficial de descargas de EMQX").

```bash
curl -LO https://www.emqx.com/en/downloads/MQTTX/v1.11.1/mqttx-cli-linux-x64
```

### 2. Instalar EMQX

Una vez descargado el archivo, lo instalamos en el directorio `/usr/local/bin`.

```bash
sudo install ./mqttx-cli-linux-x64 /usr/local/bin/mqttx
```

### 3. Verificar la instalación

Una vez instalado, podemos verificar la instalación ejecutando el siguiente comando.

```bash
mqttx --version
```

### 4. Suscribirse a un tema

Para suscribirnos a un tema, ejecutamos el siguiente comando. El cual se suscribirá al tema `topic` en el broker `broker.emqx.io` en el puerto `1883`.

```bash
mqttx sub -t "topic" -h broker.emqx.io -p 1883
```

### 5. Publicar un mensaje

Para publicar un mensaje, ejecutamos el siguiente comando. Este comando mantendrá la conexión abierta para publicar múltiples mensajes en el tema `topic` en el broker `broker.emqx.io` en el puerto `1883`.

```bash
mqttx pub -t "topic" -h 'broker.emqx.io' -p 1883 -lm
```

Ponemos cada comando en una terminal diferente para ver cómo se publican y reciben los mensajes.

![EMQX_CLI](MQTTX_terminal.png) {border-effect="rounded" width="400" thumbnail="true"}

## Instalación de la aplicación MQTTX {id="mqttx"}

MQTTX es un cliente de escritorio multiplataforma y de código abierto para MQTT 5.0, desarrollado inicialmente por EMQ, que puede ejecutarse en macOS, Linux y Windows.

La interfaz de usuario (UI) de MQTTX está diseñada con una estética similar a la de un chat, lo que simplifica su operativa. Permite a los usuarios establecer múltiples conexiones MQTT, facilitando así la prueba rápida de conexiones, así como la suscripción y publicación de mensajes MQTT/MQTTs.

### 1. Actualizar la lista de paquetes disponibles

Primero, actualiza la lista de paquetes disponibles en el sistema para asegurarte de que estás obteniendo las versiones más recientes.

```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Descargar el paquete de instalación de EMQX

Podemos descargar el paquete de instalación de EMQX desde la [página oficial](https://mqttx.app/downloads "Página oficial de descargas de MQTTX") de descargas de EMQX. En este caso, se descargará la versión para distribuciones basadas en debian.

```bash
wget https://www.emqx.com/en/downloads/MQTTX/v1.11.0/MQTTX_1.11.0_amd64.deb
```

### 3. Instalar el paquete descargado

Una vez descargado el paquete, procedemos a instalarlo.

```bash
sudo dpkg -i MQTTX_1.11.0_amd64.deb
```

### 4. Iniciar MQTTX

Una vez instalado, puedes buscar MQTTX en el menú de aplicaciones y ejecutarlo.

![MQTTX](MQTTX.png) {border-effect="rounded" width="400" thumbnail="true"}

### 5. Conectar MQTTX a EMQX {id="mqttx_conexion"}

Para conectarnos al broker EMQX, simplemente hacemos clic en el botón `+` y presionamos `New Connection`. En este caso utilizaremos un broker público proporcionado por EMQX el cual tiene las siguientes credenciales:

- **Broker**: broker.emqx.io
- **Puerto TCP**: 1883

Ponemos un nombre a la conexión y presionamos `Connect`.

![MQTTX_Connexion](MQTTX_conexion.png) {border-effect="rounded" width="400" thumbnail="true"}

> **Nota**: Si deseas conectarte a través de SSL/TLS, debe agregar el certificado de la autoridad (CA) proporcionado por EMQX.
> {style=note}

- **Puerto SSL/TLS**: 8883
- **Certificado**: [Certificate Authority](https://assets.emqx.com/data/broker.emqx.io-ca.crt "Descargar el Certificate Authority")

![MQTTX_Connexion_SSL](MQTTX_conexionSSL.png) {border-effect="rounded" width="400" thumbnail="true"}

### 6. Suscribirse a un tema

Para suscribirnos a un tema, hacemos clic en el botón `New Subscription`, ingresamos el nombre del tema al que queremos suscribirnos y presionamos `Confirm` para suscribirnos.

![MQTTX_Subscription](MQTTX_sub.png) {border-effect="rounded" width="400" thumbnail="true"}

### 7. Publicar un mensaje

Para publicar un mensaje, en la parte inferior de la ventana de MQTTX, ingresamos el tema al que queremos publicar, el formato del mensaje y la calidad de servicio (QoS) y presionamos el botón verde.

![MQTTX_Publish](MQTTX_pub.png) {border-effect="rounded" width="400" thumbnail="true"}

Podemos ver cómo se publican y reciben los mensajes en la ventana de MQTTX, los mensajes enviados se verán de color verde y los mensajes recibidos del color seleccionado anteriormente.

![MQTTX_message](MQTTX_mensajes.png) {border-effect="rounded" width="400" thumbnail="true"}

## EMQX Cloud {id="emqx-cloud"}

EMQX Cloud es un servicio de broker MQTT en la nube que permite utilizar un broker MQTT privado y escalable sin tener que preocuparse por la infraestructura subyacente. Proporciona una forma sencilla de conectar dispositivos IoT y aplicaciones a través de MQTT, con la capacidad de escalar automáticamente para manejar millones de conexiones simultáneas.

![EMQX_Cloud](EMQX_cloud.png) {width="700"}

### Características de EMQX Cloud

- **Escalabilidad**: Escala automáticamente para manejar millones de conexiones simultáneas.
- **Seguridad**: Proporciona cifrado de extremo a extremo y autenticación basada en certificados.
- **Integración con servicios en la nube**: Se integra con servicios en la nube como AWS, Google Cloud y Azure.
- **Monitoreo y análisis**: Proporciona herramientas de monitoreo y análisis para supervisar el rendimiento y la disponibilidad del broker MQTT.
- **Reglas de enrutamiento**: Permite enrutar mensajes a diferentes destinos en función de reglas predefinidas.


![EMQX_Cloud_Features](emqx_server.png) {width="700"}

### Crear un clúster en EMQX Cloud

Para crear un broker MQTT dedicado en EMQX Cloud, sigue los siguientes pasos:

1. **Crear una cuenta en EMQX Cloud**: Regístrate en [EMQX Cloud](https://www.emqx.com/en/cloud "EMQX Cloud") y entra a tu cuenta.

	![EMQX_Cloud_Register](emqxCloud_pagina.png) {border-effect="rounded" width="400" thumbnail="true"}

2. **Crear el broker MQTT**: Seleccionamos el plan que mejor se adapte a nuestras necesidades, en este caso usaremos el plan `severless` que tiene una cuota gratuita de 1 millón de minutos al mes.

	![EMQX_Cloud_Planes](emqxCloud_planes.png) {border-effect="rounded" width="400" thumbnail="true"}

3. **Configurar el broker MQTT**: Seleccionamos la región donde queremos que esté el servidor, proporcionamos un nombre para el broker y presionamos en `Deploy`.
   
	![EMQX_Cloud_Config](emqxCloud_config.png) {border-effect="rounded" width="400" thumbnail="true"}

4. **Detalles del broker MQTT**: Una vez desplegado el broker, podemos ver los detalles del broker, como la dirección del broker, el puerto y el certificado de autoridad (CA) para la conexión segura.

	![EMQX_Cloud_Details](emqxCloud_details.png) {border-effect="rounded" width="400" thumbnail="true"}

5. **Crear un usuario**: Para conectarnos al broker, es necesario crear un usuario y contraseña. Para ello, vamos a la pestaña `Authentication` y presionamos en `+ Add`, proporcionamos un nombre de usuario y contraseña y presionamos en `Confirm`.

	![EMQX_Cloud_User](emqxCloud_usuarios.png) {border-effect="rounded" width="400" thumbnail="true"}

6. **Conectar MQTTX a EMQX Cloud**: Para conectarnos al broker, simplemente seguimos los pasos de la [conexión de MQTTX a EMQX](#mqttx_conexion "Pasos para conectarnos a un broker desde la aplicación MQTTX") realizados con anterioridad y utilizamos la dirección del broker, el puerto, el usuario y contraseña que obtuvimos en los pasos anteriores.

	![EMQX_Cloud_Conexion](emqxCloud_conexion.png) {border-effect="rounded" width="400" thumbnail="true"}

> **Resultado**: Se realizó la instalación de MQTTX CLI y MQTTX, se conectó MQTTX a un broker MQTT público y se creó un broker MQTT privado desde EMQX Cloud.

