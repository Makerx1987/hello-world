#include <Servo.h>
Servo sg90;
const int sgpin = 0 ;

const int motor_a1 = 2 ;
const int motor_a2 = 4 ;
const int speedpin1 = 6 ;

const int motor_b1 = 5 ;
const int motor_b2 = 9 ;
const int speedpin2 = 3 ;

const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int led4 = 10;
const int ledadd = 7;

// 读取的值,0为白色
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
bool allstop = false;
int counter = 1;

void nmsl_smart() {
  readsensor();
  while (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1)
    return;
  nmsl_smart();
}
void readsensor() {
  s1 = digitalRead(led1);
  s2 = digitalRead(led2);
  s3 = digitalRead(led3);
  s4 = digitalRead(led4);
}

// 差速修正向右偏
void motor_right() {
  analogWrite(speedpin1, 200); //
  analogWrite(speedpin2, 0); //
}

// 差速修正向左偏
void motor_left() {
  analogWrite(speedpin1, 0); //
  analogWrite(speedpin2, 200); //
}
// 直行
void motor_run() {
  analogWrite(speedpin1, 210); //这是右边
  analogWrite(speedpin2, 190); //这是左边
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

  analogWrite(speedpin1, 100); //
  analogWrite(speedpin2, 100); //
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
  motor_run();
  delay(50);

  digitalWrite(motor_a1, LOW); // in1
  digitalWrite(motor_a2, HIGH); // in2
  digitalWrite(motor_b1, HIGH); // in3
  digitalWrite(motor_b2, LOW); // in4

  analogWrite(speedpin1, 250); //
  analogWrite(speedpin2, 250); //

  delay(400);

  nmsl_smart();

}
// 右拐
void motor_turn_right() {
  motor_run();
  delay(50);

  digitalWrite(motor_a1, HIGH); // in1
  digitalWrite(motor_a2, LOW); // in2
  digitalWrite(motor_b1, LOW); // in3
  digitalWrite(motor_b2, HIGH); // in4

  analogWrite(speedpin1, 250); //
  analogWrite(speedpin2, 250); //

  delay(400);

  nmsl_smart();
}
void motor_trans() {
  //  while (s1 != 1 && s2 != 0 && s3 != 0 && s4 != 1) {
  //    motor_back();
  //    motor_run();
  //    delay(10);
  //    readsensor();
  //  }
  //  motor_turn_left();
  //  delay(200);
  //  while (s1 != 1 && s2 != 0 && s3 != 0 && s4 != 1) {
  //    motor_turn_left();
  //    delay(10);
  //    readsensor();
  //  }
}
// 舵机动一动
void servo_on() {
  sg90.write(0);
  delay(3000);
  sg90.write(40);
  delay(1000);
  sg90.write(0);
}

void much() {
  digitalWrite(ledadd, HIGH);
  delay(300);
  if (counter == 1 || counter == 9) { //起点到终点
    motor_stop();
    servo_on();
  }
  else  if (counter == 5) {
    motor_turn_left();
  } else  if (counter == 7) {
    motor_turn_right();
  } else  if (counter == 0) {
    motor_trans();
  }
  else  if (counter > 9) {
    motor_stop();
    allstop = true;
  }
  else if (counter == 8) {
    delay(200);
    motor_stop();
    allstop = true;
  }
  else {
    motor_ahead();
    motor_run();
  }
  counter = counter + 1;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  counter = 1;
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
  pinMode(ledadd, OUTPUT);
}

void loop() {
  digitalWrite(ledadd, LOW);
  if (allstop)return;
  readsensor();
  if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1) { //前进
    motor_ahead();
    motor_run();
    delay(1);
  }
  else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1) { //向右修正
    motor_ahead();
    motor_right();
    delay(1);
  }
  else if (s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1) { //向左修正
    motor_ahead();
    motor_left();
    delay(1);
  }
  else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) { //倒车
    motor_back();
  }
  else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1) {
    //      motor_ahead();
    //      motor_right();
  }
  else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0) {
    //      motor_ahead();
    //      motor_right();
  }
  else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0) {
    motor_ahead();
    motor_left();
    delay(1);
  }
  else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1) {
    motor_ahead();
    motor_left();
    delay(1);
  }
  else {
    much();
  }
  //    Serial.println(counter);

}
