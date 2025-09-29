#include <EEPROM.h>
int config = 0;

void setup() {
  Serial.begin(9600);

  EEPROM.get(0, config);

  Serial.println("=== Menu de Configuracion ===");
  Serial.println("Seleccione una opcion:");
  Serial.println("0 - Lenta");
  Serial.println("1 - Media");
  Serial.println("2 - Rapida");
  Serial.println("-----------------------------");
  Serial.print("Configuracion actual: ");
  Serial.println(config);

}

void loop() {
  if (Serial.available() > 0) {
    char opcion = Serial.read();

    if (opcion >= '0' && opcion <= '2') {
      config = opcion - '0'; 
      EEPROM.put(0, config); 
      Serial.print("Nueva configuracion guardada: ");
      Serial.println(config);
    }
  }
}
