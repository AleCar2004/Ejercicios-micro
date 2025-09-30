#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  if (!bmp.begin(0x76)) { 
    Serial.println("No se encontró BMP280");
    while (1);
  }
  Serial.println("Maestro 1 listo");
}

void loop() {
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure() / 100.0F;

  Serial.print("Maestro 1 -> Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Pres: ");
  Serial.print(pres);
  Serial.println(" hPa");

  delay(2000); 
}
