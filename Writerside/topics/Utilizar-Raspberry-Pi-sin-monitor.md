# Utilizar Raspberry Pi sin monitor

## Conectar via SSH

Una vez que se haya instalado Raspberry Pi OS en la tarjeta microSD, es posible acceder a la Raspberry Pi de forma remota mediante SSH. A continuación se detallan los pasos necesarios:

> En caso de no haber agregado las credenciales para la conexión a la red durante la [instalación de Raspberry Pi OS](Instalación-de-Raspberry-Pi-OS.md "Documentación para la instalación de Raspberry Pi OS"), es necesario conectar la Raspberry Pi mediante un cable Ethernet.

1. **Obtener la dirección IP de la Raspberry Pi**

    Para conocer la dirección IP de la Raspberry Pi, es necesario acceder al panel de administración del router o utilizar una aplicación como Fing para escanear la red local.

    ![Fing](fing.png) {border-effect="rounded" width="400" thumbnail="true"}

2. **Acceder a la Raspberry Pi mediante SSH**

    Una vez que se conozca la dirección IP de la Raspberry Pi, es posible acceder a ella mediante SSH. Para ello, abre una terminal y ejecuta el siguiente comando, reemplazando la dirección IP de ejemplo por la dirección correcta de tu Raspberry Pi.

    > La dirección IP utilizada en este ejemplo es solo referencial. Sustitúyela por la IP que se obtuvo en el paso anterior. {style = note}
    ```bash
    ssh pi@10.213.1.89
    ```

3. **Confirmar la conexión**

    Al ejecutar el comando, aparecerá un mensaje solicitando agregar la clave RSA del servidor. Es necesario escribir `yes` y presionar "Enter". A continuación, se solicitará la contraseña del usuario `pi` que configuraste durante la instalación del sistema operativo.

    ![SSH](ssh.png) {border-effect="rounded" width="400" thumbnail="true"}

4. **Acceso al terminal**

    Después de ingresar la contraseña correctamente, se mostrará el prompt de la Raspberry Pi, lo que indica que ahora puedes ejecutar comandos en el sistema de manera remota.

    ![Promt Raspberry](promptRaspberry.png) {border-effect="rounded" width="400" thumbnail="true"}

5. **Ejecutar comandos remotamente**

    Ya puedes utilizar la terminal de la Raspberry Pi como si estuvieras trabajando directamente sobre ella, sin necesidad de un monitor.

## Habilitar el acceso remoto a la interfaz gráfica

Si deseas acceder a la interfaz gráfica de la Raspberry Pi de forma remota, necesitarás instalar un servidor VNC. A continuación se explica cómo configurarlo:

1. **Abrir la configuración de la Raspberry Pi**

    Desde la conexión SSH, es necesario ejecutar el siguiente comando para abrir la configuración de la Raspberry Pi:

    ```bash
    sudo raspi-config
    ```

2. **Activar el servidor VNC**

    Navegar hasta la opción "Interfacing Options" y seleccionar "VNC" para habilitar el servidor VNC.

    ![VNC](vnc.png) {border-effect="rounded" width="400" thumbnail="true"}

3. **Confirmar la habilitación de VNC**

    Se mostrará un mensaje de confirmación para activar el servicio. Selecciona "Yes" y presiona "Enter" para habilitar el servidor VNC en tu Raspberry Pi.

    ![Habilitar VNC](habilitarVNC.png) {border-effect="rounded" width="400" thumbnail="true"}

4. **Instalar un cliente VNC en tu computadora**

    Una vez que el servidor VNC esté habilitado, necesitarás un cliente VNC para acceder a la interfaz gráfica de la Raspberry Pi. Una opción recomendada es RealVNC, el cual puedes descargarlo desde [aquí](https://www.realvnc.com/es/connect/download/viewer/).

    ![RealVNC](realVNC.png) {border-effect="rounded" width="400" thumbnail="true"}

5. **Conectar mediante RealVNC**

    Abre la aplicación RealVNC e ingresa la dirección IP de la Raspberry Pi junto con el nombre de usuario y la contraseña que configuraste durante la instalación del sistema operativo.

    ![RealVNC](ingresarVNC.png) {border-effect="rounded" width="400" thumbnail="true"}

6. **Acceder a la interfaz gráfica**

   Al hacer clic en "Conectar", se abrirá la interfaz gráfica de la Raspberry Pi en la pantalla de tu computadora.

    ![Interfaz gráfica](interfazGrafica.png) {border-effect="rounded" width="400" thumbnail="true"}

> Se logró la conexión remota a la Raspberry Pi mediante SSH para el acceso a la terminal y VNC para la interfaz gráfica.