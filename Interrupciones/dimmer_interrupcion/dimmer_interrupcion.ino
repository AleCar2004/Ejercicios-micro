int led=0;
bool dir=false;
void setup() {
  attachInterrupt(digitalPinToInterrupt(3), direccion, RISING);
  pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(5, led);
   delay(200);
  if(dir==false){
    led=led+20;
  }else{
    led=led-20;
  }

}
void direccion(){
  !dir;
}