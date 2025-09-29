volatile bool alarmaActiva = false;
volatile bool buzzerEncendido = false;
int frecuencia = 1000; 
void setup() {
 
  pinMode(6, OUTPUT);   // Buzzer (OC2A)
  pinMode(2, INPUT);   
  pinMode(3, INPUT);    

  
  attachInterrupt(digitalPinToInterrupt(2), activarAlarma, RISING);
  attachInterrupt(digitalPinToInterrupt(3), desactivarAlarma, RISING);

 
  TCCR2A = (1 << COM2A0) | (1 << WGM21);  
  TCCR2B = 0; 
  OCR2A = calcularOCR2A(frecuencia); 

  TIMSK2 = (1 << OCIE2A);
}

void loop() {
 
}


void activarAlarma() {
  if (!alarmaActiva) {
    alarmaActiva = true;
    Serial.println("¡Movimiento detectado! Alarma activada.");

    
    TCCR2B = (1 << CS22);  
  }
}


void desactivarAlarma() {
  if (alarmaActiva) {
    alarmaActiva = false;
    Serial.println("Botón presionado. Alarma desactivada.");

    TCCR2B = 0;
    digitalWrite(6, LOW);  
  }
}


ISR(TIMER2_COMPA_vect) {
  if (alarmaActiva) {
   
    static int delta = 100;
    frecuencia += delta;

    if (frecuencia > 2000 || frecuencia < 500) {
      delta = -delta; 
    }

    OCR2A = calcularOCR2A(frecuencia);
  }
}


int calcularOCR2A(int freq) {
 
  int ocr = (16000000UL / (2 * 64UL * freq)) - 1;
  return constrain(ocr, 0, 255); 
}
