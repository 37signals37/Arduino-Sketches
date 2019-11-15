#include <CapacitiveSensor.h>
CapacitiveSensor cs1 = CapacitiveSensor(11,12);
CapacitiveSensor cs2 = CapacitiveSensor(13,14);
int button1 = 3;
int button2 = 6;
int red = 8;
int green = 9;
int blue = 10;

int value1 = 0;
const int numReadings = 50;
float readings[numReadings];      // the readings from the analog input
int readingsIter = 0;

float baseline1Total = 0;
int baseline1Average = 0;
float baseline1Sigma = 0;
boolean baseline1Set = false;

int timeConstant = 50;

void setup() {
  // initialize digital pin 8 as an output.
  pinMode(red, OUTPUT); //Red LED
  pinMode(green, OUTPUT); //Green LED
  pinMode(blue, OUTPUT); //Blue LED
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void setBaseline1ReadingsAndStats() {  
  baseline1Total = 0;  
  for (int i = 0; i < numReadings; i++) {
    baseline1Total = baseline1Total + readings[i];
  }
  baseline1Average = baseline1Total / numReadings;

  baseline1Sigma = 0;
  for (int i = 0; i < numReadings; i++) {    
    baseline1Sigma = baseline1Sigma + (readings[i] - baseline1Average) * (readings[i] - baseline1Average);
  }
  baseline1Sigma = baseline1Sigma/ (numReadings - 1);
  baseline1Sigma = sqrt(baseline1Sigma);
  baseline1Set = true;
}

void loop() {

  value1 =  cs2.capacitiveSensorRaw(timeConstant);
  readings[readingsIter++] = value1;
  if(readingsIter==numReadings){readingsIter = 0;}

//  if(value1 == 0){
//    digitalWrite(red, HIGH);  
//  }else{    
//    digitalWrite(red, LOW);
//  }
//
//  if(value1 > 100){
//    digitalWrite(blue, HIGH);  
//  }else{    
//    digitalWrite(blue, LOW);
//  }

  
  

  if(value1 > baseline1Average+1*baseline1Sigma && baseline1Set){
    digitalWrite(blue, HIGH);  
  }else{    
    digitalWrite(blue, LOW);   
  }

  if(value1 < baseline1Average-1*baseline1Sigma && baseline1Set){
    digitalWrite(red, HIGH);  
  }else{    
    digitalWrite(red, LOW);   
  }
  
  if(digitalRead(button1) == 1){
    setBaseline1ReadingsAndStats();
    for(int i = 0; i<3; i++){
      digitalWrite(red, HIGH);   // turn the Red LED on (HIGH is the voltage level)
      digitalWrite(green, HIGH);   // turn the Red LED on (HIGH is the voltage level)
      digitalWrite(blue, HIGH);   // turn the Red LED on (HIGH is the voltage level)
      delay(250);
      digitalWrite(red, LOW);   // turn the Red LED on (HIGH is the voltage level)
      digitalWrite(green, LOW);   // turn the Red LED on (HIGH is the voltage level)
      digitalWrite(blue, LOW);   // turn the Red LED on (HIGH is the voltage level)
      delay(250);
    }
  }  
}
