int led1=3;
int luz=0;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  if(luz<0)
  luz=0;
  if(luz>255)
  luz=255;

  if(digitalRead(10)==0)
    luz=luz+5;

  if(digitalRead(11)==0)
    luz=luz-5;
  
  digitalWrite(led1, luz);
  
  Serial.println(luz);
  
  delay(200);
}