#include <Servo.h>

Servo myservo;
int servoPin = 9;
int servoDelayTime = 5000;
  
void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
}

void loop() {
  myservo.write(0);
  delay(servoDelayTime);
  myservo.write(90);
  delay(servoDelayTime);  
}
