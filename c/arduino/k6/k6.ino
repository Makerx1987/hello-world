#include <MsTimer2.h>
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
int g1 = 7;
int g2 = 8;
int ds = 11;
int stcp = 12;
int shcp = 13;
int tonepin = 6;
int c = 0;
int f;
int kf;
int nf;
int ttt = 0;
int m[10][8] = \
{ 1, 0, 0, 0, 0, 0, 0, 0, \
  1, 1, 1, 0, 1, 0, 0, 1, \
  0, 0, 1, 0, 0, 1, 0, 0, \
  0, 0, 1, 0, 1, 0, 0, 0, \
  0, 1, 0, 0, 1, 0, 0, 1, \
  0, 0, 0, 0, 1, 0, 1, 0, \
  0, 0, 0, 0, 0, 0, 1, 0, \
  1, 1, 1, 0, 1, 0, 0, 0, \
  0, 0, 0, 0, 0, 0, 0, 0, \
  0, 0, 0, 0, 1, 0, 0, 0, \
};

int hz[10] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5};
void buliang() {
  for (int i = 0; i < 8; i++)
  {

    digitalWrite(ds, HIGH);
    digitalWrite(shcp, HIGH);
    digitalWrite(shcp, LOW);
  }
  digitalWrite(stcp, HIGH);
  digitalWrite(stcp, LOW);
  digitalWrite(shcp, LOW);
}
void liang(int z)
{
  for (int i = 0; i < 8; i++)
  {
    f = m[z][i];
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
}

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

void tick() {
  
  if (c > 99)c = 0;
  kf = c % 10;
  nf = c / 10;
  c = c + 1;
}

void setup() {
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(ds, OUTPUT);
  pinMode(stcp, OUTPUT);
  pinMode(shcp, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(tonepin, OUTPUT);
  digitalWrite(stcp, LOW);
  digitalWrite(shcp, LOW);
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  MsTimer2::set(1000, tick);
  MsTimer2::start();
  attachInterrupt(0, tozero, LOW);
}

void loop() {

  int period;
  if (c > 0)period = 1000000L / hz[c % 10 ];
  int pulse = period / 2;
  digitalWrite(tonepin, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(tonepin, LOW);
  delayMicroseconds(pulse);

  liang(kf);
  digitalWrite(g1, LOW);
  digitalWrite(g2, HIGH);
  delayMicroseconds(80);

//  buliang();
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  delayMicroseconds(80);
  
  liang(nf);
  digitalWrite(g1, HIGH);
  digitalWrite(g2, LOW);
  delayMicroseconds(80);

//  buliang();
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  delayMicroseconds(80);

}

