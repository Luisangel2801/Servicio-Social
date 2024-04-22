# Instalación de Vscode y PlatformIO

![VScode](vscode.png) {width="700" border-effect="rounded"}

## Instalación de Vscode

Existe varias formas de instalar `VScode` en `Linux Mint`, sin embargo, la forma más sencilla es a través de `snapd`. A continuación, se detallan los pasos para instalar `VScode` en 'Linux Mint' a través de `snapd`:

1. **Borrar el archivo llamado `nosnap.pref`**

    - Para borrar el archivo, se debe ejecutar el siguiente comando:

    ```bash
    sudo rm /etc/apt/preferences.d/nosnap.pref
    ```

2. **Actualizar la lista de paquetes**

    - Para actualizar la lista de paquetes, se debe ejecutar el siguiente comando:

    ```bash
    sudo apt update
    ```

3. **Instalar `snapd`**

    - Para instalar `snapd`, se debe ejecutar el siguiente comando:

    ```bash
    sudo apt install snapd
    ```

4. **Verificar la instalación de `snapd`**

    - Para verificar si `snapd` está instalado, podemos descargar la tienda de aplicaciones:

    ```bash
    sudo snap install snap-store
    ```

    -Si `snapd` está instalado correctamente, se desplegará un mensaje similar a:

    ```bash
    snap-store 3.38.0 from Canonical✓ installed
    ```

5. **Instalar `VScode`**

    - Para instalar `VScode`, se debe ejecutar el siguiente comando:

    ```bash
    sudo snap install --classic code
    ```

6. **Verificar la instalación de `VScode`**

    - Para verificar si `VScode` está instalado, se debe ejecutar el siguiente comando:

    ```bash
    code --version
    ```

    - Si `VScode` está instalado correctamente, se desplegará un mensaje similar a:

    ```bash
    1.86.2
    ```

## Instalación de PlatformIO

Para instalar `PlatformIO` en `VScode`, se deben seguir los siguientes pasos:

1. **Abrir `VScode`**

2. **Ir a la pestaña de `Extensiones`**
    - En la barra lateral izquierda, se debe hacer clic en el ícono de `Extensiones`
    - En la barra de búsqueda, se debe escribir `PlatformIO IDE`
    - Seleccionar la extensión `PlatformIO IDE` y hacer clic en `Instalar`
    - Una vez instalada la extensión, se debe reiniciar `VScode`
    - Para verificar que `PlatformIO` está instalado, se debe ir a la pestaña de `PlatformIO Home` en la barra lateral izquierda
    - Si `PlatformIO` está instalado correctamente, se desplegará la página de inicio de `PlatformIO`

3. **Instalar `Python` (en caso de ser necesario)**
    En caso de que `PlatformIO` nos pida instalar `Python`, se debe instalar con el siguiente comando:

    ```bash
    sudo apt install python3-venv
    ```
     En caso de volver a aparecer el mensaje de instalación de `Python`, se debe ejecutar el siguiente comando:

    ```bash
    curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
    python3 get-platformio.py
    ```

    - Una vez instalado `Python`, se debe reiniciar `VScode` y verificar que `PlatformIO` está instalado correctamente.

4. **Crear un nuevo proyecto en `PlatformIO`**

    Es posible crear un nuevo proyecto en `PlatformIO` a través del menú de `PlatformIO Home` en `VScode`, para este tutorial creará un proyecto creando los archivos necesarios para el proyecto.

    - Creamos una carpeta nueva en donde se guardará el proyecto
    - Dentro de la carpeta creada se debe crear un archivo llamado `platformio.ini` con el siguiente contenido según la placa que se desee utilizar:

    <tabs>
        <tab title="ESP8266">
            <code-block lang="text">
            [env:esp8266]
            platform = espressif8266
            board = esp12e
            framework = arduino
            </code-block>
        </tab>
        <tab title="ESP32">
            <code-block lang="text">
            [env:esp32]
            platform = espressif32
            board = esp32dev
            framework = arduino
            </code-block>
        </tab>
    </tabs>

    - Crear un archivo llamado `main.cpp` dentro de una carpeta llamada `src`, este archivo contendrá el código del proyecto. En este caso utilizaremos el código de ejemplo de `Blink` para la placa `ESP8266`:
        
    >El código de ejemplo de `Blink` es el mismo que utilizamos anteriormente, es importante señalar que se debe agregar la librería de `Arduino.h` para que el código funcione correctamente.
    > {style=warning}
    
    ```c++
    #include <Arduino.h>

    const int led = 2;
    
    void setup() {
       Serial.begin(9600);		// iniciar puerto serial
       pinMode(led, OUTPUT);	// inicializar GPIO 2 como salida
    }
    
    void loop() {
       digitalWrite(led, HIGH);	   // apaga el LED
       Serial.println("LED OFF");
       delay(1000);				   // espera un segundo
       digitalWrite(led, LOW);	   // enciende el LED
       Serial.println("LED ON");
       delay(1000);				   // espera un segundo
    }
    ```

    - Una vez creados los archivos, se debe abrir el proyecto en `VScode` y automáticamente `PlatformIO` detectará los archivos y configurará el entorno de desarrollo.
    - Para compilar y subir el código al dispositivo, se debe hacer clic en el ícono de `Upload` en la barra inferior de `VScode`.
    - Si el código se compila y sube correctamente, se habrá creado un nuevo proyecto en `PlatformIO` utilizando `VScode`.

> Se realizó la instalación de `VScode` y `PlatformIO` en `Linux Mint` y se creó un nuevo proyecto en `PlatformIO` utilizando el código de ejemplo `Blink`.
> {style=note}
