#include <Arduino_FreeRTOS.h>
#include <semphr.h>  

SemaphoreHandle_t xMutex;

void Tarea1(void *pvParameters);
void Tarea2(void *pvParameters);

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; } 

 
  xMutex = xSemaphoreCreateMutex();

  if (xMutex != NULL) {
    
    xTaskCreate(Tarea1, "Tarea1", 128, NULL, 1, NULL);
    xTaskCreate(Tarea2, "Tarea2", 128, NULL, 1, NULL);
  }

  
  vTaskStartScheduler();
}

void loop() {
  
}


void Tarea1(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("Tarea 1");
      xSemaphoreGive(xMutex);  
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}


void Tarea2(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("Tarea 2");
      xSemaphoreGive(xMutex);  
    }
    vTaskDelay(700 / portTICK_PERIOD_MS);
  }
}
