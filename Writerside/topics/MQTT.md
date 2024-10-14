# MQTT

## Descripción

MQTT (Message Queuing Telemetry Transport) es un protocolo de mensajería que se utiliza para conectar dispositivos a través de redes con recursos limitados. Los sensores inteligentes, los dispositivos portátiles y otros dispositivos de Internet de las cosas (IoT) generalmente tienen que transmitir y recibir datos a través de una red con recursos restringidos y un ancho de banda limitado. Estos dispositivos IoT utilizan MQTT para la transmisión de datos, ya que resulta fácil de implementar y puede comunicar datos IoT de manera eficiente.

![MQTT](MQTT.png) {width="700"}

## Historia

MQTT fue creado originalmente por el Dr. Andy Stanford-Clark y Arlen Nipper en 1999. El propósito original de este método de comunicación era permitir que los dispositivos de monitoreo utilizados en la industria del petróleo y el gas enviaran sus datos a servidores remotos. Con miles de sensores en el campo, la industria necesitaba una forma de comunicación que pudiera proporcionar datos de manera suficientemente fiable para su uso, mientras empleaba un ancho de banda mínimo.

En 2010, IBM lanzó MQTT 3.1 como un protocolo gratuito y abierto para que cualquiera pudiera implementarlo, que después, en 2013, se envió al organismo de especificación de la Organización para el Avance de Estándares de Información Estructurada (OASIS) para su mantenimiento. En 2019, OASIS lanzó una versión 5 de MQTT actualizada. Ahora MQTT ya no es un acrónimo sino que se considera el nombre oficial del protocolo.

## Arquitectura del Protocolo MQTT

MQTT es un protocolo de mensajería basado en el modelo de publicación/suscripción. En este modelo, los dispositivos se dividen en dos categorías: publicadores y suscriptores. Los publicadores son dispositivos que envían mensajes a un servidor MQTT, mientras que los suscriptores son dispositivos que reciben mensajes de un servidor MQTT. Un bróker es el servidor con el que se comunican los clientes: recibe comunicaciones de unos y se las envía a otros. Los clientes no se comunican directamente entre sí, sino que se conectan con el bróker. Cada cliente puede ser un publicador, un suscriptor o ambos.

![MMQTT_Proceso](MQTT_Proceso.png) {border-effect="rounded" width="600"}

MQTT es un protocolo controlado por eventos, donde no hay transmisión de datos periódica o continua. Así se mantiene el volumen de transmisión al mínimo. Un cliente sólo publica cuando hay información para enviar, y un bróker sólo envía información a los suscriptores cuando llegan nuevos datos.

## Niveles de Calidad de Servicio (QoS)

En MQTT, la calidad de servicio (QoS) controla la garantía en la entrega de mensajes mediante el transporte subyacente. Los tres niveles de QoS se definen en Especificación de protocolo MQTT. 

- **QoS 0**: Con este nivel, cada mensaje se entrega a los suscriptores una vez, sin confirmación, por lo que no hay forma de saber si los suscriptores recibieron el mensaje. Este método a veces se denomina “lanzar y olvidar” o “una entrega como máximo”. Debido a que este nivel asume que la entrega está completa, los mensajes no se almacenan para entregarlos a los clientes desconectados que luego se vuelven a conectar.

- **QoS 1**: El bróker intenta entregar el mensaje y, luego, espera una respuesta de confirmación del suscriptor. Si no se recibe una confirmación dentro de un período de tiempo especificado, el mensaje se envía de nuevo. Usando este método, el suscriptor puede recibir el mensaje más de una vez si el bróker no recibe el acuse de recibo del suscriptor a tiempo. Esto se suele denominar “entregado al menos una vez”.

- **QoS 2**: El cliente y el bróker utilizan un protocolo de enlace de cuatro pasos para garantizar no sólo que el mensaje se reciba, sino que lo haga una única vez. También se conoce como “entrega exactamente una vez”. Los mensajes se almacenan en el bróker hasta que se confirma la entrega.

![MQTT_QoS](QoS.png) {border-effect="rounded" width="600"}

## Temas y Suscripciones

En MQTT, los mensajes se transmiten a través de **temas**, que son estructuras jerárquicas delimitadas por el carácter de barra (/). Esta organización se asemeja a un árbol de directorios en un sistema de archivos de ordenador. Por ejemplo, una estructura como `miCasa/plantaBaja/sala/temperatura` permite a un suscriptor especificar que únicamente recibirá datos de los clientes que publiquen en el tema `temperatura` de la sala de la planta baja.

En MQTT, los temas no se crean de forma explícita. Si un agente recibe datos publicados sobre un tema que aún no existe, simplemente lo crea automáticamente, permitiendo que los clientes se suscriban a él sin necesidad de configuraciones adicionales.

![tema](tema.png) {border-effect="rounded" width="600"}

Estas son las características que hay que considerar para definir un tema como válido.

- Deben contener al menos un carácter por lo que una diagonal sola “ / ” es válido.
- Puede contener espacios (aunque no se recomienda)
- Son sensibles a mayúsculas y minúsculas por lo que `miCasa/temperatura` es diferente a `miCasa/Temperatura`

## Mensajes Retenidos

Para mantener una huella reducida, los mensajes recibidos no se almacenan en el bróker a menos que estén marcados con la **bandera de retención**, lo que se denomina **mensaje retenido**. Los usuarios que deseen conservar los mensajes deberán almacenarlos externamente, fuera del protocolo MQTT. Sin embargo, existe una excepción a esta regla.

Dado que MQTT es un protocolo basado en eventos, es posible e incluso probable que un suscriptor reciba muy pocos mensajes sobre un tema determinado, incluso durante largos períodos de tiempo. Por ejemplo, en la estructura de temas mencionada anteriormente, los mensajes relacionados con el tema `temperatura` solo se enviarían cuando un sensor detecte un cambio de la temperatura.

Para asegurar que un nuevo suscriptor reciba los mensajes de un tema, los brókeres pueden conservar el último mensaje enviado a cada tema, conocido como **mensaje retenido**. De este modo, cada vez que un nuevo cliente se suscribe a un tema o cuando un cliente existente se reconecta, el mensaje retenido se envía automáticamente a los suscriptores. Esto garantiza que la suscripción esté activa y que el suscriptor reciba la información más reciente sin esperar a que se publique un nuevo mensaje.

## Seguridad

El objetivo original del protocolo MQTT era hacer posible la transmisión de datos de una forma más pequeña y eficiente a través de líneas de comunicación costosas y poco fiables. Como tal, la seguridad no fue una de las principales preocupaciones durante el diseño e implementación de MQTT.

Sin embargo, hay algunas opciones de seguridad disponibles a costa de una carga superior en la transmisión de datos. Por ejemplo, el protocolo MQTT admite conexiones seguras a través de TLS/SSL, lo que garantiza que los datos se transmitan de forma segura. Además, los brókeres MQTT pueden requerir autenticación de usuario y contraseña para conectarse.