#include <Servo.h>
Servo sg90;
const int sgpin = 9 ;

const int motor_a1 = 2 ;
const int motor_a2 = 4 ;
const int speedpin1 = 3 ;

const int motor_b1 = 5 ;
const int motor_b2 = 7 ;
const int speedpin2 = 6 ;

const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int led4 = 10;
// 读取的值,0为白色
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
bool allstop = false;
int counter = 0;
// 差速修正向右偏
void motor_right() {
  analogWrite(speedpin1, 255); //
  analogWrite(speedpin2, 100); //
}

// 差速修正向左偏
void motor_left() {
  analogWrite(speedpin1, 100); //
  analogWrite(speedpin2, 255); //
}
// 直行
void motor_run() {
  analogWrite(speedpin1, 255); //
  analogWrite(speedpin2, 255); //
}
// 停止
void motor_stop() {
  analogWrite(speedpin1, 0); //
  analogWrite(speedpin2, 0); //
}

// 倒车
void motor_back() {
  digitalWrite(motor_a1, LOW); // in1
  digitalWrite(motor_a2, HIGH); // in2
  digitalWrite(motor_b1, LOW); // in3
  digitalWrite(motor_b2, HIGH); // in4
}
// 前进
void motor_ahead() {
  digitalWrite(motor_a1, HIGH); // in1
  digitalWrite(motor_a2, LOW); // in2
  digitalWrite(motor_b1, HIGH); // in3
  digitalWrite(motor_b2, LOW); // in4
}
// 左拐
void motor_turn_left() {
  digitalWrite(motor_a1, LOW); // in1
  digitalWrite(motor_a2, HIGH); // in2
  digitalWrite(motor_b1, HIGH); // in3
  digitalWrite(motor_b2, LOW); // in4
  while (s1 != 1 && s2 != 0 && s3 != 0 && s4 != 1) {
    //    motor_ahead();
    //    motor_left();
    //    delay(100);
    //    motor_back();
    //    motor_right();
    //    delay(100);
    analogWrite(speedpin1, 100); //
    analogWrite(speedpin2, 255); //
    delay(10);
    readsensor();
  }
}
// 右拐
void motor_turn_right() {
  digitalWrite(motor_a1, HIGH); // in1
  digitalWrite(motor_a2, LOW); // in2
  digitalWrite(motor_b1, LOW); // in3
  digitalWrite(motor_b2, HIGH); // in4
  while (s1 != 1 && s2 != 0 && s3 != 0 && s4 != 1) {
    //    motor_ahead();
    //    motor_left();
    //    delay(100);
    //    motor_back();
    //    motor_right();
    //    delay(100);
    analogWrite(speedpin1, 255); //
    analogWrite(speedpin2, 100); //
    delay(10);
    readsensor();
  }
}
void motor_trans() {
  while (s1 != 1 && s2 != 0 && s3 != 0 && s4 != 1) {
    motor_back();
    motor_run();
    delay(10);
    readsensor();
  }
  motor_turn_left();
  delay(200);
  while (s1 != 1 && s2 != 0 && s3 != 0 && s4 != 1) {
    motor_turn_left();
    delay(10);
    readsensor();
  }
}
// 舵机动一动
void servo_on() {
  sg90.write(0);
  delay(3000);
  sg90.write(40);
  delay(1000);
  sg90.write(0);
}
void readsensor() {
  s1 = digitalRead(led1);
  s2 = digitalRead(led2);
  s3 = digitalRead(led3);
  s4 = digitalRead(led4);
}
void much() {
  if (counter == 0) {
    motor_stop();
    servo_on();
  }
  else  if (counter == 0) {
    motor_turn_left();
  } else  if (counter == 0) {
    motor_turn_right();
  } else  if (counter == 0) {
    motor_trans();
  } else {
    motor_ahead();
    motor_run();
  }
  counter = counter + 1;
}
void setup() {
  // put your setup code here, to run once:
  counter = 0;
  allstop = false;
  sg90.attach(sgpin);
  Serial.begin(9600);
  pinMode(motor_a1, OUTPUT);
  pinMode(motor_a2, OUTPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);
  pinMode(speedpin1, OUTPUT);
  pinMode(speedpin2, OUTPUT);
  pinMode(led1, INPUT);
  pinMode(led2, INPUT);
  pinMode(led3, INPUT);
  pinMode(led4, INPUT);
}

void loop() {
  if (allstop)return;
  readsensor();
  if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1) { //前进
    motor_ahead();
    motor_run();
    delay(10);
  }
  else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1) { //右偏
    motor_ahead();
    motor_right();
    delay(10);
  }
  else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1) { //左偏
    motor_ahead();
    motor_left();
    delay(10);
  }
  else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) { //倒车
    motor_back();
    motor_run();
    delay(10);
  }
  else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1) { //倒车

  }
  else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0) { //倒车

  }
  else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0) { //倒车

  }
  else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1) { //倒车

  }
  else {
    much();
  }

}
