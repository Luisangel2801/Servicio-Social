# Node Red

Node-RED es una herramienta de programación visual que facilita la conexión de dispositivos y servicios web de manera intuitiva. Basado en un editor de flujos accesible desde el navegador, permite agregar o eliminar nodos, y establecer conexiones entre ellos para crear flujos de trabajo.

![Node-RED](nodeRed.png) {width="700"}

>**Advertencia:** Asegúrate de tener Docker instalado en tu sistema antes de comenzar con la instalación de Node Red. Si aún no has instalado Docker, consulta la guía [aquí](Docker.md "Documentación para instalar Docker").
> {style = warning}

## Instalación

### 1. Actualizar el sistema

Es recomendable actualizar los paquetes de la Raspberry Pi antes de instalar nuevos contenedores.
   
```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Crear un directorio para los datos de Node-RED

Crea un directorio dedicado para almacenar los datos de Node-RED de manera persistente.
   
```bash
mkdir ~/docker/nodered
mkdir ~/docker/nodered/data
```

### 3. Desplegar el contenedor de Node-RED

Ejecuta el siguiente comando para descargar la imagen de Node-RED y crear el contenedor. En este caso, se mapea el puerto 1880 del contenedor al puerto 1880 del host, el cual se utilizará para acceder a la interfaz web de Node-RED.
   
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

### 4. Verificar la instalación

Para asegurarte de que Node-RED se está ejecutando correctamente, lista los contenedores activos:
   
```bash
docker ps
```

Deberías ver una salida similar a la siguiente:
   
```bash
CONTAINER ID   IMAGE              COMMAND             CREATED          STATUS                             PORTS                                       NAMES
a213b917b381   nodered/node-red   "./entrypoint.sh"   36 seconds ago   Up 28 seconds (health: starting)   0.0.0.0:1880->1880/tcp, :::1880->1880/tcp   nodered
```

## Acceder a la interfaz web de Node-RED

Una vez que Node-RED esté en ejecución, puedes acceder a su interfaz web a través de tu navegador.

### 1. Abrir un navegador web

Abre un navegador web en tu computadora y accede a la dirección IP de la Raspberry Pi seguida del puerto 1880:

```bash
http://<IP_DE_LA_RASPBERRY_PI>:1880
```

También puedes acceder a través del nombre de host de tu Raspberry Pi:
    
```bash
http://<NOMBRE_DE_HOST>:1880
```

![Node-RED-Web](nodeRedWeb.png) {border-effect="rounded" width="400" thumbnail="true"}
   
### 2. Interfaz de Node-RED

Al acceder por primera vez, verás la interfaz de Node-RED, que consta de tres secciones principales:

- **Panel de Nodos (Izquierda):** Contiene una variedad de nodos que puedes arrastrar y soltar para construir tus flujos.
- **Área de Trabajo (Centro):** Donde construyes y organizas tus flujos conectando los nodos.
- **Panel de Información (Derecha):** Muestra información sobre los nodos seleccionados y mensajes de depuración.

![Node-RED-Interfaz](nodeRed_interfaz.png) {border-effect="rounded" width="400" thumbnail="true"}

## Primeros pasos

Una vez que hemos accedido a Node-RED, podemos comenzar a crear flujos de trabajo. A continuación, se muestra un ejemplo sencillo de un flujo que recibe un mensaje y lo imprime en la consola.

### 1. Arrastrar nodos al área de trabajo

- Arrastra un nodo `Inject` al área de trabajo. El nodo `Inject` permite inyectar mensajes en un flujo, ya sea haciendo clic en el botón en el nodo, o establecer un intervalo de tiempo entre inyecciones.
- Arrastra un nodo `Debug` al área de trabajo. El nodo `Debug` hace que cualquier mensaje se muestre en la barra lateral de depuración. Por defecto, el nodo muestra los mensajes de payload.

![Node-Red-Flow](nodeRedFlow.png) {border-effect="rounded" width="400" thumbnail="true"}

### 2. Conectar los nodos

Conecta el nodo **Inject** al nodo **Debug** haciendo clic en el círculo blanco en la parte lateral del nodo **Inject** y arrastrando la línea al nodo **Debug**. 

![Node-Red-Nodos](nodeRed_nodos.png) {border-effect="rounded" width="400" thumbnail="true"}

### 3. Configurar el nodo Inject

Selecciona el nodo **Inject** y haz doble clic para abrir su configuración. Puedes cambiar el tipo de mensaje y el intervalo de tiempo en el que se envía el mensaje. En este caso, cambiaremos el Payload a `Hello World` y dejaremos el resto de las opciones por defecto. Haz clic en **Done** para guardar los cambios.

![Node-Red-Inject](nodeRed_inject.png) {border-effect="rounded" width="400" thumbnail="true"}

### 4. Ejecutar el flujo

Haz clic en el botón **Deploy** en la esquina superior derecha para guardar y ejecutar el flujo. 

![Node-Red-Deploy](nodeRed_deploy.png) {border-effect="rounded" width="400" thumbnail="true"}

### 5. Probar el flujo

Una vez que el flujo esté desplegado, haz clic en el botón del nodo **Inject** para enviar un mensaje. Verás el mensaje `Hello World` en la barra lateral de depuración.

![Node-Red-Debug](nodeRed_debug.png) {border-effect="rounded" width="400" thumbnail="true"}

### 6. Explorar más nodos

Node-RED cuenta con una amplia variedad de nodos integrados y nodos de terceros que puedes instalar para ampliar su funcionalidad. Puedes explorar y experimentar con diferentes nodos para crear flujos más complejos y personalizados. Para instalar nuevos nodos, haz clic en el menú en la esquina superior derecha y selecciona **Manage palette**.

![Node-Red-Palette](nodeRed_palette.png) {border-effect="rounded" width="400" thumbnail="true"}

Puedes buscar nodos en la pestaña **Install** y hacer clic en el botón **Install** para agregarlos a tu paleta de nodos.

![Node-Red-Install](nodeRed_install.png) {border-effect="rounded" width="400" thumbnail="true"}

> **Resultado:** Se realizó la instalación de Node-RED en un contenedor de Docker, este método facilita la instalación y configuración de Node-RED en cualquier sistema operativo que soporte Docker, además de permitir la portabilidad de la aplicación entre diferentes entornos.

<seealso>
    <category ref="external">
        <a href="https://nodered.org/docs/">Documentación oficial de Node-RED</a>
    </category>
</seealso>



