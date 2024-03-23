# Raspberry Pi OS

Raspberry Pi OS es un sistema operativo basado en Debian, diseñado para la Raspberry Pi. Este sistema operativo es el recomendado para la Raspberry Pi, ya que es el que mejor soporte tiene y el que mejor rendimiento ofrece.

![raspberry](raspberryPi.png) {width="700"}

> Es necesario contar con una tarjeta microSD de al menos 8 GB para instalar Raspberry Pi OS.
> {style = warning}

## Material necesario

- Raspberry Pi 3 o 4
- Tarjeta microSD de al menos 8 GB
- Lector de tarjetas microSD

## Instalación de Raspberry Pi OS
<procedure title ="Pasos para instalar Raspberry Pi OS en la tarjeta microSD" id = "Instalar-Pi-OS" type="steps">
    <step>
        <p> Descargar el instalador de Raspberry Pi OS desde el <a href="https://www.raspberrypi.com/software/">sitio web oficial</a> de Raspberry Pi. </p>
        <img src="descargarInstalador.png" alt="Descargar instalador" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p> Ejcutar el instalador y seleccionar la versión de Raspberry Pi, la versión de Raspberry Pi OS y la tarjeta microSD en la que se instalará el sistema operativo. </p>
        <img src="ejecutarInstalador.png" alt="Ejecutar instalador" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p> Al hacer clic en "Siguiente", el instalador nos arrojará un mensaje para realizar configuraciones adicionales como el cambio de contraseña, la conexión a una red Wi-Fi, la configuración de la región y la zona horaria. </p>
        <note>
            <p style="note">Es importante configurar el SSID y la contraseña de la red Wi-Fi para poder acceder a la Raspberry Pi de forma remota.</p>
        </note>
        <img src="configuraciones.png" alt="Configuraciones" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p> Es importante activar la opción "Activar SSH" para poder acceder a la Raspberry Pi de forma remota. </p>
        <img src="habilitarSSH.png" alt="Habilitar SSH" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p> Al hacer clic en "Instalar", el instalador comenzará a descargar y a instalar Raspberry Pi OS en la tarjeta microSD. </p>
        <img src="escribirSD.png" alt="Instalación" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p> Una vez que la instalación haya finalizado, el instalador nos mostrará un mensaje de confirmación. </p>
        <img src="instalacionCompletada.png" alt="Instalación completada" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p> Retirar la tarjeta microSD del lector y colocarla en la Raspberry Pi. Conectar la Raspberry Pi a la corriente y a un monitor mediante un cable HDMI. </p>
    </step>
</procedure>

> Se realizó la instalación de Raspberry Pi OS en un raspberry Pi 4 con 4GB de RAM.