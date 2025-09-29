#include <Arduino_FreeRTOS.h>


#define LED1 8
#define LED2 9


void TaskBlink500(void *pvParameters);
void TaskBlink1000(void *pvParameters);

void setup() {
  // Inicializamos pines
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Crear tareas
  xTaskCreate(
    TaskBlink500,        // Función que implementa la tarea
    "LED1_500ms",        // Nombre de la tarea (para debugging)
    128,                 // Tamaño de pila en palabras
    NULL,                // Parámetro para la tarea
    1,                   // Prioridad (1 es baja, mayor número = mayor prioridad)
    NULL                 // Handle de la tarea (no lo necesitamos aquí)
  );

  xTaskCreate(
    TaskBlink1000,
    "LED2_1000ms",
    128,
    NULL,
    1,
    NULL
  );

  // Importante: después de crear tareas, el loop() ya no se ejecutará como en Arduino normal
}

void loop() {
  // En RTOS, loop() NO se usa. El sistema ejecuta las tareas.
}

void TaskBlink500(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    digitalWrite(LED1, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // Espera no bloqueante
    digitalWrite(LED1, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void TaskBlink1000(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    digitalWrite(LED2, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED2, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}