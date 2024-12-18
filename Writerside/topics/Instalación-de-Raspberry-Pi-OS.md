# Raspberry Pi OS

Raspberry Pi OS es un sistema operativo gratuito basado en Debian, diseñado específicamente para la Raspberry Pi. Es el sistema operativo recomendado por la Fundación Raspberry Pi por su estabilidad, soporte y optimización para el hardware de la Raspberry Pi.

En este documento se describen los pasos para instalar Raspberry Pi OS en una tarjeta microSD y configurar la Raspberry Pi para su uso.

![raspberry](raspberryPi.png) {width="700"}

> **Advertencia:** Es necesario contar con una tarjeta microSD de al menos 8 GB para instalar Raspberry Pi OS.
> {style = warning}

## Material necesario

- Raspberry Pi 3 o 4 (se recomienda la versión 4 para mejor rendimiento)
- Tarjeta microSD de al menos 8 GB (preferentemente clase 10 o UHS-1 para mejor rendimiento)
- Lector de tarjetas microSD (si la computadora no tiene uno integrado)
- Cable HDMI (para conectar la Raspberry Pi a un monitor)
- Fuente de alimentación (para Raspberry Pi 3 o 4, se recomienda una fuente de 5 V 3A)
- Teclado y ratón (si planeas usar el entorno gráfico de usuario)

## Instalación de Raspberry Pi OS
<procedure title ="Pasos para instalar Raspberry Pi OS en la tarjeta microSD" id = "Instalar-Pi-OS" type="steps">
    <step>
        <control>Descargar el instalador</control>
        <p> Accede al <a href="https://www.raspberrypi.com/software/" summary="Sitio oficial para descargar el instalador de Raspberry Pi OS">sitio web oficial de Raspberry Pi</a> y descarga el instalador Raspberry Pi Imager. </p>
        <img src="descargarInstalador.png" alt="Descargar instalador" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <control>Ejecutar el instalador</control>
        <p> Al ejecutar el instalador, se mostrará una ventana con las siguientes opciones: </p>
        <list type="bullet">
            <li>La versión de Raspberry Pi que posees</li>
            <li>La versión de Raspberry Pi OS que deseas instalar</li>
            <li>La tarjeta microSD en la que deseas instalar Raspberry Pi OS</li>
        </list>
        <img src="ejecutarInstalador.png" alt="Ejecutar instalador" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <control>Configuraciones adicionales</control>
        <p> El instalador te permitirá realizar configuraciones importantes como: </p>
        <list type="bullet">
            <li>Cambiar la contraseña predeterminada</li>
            <li>Configurar la conexión a una red wifi</li>
            <li>Establecer la región y la zona horaria</li>
        </list>
        <note>
            <p style="note"><control> Nota:</control> Asegúrate de configurar el SSID y la contraseña de la red wifi para poder acceder a la Raspberry Pi de forma remota.</p>
        </note>
        <img src="configuraciones.png" alt="Configuraciones" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <control>Habilitar acceso remoto</control>
        <p> Es fundamental activar la opción de SSH para poder administrar tu Raspberry Pi de forma remota.</p>
        <img src="habilitarSSH.png" alt="Habilitar SSH" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <control>Iniciar instalación</control>
        <p> Haz clic en "Instalar" y espera a que el proceso de escritura en la tarjeta microSD se complete. </p>
        <img src="escribirSD.png" alt="Instalación" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <control>Finalizar configuración</control>
        <p> Una vez que la instalación haya finalizado, el instalador nos mostrará un mensaje de confirmación, retira la tarjeta microSD del lector y colócala en la Raspberry Pi. </p>
        <img src="instalacionCompletada.png" alt="Instalación completada" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <control>Conectar la Raspberry Pi</control>
        <p> Conecta la Raspberry Pi a un monitor, teclado, ratón y fuente de alimentación para configurarla y comenzar a utilizarla. </p>
    </step>
</procedure>

## Conectarse a una red inalámbrica desde terminal

Para conectarse a una red inalámbrica desde la terminal, es necesario seguir los siguientes pasos:

### 1. Configurar el país de la LAN inalámbrica

En una instalación nueva, se debe especificar el país en el que utiliza su dispositivo. Esto permite que su dispositivo elija las bandas de frecuencia correctas para redes de 5 GHz. Una vez que haya especificado un país de LAN inalámbrica, puede utilizar el módulo de red inalámbrica incorporado de su Raspberry Pi. Para configurar el país, ejecute el siguiente comando:

```bash
sudo raspi-config
```

En el menú de configuración, seleccione `Localisation Options` y luego `WLAN Country`. A continuación, seleccione su país en la lista y presione `Enter`.

![cambiarPais](raspberry_locacion.png) {border-effect="rounded" width="400" thumbnail="true"}

### 2. Verificar la conexión inalámbrica

Para verificar que la conexión inalámbrica está activa, ejecute el siguiente comando:

```bash
nmcli radio wifi
```

Si la conexión inalámbrica está desactivada, el comando mostrará `disabled`. En caso de que la conexión inalámbrica esté activada, mostrará `enabled`.

![verificarConexion](raspberryWifi_estado.png) {border-effect="rounded" width="400" thumbnail="true"}

### 3. Activar la conexión inalámbrica

En caso de que la conexión inalámbrica esté desactivada, actívela con el siguiente comando:

```bash
sudo nmcli radio wifi on
```

### 4. Escanear las redes inalámbricas disponibles

Para ver las redes inalámbricas disponibles, ejecute el siguiente comando:

```bash
nmcli device wifi list
```

Deberías ver una lista de las redes inalámbricas disponibles, incluyendo el nombre de la red (SSID), el modo de seguridad, la intensidad de la señal y si la red está oculta.

```bash
IN-USE  BSSID              SSID            MODE   CHAN  RATE        SIGNAL  BARS    SECURITY
        90:72:40:1B:42:05  myNetwork       Infra  132   405 Mbit/s  89      ▂▄▆█   WPA2
        90:72:42:1B:78:04  myNetwork5G     Infra  11    195 Mbit/s  79      ▂▄▆_   WPA2
        9C:AB:F8:88:EB:0D  Pi Towers       Infra  1     260 Mbit/s  75      ▂▄▆_   WPA2 802.1X
        B4:2A:0E:64:BD:BE  Example         Infra  6     195 Mbit/s  37      ▂▄__    WPA1 WPA2
```

Guarda el nombre de la red (SSID) a la que deseas conectarte.

### 5. Conectarse a una red inalámbrica

Para conectarte a una red inalámbrica utilizando la terminal, ejecuta el siguiente comando, reemplazando `<SSID>` por el nombre de la red a la que deseas conectarte:

```bash
sudo nmcli --ask dev wifi connect <SSID>
```

Se te pedirá que ingreses la contraseña de la red inalámbrica. Una vez que ingreses la contraseña, presiona `Enter` para conectarte a la red.

### 6. Verificar la conexión

Para verificar que la conexión inalámbrica se ha establecido correctamente, ejecuta el siguiente comando:

```bash
nmcli dev wifi list
```
Comprueba que la red a la que te has conectado aparezca un `*` en la columna `IN-USE`.

```bash
IN-USE  BSSID              SSID            MODE   CHAN  RATE        SIGNAL  BARS     SECURITY
*       90:72:40:1B:42:05  myNetwork       Infra  132   405 Mbit/s  89      ▂▄▆█   WPA2
        90:72:42:1B:78:04  myNetwork5G     Infra  11    195 Mbit/s  79      ▂▄▆_   WPA2
        9C:AB:F8:88:EB:0D  Pi Towers       Infra  1     260 Mbit/s  75      ▂▄▆_   WPA2 802.1X
        B4:2A:0E:64:BD:BE  Example         Infra  6     195 Mbit/s  37      ▂▄__    WPA1 WPA2
```

### 7. Apagar la conexión inalámbrica

En caso de que desees apagar la conexión inalámbrica, ejecuta el siguiente comando:

```bash
sudo nmcli radio wifi off
```

## Configurar IP estática

En una red local (Local Area Network o LAN), el router es el encargado de distribuir los datos entre los diferentes dispositivos, pero también de la asignación de direcciones IP, más específicamente del servidor DHCP integrado en el mismo. El DHCP (Dynamic Host Configuration Protocol) asigna direcciones IP automáticamente a los respectivos dispositivos.

Para poder acceder a Raspberry Pi en la red local siempre con la misma dirección, hay que dotarlo de una IP estática. Este tipo de dirección fija suele utilizarse para el mantenimiento remoto del ordenador con el protocolo de red SSH (Secure Shell). De esta forma, ya no es necesario conectar un monitor y dispositivos de entrada por separado. Ahora bien, si el Raspberry Pi dispone de una dirección IP dinámica, será necesario buscarla y encontrarla cada vez que se quiera conectar con el cliente SSH, mientras que con una IP estática siempre se podrá acceder a la Raspberry Pi con la misma dirección para utilizarlo como servidor. Antes de configurar la IP estática, es necesario conocer los siguientes datos:

### 1. Dirección IP actual

Para conocer la dirección IP actual de la Raspberry Pi, abre una terminal y ejecuta el siguiente comando:

```bash
hostname -I
```
Anota la dirección IP que se muestra en la terminal.

### 2. Máscara de red

La máscara más común para redes domésticas es `255.255.255.0` o `/24`, y se puede obtener con el siguiente comando:

```bash
ip -4 addr show
```

Busca la línea que muestre la dirección IP que anotamos anteriormente y la máscara de red se encuentra a la derecha de la dirección IP.

### 3. Puerta de enlace

La puerta de enlace es la dirección IP del router y se puede obtener con el siguiente comando:

```bash
ip route | grep default
```

La dirección IP que aparece a la derecha de `via` es la puerta de enlace. Por ejemplo, `default via 192.168.1.1` dev eth0 indica que tu puerta de enlace es `192.168.1.1`.

### 4. Servidor DNS

El servidor DNS es la dirección IP del servidor que traduce los nombres de dominio en direcciones IP. Para obtener la dirección IP del servidor DNS, ejecuta el siguiente comando:

```bash
cat /etc/resolv.conf
```

La dirección IP que aparece a la derecha de `nameserver` es la dirección IP del servidor DNS.

### 5. Configuración de la IP estática

Para configurar la IP estática, edita el archivo de configuración de la interfaz de red con el siguiente comando:

```bash
sudo nano /etc/dhcpcd.conf
```

Agrega las siguientes líneas al final del archivo:

> **Nota:** Asegúrate de cambiar los valores de `interface`, `static ip_address`, `static routers` y `static domain_name_servers` por los valores propios de tu red.
> {style=note}

```shell
interface eth0
static ip_address=192.168.1.254/24
static routers=192.168.1.1
static domain_name_servers=192.168.1.1
```

Donde:

- `interface eth0` indica la interfaz a configurar. Si usas Wi-Fi, reemplaza **eth0** por **wlan0**.
- `static ip_address` es la IP que asignarás a tu Raspberry Pi (por ejemplo, **192.168.1.254/24**), es recomendable utilizar las últimas direcciones asignables dentro del rango de direcciones IP de tu red.
- `static routers` es la puerta de enlace (normalmente el IP del router).
- `static domain_name_servers` son los servidores DNS que la Raspberry Pi usará para resolver nombres de dominio.

### 6. Guardar y salir

Guarda los cambios realizados en el archivo presionando `Ctrl + O` y luego `Enter`. Para salir del editor, presiona `Ctrl + X`.

### 7. Reservar la dirección IP en el router

Para evitar conflictos de direcciones IP, es recomendable reservar la dirección IP estática en el router. Para ello, accede a la configuración del router y busca la sección de asignación de direcciones IP estáticas. Agrega la dirección IP estática de la Raspberry Pi junto con su dirección MAC y el nombre del dispositivo.

![reservarIP](reservarIP.png) {border-effect="rounded" width="400" thumbnail="true"}

La dirección MAC de la Raspberry Pi se puede obtener con el siguiente comando:

```bash
ip link show eth0
```

> **Nota:** Si usas Wi-Fi, reemplaza **eth0** por **wlan0**.
> {style=note}

### 8. Reiniciar la Raspberry Pi

Reinicia la Raspberry Pi para aplicar los cambios realizados con el siguiente comando:

```bash
sudo reboot
```

Una vez reiniciada la Raspberry Pi, podrás acceder a ella con la dirección IP estática que configuraste. También puedes hacer un ping a la dirección IP o al nombre de host para verificar la conexión.

```bash
ping pi.local
```

> **Nota:** En caso de no contar con un monitor, teclado y ratón, puedes seguir los pasos descritos en el documento [utilizar la Raspberry Pi sin monitor](Utilizar-Raspberry-Pi-sin-monitor.md) para utilizar el Raspberry Pi.
> {style=note}


> **Resultado:** Se realizó la instalación del sistema operativo Raspberry Pi OS en una tarjeta microSD, se configuró la conexión a una red inalámbrica desde la terminal y se estableció una dirección IP estática para la Raspberry Pi.