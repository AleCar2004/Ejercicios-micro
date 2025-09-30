#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

Adafruit_BMP280 bmp; 


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");

  
  if (!bmp.begin(0x76)) { 
    Serial.println("No se encontró BMP280");
    lcd.clear();
    lcd.print("BMP280 ERROR");
    while (1);
  }

  lcd.clear();
  lcd.print("BMP280 listo");
  delay(1000);
}

void loop() {
  float temperatura = bmp.readTemperature();
  float presion = bmp.readPressure() / 100.0F; 

  Serial.print("Temp: ");
  Serial.print(temperatura);
  Serial.print(" *C  |  ");
  Serial.print("Presion: ");
  Serial.print(presion);
  Serial.println(" hPa");

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1); 
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Pres: ");
  lcd.print(presion, 0); 
  lcd.print(" hPa");

  delay(2000); 
}
