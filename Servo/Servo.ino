#include <Servo.h>

Servo servo1;
int endPos = 150;
int servoPos = endPos;
int servoIncrement = 1;
int delayTime = 10;

int cwPin = 7;
int ccwPin = 8;
int resetPin = 4;

int cwVal = 0;
int ccwVal = 0;
int resetVal = 0;

boolean cw = false;
boolean ccw = false;
boolean reset = false;

float dipTime = 600000;
//int dipTime = 10000;
int dipInterval = dipTime/90;


void setup() {

  servo1.attach(9);
  servo1.write(servoPos);
  
  pinMode(cwPin, INPUT_PULLUP);
  digitalWrite(cwPin, LOW);
  pinMode(ccwPin, INPUT_PULLUP);
  digitalWrite(ccwPin, LOW);
  pinMode(resetPin, INPUT_PULLUP);
  digitalWrite(resetPin, LOW);


  Serial.begin(19200);
  Serial.println("Ready");
  
  }

void loop() {

  cwVal = 0;
  ccwVal = 0;
  resetVal = 0;
  
  cwVal = digitalRead(cwPin);
  ccwVal = digitalRead(ccwPin);
  resetVal = digitalRead(resetPin);

  Serial.print(servoPos);
  Serial.print("   ");
  Serial.print(cwVal);
  Serial.print("   ");
  Serial.print(ccwVal);
  Serial.print("   ");
  Serial.println(resetVal);
  delay(1);
    
  if(cwVal==1 && servoPos>1){
      servoPos = servoPos - servoIncrement;
      Serial.println("Clockwise ");
      Serial.println(servoPos);    
      servo1.write(servoPos);  
      delay(delayTime);
  }
  if(ccwVal==1 && servoPos<endPos){
      servoPos = servoPos + servoIncrement;
      Serial.print("Counter Clockwise ");
      Serial.println(servoPos);    
//      servo1.write(179);
      servo1.write(servoPos);
      delay(delayTime);
  }
  if(resetVal==1){
    servoPos = endPos;
    Serial.println("Reset ");
    Serial.println(servoPos);
    servo1.write(servoPos);
    delay(delayTime);
  };

  if(cwVal == 1 && resetVal==1){
    raise();
  }
  
}

void raise() {
  for (int j=0;j<40;j++){
    for(int i = endPos; i > 59; i--){
      delay(dipInterval);
      servoPos = i;
      servo1.write(servoPos);      
    }
  
    for(int i = 59; i < endPos; i++){
      delay(dipInterval);
      servoPos = i;
      servo1.write(servoPos);      
    }
  }
}

