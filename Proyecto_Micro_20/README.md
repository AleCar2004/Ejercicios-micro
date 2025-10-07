# PROYECTO MICROCONTROLADORES
Integración de los temas vistos en el primer corte (EEPROM, RTOS, I2C y MQTT)
## Descripción
Comparación de un valor analogo registrado por un sensor con un valor umbral o máximo que no debe ser superado. El programa define un valor umbral inicial, este valor puede ser modificado desde el broker con la comunicación MQTT, guardandolo en la memoria EEPROM para mantener el valor configurado aún despues de reiniciar el microcontrolador. 
El programa envia al broker los valores del sensor y del umbral máximo, como tambien el estado, mientras el valor del sensor no supere el umbral, el estado será "OK", pero si es superior, enviará un mensaje de "ALERTA!"; esta misma información tambien es mostrada en la pantalla LCD, enviando los datos por el modulo PCD8544 con comunicación I2C. 
Para verificar el funcionamiento del programa sin depender del valor de un sensor, se registra la señal de un potenciómetro, así se logra modificar rapidamente el valor leído por el microcontrolador y visualizar la reacción del programa al estado de alerta generado por superar el valor umbral.
Mediante el sistema operativo en tiempo real (RTOS), el microcontrolador gestiona las tareas que debe cumplir el programa (leer el valor del sensor, comparar el valor analogo con el umbral, publicar la información en el broker, mostrar los datos en la pantalla LCD y mantener la comunicación MQTT del microcontrolador con el broker).


