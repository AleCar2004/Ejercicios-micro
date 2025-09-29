#include <Wire.h>  

void setup() {
  Wire.begin();              
  Serial.begin(115200);                   
  Serial.println("\nEscaneo de dispositivos I2C...");
}

void loop() {
  byte error, address;
  int dispositivos = 0;

  Serial.println("Buscando dispositivos...");
  
 
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado en dirección: 0x");
      if (address < 16) Serial.print("0"); 
      Serial.println(address, HEX);
      dispositivos++;
    }
    else if (error == 4) {
      Serial.print("Error desconocido en la dirección 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (dispositivos == 0) {
    Serial.println("No se encontraron dispositivos I2C.");
  } else {
    Serial.print("Total de dispositivos detectados: ");
    Serial.println(dispositivos);
  }

  delay(5000); 
}
