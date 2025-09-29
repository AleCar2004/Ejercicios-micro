const int led= 13;     
const int Puls = 5;    

bool EstadoLed = false;     
bool EstadoLedAnt = HIGH; 

void setup() {
  pinMode(led, OUTPUT);
  pinMode(Puls, INPUT_PULLUP);  
  digitalWrite(led, EstadoLed);   
  
}

void loop() {
  bool EstadoActual = digitalRead(Puls);

  if (EstadoActual == LOW && EstadoLedAnt == HIGH) {
    EstadoLed = !EstadoLed; 
    digitalWrite(led, EstadoLed);
  }

  EstadoLedAnt = EstadoActual; 

}