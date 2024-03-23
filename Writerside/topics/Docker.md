# Docker

Docker es una plataforma de código abierto que permite automatizar el despliegue de aplicaciones dentro de contenedores
de software.
Los contenedores permiten empaquetar una aplicación con todas sus dependencias, lo que garantiza que la aplicación se
ejecute de la misma forma en cualquier entorno.

![Docker](docker.png) {width="700"}

> Realizamos la instalación de Docker en una Raspberry Pi 4 con 4GB de RAM, utilizando el sistema operativo Raspberry Pi OS.
> {style="warning"}

## Instalación
Para instalar Docker en una Raspberry Pi, seguimos los siguientes pasos:

1. Actualizamos la lista de paquetes disponibles y sus versiones.

    ```bash
    sudo apt update
    ```

2. Descargar el siguiente fichero de instalación de Docker.

    ```bash
    curl -fsSL https://get.docker.com -o get-docker.sh
    ```

3. Ejecutar el script de instalación de Docker.

    ```bash
    sudo sh get-docker.sh
    ```

4. Para evitar utilizar el comando `sudo` cada vez que ejecutamos un comando de Docker, agregamos el usuario al
   grupo `docker`.

    ```bash
    sudo usermod -aG docker $USER
    ```

5. Reiniciamos la Raspberry Pi.

    ```bash
    sudo reboot
    ```

6. Verificamos que Docker se ha instalado correctamente ejecutando el siguiente comando.

    ```bash
    docker --version
    ```

7. Creamos un directorio para almacenar los datos de los contenedores que crearemos en el futuro.

    ```bash
    mkdir ~/docker
    ```

8. Cambiamos los permisos del directorio para que el usuario pueda escribir en él.

    ```bash
    sudo chown $USER ~/docker
    ```

## Comandos básicos

{type="wide"}
`docker --version`
: Muestra la versión de Docker instalada.

`docker run hello-world`
: Descarga una imagen de prueba y la ejecuta en un contenedor.

`docker ps`
: Muestra los contenedores en ejecución.

`docker ps -a`
: Muestra todos los contenedores, incluidos los que están detenidos.

`docker stop CONTAINER_ID`
: Detiene un contenedor en ejecución.

`docker start CONTAINER_ID`
: Inicia un contenedor detenido.

`docker rm CONTAINER_ID`
: Elimina un contenedor.

`docker exec -it CONTAINER_ID comando`
: Ejecuta un comando en un contenedor en ejecución.

> Se realizó la instalación de Docker en una Raspberry Pi 4 con 4GB de RAM, lo que permitirá instalar aplicaciones con
> todas sus dependencias y ejecutarlas de la misma forma en cualquier entorno. Además, se creó un directorio para almacenar los datos de los contenedores que se crearán en el futuro.