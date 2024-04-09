# Linux Mint

Linux Mint es una distribución de Linux basada en Ubuntu que ofrece una experiencia de usuario amigable y fácil de usar. En este documento se describen los pasos necesarios para instalar Linux Mint en un equipo con Windows utilizando dual boot.

## Requisitos

- Un equipo con Windows instalado.
- Un dispositivo USB con al menos 8 GB de almacenamiento.
- Una imagen ISO de Linux Mint.
- Un programa para crear un USB booteable, como Balena Etcher o Rufus.
- Espacio libre en el disco duro para la instalación de Linux Mint.
- Conexión a Internet.

## Instalación de Linux Mint

<procedure title="Pasos para instalar Linux Mint en un equipo con Windows" id="Instalar-Linux-Mint" type="steps">
    <step>
        <p><control>Descarga la imagen ISO de Linux Mint</control> </p>
        <p>Para descargar la imagen ISO de Linux Mint, visita la página oficial de Linux Mint en el siguiente enlace: <a href="https://linuxmint.com/download.php">Descargar Linux Mint</a></p>
        <img src="LinuxMintPaginaPrincipal.png" alt="Descarga de Linux Mint" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Selecciona la edición de Linux Mint</control></p>
        <p> En la página de descarga, selecciona la edición de Linux Mint que deseas instalar. En esta computadora se escogió la edición Cinnamon, pero también puedes elegir entre otras ediciones como MATE o Xfce.</p>
            <list>
                <li> Cinnamon - Es fluida y fácil de usar.</li>
                <li> MATE - Es una edición más ligera y rápida de Linux Mint.</li>
                <li> Xfce - Es una edición ligera y personalizable de Linux Mint.</li>
            </list>
        <img src="LinuxMintEdiciones.png" alt="Selección de edición" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Crea un USB booteable</control></p>
        <p>Una vez seleccionada y descargada la imagen ISO de Linux Mint, crea un USB booteable utilizando un programa como Balena Etcher o Rufus.</p>
        <!--<img src="BalenaEtcher.png" alt="Balena Etcher" width="400" border-effect="rounded" thumbnail="true"/>-->
    </step>
    <step>
        <p><control>Arrancar Linux Mint</control></p>
        <p>Reinicia el equipo y accede a la configuración de la BIOS o UEFI para cambiar el orden de arranque y seleccionar el USB como dispositivo de arranque, esto varía dependiendo del fabricante de la computadora.</p>
        <img src="BIOS.png" alt="Configuración de la BIOS" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Iniciar la instalación de Linux Mint</control></p>
        <p>Una vez que el equipo arranque desde el USB, selecciona la opción de instalar Linux Mint en el menú de inicio.</p>
        <img src="InstalacionLinuxMint.png" alt="Instalación de Linux Mint" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Configurar la instalación</control></p>
        <p> Seleccione el idioma, la distribución del teclado y otras configuraciones de la instalación.</p>
        <img src="idioma.png" alt="Configuración del idioma" width="400" border-effect="rounded" thumbnail="true"/>
        <img src="teclado.png" alt="Configuración del teclado" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Tipo de instalación</control></p>
        <p> En este apartado existe tres opciones de instalación:</p>
        <list>
            <li> Instalar Linux Mint junto a Windows - Esta opción permite instalar Linux Mint en el mismo disco duro que Windows.</li>
            <li> Borrar disco e instalar Linux Mint - Esta opción elimina todo el contenido del disco duro y lo reemplaza con Linux Mint.</li>
            <li> Otras opciones - Esta opción permite realizar una instalación personalizada de Linux Mint.</li>
        </list>
        <p> En este caso se seleccionó la opción de instalar Linux Mint junto a Windows.</p>
        <img src="tipoInstalacion.png" alt="Tipo de instalacion" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control> Crear usuario</control></p>
        <p> Crea un usuario y una contraseña para acceder a Linux Mint.</p>
        <img src="usuario.png" alt="Crear usuario" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Finalizar la instalación</control></p>
        <p> Espera a que la instalación de Linux Mint finalice y reinicia el equipo.</p>
        <img src="instalacionFinalizada.png" alt="Instalación finalizada" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
</procedure>

## Post-instalación
Despues de instalar Linux Mint, es necesario realizar algunas configuraciones adicionales para configurar el grub.

<procedure title="Configuración de Grub" id="Configuracion-Grub" type="steps">
    <step>
        <p><control> Selección del sistema operativo por defecto</control></p>
        <p>Abre el archivo de configuración de Grub en un editor de texto:</p>
        <code>sudo nano /etc/default/grub</code>
        <p> Podemos especificar con que sistema operativo queremos que inicie por defecto, para ello modificamos la siguiente línea:</p>
        <code>GRUB_DEFAULT</code>
        <warning> El valor de Windows depende de la posición en la lista de sistemas operativos que aparecen en el menú al iniciar el equipo. Es importante recordar que la lista comienza en 0.</warning>
        <list>
            <li>
                <p>Si queremos que inicie con Windows, cambiamos el valor a 2.</p>
                <code>GRUB_DEFAULT=2</code>
            </li>
            <li>
                <p>Si queremos que inicie con Linux Mint, cambiamos el valor a 0.</p>
                <code>GRUB_DEFAULT=0</code>
            </li>
        </list>
    </step>
    <step>
        <p><control>Configuración del tiempo de espera</control></p>
        <p>Podemos configurar el tiempo de espera para seleccionar el sistema operativo en el arranque. En el archivo de configuración de Grub, busca la línea:</p>
        <code>GRUB_TIMEOUT</code>
        <p>Por ejemplo, si queremos que el tiempo de espera sea de 10 segundos, cambiamos el valor a 10:</p>
        <code>GRUB_TIMEOUT=10</code>
    </step>
    <step>
        <p><control>Guardar los cambios</control></p>
        <p>Guarda los cambios y cierra el editor de texto. Luego, ejecuta el siguiente comando para aplicar los cambios:</p>
        <code>sudo update-grub</code>
    </step>
</procedure>

## Configuración adional

Una vez instalado Linux Mint, es necesario realizar algunas configuraciones básicas para personalizar el sistema operativo y asegurar su correcto funcionamiento.

<procedure title="Configuración de Linux Mint" id="Configuracion-Linux-Mint" type="steps">
    <step>
        <p><control>Configurar la red</control></p>
        <p>Configura la red Wi-Fi o Ethernet desde el menú de configuración para poder acceder a Internet.</p>
        <img src="configuracionRed.png" alt="Configuración de red" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Actualizar el sistema</control></p>
        <p>Abre la terminal y ejecuta el siguiente comando para actualizar el sistema:</p>
        <code>sudo apt update && sudo apt upgrade</code>
    </step>
    <step>
        <p><control>Instalar controladores adicionales</control></p>
        <p>Si es necesario, instala controladores adicionales para tu hardware. Puedes hacerlo desde el "Gestor de controladores" en el menú de inicio.</p>
        <img src="gestorControladores.png" alt="Gestor de controladores" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Personalizar el escritorio</control></p>
        <p>Personaliza el escritorio de Linux Mint cambiando el fondo de pantalla, los iconos, el tema y otras configuraciones desde el menú de configuración.</p>
        <img src="configuracion.png" alt="Configuración" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Instalar aplicaciones</control></p>
        <p>Instala las aplicaciones que necesites desde la "Tienda de aplicaciones" o utilizando el gestor de paquetes de Linux Mint.</p>
        <img src="tiendaAplicaciones.png" alt="Tienda de aplicaciones" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
</procedure>

> Se realizó la instalación de Linux Mint 21.3 "Virginia" en una computadora con Windows 10.
> {style = note}