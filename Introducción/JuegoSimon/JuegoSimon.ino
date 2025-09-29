#define NUM_LEDS 4
#define MAX_SECUENCIA 50

int leds[NUM_LEDS] = {2, 3, 4, 5};
int botones[NUM_LEDS] = {6, 7, 8, 9};

int secuencia[MAX_SECUENCIA];
int nivel = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botones[i], INPUT_PULLUP); 
  }

  randomSeed(analogRead(A0));
  nivel = 1;
  secuencia[0] = random(NUM_LEDS);
  delay(1000);
}

void loop() {
  
  for (int i = 0; i < nivel; i++) {
    digitalWrite(leds[secuencia[i]], HIGH);
    delay(500);
    digitalWrite(leds[secuencia[i]], LOW);
    delay(250);
  }

  
  for (int i = 0; i < nivel; i++) {
    int botonPresionado = -1;
    while (botonPresionado == -1) {
      for (int j = 0; j < NUM_LEDS; j++) {
        if (digitalRead(botones[j]) == LOW) {
          botonPresionado = j;
          digitalWrite(leds[j], HIGH);
          delay(300);
          digitalWrite(leds[j], LOW);
          delay(200);
        }
      }
    }

    if (botonPresionado != secuencia[i]) {
      Serial.println("❌ Fallaste. Reiniciando...");
      nivel = 1;
      secuencia[0] = random(NUM_LEDS);
      delay(1000);
      return; // Salir del loop y reiniciar
    }
  }

  
  nivel++;
  if (nivel >= MAX_SECUENCIA) {
    Serial.println("🎉 ¡Ganaste el juego completo!");
    nivel = 1;
  }
  secuencia[nivel - 1] = random(NUM_LEDS);
  delay(1000);
}
