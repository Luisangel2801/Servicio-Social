# Instalación de Docker

Docker es una plataforma de código abierto que permite automatizar el despliegue de aplicaciones dentro de contenedores
de software.
Los contenedores permiten empaquetar una aplicación con todas sus dependencias, lo que garantiza que la aplicación se
ejecute de la misma forma en cualquier entorno.

![Docker](docker.png) {width="700"}

> Esta guía detalla cómo realizar la instalación de Docker en una Raspberry Pi 4 con 4 GB de RAM, utilizando el sistema operativo Raspberry Pi OS.

## Instalación

Para instalar Docker en una Raspberry Pi, sigue estos pasos:

### 1. Actualizar la lista de paquetes disponibles

Primero, actualiza la lista de paquetes disponibles en el sistema para asegurarte de que estás obteniendo las versiones más recientes.

```bash
sudo apt update
```

### 2. Descargar el script de instalación de Docker

Utiliza `curl` para descargar el script de instalación oficial de Docker.

```bash
curl -fsSL https://get.docker.com -o get-docker.sh
```

### 3. Ejecutar el script de instalación

Ejecuta el script descargado para instalar Docker. Este script automáticamente configura Docker en el raspberry Pi.

```bash
sudo sh get-docker.sh
```

### 4. Agregar `docker` al grupo de usuarios

Para evitar utilizar el comando `sudo` cada vez que ejecutamos un comando de Docker, agregamos nuestro usuario al grupo `docker`.

```bash
sudo usermod -aG docker $USER
```

> **Nota:** Después de agregar tu usuario al grupo `docker`, es necesario reiniciar la Raspberry Pi para que los cambios tengan efecto.

### 5. Reiniciar la Raspberry Pi

Para que los cambios surtan efecto, reinicia el sistema.

```bash
sudo reboot
```

### 6. Verificar la instalación

Una vez que la Raspberry Pi se reinicie, verifica que Docker esté instalado correctamente ejecutando el siguiente comando para comprobar la versión instalada:

```bash
docker --version
```

### 7. Crear un directorio para almacenar datos de contenedores

Es recomendable crear un directorio específico donde se almacenarán los datos de los contenedores que crees en el futuro.

```bash
mkdir ~/docker
```

### 8. Cambiar los permisos del directorio

Asegúrate de que el usuario tenga permisos de escritura en el directorio creado, para evitar problemas al gestionar los contenedores.

```bash
sudo chown $USER ~/docker
```

## Extraer una imagen de Docker Hub

### 1. Buscar una imagen

Puedes buscar imágenes de Docker en el [sitio web de Docker Hub](https://hub.docker.com/ "Página oficial de Docker Hub"), usa la barra de búsqueda para encontrar la imagen que deseas, o puede buscarlas directamente desde el terminal utilizando el siguiente comando:

```bash
docker search <nombre_imagen>
```

Esto devolverá una lista de imágenes disponibles en Docker Hub que coinciden con el término de búsqueda. Para este ejemplo buscaremos la imagen `hello-world`:

```bash
docker search hello-world
```

La salida mostrará una lista de imágenes relacionadas con `hello-world`, incluyendo el nombre de la imagen, la descripción y el número de estrellas.

![DockerSearch](docker_search.png) {border-effect="rounded" width="400" thumbnail="true"}

### 2. Descargar una imagen

Para descargar una imagen de Docker Hub, utiliza el comando `docker pull` seguido del nombre de la imagen y la etiqueta correspondiente.

![DockerPull](docker_pull.png) {border-effect="rounded" width="400" thumbnail="true"}

```bash
docker pull hello-world
```

> **Nota:** Si no se especifica una etiqueta, Docker descargará la última versión de la imagen por defecto.

### 3. Verificar la imagen descargada

Para verificar que la imagen se ha descargado correctamente, puedes listar las imágenes locales con el siguiente comando:

```bash
docker images -a
```

Esto mostrará una lista de las imágenes descargadas, incluyendo el nombre de la imagen, la etiqueta, el ID de la imagen, el tamaño y cuándo se creó.

![DockerImages](docker_images.png) {border-effect="rounded" width="400" thumbnail="true"}

### 4. Ejecutar el contenedor de la imagen

Para ejecutar un contenedor basado en la imagen descargada, utiliza el comando `docker run` seguido del nombre de la imagen.

```bash
docker run hello-world
```

Esto iniciará un contenedor con la imagen `hello-world` y mostrará un mensaje de prueba en la consola.

![DockerRun](docker_run.png) {border-effect="rounded" width="400" thumbnail="true"}

> **Nota:** Si la imagen no está disponible localmente, Docker la descargará automáticamente antes de ejecutar el contenedor.

### 5. Verificar el contenedor en ejecución

Para verificar los contenedores en ejecución, utiliza el siguiente comando:

```bash
docker ps -a
```

Esto mostrará una lista de los contendores en ejecución, incluyendo el ID del contenedor, el nombre de la imagen, el estado, el puerto y cuándo se creó.

![DockerPS](docker_ps.png) {border-effect="rounded" width="400" thumbnail="true"}

### 6. Detener y eliminar el contenedor

Para detener y eliminar el contenedor en ejecución, utiliza los siguientes comandos:

```bash
docker stop <CONTAINER_ID>
docker rm <CONTAINER_ID>
```

Reemplaza `<CONTAINER_ID>` con el ID del contenedor que deseas detener y eliminar. También puedes utilizar el nombre del contenedor en lugar del ID.

![DockerStop](docker_stop.png) {border-effect="rounded" width="400" thumbnail="true"}

> **Nota:** Si el contenedor ya está detenido, no es necesario ejecutar el comando `docker stop`.

### 7. Eliminar una imagen

Para eliminar una imagen de Docker, utiliza el comando `docker rmi`.

```bash
docker rmi <IMAGE_ID>:<TAG>
```

Reemplaza `<IMAGE_ID>` con el ID de la imagen que deseas eliminar o el nombre de la imagen y la etiqueta correspondiente.

![DockerRMI](docker_rmi.png) {border-effect="rounded" width="400" thumbnail="true"}

## Comandos básicos de Docker

{type="wide"}
`docker --version`
: Muestra la versión de Docker instalada.

`docker ps`
: Muestra los contenedores en ejecución.

`docker ps -a`
: Muestra todos los contenedores, incluidos los que están detenidos.

`docker restart NAME`
: Reinicia un contenedor en ejecución.

`docker stop NAME`
: Detiene un contenedor en ejecución.

`docker start NAME`
: Inicia un contenedor detenido.

`docker rm NAME`
: Elimina un contenedor detenido.

`docker exec -it NAME comando`
: Ejecuta un comando en un contenedor en ejecución.

`docker pull IMAGE_NAME`
: Descarga una imagen de Docker Hub.

`docker images -a`
: Muestra las imágenes que se han descargado.

`docker rmi IMAGE_ID`
: Elimina una imagen por su ID.

`docker volume ls`
: Muestra los volúmenes de Docker que se han creado.

`docker volume rm VOLUME_NAME`
: Elimina un volumen por su nombre.

> Se realizó la instalación de Docker en una Raspberry Pi 4 con 4 GB de RAM, utilizando el sistema operativo Raspberry Pi OS. Se descargó una imagen de Docker Hub, se ejecutó un contenedor y se realizaron comandos básicos de Docker.