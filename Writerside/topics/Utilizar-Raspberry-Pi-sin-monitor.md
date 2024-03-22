# Utilizar Raspberry Pi sin monitor

## Conectar via SSH

Una vez que se haya instalado Raspberry Pi OS en la tarjeta microSD, es posible acceder a la Raspberry Pi de forma remota mediante SSH. Para ello, es necesario seguir los siguientes pasos:

1. Para conocer la dirección IP de la Raspberry Pi, es necesario acceder al panel de administración del router o utilizar una aplicación como Fing para escanear la red local.

    ![Fing](fing.png) {border-effect="rounded" width="400" thumbnail="true"}

2. Una vez que se conozca la dirección IP de la Raspberry Pi, es posible acceder a ella mediante SSH. Para ello, es necesario abrir una terminal y ejecutar el siguiente comando:

    > La dirección IP es un ejemplo, es necesario reemplazarla por la dirección IP de la Raspberry Pi.
    > {style = note}
    ```bash
    ssh pi@10.213.1.89
    ```

3. Al ejecutar el comando, se mostrará un mensaje de confirmación para agregar la clave RSA del servidor. Es necesario escribir "yes" y presionar "Enter". Posteriormente, se solicitará la contraseña del usuario "pi" que se configuró durante la instalación.

    ![SSH](ssh.png) {border-effect="rounded" width="400" thumbnail="true"}

4. Una vez que se haya ingresado la contraseña, se mostrará el prompt de la Raspberry Pi.

    ![Promt Raspberry](promptRaspberry.png) {border-effect="rounded" width="400" thumbnail="true"}

5. Ahora es posible ejecutar comandos en la Raspberry Pi de forma remota.

## Habilitar el acceso remoto a la interfaz gráfica

Para habilitar el acceso remoto a la interfaz gráfica de la Raspberry Pi, es necesario instalar un servidor VNC. Para ello, es necesario seguir los siguientes pasos:

1. Desde la conexión SSH, es necesario ejecutar el siguiente comando para abrir la configuración de la Raspberry Pi:

    ```bash
    sudo raspi-config
    ```

2. Navegar hasta la opción "Interfacing Options" y seleccionar "VNC".

   ![VNC](vnc.png) {border-effect="rounded" width="400" thumbnail="true"}

3. Al seleccionar "VNC", se mostrará un mensaje de confirmación para habilitar el servicio. Es necesario seleccionar "Yes" y presionar "Enter".

   ![Habilitar VNC](habilitarVNC.png) {border-effect="rounded" width="400" thumbnail="true"}

4. Una vez que se haya habilitado el servicio de VNC, es necesario instalar un cliente de VNC en la computadora desde la que se desea acceder a la Raspberry Pi. Una opción recomendada es RealVNC, el cual se puede descargar desde el siguiente [enlace](https://www.realvnc.com/es/connect/download/viewer/).

   ![RealVNC](realVNC.png) {border-effect="rounded" width="400" thumbnail="true"}

5. Al abrir RealVNC, es necesario ingresar la dirección IP de la Raspberry Pi y el nombre de usuario y contraseña que se configuraron durante la instalación.

   ![RealVNC](ingresarVNC.png) {border-effect="rounded" width="400" thumbnail="true"}

6. Al hacer clic en "Conectar", se mostrará la interfaz gráfica de la Raspberry Pi.

   ![Interfaz gráfica](interfazGrafica.png) {border-effect="rounded" width="400" thumbnail="true"}

> Se realizó la conexión a la Raspberry Pi de forma remota mediante SSH y VNC.