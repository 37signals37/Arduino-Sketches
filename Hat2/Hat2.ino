#include <CapacitiveSensor.h>

int pwmPin = 3;
int cycleDelay = 1000;
int cycleCounter = 0;
int state = 0; //0: not worn  1: not worn, being tapped  2: being worn  3: being worn, being tapped
int prevState = 0;
int mode = 3; //1:off  2:flashing  3:perm on
boolean indicating = false; //indicating mode through flashes
int pwmVal = 135;
int pwmMin = 0;
int beingWornThreshold = 350;

const int numReadings = 4;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
float average = 0;                // the average
float prevAve = 0;
int latestreading = 0;

float stdev = 0;
float prevstdev = 0;

int startUpCounter = 0;

CapacitiveSensor   cs_5_2 = CapacitiveSensor(8,12);

void setup()
{
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);

//  analogWrite(pwmPin, 0);
//  delay(2000);
//  analogWrite(pwmPin, pwmVal);
//  delay(2500);
//  analogWrite(pwmPin, 0);
}

void loop(){

  long value =  cs_5_2.capacitiveSensor(500);

  //Averaging and array storage
  total = total - readings[readIndex];
  latestreading = value;
  readings[readIndex] = latestreading;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  average = total / numReadings;

  if (readIndex >= numReadings){
      readIndex = 0;
  }

  //Standard Deviation Calculation
  stdev = 0;
  for(int i=0; i<numReadings;i++){
    stdev = (average-value)*(average-value);
  }
  stdev = stdev/(numReadings-1);
  stdev = sqrt(stdev);

  if(value > 5*prevAve && startUpCounter >= numReadings){
      state++;
  }

  Serial.print(value);
  Serial.print("\t");
  Serial.print(average);
  Serial.print("\t");
  Serial.print(stdev);
  Serial.print("\t");
  Serial.println(state);

//  if(value < 175){state = 0;}  //!worn, !tapped
//  if(value >= 175){state = 1;} //worn or tapped  
//  if(value >= 750){state = 2;} //worn and tapped  

//  Serial.println(value);
//  Serial.print("   CycleCounter: ");
//  Serial.print(cycleCounter);
//  Serial.print("   State: ");
//  Serial.print(state);
//  Serial.print("   PrevState: ");
//  Serial.println(prevState);


//  if(state == 0 && prevState > 0){
//    analogWrite(pwmPin, 0);    
//    if(cycleCounter <5){
//      mode = mode+1;
//      if(mode == 5){mode = 1;}    
//      for(int i = 0; i<mode; i++){
//        Serial.println("FLASH");
//        analogWrite(pwmPin, pwmVal);
//        delay(400);
//        analogWrite(pwmPin, 0);
//        delay(400);
//      }
//    }
//    analogWrite(pwmPin, 0);
//    cycleCounter = 0;
//  }
//
//  if(state == 1 && prevState == 0){
//    cycleCounter = 1;
//  }
//
//  if(state >= 1 && prevState >= 1 && value >= beingWornThreshold){
//    cycleCounter++;
//    if(cycleCounter > 15){
//      Serial.println("BEING WORN");
//      
//      if(mode==1){
//        analogWrite(pwmPin, 0);
////        Serial.println("Light Off");
//      }
//      if(mode==2){
//        if(value<900){
//          analogWrite(pwmPin, pwmVal);                    
//        }else if(value <1200){
//          analogWrite(pwmPin, 0);
//        }else if(value <1600){
//          analogWrite(pwmPin, 20);
//        }else{
//          analogWrite(pwmPin, pwmVal);
//        }                               
//        Serial.print("Light On ");
//      }
//      if(mode==3){
//        if(value<900){
//          analogWrite(pwmPin, 0);
//        }else if(value <1200){
//          analogWrite(pwmPin, 20);
//        }else if(value <1600){
//          analogWrite(pwmPin, 40);
//        }else{
//          analogWrite(pwmPin, pwmVal);
//        }
//        Serial.print("Mode 3: Light Off except when touched ");
//      }
//      if(mode==4){
//        for(int i=0;i<pwmVal;i++){
//          analogWrite(pwmPin, i);
//          delay(12);
//        }
//
//        delay(750);
//        
//        for(int i=pwmVal;i>0;i=i-1){
//          analogWrite(pwmPin, i);
//          delay(12);
//        }
//        analogWrite(pwmPin, 0);
//        delay(1500);
//        Serial.println("Blinking");
//      }      
//    }
//  }

  if(startUpCounter<numReadings){startUpCounter++;}
  prevState = state;
  prevAve = average;
  prevstdev = stdev;
  delay(cycleDelay);  
}
