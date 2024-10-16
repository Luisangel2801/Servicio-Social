---
switcher-label: Placa
---

# Tarjeta de Desarrollo

<show-structure/>

## ESP8266 {switcher-key="ESP8266"}

### Descripción {id="Descripcion-ESP8266"}

La **NodeMCU ESP8266** es una placa de desarrollo de código abierto diseñada específicamente para proyectos de Internet de las Cosas (IoT). Basada en el módulo ESP8266, esta plataforma integra conectividad Wi-Fi y un conjunto completo de pines de entrada/salida, lo que la hace ideal para aplicaciones conectadas y proyectos electrónicos.

La NodeMCU ESP8266 combina tanto un firmware como una placa de desarrollo fabricada por **Espressif Systems**. En su versión v2, la placa está equipada con el módulo ESP-12E, que contiene el RISC LX106 de 32 bits Tensilica Xtensa® que opera a una frecuencia de reloj ajustable de 80 a 160 MHz y admite RTOS. Además, incluye un conversor USB-Serial TTL CP2102 y un conector micro-USB, necesarios para la programación y comunicación con una PC. Esto facilita su uso, ya que está diseñada para funcionar montada en una protoboard o soldada sobre una placa de circuito impreso.

<procedure title="Características de la placa ESP-12E" id="Caracteristicas_ESP-12E" collapsible="true">
    <step>Tensilica Xtensa® 32-bit LX106</step>
    <step>Frecuencia de reloj ajustable de 80 a 160 MHz</step>
    <step>Memoria flash de 4 MB</step>
    <step> 128 KB de RAM</step>
    <step>Utiliza Wi-Fi 802.11 b/g/n</step>
</procedure>

![ESP-12E](ESP-12E.jpg)

> El ESP8266 incorpora un transceptor Wi-Fi 802.11 b/g/n HT40, lo que le permite conectarse a una red Wi-Fi para acceder a Internet (modo estación) o crear su propia red Wi-Fi (modo punto de acceso).
> {style="note"}

### Características {id="Caracteristicas-ESP8266"}

1. **CPU:** El ESP8266 está equipado con un microprocesador RISC LX106 de 32 bits Tensilica Xtensa® que opera a una frecuencia de reloj ajustable de 80 a 160 MHz
2. **Memoria RAM:** 160 KB (50 KB disponibles para el usuario).
3. **Memoria Flash:** Generalmente 4 MB (depende del módulo).
4. **Conectividad Wi-Fi:** IEEE 802.11 b/g/n integrado.
5. **Interfaces:**
   1. **[GPIO](#GPIO-ESP8266):** Hasta 17 pines de propósito general.
   2. **[ADC](#ADC-ESP8266):** 1 canal de ADC SAR de precisión de 10 bits
   3. **[SPI](#SPI-ESP8266):** Soporte para comunicación SPI.
   4. **[I2C](#I2C-ESP8266):** Soporte para comunicación I2C.
   5. **[PWM](#PWM-ESP8266):** 4 pines PWM para controlar cosas como la velocidad del motor o el brillo del LED.
   6. **UART:** Soporte para comunicación UART.
   7. **[Alimentación](#Alimentacion-ESP8266):** Entrada de 5V a través del puerto USB o pin VIN, con regulador interno a 3.3V.
   
   {type="alpha-lower"}

### Ventajas frente al Arduino {id="Ventajas-ESP8266"}

1. **Conectividad Wi-Fi integrada:** El ESP8266 tiene conectividad Wi-Fi integrada, lo que permite la conexión a Internet sin necesidad de un módulo adicional.
2. **Mayor Velocidad de Procesamiento:** CPU de 32 bits a 80 MHz, frente a los 16 MHz de un Arduino Uno.
3. **Mayor Memoria:** Más RAM y memoria flash, permitiendo programas más complejos y funcionalidad ampliada.
4. **Costo Efectivo:** Generalmente más económica que un Arduino con un módulo Wi-Fi adicional.
5. **Compatibilidad con Arduino IDE:** Puede ser programada utilizando el entorno familiar del Arduino IDE.

### Interruptores integrados e indicador LED {id="Interruptores-LED-ESP8266"}

Hay dos botones en el NodeMCU ESP8266. El botón de reinicio, denominado RST, se utiliza para reiniciar el chip ESP8266. El otro botón es el botón FLASH, que se utiliza para actualizar el firmware. Además, hay un LED integrado que se puede utilizar para indicar el estado del chip.

![interruptores_ESP8266](interruptores_ESP8266.jpg)

### Pinout {id="Pinout-ESP8266"}

El NodeMCU ESP8266 tiene un total de 30 pines, que incluyen pines GPIO, pines de alimentación, pines de control y pines de comunicación. A continuación, se muestra el pinout de la placa NodeMCU ESP8266.

![ESP8266_Pinout](ESP8266_Pinout.png) {border-effect="rounded" width="500" thumbnail="true"}

### Pines GPIO {id="GPIO-ESP8266"}

El NodeMCU ESP8266 tiene 17 pines GPIO a los que se les pueden asignar diferentes funciones programando los registros correspondientes. Cada GPIO se puede configurar con pull-up o pull-down internos, o se puede configurar con alta impedancia.

- Los pines GPIO se pueden configurar como entradas o salidas digitales.
- Los pines GPIO también admiten funciones como `PWM`, `I2C`, `SPI` y `UART`.
- Los pines GPIO pueden proporcionar hasta 12 mA de corriente.
- Los pines GPIO pueden soportar un voltaje de 0 a 3.3 V.

![ESP8266_GPIO](ESP8266_GPIO.png) {border-effect="rounded" width="500" thumbnail="true"}

En la tabla siguiente se muestra la correspondencia entre los pines del NodeMCU ESP8266 y los pines GPIO del ESP8266.

<table style="both" >
   <tr><td>Pin NodeMCU</td ><td>GPIO</td><td>Notas</td></tr>
   <tr><td>D0</td><td>GPIO 16</td><td>Wake up, conectado al LED integrado de color rojo</td></tr>
   <tr><td>D1</td><td>GPIO 5</td><td>SCL (I2C)</td></tr>
   <tr><td>D2</td><td>GPIO 4</td><td>SDA (I2C)</td></tr>
   <tr><td>D3</td><td>GPIO 0</td><td> El arranque falla si se pone BAJO</td></tr>
   <tr><td>D4</td><td>GPIO 2</td><td>Conectado al LED integrado color Azul, El arranque falla si se pone BAJO.</td></tr>
   <tr><td>D5</td><td>GPIO 14</td><td>SCLK (SPI)</td></tr>
   <tr><td>D6</td><td>GPIO 12</td><td>MISO (SPI)</td></tr>
   <tr><td>D7</td><td>GPIO 13</td><td> MOSI (SPI) </td></tr>
   <tr><td>D8</td><td>GPIO 15</td><td> CS (SPI), el arranque falla si se pone en ALTO</td></tr>
   <tr><td>D9 (RX)</td><td>GPIO 3</td><td>RX UART, programación y comunicación serial</td></tr>
   <tr><td>D10 (TX)</td><td>GPIO 1</td><td>TX UART, programación y comunicación serial</td></tr>
   <tr><td>CLK</td><td>GPIO 6</td><td> </td></tr>
   <tr><td>SD0</td><td>GPIO 7</td><td> </td></tr>
   <tr><td>CMD</td><td>GPIO 11</td><td> </td></tr>
   <tr><td>SD1</td><td>GPIO 8</td><td> </td></tr>
   <tr><td>SD2</td><td>GPIO 9</td><td> </td></tr>
   <tr><td>SD3</td><td>GPIO 10</td><td> </td></tr>
   <tr><td>A0</td><td>ADC 0</td><td>Pin analógico, no se puede configurar como salida</td></tr>
</table>


### Pines ADC {id="ADC-ESP8266"}

El **ESP8266** está equipado con un convertidor analógico-digital (ADC) de **10 bits** de alta precisión, lo que le permite detectar hasta **1024 niveles analógicos discretos** $(2^{10})$. En otras palabras, convierte voltajes de entrada que varían entre 0 y 3,3 V (voltaje operativo) en valores enteros que van de 0 a 1024. Esto resulta en una resolución de 3,3 V divididos por 1024 unidades, es decir, 0,0032 V (3,2 mV) por unidad.

Esta capacidad de conversión permite al ESP8266 interpretar con precisión señales analógicas, facilitando su integración en diversos proyectos de Internet de las Cosas (IoT) y aplicaciones electrónicas que requieren monitoreo y control precisos de variables analógicas.

En la siguiente imagen se muestra la distribución de los pines ADC en la placa NodeMCU ESP8266.

![ESP8266_ADC](ESP8266_ADC.png) {border-effect="rounded" width="500" thumbnail="true"}

### Pines SPI {id="SPI-ESP8266"}

Los pines SPI permiten la comunicación de alta velocidad con periféricos como sensores y pantallas, la placa NODEMCU ESP8266 proporciona cuatro pines para comunicaciones SPI (`D5`, `D6`, `D7`, `D8`). Cualquier dispositivo que admita el protocolo SPI se puede conectar a estos cuatro pines.

- **MISO (Master In Slave Out):** Es el pin de datos de entrada para el maestro y de salida para el esclavo.
- **MOSI (Master Out Slave In):** Es el pin de datos de salida para el maestro y de entrada para el esclavo.
- **SCK (Serial Clock):** Es el pin de reloj que sincroniza la transferencia de datos.
- **CS (Chip Select):** Es el pin que selecciona el dispositivo con el que se desea comunicar.

![ESP8266_SPI](ESP8266_SPI.png) {border-effect="rounded" width="500" thumbnail="true"}

En la siguiente tabla se muestra la correspondencia entre los pines SPI de la placa NodeMCU ESP8266 y los pines GPIO del ESP8266.

| Función SPI | Pin NodeMCU | GPIO ESP8266 |
|-------------|-------------|--------------|
| CS          | D8          | GPIO 15      |
| MOSI        | D7          | GPIO 13      |
| MISO        | D6          | GPIO 12      |
| SCK         | D5          | GPIO 14      |

### Pines I2C {id="I2C-ESP8266"}

El protocolo I2C es un protocolo de comunicación que permite la comunicación entre dispositivos a través de un bus de dos cables, un cable de datos (SDA) y un cable de reloj (SCL). El ESP8266 no tiene pines I2C de hardware, pero se pueden implementar en software utilizando cualquier par de pines GPIO. Por lo tanto, puede utilizar cualquier GPIO como I2C.

![ESP8266_I2C](ESP8266_I2C.png) {border-effect="rounded" width="500" thumbnail="true"}

 Por lo general, se utilizan los siguientes GPIO como pines I2C:

| Función I2C | Pin NodeMCU | GPIO ESP8266 |
|-------------|-------------|--------------|
| SDA         | D2          | GPIO 4       |
| SCL         | D1          | GPIO 5       |

### Pines PWM {id="PWM-ESP8266"}

La modulación por ancho de pulsos (PWM) se puede implementar en todos los pines GPIO del ESP8266, desde `GPIO0` hasta el `GPIO15`. En este microcontrolador, la señal PWM cuenta con una resolución de 10 bits, lo que permite una variación precisa del ancho de pulso. Además, el rango de frecuencia PWM es ajustable entre 100 Hz y 1 kHz, equivalente a periodos de 1000 μs a 10000 μs.

Esta versatilidad en la configuración de la señal PWM facilita su uso en diversas aplicaciones, como el control de motores, la regulación de la intensidad de luces LED o la gestión de otros dispositivos electrónicos que requieran un control preciso de la potencia o la señal.

![ESP8266_PWM](ESP8266_PWM.png) {border-effect="rounded" width="500" thumbnail="true"}

### Pines de alimentación {id="Alimentacion-ESP8266"}

El pin `VIN` puede utilizarse para alimentar directamente el ESP8266 y sus periféricos, siempre que se emplee una fuente de alimentación regulada de 5 V. Por otro lado, el pin `3V3` proporciona hasta 600 mA de corriente, lo que permite alimentar sensores y otros dispositivos electrónicos adicionales.

![ESP8266_VIN](ESP8266_VIN.png) {border-effect="rounded" width="500" thumbnail="true"}

La placa incluye un regulador de tensión LDO para mantener la tensión estable en 3,3 V. Puede proporcionar de forma fiable hasta 600 mA, lo que debería ser suficiente incluso cuando el ESP8266 está consumiendo su corriente máxima (80 mA)

<procedure title="Requisitos de alimentación" id="Requisitos_alimentación_ESP8266" collapsible="true">
    <step>Regulador de tensión LDO integrado de <math>3,3 V</math> y <math>600 mA</math></step>
    <step>Alimentación de <math>5 V</math> a través del puerto USB o pin VIN</step>
    <step>Corriente de  funcionamiento de <math>80 mA</math></step>
    <step>Corriente de <math> 20 \mu A </math> en modo de suspensión profunda</step>
</procedure>

![ESP8266_LDO](regulador_ESP8266.jpg)

### Pines de control {id="Control-ESP8266"}

El pin `EN` (también conocido como `CH_PD` o **Chip Power Down**) es el **pin de habilitación** del ESP8266 y está activado en alto de manera predeterminada. Cuando este pin está en ALTO, el chip se habilita; cuando está en BAJO, el chip se deshabilita.

El pin `RST` es el **pin de reinicio** del ESP8266 y también está activo de forma predeterminada. Si se conecta momentáneamente a tierra, el ESP8266 se reiniciará, funcionando de manera equivalente a presionar el botón `RST` integrado en la placa.

El pin `FLASH` es utilizado por el ESP8266 para determinar cuándo iniciar el **gestor de arranque**. Si este pin se mantiene en BAJO durante el encendido, el dispositivo comenzará el proceso de carga de arranque, de forma similar a pulsar el botón `FLASH` integrado.

Finalmente, el pin `WAKE` se utiliza para despertar al ESP8266 del **modo de suspensión profunda**. Esto permite reactivar el dispositivo sin necesidad de un reinicio completo, optimizando el consumo de energía en aplicaciones que requieren eficiencia energética.


![ESP8266_Control](ESP8266_Control.png) {border-effect="rounded" width="500" thumbnail="true"}

> En resumen, el ESP8266 es una placa de desarrollo de bajo costo y fácil de usar que ofrece conectividad Wi-Fi integrada y un conjunto completo de pines de entrada/salida. Esto la convierte en una opción popular para proyectos de IoT y aplicaciones electrónicas que requieren conectividad a Internet.


## ESP32 {switcher-key="ESP32"}



<seealso>
       <category ref="external">
           <a href="https://lastminuteengineers.com/esp8266-pinout-reference/">ESP8266 Pinout Reference</a>
            <a href="https://naylampmechatronics.com/espressif-esp/153-nodemcu-v2-esp8266-wifi.html">Naylamp Mechatronics</a>
           <a href="https://lastminuteengineers.com/esp32-pinout-reference/">ESP32 Pinout Reference</a>
       </category>
</seealso>
