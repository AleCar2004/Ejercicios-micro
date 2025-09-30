#include <Wire.h>

int numero = 0;

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(8);   
  Wire.write(numero);          
  Wire.endTransmission();

  Serial.print("Enviado: ");
  Serial.println(numero);

  numero++;                     
  if (numero > 99) numero = 0;  

  delay(1000); 
}
