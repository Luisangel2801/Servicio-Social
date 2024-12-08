# Docker

Docker es una plataforma de contenedores de código abierto que permite automatizar el despliegue de aplicaciones dentro de contenedores de software. Con el eslogan **“Build, Ship and Run Any App, Anywhere”** (Construye, Envía y Ejecuta Cualquier Aplicación, en Cualquier Lugar), Docker ofrece una alternativa flexible y eficiente a la emulación de componentes de hardware basada en máquinas virtuales (VM).

![Docker](docker.png) {width="700"}

## Descripción

Docker está diseñado para desarrollar, enviar y ejecutar aplicaciones aprovechando la tecnología de contenedores. A diferencia de la virtualización tradicional, que implica iniciar diferentes sistemas huéspedes en un mismo sistema anfitrión (host), Docker permite que las aplicaciones se ejecuten como procesos aislados dentro del mismo sistema mediante contenedores. Esto logra una virtualización a nivel del sistema operativo, proporcionando múltiples beneficios:

1. **Aislamiento de Aplicaciones**: Las aplicaciones en contenedores se ejecutan de forma aislada, lo que garantiza que no interfieran entre sí y que los cambios en una aplicación no afecten a otras.
2. **Portabilidad**: Las aplicaciones en contenedores son portátiles y se pueden ejecutar en cualquier entorno que tenga Docker instalado, independientemente de las diferencias en el sistema operativo o la infraestructura subyacente.
3. **Eficiencia**: Los contenedores comparten el núcleo del sistema operativo del anfitrión, lo que los hace más ligeros y eficientes en términos de recursos que las máquinas virtuales tradicionales.

### Docker se presenta en dos versiones principales:
- **Docker Community Edition (CE)**: Versión gratuita y de código abierto destinado a desarrolladores y pequeños equipos.
- **Docker Enterprise Edition (EE)**: Versión comercial con características adicionales de seguridad, gestión y soporte, dirigida a organizaciones más grandes.

## Componentes de Docker

![DockerComponents](docker_objeto.png) {width="700"}

### Dockerfile

Un Dockerfile es un archivo de texto que contiene una serie de instrucciones para construir una imagen Docker.  El Dockerfile facilita la creación de imágenes personalizadas, permitiendo que los desarrolladores especifiquen cómo deben ser construidas, qué dependencias se necesitan y qué procesos deben ejecutarse al iniciar la imagen.

### Docker Image

Las imágenes de Docker son plantillas de solo lectura y se crean a partir de un conjunto de instrucciones especificadas en un archivo Docker, conocido como **Dockerfile**. El comando `docker build` lee estas instrucciones y genera la imagen correspondiente. Las imágenes actúan como plantillas para crear contenedores Docker, es decir, contienen los detalles sobre cómo debe empaquetarse la aplicación y sus dependencias, así como los procesos que deben ejecutarse cuando se inicia un contenedor.

### Contenedor

Un contenedor Docker es una instancia en ejecución de una imagen Docker. Proporciona una virtualización ligera a nivel del sistema operativo mediante la abstracción del "espacio del usuario". Los contenedores comparten el núcleo del sistema host con otros contenedores, lo que los hace más eficientes en términos de recursos comparados con las máquinas virtuales tradicionales. En términos sencillos, una imagen es una plantilla que define la configuración de la aplicación, mientras que un contenedor es una instancia en ejecución de esa plantilla.

### Volumen Docker

Un volumen Docker es un mecanismo de almacenamiento persistente que permite a los contenedores acceder y compartir datos con el sistema de archivos del sistema host. Los volúmenes se utilizan para almacenar datos que deben persistir más allá del ciclo de vida de un contenedor.

## Comparación entre Contenedores y Máquinas Virtuales

Los contenedores son ligeros al compartir el sistema operativo del anfitrión, lo que los hace ideales para una implementación rápida. Por su parte, las máquinas virtuales cuentan con su propio sistema operativo, brindando un mayor aislamiento, aunque a costa de un mayor consumo de recursos.

![DockerVsVM](dockerVsVM.png) {width="700"}

### Máquinas Virtuales

Una máquina virtual (VM) es una tecnología que permite la virtualización a nivel de hardware, facilitando la ejecución de múltiples sistemas operativos en una única máquina física. Cada VM opera como un sistema aislado, con su propio sistema operativo, aplicaciones y dependencias. Esto se logra mediante el software denominado "hipervisor", el cual asigna recursos de hardware, como núcleos de CPU y almacenamiento, a cada máquina virtual.

La arquitectura de una máquina virtual suele constar de los siguientes componentes:

- **Hardware:** La máquina física.
- **Sistema operativo:** El sistema operativo instalado en la máquina física.
- **Hipervisor:** El software que asigna recursos a las máquinas virtuales.
- **SO huésped:** El sistema operativo instalado en cada máquina virtual.
- **Aplicación:** El software que se ejecuta en la máquina virtual.
- **Dependencias:** Las bibliotecas/binarios necesarios para ejecutar la aplicación.

![VirtualMachine](docker_MV.png) {width="500"}

### Contenedores

Un contenedor es una forma de virtualización que opera a nivel del sistema operativo, permitiendo que múltiples aplicaciones se ejecuten sobre el mismo núcleo del SO. A diferencia de las máquinas virtuales, los contenedores no incluyen su propio sistema operativo, sino que comparten el sistema operativo anfitrión, lo que los hace mucho más ligeros y eficientes.

Los contenedores integran una aplicación junto con todas sus dependencias, y están diseñados para funcionar de manera consistente, sin importar el entorno en el que se desplieguen.

Una arquitectura de contenedores típica consta de los siguientes componentes:

- **Hardware:** La máquina física.
- **Sistema operativo anfitrión:** El sistema operativo de la máquina física (o VM).
- **Motor de contenedor:** Software que gestiona la creación y el mantenimiento de contenedores.
- **Aplicación:** El software que se ejecuta en el contenedor.
- **Dependencias:** Las bibliotecas/binarios necesarios para ejecutar la aplicación.

![DockerContainer](docker_contenedor.png) {width="500"}

## Docker Hub

[Docker Hub](https://hub.docker.com/ "Página oficial de Docker Hub") es un servicio de registro basado en la nube proporcionado por Docker para almacenar y compartir imágenes de Docker. Sirve como repositorio predeterminado para los contenedores Docker, lo que facilita la distribución de aplicaciones en contenedores y la colaboración entre desarrolladores.

![DockerHub](docker_hub.png) {width="700"}

### Características de Docker Hub

- **Repositorios públicos:** Son repositorios de código abierto en los que cualquiera puede compartir y acceder a imágenes de Docker. Los desarrolladores pueden buscar imágenes, extraerlas y ejecutarlas localmente o en la nube.
- **Repositorios privados:** Son repositorios de pago que permiten a los usuarios almacenar imágenes de Docker de forma segura y restringir el acceso. Esto es útil para las organizaciones que necesitan mantener la privacidad de sus aplicaciones personalizadas o imágenes propietarias.
- **Compilaciones automatizadas:** Docker Hub puede crear imágenes automáticamente desde un repositorio de GitHub o Bitbucket. Cada vez que se insertan cambios en el código fuente, Docker Hub puede desencadenar una nueva compilación y actualizar la imagen automáticamente.
- **Control de versiones:** Docker Hub admite el control de versiones, por lo que los desarrolladores pueden enviar varias versiones de una imagen, lo que facilita la administración de diferentes etapas de desarrollo o versiones.
- **Comunidad de Docker Hub:** Docker Hub sirve como un lugar para que la comunidad de Docker colabore, comparta aplicaciones en contenedores y contribuya a proyectos de código abierto.