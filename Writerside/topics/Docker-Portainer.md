# Docker Portainer

Portainer es una interfaz web que nos permite simplificar la administración de Docker. Con Portainer, podemos gestionar contenedores, imágenes y volúmenes de Docker de forma visual e intuitiva sin necesidad de depender exclusivamente de la línea de comandos. Además, Portainer nos proporciona un panel de control con estadísticas en tiempo real y nos permite configurar usuarios y roles para controlar el acceso a los recursos de Docker.

![Portainer](portainer.png) {width="700"}

>**Advertencia:** Asegúrate de tener Docker instalado en tu sistema antes de comenzar con la instalación de Portainer. Si aún no has instalado Docker, consulta la guía [aquí](Docker.md "Documentación para instalar Docker").
> {style = warning}

## Instalación de Portainer

Para instalar Portainer, sigue estos pasos:

### 1. Actualizar Docker

Antes de instalar Portainer, asegúrate de tener Docker instalado y actualizado en tu sistema. Puedes seguir la guía de [instalación de Docker](Instalación-de-Docker.md "Documentación para instalar Docker") si aún no lo has hecho. En caso de que ya tengas Docker instalado, puedes verificar su versión con el siguiente comando:

```bash
    docker --version
```

### 2. Crear un volumen para persistir los datos de Portainer

En primer lugar, creamos un volumen Docker que contendrá los datos gestionados por el servidor Portainer:

```bash
    docker volume create portainer_data
```

A continuación, verificamos que el volumen Docker llamado ‘Portainer_data’ existe:

```bash
    docker volume ls
```

### 3. Desplegar Portainer como un contenedor

Ejecuta el siguiente comando para descargar e instalar la imagen de Portainer Community Edition y crear un contenedor con ella:

```bash
    docker run -itd -p 8000:8000 -p 9000:9000 --name=portainer --restart=always -v /var/run/docker.sock:/var/run/docker.sock -v /docker/portainer:/data portainer/portainer-ce
```
**Explicación de los parámetros:**

{type="medium"}
`-itd`
: Ejecuta el contenedor en modo interactivo y en segundo plano.

`-p`
: Mapea los puertos 8000 y 9000 del contenedor al host.

`--name=portainer`
: Asigna el nombre "portainer" al contenedor.

`--restart=always`
: Indica que el contenedor se iniciará automáticamente al arrancar la Raspberry Pi.

`-v`
: Permite a Portainer comunicarse con el daemon de Docker para administrar los contenedores.

`portainer/portainer-ce`
: Especifica la imagen de Portainer Community Edition.

### 4. Verificar la instalación

Para asegurarte de que Portainer se está ejecutando correctamente, puedes listar los contenedores activos:

```bash
    docker ps
```

Deberías ver un contenedor llamado "portainer" en la lista.

## Acceso a la interfaz web de Portainer

Si el servidor Portainer se ha instalado correctamente, la interfaz web de Portainer es accesible en el host local en el puerto especificado. En nuestro caso, es el puerto 9000. Para acceder a la interfaz web de Portainer, sigue estos pasos:

### 1. Abre tu navegador web

En la barra de direcciones, escribe la dirección IP de tu Raspberry Pi o su nombre de host, seguido del puerto 9000:

```bash
    http://<IP_de_la_Raspberry_Pi>:9000
```
También puedes acceder a través del nombre de host de tu Raspberry Pi:

```bash
    http://<nombre_de_host>.local:9000
```

### 2. Configura el usuario y la contraseña de administrador

La primera vez que accedas a la interfaz web de Portainer, deberás configurar un usuario y una contraseña de administrador. Introduce los datos solicitados y haz clic en "Create user".

![Configuración de usuario](portainer_login.png) {border-effect="rounded" width="400" thumbnail="true"}

### 3. Seleccionar el entorno de Docker

Después de iniciar la sesión como usuario administrador, llegamos al asistente de configuración rápida de la interfaz web de Portainer. Además del entorno Docker local, se pueden añadir entornos remotos. En este caso, seleccionamos "Get Started" para configurar el entorno de Docker local.

![Portainer Environment](portainer_environment.png) {border-effect="rounded" width="400" thumbnail="true"}

## Uso de Portainer

Con Portainer configurado, ahora puedes utilizar su interfaz para gestionar tus contenedores y recursos de Docker. 

### 1. Panel de control (Dashboard)

El panel de control de Portainer muestra una visión general de los contenedores, imágenes, volúmenes y redes de Docker en tu sistema. Puedes ver estadísticas en tiempo real y acceder a las diferentes secciones de administración.

![Portainer Dashboard](portainer_dashboard.png) {border-effect="rounded" width="400" thumbnail="true"}

### 2. Gestión de contenedores

Portainer te permite gestionar tus contenedores de Docker de forma sencilla. Algunas de las acciones que puedes realizar son:

- **Ver lista de contenedores**: Navega a la sección "Containers" para ver todos los contenedores.
- **Iniciar/Detener contenedores**: Usa los botones de acción para iniciar, detener o reiniciar contenedores.
- **Crear nuevos contenedores**: Haz clic en "Add Container" para desplegar nuevos contenedores.
- **Eliminar contenedores**: Elimina contenedores que ya no necesites.
- **Terminal de contenedores**: Accede a la terminal de un contenedor para ejecutar comandos. 

![Portainer Containers](portainer_gestion.png) {border-effect="rounded" width="400" thumbnail="true"}

### 3. Gestión de imágenes

En la sección "Images", puedes ver todas las imágenes de Docker disponibles en tu sistema. Puedes buscar imágenes en Docker Hub, descargarlas y crear contenedores a partir de ellas.

![Portainer Images](portainer_images.png) {border-effect="rounded" width="400" thumbnail="true"}

### 4. Gestión de volúmenes

Portainer también te permite gestionar volúmenes de Docker. Puedes ver los volúmenes existentes, crear nuevos volúmenes y asignarlos a contenedores.

![Portainer Volumes](portainer_volumes.png) {border-effect="rounded" width="400" thumbnail="true"}

### 5. Gestión de usuarios y roles

En la sección "User-related", puedes gestionar usuarios y roles en Portainer. Puedes añadir nuevos usuarios, asignarles roles y configurar permisos de acceso.

![Portainer Users](portainer_user.png) {border-effect="rounded" width="400" thumbnail="true"}

## Acciones comunes

### 1. Desplegar un contenedor

<procedure title ="Pasos para desplegar un nuevo contenedor desde Portainer" id = "Crear-Contenedor" type="steps">
    <step>
        <p> Haz clic en la sección <strong>Containers</strong> en la barra lateral izquierda de la interfaz de Portainer. </p>
    </step>
    <step>
        <p> Haz clic en <strong>Add Container</strong> en la parte superior derecha de la página. </p>
    </step>
    <step>
        <p> Introduce un nombre para el contenedor y selecciona la imagen que deseas utilizar. </p>
    </step>
    <step>
        <p> Configura los puertos, volúmenes y variables de entorno según tus necesidades. </p>
    </step>
    <step>
        <p> Haz clic en <strong>Deploy the container</strong> para crear el contenedor. </p>
    </step>
    <img src="portainer_crearContainer.png" alt="Portainer Deploy Container" width="400" border-effect="rounded" thumbnail="true"/>
</procedure>

### Actualizar un contenedor

<procedure title ="Pasos para actualizar un contenedor desde Portainer" id = "Actualizar-Contenedor" type="steps">
    <step>
        <p> Haz clic en el contenedor que deseas actualizar en la sección <strong>Containers</strong>. </p>
    </step>
    <step>
        <p> Haz clic en <strong>Recreate</strong> en la parte superior derecha de la página. </p>
    </step>
    <step>
        <p> Habilita la opción <strong>Re-pull image</strong> y haz clic en <strong>Recreate</strong>. </p>
    </step>
    <img src="portainer_recreate.png" alt="Portainer Update Container" width="400" border-effect="rounded" thumbnail="true"/>
</procedure>

### Eliminar un contenedor

<procedure title ="Pasos para eliminar un contenedor desde Portainer" id = "Eliminar-Contenedor" type="steps">
    <step>
        <p> Haz clic en el contenedor que deseas eliminar en la sección <strong>Containers</strong>. </p>
    </step>
    <step>
        <p> Haz clic en <strong>Remove</strong> en la parte superior derecha de la página. </p>
    </step>
    <step>
        <p> Confirma la eliminación del contenedor. </p>
    </step>
</procedure>

## Seguridad y buenas prácticas

- **Actualiza Portainer regularmente**: Mantén Portainer y Docker actualizados para beneficiarte de las últimas funciones y parches de seguridad.
- **Usa contraseñas seguras**: Asegúrate de que las credenciales de acceso sean robustas.
- **Restringe el acceso**: Si Portainer está expuesto en una red pública, considera implementar medidas adicionales como SSL/TLS y autenticación de dos factores.

> Se realizó la instalación y configuración de Portainer en una Raspberry Pi 4 con 4 GB de RAM. Se creó un volumen Docker para persistir los datos de Portainer y se desplegó un contenedor con la imagen de Portainer Community Edition. Además, se accedió a la interfaz web de Portainer y se utilizaron sus funcionalidades para gestionar contenedores, imágenes y volúmenes de Docker.