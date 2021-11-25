#include <Servo.h>
#define SERVO_PIN 40

Servo servo;
void setup() {
  // put your setup code here, to run once:
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000); 
}
