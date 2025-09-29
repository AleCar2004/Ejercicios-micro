int cont = 0;
bool time = false;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), pulsos, RISING);
  pinMode(5, OUTPUT);
  
  TCCR1A = 0;                
  TCCR1B = 0;                
  TCNT1  = 0;

  OCR1A = 15625;             

  TCCR1B |= (1 << WGM12);   
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

}

void loop() {
  if(time){
   noInterrupts();
    int frec = cont;
    cont = 0;
    time = false;
    interrupts();
    Serial.print("La frecuencia de pulsos es: ");
    Serial.print(frec);
    Serial.println(" Hz");
  }
}

ISR(TIMER1_COMPA_vect){
  time = true;
}

void pulsos(){
  cont++;
}