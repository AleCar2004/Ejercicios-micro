
void setup() {
  pinMode(5, OUTPUT);

  TCCR1A = 0;                
  TCCR1B = 0;                
  TCNT1  = 0;

  // Frecuencia del Arduino UNO: 16 MHz
  // Prescaler = 1024  →  16,000,000 / 1024 = 15625 ticks por segundo
  // Para 500 ms → necesitamos 7812.5 ticks ≈ 7812
  OCR1A = 7812;             

  TCCR1B |= (1 << WGM12);   
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);   

}

void loop() {

}
ISR(TIMER1_COMPA_vect) {
  digitalWrite(5, !digitalRead(5)); 
}