#include <Arduino_FreeRTOS.h>


const int ledParpadeo = 2;   
const int ledBoton = 3;      
const int boton = 4;         
const int potPin = A0;       

void TareaParpadeo(void *pvParameters);
void TareaPotenciometro(void *pvParameters);
void TareaBoton(void *pvParameters);

void setup() {
  Serial.begin(9600);

  pinMode(ledParpadeo, OUTPUT);
  pinMode(ledBoton, OUTPUT);
  pinMode(boton, INPUT_PULLUP);

  
  xTaskCreate(TareaParpadeo, "LED", 128, NULL, 1, NULL);       
  xTaskCreate(TareaPotenciometro, "POT", 128, NULL, 2, NULL);  
  xTaskCreate(TareaBoton, "BOTON", 128, NULL, 3, NULL);        


  vTaskStartScheduler();
}

void loop() {
  
}


void TareaParpadeo(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    digitalWrite(ledParpadeo, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(ledParpadeo, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void TareaPotenciometro(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    int valor = analogRead(potPin);
    Serial.print("Potenciometro: ");
    Serial.println(valor);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}


void TareaBoton(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    if (digitalRead(boton) == LOW) {
      digitalWrite(ledBoton, HIGH);
    } else {
      digitalWrite(ledBoton, LOW);
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); 
  }
}
