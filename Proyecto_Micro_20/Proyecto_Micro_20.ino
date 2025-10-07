
// ---------------- PROYECTO MICROCONTROLADORES 20% ---------------------
// David Alejandro Cárdenas Gutiérrez 

#include <WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

// --------- CONFIGURACIÓN ----------

#define UBICACION_EEPROM 0   
#define SENSOR_PIN 34             

// WiFi
const char* ssid = "Alejo";
const char* password = "alejo1000";

// Broker
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const char* mqtt_topic_sub = "esp32/config";
const char* mqtt_topic_pub = "esp32/data";

// Client
WiFiClient espClient;
PubSubClient client(espClient);

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Variables Sensor
int valorSensor = 0;
int umbral = 60;   
String estado = "OK";

// Mutex 
SemaphoreHandle_t mutex;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(64);

  //Umbral
  int savedUmbral = leerUmbralEEPROM();
  if (savedUmbral > 0) {
    umbral = savedUmbral;
  }
  // LCD
  lcd.init();
  lcd.backlight();

  // Mutex
  mutex = xSemaphoreCreateMutex();

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");

  // MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Tareas
  xTaskCreatePinnedToCore(TaskADC, "TaskADC", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskProcesamiento, "TaskProcesamiento", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskLCD, "TaskLCD", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskMQTT, "TaskMQTT", 4096, NULL, 1, NULL, 1);
}

// ------------- FUNCIONES -------------

void guardarUmbralEEPROM(int nuevoUmbral) {
  EEPROM.writeInt(UBICACION_EEPROM, nuevoUmbral);
  EEPROM.commit();
}

int leerUmbralEEPROM() {
  return EEPROM.readInt(UBICACION_EEPROM);
}

void callback(char* topic, byte* message, unsigned int length) {
  String payload;
  for (unsigned int i = 0; i < length; i++) {
    payload += (char)message[i];
  }
  Serial.print("Mensaje MQTT recibido [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(payload);

  int nuevoUmbral = payload.toInt();
  if (nuevoUmbral > 0) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    umbral = nuevoUmbral;
    xSemaphoreGive(mutex);

    guardarUmbralEEPROM(nuevoUmbral);
    Serial.print("Nuevo umbral guardado: ");
    Serial.println(nuevoUmbral);
  }
}

void reconnect() {
  while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("Intentando conexión MQTT...");
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Conectado a broker público EMQX MQTT");
            client.subscribe(mqtt_topic_sub);
        } else {
            Serial.print("Error ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

// ------------ RTOS ------------

// Task: Sensor
void TaskADC(void* pvParameters) {
  while (1) {
    int lectura = analogRead(SENSOR_PIN);
    xSemaphoreTake(mutex, portMAX_DELAY);
    valorSensor = lectura;
    valorSensor = map(valorSensor, 0, 4100, 0, 100);
    xSemaphoreGive(mutex);
    vTaskDelay(pdMS_TO_TICKS(1000)); 
  }
}

// Task: Umbral
void TaskProcesamiento(void* pvParameters) {
  while (1) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    int valor = valorSensor;
    int u = umbral;
    if (valor > u) {
      estado = "ALERTA!";
    } else {
      estado = "OK";
    }
    xSemaphoreGive(mutex);

    // Publicar al broker
    String mensaje = "Valor Sensor: " + String(valor) + ", Valor Máximo: " + String(u) + ", Estado: " + estado;
    client.publish(mqtt_topic_pub, mensaje.c_str());

    vTaskDelay(pdMS_TO_TICKS(3000)); 
  }
}

// Task: LCD
void TaskLCD(void* pvParameters) {
  while (1) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    int valor = valorSensor;
    int u = umbral;
    String est = estado;
    xSemaphoreGive(mutex);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor:");
    lcd.print(valor);
    lcd.setCursor(0, 1);
    lcd.print("MAX:");
    lcd.print(u);
    lcd.print("  ");
    lcd.print(est);

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// Task: MQTT
void TaskMQTT(void* pvParameters) {
  while (1) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void loop() {
  
}