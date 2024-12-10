# Grafana

Grafana es una plataforma interactiva y open source de visualización de datos desarrollada por Grafana Labs. Dicha plataforma permite a los usuarios ver sus datos a través de tablas y gráficos que se unifican en un panel de control (o en varios) para facilitar la interpretación y la comprensión.

![Grafana](grafana.png) {width="700"}

> **Advertencia**: Asegúrate de que Docker esté correctamente instalado y funcionando en tu Raspberry Pi antes de comenzar con la instalación de Grafana.
> {style="warning"}

## Características de Grafana

- **Interfaz web**: Grafana se ejecuta en un servidor web y se accede a través de un navegador web.
- **Soporte para múltiples fuentes de datos**: Grafana puede conectarse a una amplia variedad de fuentes de datos, incluidas bases de datos relacionales y bases de datos de series temporales.
- **Paneles personalizables**: Los paneles de Grafana son altamente personalizables y permiten a los usuarios crear visualizaciones de datos a medida.
- **Alertas y notificaciones**: Grafana permite configurar alertas y notificaciones basadas en umbrales y condiciones específicas.

## Instalación

### 1. Actualizar el sistema

Es recomendable actualizar los paquetes de la Raspberry Pi antes de instalar nuevos contenedores.

```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Crear un directorio para Grafana

Crea un directorio dedicado para almacenar los datos de Grafana de manera persistente.

```bash
mkdir ~/docker/grafana 
mkdir ~/docker/grafana/var 
mkdir ~/docker/grafana/var/lib 
mkdir ~/docker/grafana/var/lib/grafana
```

### 3. Desplegar el contenedor de Grafana

Ejecuta el siguiente comando para descargar la imagen de Grafana y crear el contenedor. En este caso se utiliza el puerto 3000 para acceder a la interfaz web de Grafana.

```bash
docker run --name grafana -itd --user $(id -u) --restart=always -p 3000:3000 -v /docker/grafana/var/lib/grafana:/var/lib/grafana grafana/grafana
```

**Explicación de los parámetros:**

{type="wide"}
`--name=grafana`
: Asigna el nombre "grafana" al contenedor.

`-itd`
: Permite la interacción con el contenedor y ejecutarlo en segundo plano.

`--user $(id -u)`
: Asigna el ID de usuario actual al contenedor.

`--restart=always`
: Configura el contenedor para que se inicie automáticamente al arrancar el sistema.

`-p 3000:3000`
: Mapea el puerto 3000 del contenedor al puerto 3000 del host.

`-v`
: Monta el directorio `/docker/grafana/var/lib/grafana` del host en el directorio `/var/lib/grafana` del contenedor.

`grafana/grafana`
: Especifica la imagen de Grafana que se utilizará para crear el contenedor.

### 4. **Verificar la instalación**

Para asegurarte de que Grafana se está ejecutando correctamente, lista los contenedores activos:

```bash
docker ps
```

Deberías ver una salida similar a la siguiente:

```bash
CONTAINER ID   IMAGE              COMMAND             CREATED         STATUS                       PORTS                                       NAMES
fdf3b88b828e   grafana/grafana    "/run.sh"           8 seconds ago   Up Less than a second        0.0.0.0:3000->3000/tcp, :::3000->3000/tcp   grafana
```

## Acceder a la interfaz web de Grafana

Ahora que Grafana está en funcionamiento, puedes acceder a la interfaz web desde cualquier navegador en tu red local.

### 1. Abrir el navegador

Abre tu navegador web favorito e ingresa la dirección IP de tu Raspberry Pi seguida del puerto 3000:

```
http://<IP_DE_LA_RASPBERRY_PI>:3000
```

Tamibén puedes acceder a Grafana a través del nombre del host de tu Raspberry Pi:

```bash
http://<NOMBRE_DEL_HOST>:3000
```

### 2. Configurar el usuario administrador

La primera vez que accedas a Grafana, se te pedirá que inicies sesión con las credenciales predeterminadas:

- **Usuario**: `admin`
- **Contraseña**: `admin`

![Iniciar sesión en Grafana](grafana_inicio.png) {border-effect="rounded" width="400" thumbnail="true"}

### 3. Cambiar la contraseña

Una vez que hayas iniciado sesión, se te pedirá que cambies la contraseña predeterminada. Ingresa la nueva contraseña y haz clic en "Submit".

![Cambiar contraseña de Grafana](grafana_password.png) {border-effect="rounded" width="400" thumbnail="true"}

## Crear un nuevo panel de visualización

Con Grafana instalado y configurado, puedes comenzar a crear paneles de visualización para tus datos. A continución, se describen los pasos para crear un panel de visualización en Grafana.

<procedure title="Pasos para crear un panel de visualización" id="Crear-panel-visualizacion" type="steps">
    <step>
        <p><control>Agregar datos a la base de datos</control></p>
        <p>Antes de comenzar, agregamos datos a la base de datos de InfluxDB para visualizarlos en Grafana. Para ello, utilizamos los siguientes comandos:</p>
        <list>
            <li>
                <p>Conéctate al contenedor de InfluxDB:</p>
            </li>
        </list>
        <code-block lang="bash">
            docker exec -it influxdb influx
        </code-block>
        <list>
            <li>
                <p>Crea una nueva base de datos, en este caso llamada <code>prueba</code>:</p>
            </li>
        </list>
        <code-block lang="bash">
            CREATE DATABASE prueba
        </code-block>
        <list>
            <li>
                <p>Utiliza la base de datos creada:</p>
            </li>
        </list>
        <code-block lang="bash">
            USE prueba
        </code-block>
        <list>
            <li>
                <p>Inserta datos en la base de datos:</p>
            </li>
        </list>
        <code-block lang="bash">
            INSERT sensores,id="W312" temperatura=26,humedad=24.9,co2_ppm=490
        </code-block>
        <list>
            <li>
                <p>Verifica que los datos se hayan insertado correctamente:</p>
            </li>
        </list>
        <code-block lang="bash">
            SELECT * FROM sensores
        </code-block>
        <img src="grafana_terminal.png" alt="Datos insertados en InfluxDB" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Agregar la fuente de datos</control></p>
        <p>En el menú lateral, haz clic en <control>Connections</control> y selecciona <control>Add new connection</control>.</p> 
        <img src="grafana_connections.png" alt="Agregar fuente de datos" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Seleccionar influxDB como fuente de datos</control></p>
        <p>Buscamos <control>InfluxDB</control> en la lista de fuentes de datos disponibles y hacemos clic en <control>Add new source</control>.</p>
        <img src="grafana_influxdb.png" alt="Seleccionar Prometheus como fuente de datos" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Configurar la conexión con InfluxDB</control></p>
        <p>Agregamos los detalles de la conexión a InfluxDB.</p>
        <list>
            <li>
                <p>En el campo <control>URL</control>, ingresamos la dirección IP de la Raspberry Pi seguida del puerto de InfluxDB, por ejemplo: <code>http://&lt;IP_DE_LA_RASPBERRY_PI&gt;:8086</code>.</p>
            </li>
            <li>
                <p>Especifica la base de datos que deseas utilizar, en este caso <code>prueba</code>.</p>
            </li>
            <li>
                <p>Utilizamos <control>GET</control> como método HTTP.</p>
            </li>
        </list>
        <p>Una vez que hayas completado los detalles, haz clic en <control>Save & Test</control> para verificar la conexión.</p>
        <img src="grafana_conexionInflux.png" alt="Configurar la conexión a InfluxDB" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Crear un nuevo panel de visualización</control></p>
        <p>Retrocede al panel principal de Grafana y haz clic en <control>New dashboard</control> para crear un nuevo panel.</p>
        <img src="grafana_dashboard.png" alt="Crear un nuevo panel de visualización" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Agregar una visualización</control></p>
        <p>Haz clic en <control>Add visualization</control> para agregar una visualización al panel.</p>
        <img src="grafana_visualization.png" alt="Agregar un nuevo panel" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Seleccionar fuente de datos</control></p>
        <p>Selecciona la fuente de datos que configuraste anteriormente para conectar Grafana a InfluxDB.</p>
        <img src="grafana_seleccionarBD.png" alt="Seleccionar fuente de datos" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Configurar la visualización</control></p>
        <p>Dentro de la visualización, puedes personalizar los datos que deseas mostrar, como la consulta a la base de datos, el tipo de gráfico y los ejes X e Y.</p>
        <img src="grafana_grafica.png" alt="Configurar la visualización" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Guardar el panel</control></p>
        <p>Una vez que hayas configurado la visualización, haz clic en <control>Save dashboard</control> y asigna un nombre al panel.</p>
        <img src="grafana_save.png" alt="Guardar el panel de visualización" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
    <step>
        <p><control>Visualizar los datos</control></p>
        <p>Posteriormente, se mostrará el panel de visualización con los datos obtenidos de InfluxDB en la sección de dashboard.</p>
        <img src="grafana_grafico.png" alt="Visualizar los datos en Grafana" width="400" border-effect="rounded" thumbnail="true"/>
    </step>
</procedure>

> **Resultado:** Se realizó la instalación de Grafana en una Raspberry Pi dentro de un contenedor de Docker y se creó un panel de visualización para mostrar datos de una base de datos de series temporales.





