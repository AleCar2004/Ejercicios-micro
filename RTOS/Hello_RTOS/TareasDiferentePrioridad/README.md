# Reto 2: Tareas con diferentes prioridades
#### Objetivo: 
Comprender cómo RTOS asigna CPU a las tareas según su prioridad.

#### Descripción:

Crear tres tareas:
Tarea de baja prioridad: parpadeo de LED cada 1000 ms.
Tarea de prioridad media: leer un potenciómetro y mostrar el valor por Serial cada 500 ms.
Tarea de alta prioridad: responder a la pulsación de un botón encendiendo un LED inmediatamente.
Comparar qué pasa si todas las tareas tienen la misma prioridad vs. cuando se asignan prioridades distintas.
