#include <Servo.h>
Servo servo;

void servo_setup(int servoPin)
{
  servo.attach(servoPin);
}

void rotate0() {
  servo.write(0);
}

void rotate180() {
  servo.write(180);
//  for (int i = 180; i >= 0; i--)
//  {
//    servo.write(i);
//    delay(10);
//  }
  //  servo.write(180);
}
