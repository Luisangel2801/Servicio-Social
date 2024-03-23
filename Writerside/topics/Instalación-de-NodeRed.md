# Node Red

Node-RED es una herramienta de programación visual para conectar dispositivos, servicios y aplicaciones de Internet de las Cosas. Es una herramienta de código abierto que se ejecuta en Node.js.

![Node-RED](nodeRed.png) {width="700"}

> Es importante haber instalado previamente docker en el sistema operativo.
> {style = warning}

## Instalación

1. **Actualizar el sistema**
   
    Antes de instalar Node-RED, es recomendable actualizar el sistema. Para ello, ejecuta el siguiente comando en la terminal:
   
    ```bash
    sudo apt update && sudo apt upgrade -y
    ```

2. **Crear directorio para los datos de Node-RED**
   
    Crea los directorios en el sistema para almacenar los datos de Node-RED. Para ello, ejecuta los siguientes comandos:
   
    ```bash
    mkdir ~/docker/nodered
    mkdir ~/docker/nodered/data
    ```

3. **Descargar la imagen de Node-RED**
   
    Corremos el siguiente comando para descargar la imagen de Node-RED.
   
    ```bash
    docker run -itd -p 1880:1880 -v ~/docker/nodered/data:/data --name nodered nodered/node-red
    ```

    {type="medium"}
    `docker run`
    : Comando para crear y ejecutar un contenedor.

    `-itd`
    : Permite la interacción con el contenedor y ejecutarlo en segundo plano.

    `-p`
    : Mapea el puerto 1880 del contenedor al puerto 1880 del host.

    `-v`
    : Monta el directorio `~/docker/nodered/data` del host en el directorio `/data` del contenedor.

    `--name nodered`
    : Asigna un nombre al contenedor.

    `nodered/node-red`
    : Especifica la imagen de Node-RED que se utilizará.

4. **Acceder a Node-RED**
   
    Para acceder a Node-RED, abre un navegador web y escribe la dirección IP de la Raspberry Pi seguida del puerto 1880.
   
    ```bash
    http://<dirección IP de la Raspberry Pi>:1880
    ```
   
    ![Node-RED](nodeRedWeb.png) {border-effect="rounded" width="400" thumbnail="true"}
   
    > Para conocer nuestra dirección IP, ejecutamos `hostname -I` en la terminal de la Raspberry Pi.
    {style="note"}


## Primeros pasos

Una vez que hemos accedido a Node-RED, podemos comenzar a crear flujos de trabajo. Para ello, arrastramos los nodos desde 
la barra lateral izquierda al área de trabajo central y los conectamos entre sí, para ejecutar las acciones deberemos hacer clic en el botón `Deploy`.


![Node-RED](nodeRedFlow.png) {border-effect="rounded" width="400" thumbnail="true"}

> Para más información sobre cómo utilizar Node-RED, visita la [documentación oficial](https://nodered.org/docs/).

## Detener y eliminar el contenedor

Para detener y eliminar el contenedor de Node-RED, ejecuta los siguientes comandos en la terminal:

```bash
docker stop nodered
docker rm nodered
```

> Se realizó la instalación de Node-RED en un contenedor de Docker, este método facilita la instalación y configuración de Node-RED en cualquier sistema operativo que soporte Docker, además de permitir la portabilidad de la aplicación.




