#include <EEPROM.h>

int encendido = 0;

void setup() {
  
  Serial.begin(9600);
  
  encendido = EEPROM.read(0);
  Serial.print("El sistema se ha encendido ");
  Serial.print(encendido);
  Serial.println(" veces");
  encendido++;
  EEPROM.update(0, encendido);

}

void loop() {
  // put your main code here, to run repeatedly:

}
