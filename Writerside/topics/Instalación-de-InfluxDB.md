# InfluxDB

InfluxDB es una base de datos de series temporales de código abierto, está diseñada para manejar altos volúmenes de escritura 
y lectura, y es capaz de almacenar y consultar datos de series temporales en tiempo real. En este tutorial, se explicará 
cómo instalar InfluxDB en un sistema operativo basado en Debian.

![influxdb](InfluxData-logo.png) {width="700"}

> Es importante haber instalado previamente docker en el sistema operativo.
> {style = warning}


## Instalación

1. **Actualizar el sistema** 

    Antes de instalar InfluxDB, es recomendable actualizar el sistema. Para ello, ejecuta el siguiente comando en la terminal:

    ```bash
    sudo apt update && sudo apt upgrade -y
    ```

2. **Crear directorio para los datos de InfluxDB**

    Crea los directorios en el sistema para almacenar los datos de InfluxDB. Para ello, ejecuta los siguientes comandos:

    ```bash
    mkdir ~/docker/influxdb
    mkdir ~/docker/influxdb/var/
    mkdir ~/docker/influxdb/var/lib/
    mkdir ~/docker/influxdb/var/lib/influxdb
    mkdir ~/docker/influxdb/etc/
    mkdir ~/docker/influxdb/etc/influxdb
    ```

3. **Descargar la imagen de InfluxDB**

    Corremos el siguiente comando según la versión de InfluxDB que se desee instalar.
    
    > Se recomienda utilizar la versión 1.8 de InfluxDB para evitar problemas de compatibilidad con otras aplicaciones, además de que usa SQL como lenguaje de consulta.
   
    <tabs>
        <tab title="InfluxDB 1.8">
            <code-block lang="bash"> docker run --name influxdb -itd --restart=always -p 8086:8086 -p 8083:8083 -p 2003:2003 -v ~/docker/influxdb/var/lib/influxdb:/var/lib/influxdb -v /docker/influxdb/etc/influxdb:/etc/influxdb influxdb:1.8</code-block>
        </tab>
        <tab title="InfluxDB 3.0">
            <code-block lang="bash"> docker run --name influxdb -itd  --restart=always -p 8086:8086 -p 8083:8083 -p 2003:2003  -v ~/docker/influxdb/var/lib/influxdb:/var/lib/influxdb -v /docker/influxdb/etc/influxdb:/etc/influxdb influxdb</code-block>
        </tab>
    </tabs>

    {type="medium"}
    `docker run`
    : Comando para crear y ejecutar un contenedor.
    
    `--name influxdb`
    : Asigna un nombre al contenedor.

    `-itd`
    : Permite la interacción con el contenedor.

    `--restart=always`
    : Indica que el contenedor se iniciará automáticamente al arrancar la Raspberry Pi.

    `-p`
    : Mapea los puertos del contenedor a los puertos del host.

    `-v`
    : Mapea los directorios del host al contenedor.

    `influxdb:1.8`
    : Especifica la imagen de Docker que se utilizará para crear el contenedor.

4. **Verificar la instalación**

    Para verificar que InfluxDB se ha instalado correctamente, ejecuta el siguiente comando:

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

2. **Crear una base de datos**

    Una vez dentro del contenedor de InfluxDB, ejecuta el siguiente comando para crear una base de datos:

    ```bash
    CREATE DATABASE nombre_de_la_base_de_datos
    ```

    > Sustituye `nombre_de_la_base_de_datos` por el nombre que desees asignar a la base de datos.
   > Se recomienda utilizar un nombre descriptivo y sin espacios para la base de datos.
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

> Se realizó la instalación de InfluxDB y la creación de una base de datos en una Raspberry Pi dentro de un contenedor de Docker.













