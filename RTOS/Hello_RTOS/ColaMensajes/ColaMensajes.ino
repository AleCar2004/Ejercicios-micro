#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>


#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


const int led = 2;


QueueHandle_t colaTemperatura;


void TareaLectura(void *pvParameters);
void TareaProcesamiento(void *pvParameters);
void TareaMonitoreo(void *pvParameters);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(led, OUTPUT);

  
  colaTemperatura = xQueueCreate(5, sizeof(float));

  if (colaTemperatura != NULL) {
    
    xTaskCreate(TareaLectura, "Lectura", 128, NULL, 2, NULL);
    xTaskCreate(TareaProcesamiento, "Procesamiento", 128, NULL, 2, NULL);
    xTaskCreate(TareaMonitoreo, "Monitoreo", 128, NULL, 1, NULL);
  } else {
    Serial.println("Error al crear la cola");
  }

  
  vTaskStartScheduler();
}

void loop() {
  
}


void TareaLectura(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    float temp = dht.readTemperature();
    if (!isnan(temp)) {
      // Enviar valor a la cola
      xQueueSend(colaTemperatura, &temp, portMAX_DELAY);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS); 
  }
}


void TareaProcesamiento(void *pvParameters) {
  (void) pvParameters;
  float tempRecibida;
  for (;;) {
    if (xQueueReceive(colaTemperatura, &tempRecibida, portMAX_DELAY) == pdTRUE) {
      Serial.print("🌡️ Temperatura: ");
      Serial.print(tempRecibida);
      Serial.println(" °C");

      if (tempRecibida > 28.0) {
        digitalWrite(led, HIGH);
        Serial.println("¡Temperatura alta! LED encendido.");
      } else {
        digitalWrite(led, LOW);
      }
    }
  }
}


void TareaMonitoreo(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    Serial.println("Sistema en funcionamiento...");
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}
