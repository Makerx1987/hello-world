int led1 = 13;
int led2 = 12;
int led3 = 8;
int led4 = 7;
int c = 0;
int d = 0;
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}
void loop() {
  if (c > 15)c = c - 16;
  if (c >= 8) {
    digitalWrite(led4, HIGH);
    d = c - 8;
  }
  else {
    digitalWrite(led4, LOW);
    d = c;
  }
  if (d >= 4) {
    digitalWrite(led3, HIGH);
    d = d - 4;
  }
  else {
    digitalWrite(led3, LOW);
    d = d;
  }
  if (d >= 2) {
    digitalWrite(led2, HIGH);
    d = d - 2;
  }
  else {
    digitalWrite(led2, LOW);
    d = d;
  }
  if (d >= 1) {
    digitalWrite(led1, HIGH);
    d = d - 1;
  }
  else {
    digitalWrite(led1, LOW);
    d = d;
  }
  c = c + 1;
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}
