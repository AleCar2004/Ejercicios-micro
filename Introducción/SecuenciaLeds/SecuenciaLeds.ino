int led=1;

void setup() {

pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, INPUT_PULLUP);

}

void loop() {

while(digitalRead(10)==0&&led<=8){
  led++;
  digitalWrite(led, 1);
  delay(500);
}
while(digitalRead(10)==1&&led>1){
  digitalWrite(led, 0);
  led--;
  delay(500);
}

}
