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
            <p style="note"><control>Consejo importante:</control> Asegúrate de configurar el SSID y la contraseña de la red wifi para poder acceder a la Raspberry Pi de forma remota.</p>
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

> En caso de no contar con un monitor, teclado y ratón, puedes seguir los pasos descritos en el documento [utilizar la Raspberry Pi sin monitor](Utilizar-Raspberry-Pi-sin-monitor.md).
> {style=note}

> Se realizó la instalación de Raspberry Pi OS en un raspberry Pi 4 con 4 GB de RAM.