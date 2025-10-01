#include <Arduino_FreeRTOS.h>


#define LED1 8
#define LED2 9


void TaskBlink500(void *pvParameters);
void TaskBlink1000(void *pvParameters);

void setup() {
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  xTaskCreate(TaskBlink500, "LED1_500ms", 128, NULL, 1, NULL);

  xTaskCreate(TaskBlink1000, "LED2_1000ms", 128, NULL, 1, NULL);

  
}

void loop() {
  
}

void TaskBlink500(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    digitalWrite(LED1, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); 
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
