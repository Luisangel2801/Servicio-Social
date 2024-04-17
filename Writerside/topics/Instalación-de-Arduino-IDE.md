# Instalación de Arduino IDE

Arduino IDE es un entorno de desarrollo integrado (IDE) que permite programar y cargar código en las placas de desarrollo de Arduino y otros microcontroladores compatibles. En este documento se describen los pasos necesarios para instalar Arduino IDE en el sistema operativo Linux Mint.

![Arduino IDE](arduino.png) {width="700" border-effect="rounded"}

> Se realizará la instalación del IDE de Arduino para poder programar y cargar códigos en las tarjetas de desarrollo ESP.


## Descargar el IDE de Arduino

Para realizar la instalación del IDE de Arduino, se debe descargar el paquete de instalación desde la [página oficial](https://www.arduino.cc/en/software "Arduino Software") de Arduino. Seleccionamos la versión que corresponda con el sistema operativo y la arquitectura del sistema, en este caso se utilizará la versión 1.8.19 para Linux.

![Descargar Arduino](descargarArduino.png) { width="400" border-effect="rounded" thumbnail="true"}

## Descomprimir el paquete de instalación

Una vez que el paquete de instalación esté descargado, se debe mover el archivo a la carpeta Home del usuario y descomprimirlo. Para ello, se puede utilizar el comando `tar` en la terminal de Linux Mint o descomprimirlo desde el administrador de archivos.

```bash
    tar -xvzf arduino-1.8.19-linux64.tar.xz
```

## Ejecutar el instalador

Antes de realizar la instalación, se debe ejecutar el archivo `arduino-linux-setup.sh` que se encuentra dentro de la carpeta descomprimida, este archivo instalará las dependencias necesarias para el IDE de Arduino y no tener problemas con los puertos USB. Para ello, se debe ejecutar el siguiente comando:

```bash
./arduino-linux-setup.sh $USER
```

Posteriormente, se debe ejecutar el archivo `install.sh` para instalar el IDE de Arduino en el sistema. Para ello, se debe ejecutar el siguiente comando:

```bash
sudo ./install.sh
```

## Ejecutar Arduino IDE

Una vez que la instalación haya finalizado, se puede ejecutar el IDE de Arduino desde la terminal utilizando el comando `arduino`. También se puede buscar en el menú de aplicaciones de Linux Mint.

```bash
arduino
```

## Configurar el IDE de Arduino para las tarjetas ESP

Para poder programar las tarjetas de desarrollo ESP8266 y ESP32, se debe configurar el IDE de Arduino para que reconozca las tarjetas. Para ello, se debe seguir los siguientes pasos:

<procedure title="Pasos para configurar el IDE de Arduino para utilizar las tarjetas ESP" id="configurar-IDE-Arduino">
    <step>
        <p>Abrir el IDE de Arduino</p>
    </step>
    <step> 
        <p>Ir a la pestaña <code>Archivo</code> y seleccionar <code>Preferencias</code></p>
    </step>
    <step>
        <p>En el campo <code>Gestor de URLs Adicionales de Tarjetas</code> se debe agregar la URL que corresponda con la tarjeta que se desea utilizar</p>
        <img src="arduinoURL.png" alt="URLs adicionales" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p>Dependiendo de la tarjeta que se desee utilizar, se debe agregar la URL correspondiente, en este caso de utilizar ambas tarjetas, se deben agregar las dos URL's separadas por una coma</p>
        <tabs>
            <tab title="ESP 8266">
                <code-block lang="plain text">https://arduino.esp8266.com/stable/package_esp8266com_index.json</code-block>
            </tab>
            <tab title="ESP 32">
                <code-block lang="plain text">https://dl.espressif.com/dl/package_esp32_index.json</code-block>
            </tab>
        </tabs>
    </step>
    <step>
        <p>Una vez que se hayan agregado las URL's, se debe ir a la pestaña <code>Herramientas</code> y seleccionar <code>Placa</code> y <code>Gestor de Tarjetas</code></p>
    </step>
    <step>
        <p>En el campo de búsqueda se debe escribir <code>ESP</code> y seleccionar la tarjeta que se desee instalar</p>
        <img src="arduinoESP.png" alt="Seleccionar tarjeta" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
</procedure>

## Cargar un código de ejemplo

Para verificar que la instalación del IDE de Arduino se realizó correctamente, se debe cargar un código de ejemplo en una tarjeta ESP8266 o ESP32. Para ello, se debe seguir los siguientes pasos:

<procedure title="Pasos para cargar un código de ejemplo en una tarjeta ESP" id="cargar-codigo-ejemplo">
    <step>
        <p>Abrir el IDE de Arduino</p>
    </step>
    <step>
        <p>Seleccionar la tarjeta de desarrollo ESP8266 o ESP32</p>
        <p> Esto se realiza desde la pestaña <code>Herramientas</code> y seleccionando la tarjeta correspondiente</p>
    </step>
    <step>
        <p>Seleccionar el puerto serie al que se encuentra conectada la tarjeta</p>
        <p> Esto se realiza desde la pestaña <code>Herramientas</code> y seleccionando el puerto correspondiente</p>
    </step>
    <step>
        <p>Cargar el código en la tarjeta</p>
        <p> Utilizamos el código de ejemplo <code>Blink</code> que se encuentra a continuación</p>
        <code-block lang="c">
        const int salida = 2;
        void setup() {
        // inicializa el pin digital como salida
        pinMode(salida, OUTPUT);
        }
        // la función loop infinitamente
        void loop() {
        // enciende el LED (HIGH es ALTO y es el nivel de voltaje)
        digitalWrite(salida, HIGH);
        // espera 1000 milisegundos = un segundo
        delay(1000);
        // apaga el LED (LOW es BAJO y es el nivel de voltaje)
        digitalWrite(salida, LOW);
        delay(1000);
        }
        </code-block>
    </step>
    <step>
        <p>Compilar y cargar el código en la tarjeta</p>
        <p> Para compilar y cargar el código en la tarjeta, se debe seleccionar el icono de <code>Verificar</code> y <code>Cargar</code> en la parte superior del IDE</p>
    </step>
    <step>
        <p>Ejecutar el código en la tarjeta</p>
        <p>Una vez que el código se haya cargado en la tarjeta, se debe observar el LED parpadeando cada segundo</p>
    </step>
</procedure>

> Se realizó la instalación del IDE de Arduino en Linux Mint y se configuró para utilizar las tarjetas de desarrollo ESP8266 y ESP32. Además, se cargó un código de ejemplo en una tarjeta ESP8266 para verificar que la instalación se realizó correctamente.
> {style=note}
