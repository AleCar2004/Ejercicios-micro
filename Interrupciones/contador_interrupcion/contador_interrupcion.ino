void setup() {
  attachInterrupt(digitalPinToInterrupt(2), cuenta, RISING);
  Serial.begin(9600);
 

}

void loop() {
  

}

void cuenta(){
  int cont=0;
  Serial.println(cont);
  cont++;
}