# InfluxDB

InfluxDB es una base de datos de series temporales de código abierto, diseñada para manejar grandes volúmenes de escritura y lectura de datos en tiempo real. Es ideal para almacenar y consultar series temporales, como métricas, registros de eventos, datos de sensores, entre otros. Este documento describe cómo instalar InfluxDB en una Raspberry Pi utilizando Docker.

![influxdb](InfluxData-logo.png) {width="700"}

>**Advertencia:** Asegúrate de tener Docker instalado en tu sistema antes de comenzar con la instalación de InfluxDB. Si aún no has instalado Docker, consulta la guía [aquí](Docker.md "Documentación para instalar Docker").
> {style = warning}


## Instalación

1. **Actualizar el sistema**

    Antes de comenzar con la instalación de InfluxDB, es recomendable actualizar el sistema para asegurarse de que todos los paquetes estén al día. Ejecuta el siguiente comando en la terminal:

    ```bash
    sudo apt update && sudo apt upgrade -y
    ```

2. **Crear directorio para los datos de InfluxDB**

    Es necesario crear los directorios donde se almacenarán los datos de InfluxDB. Puedes hacerlo con los siguientes comandos:

    ```bash
    mkdir ~/docker/influxdb
    mkdir ~/docker/influxdb/var/
    mkdir ~/docker/influxdb/var/lib/
    mkdir ~/docker/influxdb/var/lib/influxdb
    mkdir ~/docker/influxdb/etc/
    mkdir ~/docker/influxdb/etc/influxdb
    ```
    Estos directorios se utilizarán para almacenar los datos y la configuración de InfluxDB de forma persistente en el host.

3. **Descargar la imagen de InfluxDB**

    Descarga la imagen de InfluxDB desde el registro de Docker ejecutando el siguiente comando:

   >Se recomienda utilizar la versión 1.8 de InfluxDB para evitar problemas de compatibilidad con otras aplicaciones y porque esta versión utiliza SQL como lenguaje de consulta.
   
    <tabs>
        <tab title="InfluxDB 1.8">
            <code-block lang="bash"> docker run --name influxdb -itd --restart=always -p 8086:8086 -p 8083:8083 -p 2003:2003 -v ~/docker/influxdb/var/lib/influxdb:/var/lib/influxdb -v /docker/influxdb/etc/influxdb:/etc/influxdb influxdb:1.8</code-block>
        </tab>
        <tab title="InfluxDB 3.0">
            <code-block lang="bash"> docker run --name influxdb -itd  --restart=always -p 8086:8086 -p 8083:8083 -p 2003:2003  -v ~/docker/influxdb/var/lib/influxdb:/var/lib/influxdb -v /docker/influxdb/etc/influxdb:/etc/influxdb influxdb</code-block>
        </tab>
    </tabs>

    **Explicación de los parámetros del comando:**

    {type="medium"}
    `docker run`
    : Este comando crea y ejecuta un contenedor.

    `--name influxdb`
    : Asigna el nombre `influxdb` al contenedor.

    `-itd`
    : Ejecuta el contenedor en modo interactivo y en segundo plano.

    `--restart=always`
    : Indica que el contenedor se iniciará automáticamente al arrancar la Raspberry Pi.

    `-p`
    : Mapea los puertos del contenedor a los puertos del host.

    `-v`
    : Mapea los directorios del host al contenedor.

    `influxdb:1.8`
    : Especifica la imagen de Docker que se utilizará para crear el contenedor.

4. **Verificar la instalación**

    Para verificar que InfluxDB se ha instalado correctamente, ejecuta el siguiente comando para ver los contenedores en ejecución:

    ```bash
    docker ps
    ```

    Si InfluxDB se ha instalado correctamente, deberías ver un contenedor llamado `influxdb` en la lista de contenedores.

## Crear una base de datos en InfluxDB

1. **Acceder al contenedor de InfluxDB**

    Para acceder al contenedor de InfluxDB, ejecuta el siguiente comando:

    ```bash
    docker exec -it influxdb influx
    ```
    Este comando te permitirá acceder a la línea de comandos de InfluxDB dentro del contenedor.

2. **Crear una base de datos**

    Una vez dentro del contenedor de InfluxDB, crea una base de datos ejecutando el siguiente comando:

    ```bash
    CREATE DATABASE nombre_de_la_base_de_datos
    ```

    > **Nota:** Sustituye `nombre_de_la_base_de_datos` por el nombre que desees para tu base de datos. Se recomienda usar un nombre descriptivo y sin espacios para facilitar su gestión.
    > {style = note}

3. **Verificar la creación de la base de datos**

    Para verificar que la base de datos se ha creado correctamente, ejecuta el siguiente comando:

    ```bash
    SHOW DATABASES
    ```

    Deberías ver el nombre de la base de datos que acabas de crear en la lista de bases de datos.
4. **Salir del contenedor de InfluxDB**

    Para salir del contenedor de InfluxDB, ejecuta el siguiente comando:

    ```bash
    exit
    ```

>**Resultado:** Se realizó la instalación de InfluxDB y la creación de una base de datos en una Raspberry Pi dentro de un contenedor de Docker para almacenar y consultar series temporales de datos.













