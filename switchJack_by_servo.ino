#include <Servo.h>
#define pin 8

#define UP 110
#define DOWN 76
#define STOP 86
Servo myServo;
char str;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(pin);
  myServo.write(STOP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  test();
  str = "";
  if (Serial.available()) {
    str = Serial.read();
  }
  if (str == 'u') {
    //up
    myServo.write(UP);
  }
  if (str == 'd') {
    //down
    myServo.write(DOWN);
  }
  if (str == 's') {
    //stop
    myServo.write(STOP);
  }
}

void test() {
  myServo.write(78);
  delay(1000);
  myServo.write(90);
  delay(1000);
  myServo.write(110);
  delay(1000);
  myServo.write(90);
  delay(1000);
}
