int ds = 11;
int stcp = 12;
int shcp = 13;
int c = 0;
int f;
//int oldstate = HIGH;
//int newstate = HIGH;
int m[10][8] = \
{ 0, 0, 1, 1, 1, 1, 1, 1, \
  0, 0, 0, 0, 0, 1, 1, 0, \
  0, 1, 0, 1, 1, 0, 1, 1, \
  0, 1, 0, 0, 1, 1, 1, 1, \
  0, 1, 1, 0, 0, 1, 1, 0, \
  0, 1, 1, 0, 1, 1, 0, 1, \
  0, 1, 1, 1, 1, 1, 0, 1, \
  0, 0, 0, 0, 0, 1, 1, 1, \
  0, 1, 1, 1, 1, 1, 1, 1, \
  0, 1, 1, 0, 1, 1, 1, 1,
};

void tozero() {
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(ds, LOW);
    digitalWrite(shcp, HIGH);
    digitalWrite(shcp, LOW);
  }
  digitalWrite(stcp, HIGH);
  digitalWrite(stcp, LOW);
  digitalWrite(shcp, LOW);
  c = 0;
}

void setup() {
  pinMode(ds, OUTPUT);
  pinMode(stcp, OUTPUT);
  pinMode(shcp, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  digitalWrite(ds, LOW);
  digitalWrite(stcp, LOW);
  digitalWrite(shcp, LOW);
  attachInterrupt(0, tozero, LOW);
}

void loop() {
  int i;
  if (c > 9)c = 0;
  for (i = 0; i < 8; i++)
  {
    f = m[c][i];
    if (f > 0)
    {
      digitalWrite(ds, HIGH);
      digitalWrite(shcp, HIGH);
      digitalWrite(shcp, LOW);
    }
    else
    {
      digitalWrite(ds, LOW);
      digitalWrite(shcp, HIGH);
      digitalWrite(shcp, LOW);
    }
  }
  digitalWrite(stcp, HIGH);
  digitalWrite(stcp, LOW);
  digitalWrite(shcp, LOW);
  c = c + 1;
  delay(1000);
}
