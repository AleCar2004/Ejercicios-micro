int led1=2;
int led2=3;

void setup() {
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(10, INPUT_PULLUP);
pinMode(11, INPUT_PULLUP);

}

void loop() {
if(digitalRead(10)==0){
  while(digitalRead(11)!=0){
     digitalWrite(led1, 1);
    
    delay(300);
    digitalWrite(led1, 0);
    digitalWrite(led2, 1);
   
    delay(300);
    digitalWrite(led2, 0);
    
  }
}

}
