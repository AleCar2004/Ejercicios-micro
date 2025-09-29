int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;


int dec = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(10, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(10)==0) {
    dec++;
    if (dec > 15) {
      dec = 0;}
    binario(dec);
    delay(200);
  }
}

void binario(int dec) {
  digitalWrite(led1, dec & 1);
  digitalWrite(led2, dec & 2);
  digitalWrite(led3, dec & 4);
  digitalWrite(led4, dec & 8);
}