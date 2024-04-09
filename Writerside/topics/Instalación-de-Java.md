# Instalación de Java

Java es un lenguaje de programación de propósito general que se utiliza en una amplia variedad de aplicaciones. En este tutorial, aprenderás cómo instalar y configurar Java en el sistema operativo Linux Mint.

![Java](Java.png) {width="700"}

> Se realizará la instalación de Java en un sistema operativo Linux, en este caso se utilizará Linux Mint 21.3 "Virginia".

### Actualizar el sistema

Antes de realizar cualquier instalación, es recomendable actualizar el sistema para asegurarse de que se instalen las
últimas versiones de los paquetes. Para ello, se debe ejecutar el siguiente comando:

<procedure title="Pasos para actualizar el sistema" id="actualizar-sistema">
    <step>
        <p>Actualizar la lista de paquetes:</p>
        <p>Para actualizar la lista de paquetes, se debe ejecutar el siguiente comando: </p>
        <code>sudo apt update</code>
    </step>
    <step>
        <p>Actualizar los paquetes instalados: Para actualizar los paquetes instalados, se debe ejecutar el siguiente comando: </p>
        <code>sudo apt upgrade</code>
    </step>
</procedure>

### Descargar el paquete de Java

Una vez que el sistema esté actualizado, se debe descargar el paquete de Java. Para ello, nos dirigimos a
la [Página oficial](https://www.oracle.com/mx/java/technologies/downloads/ "Java for Linux") y seguimos los siguientes
pasos:

<procedure title="Pasos para descargar el JDK" id="descargar-JDK">
    <step>
        <p>Seleccionar la versión de Java que se desea instalar</p>
        <img src="versionJava.png" alt="Seleccionar versión" border-effect="line"/>
    </step>
    <step>
        <p>Seleccionar la plataforma y el tipo de paquete</p>
        <img src="plataforma.png" alt="Seleccionar paquete" border-effect="line"/>
    </step>
    <step>
        <p>Descargar el paquete, en este caso se utilizó la versión 17 de JAVA y el paquete <code>.tar.gz</code> </p>
        <a href='https://download.oracle.com/java/17/latest/jdk-17_linux-x64_bin.tar.gz '> x64 Compressed Archive </a>
    </step>
</procedure>

### Instalar el paquete de Java

Nos dirigimos a la carpeta donde descargamos el archivo y lo descomprimimos con el siguiente comando (también podemos utilizar el ambiente gráfico).

```bash
sudo tar -xvzf jdk-17_linux-x64_bin.tar.gz
```
El siguiente paso es mover el directorio descomprimido a la carpeta `/usr/lib/jvm/`, en caso de que no exista, se debe crear con el siguiente comando:

```bash
mkdir /usr/lib/jvm
```
Movemos la carpeta descomprimida a la carpeta `/usr/lib/jvm/` con el siguiente comando:

```bash
sudo mv jdk-17.0.10/ /usr/lib/jvm/
```
Una vez que se haya movido el directorio, se debe configurar las variables de entorno para que el sistema pueda reconocer la instalación de Java. Para ello, se debe editar el archivo `/etc/environment` con el siguiente comando:

```bash
sudo nano /etc/environment
```
Se debe agregar las siguientes dos líneas al final del archivo:

```bash
:/usr/lib/jvm/jdk-17.0.10/bin
JAVA_HOME="/usr/lib/jvm/jdk-17.0.10"
```
### Configurar las variables de entorno

Para que el sistema tome en cuenta las variables de entorno, se debe ejecutar el siguiente comando:

```bash
sudo update-alternatives --install "/usr/bin/java" "java" "/usr/lib/jvm/jdk-17.0.10/bin/java" 0
sudo update-alternatives --install "/usr/bin/javac" "javac" "/usr/lib/jvm/jdk-17.0.10/bin/javac" 0
sudo update-alternatives --set java /usr/lib/jvm/jdk-17.0.10/bin/java
sudo update-alternatives --set javac /usr/lib/jvm/jdk-17.0.10/bin/javac
```
Para actualizar las variables de entorno, se debe ejecutar el siguiente comando:

```bash
update-alternatives --list java
update-alternatives --list javac
```
### Verificar la instalación

Para verificar que la instalación se realizó correctamente, se debe ejecutar el siguiente comando:

```bash
java -version
```
Si la instalación se realizó correctamente, se mostrará la versión de Java instalada.

> Se realizó la instalación de Java 17 en un sistema operativo Linux Mint 21.3 "Virginia".
> {style=note}