#include <Servo.h>

Servo myservo;
int servoPin = 9;
int measurementDelayTime = 10;
int numOfMeasurements = 200;
int servoDelayTime = 6000 - (measurementDelayTime * numOfMeasurements);
int cycleCounter = 0;

int analogPin = A0;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = 5000;
float R2 = 0;
float buffer = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  
  Serial.print("Measurement Delay Time: ");
  Serial.print(measurementDelayTime);
  Serial.print("     Number of Measurements: ");
  Serial.print(numOfMeasurements);
  Serial.print("     ServoDelayTime: ");
  Serial.println(servoDelayTime);
  Serial.println("------------");

}

void takeMeasurements(int cycleCounter, int srvPos){
  float sum = 0.0;
  int goodCounts = 0;
  float measurements[numOfMeasurements];
  float average = 0.0;
  
  for(int i = 0; i < numOfMeasurements; i++){
    raw= analogRead(analogPin);    
    if(raw){
      sum += raw;
      measurements[goodCounts] = raw;
      goodCounts++;      
    }
  }

  average = sum/goodCounts;
  float stdDev = 0.0;
  
  for(int i = 0; i<goodCounts; i++){
    stdDev += sq((measurements[i] - average));
  }
  stdDev = sqrt(stdDev/(goodCounts-1));

  if(srvPos == 0){
    Serial.print("Cycle Counter: ");
    Serial.print(cycleCounter);
    Serial.print(" | ");
  }
  Serial.print(srvPos);
  Serial.print(" | ");

  
  Serial.print("Average: ");
  Serial.print(average);
  Serial.print(" | ");
  Serial.print("Standard Deviation: ");
  if(srvPos == 0){
    Serial.print(stdDev);
    Serial.print(" | ");
  }else{
    Serial.println(stdDev);
  }
           
//  buffer= raw * Vin;
//  Vout= (buffer)/1024.0;
//  buffer= (Vin/Vout) -1;
//  R2 = R1 * buffer;
      
  delay(measurementDelayTime);
  
  
  
}

void loop() {
  
  myservo.write(0);
  delay(servoDelayTime);
  takeMeasurements(cycleCounter, 0);

  myservo.write(95);
  delay(servoDelayTime);
  takeMeasurements(cycleCounter, 90);

  cycleCounter++;
}
