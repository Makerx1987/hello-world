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
int ds = 11;
int stcp = 12;
int shcp = 13;
int tonepin = 6;
int c = 0;
int f;
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
//int hz[10] = {262, 294, 330, 350, 392,  440,  494,  523,  587, 660};
int hz[10] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5};

//void newtone(byte tonePin, int frequency, int duration = 0) {
//  int period = 1000000L / frequency;
//  int pulse = period / 2;
//  for (long i = 0; i < duration * 1000L; i += period) {
//    digitalWrite(tonePin, HIGH);
//    delayMicroseconds(pulse);
//    digitalWrite(tonePin, LOW);
//    delayMicroseconds(pulse);
//  }
//}
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
  int i;
  noTone(6);
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

  //  for (i = 0; i < hz[c]; i++) //输出一个频率的声音
  //  {
  //    digitalWrite(tonepin, HIGH); //发声音
  //    delay(1);//延时1ms
  //    digitalWrite(tonepin, LOW); //不发声音
  //    delay(1);//延时ms
  //  }

  //  digitalWrite(tonepin, HIGH);
  //  delayMicroseconds(pulse);
  //  digitalWrite(tonepin, LOW);
  //  delayMicroseconds(pulse);
  c = c + 1;
}

void setup() {
  pinMode(ds, OUTPUT);
  pinMode(stcp, OUTPUT);
  pinMode(shcp, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(tonepin, OUTPUT);
  digitalWrite(stcp, LOW);
  digitalWrite(shcp, LOW);
  MsTimer2::set(1000, tick);
  MsTimer2::start();
  attachInterrupt(0, tozero, LOW);
}

void loop() {

  int period;
  if (c > 0)period = 1000000L / hz[c - 1];
  int pulse = period / 2;
  digitalWrite(tonepin, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(tonepin, LOW);
  delayMicroseconds(pulse);

}

