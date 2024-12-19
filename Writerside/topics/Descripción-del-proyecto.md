# Descripción del proyecto

La presente documentación tiene como objetivo describir los proyectos realizados durante el servicio social en la Universidad Autónoma Metropolitana Unidad Azcapotzalco. Estos proyectos se enfocan en el desarrollo de Internet de las Cosas (IoT) utilizando microcontroladores ESP8266 y ESP32.

## Contenido

- [Configuración del Entorno](#configuraci-n-del-entorno)
- [Configuración del Servidor](#configuraci-n-del-servidor)
- [Proyectos](#proyectos)

## Configuración del Entorno

Para desarrollar el proyecto, fue necesario contar con un entorno adecuado. En esta sección se describen los pasos para instalar y configurar:

1. [Instalación de Linux Mint](Instalacion-de-Linux-Mint.md)  
   Explica cómo instalar y configurar el sistema operativo Linux Mint, que será la base para el desarrollo de los proyectos.

2. [](Instalación-de-Arduino-IDE.md)
   Muestra cómo instalar y preparar el entorno Arduino IDE para programar los microcontroladores ESP8266 y ESP32.

3. [Visual Studio Code y PlatformIO](Instalación-de-Vscode-y-PlatformIO.md)
   Detalla la instalación de Visual Studio Code y la extensión PlatformIO, para programar los microcontroladores de manera más eficiente.

4. [Instalación de MQTTX](MQTT.md)
   Indica el procedimiento para instalar MQTTX, un cliente MQTT que permite visualizar y depurar las comunicaciones entre dispositivos y el broker.

## Configuración del Servidor

Para el despliegue de servicios, se utilizó una Raspberry Pi 4 como servidor. Aquí se detalla la configuración del servidor mediante Docker, lo que facilita la replicación del entorno:

1. [](Docker.md)
   Introducción a la instalación y configuración de Docker en la Raspberry Pi 4, para la gestión de contenedores y
   servicios.

2. [](Docker-Portainer.md)
   Explica cómo instalar Portainer, una herramienta gráfica para gestionar contenedores Docker.

3. [Instalación de InfluxDB](Instalación-de-InfluxDB.md)  
   Describe la instalación de InfluxDB para el almacenamiento de datos de sensores en series temporales.

4. [Node-RED](Instalación-de-NodeRed.md)
   Detalla cómo instalar Node-RED para la orquestación de flujos y procesamiento de datos IoT.

5. [](Grafana.md)
   Indica los pasos para instalar Grafana, herramienta de visualización para crear paneles y monitorear datos
   recopilados por InfluxDB.

## Proyectos

En esta sección se presentan los proyectos desarrollados con el ESP8266 y el ESP32. Cada proyecto incorpora funcionalidades específicas, en cada sección se detalla la descripción, especificaciones del sensor, el diagrama de conexión y el código fuente.

1. **Proyecto 1: Blink**
    - Descripción: Prueba inicial para verificar la configuración del entorno y el correcto funcionamiento del IDE con el ESP8266.
    - [Documentación de Blink](Blink.md)
    - Repositorio: [1 - Blink](https://github.com/Luisangel2801/Servicio-Social/tree/main/1%20-%20Blink)

2. **Proyecto 2: DHT**
   - Descripción: Lectura de temperatura y humedad utilizando el sensor DHT.
   - [Documentación del sensor DHT](Sensor-DHT.md)
   - Repositorio: [2 - DHT11](https://github.com/Luisangel2801/Servicio-Social/tree/main/2%20-%20DHT11)

3. **Proyecto 3: LCD I2C**
    - Descripción: Integración de una pantalla LCD utilizando la interfaz I2C.
    - [Documentación de Pantalla la pantalla LCD 16x2](Pantalla-LCD.md)
    - Repositorio: [3 - LCD I2C module](https://github.com/Luisangel2801/Servicio-Social/tree/main/3%20-%20LCD%20I2C%20module)

4. **Proyecto 4: DHT11 con la pantalla LCD**
    - Descripción: Combina la lectura de temperatura y humedad con la visualización en la pantalla LCD.
    - [Documentación del sensor DHT con la pantalla LCD](Sensor-DHT-con-la-pantalla-LCD.md)
    - Repositorio: [4 - DHT11 with LCD Screen](https://github.com/Luisangel2801/Servicio-Social/tree/main/4%20-%20DHT11%20with%20LCD%20Screen)

5. **Proyecto 5: MQ135**
    - Descripción: Lectura de la calidad del aire mediante el sensor MQ135.
    - [Documentación del sensor MQ135](MQ135.md)
    - Repositorio: [5 - MQ135](https://github.com/Luisangel2801/Servicio-Social/tree/main/5%20-%20MQ135)
   
6. **Proyecto 6: Sensor de luz BH1750**
    - Descripción: Lectura de la intensidad de luz con el sensor BH1750.
    - [Documentación del sensor BH1750](Sensor-BH1750.md)
    - Repositorio: [6 - BH1750](https://github.com/Luisangel2801/Servicio-Social/tree/main/6%20-%20Light%20meter%20BH1750)
   
7. **Proyecto 7: Sensor de luz con la pantalla LCD**
    - Descripción: Combina la lectura de la intensidad de luz con la visualización en la pantalla LCD.
    - [Documentación del sensor BH1750 con la pantalla LCD](Sensor-BH1750-con-la-pantalla-LCD.md)
    - Repositorio: [7 - BH1750 with LCD Screen](https://github.com/Luisangel2801/Servicio-Social/tree/main/7%20-%20Light%20meter%20with%20LCD%20Screen)
   
8. **Proyecto 8: Conexión a Internet**
    - Descripción: Conexión de la placa de desarrollo a Internet mediante wifi.
    - [Documentación de la conexión a Internet](Conexión-a-Internet.md)
    - Repositorio: [8 - Internet Connection](https://github.com/Luisangel2801/Servicio-Social/tree/main/8%20-%20Internet%20connection)

9. **Proyecto 9: MQTT** 
    - Descripción: Envío de mensajes a través del protocolo MQTT.
    - [Documentación de MQTT](Conexión-a-Internet.md)
    - Repositorio: [9 - MQTT](https://github.com/Luisangel2801/Servicio-Social/tree/main/9%20-%20MQTT%20with%20ESP32)
