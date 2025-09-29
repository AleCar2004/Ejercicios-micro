# Reto 3: Sincronización con semáforos
#### Objetivo: 
Introducir el control de acceso a recursos compartidos.

#### Descripción:

Dos tareas intentan escribir en la pantalla LCD o en el puerto Serial (recurso compartido).
Usar un semáforo binario o un mutex para que solo una tarea acceda al recurso a la vez.
Mostrar en la salida Serial qué tarea está escribiendo y verificar que no haya mensajes mezclados.
