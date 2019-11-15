//http://www.instructables.com/id/How-To-Use-Touch-Sensors-With-Arduino/
#include <CapacitiveSensor.h>

int loopDelay = 100;

int value = 0;
const int numReadings = 10;
long readings[numReadings];      // the readings from the analog input
long total = 0;                  // the running total
float average = 0;                // the average
float prevAve = 0;
float sigma = 0;

int touchThreshold = 3000;

int debounce = 250;
int threshold = 100;
int motorPin = 5;

int buttonPin = 13;
//int buttonPin2 = 4;

// 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired// To add more sensors...//CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
//CapacitiveSensor   cs_10_9 = CapacitiveSensor(10,9);
CapacitiveSensor   cs_10_12 = CapacitiveSensor(10,12);

void setup()                    
{
//  cs_10_9.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
  cs_10_12.set_CS_AutocaL_Millis(0xFFFFFFFF);
//  pinMode(motorPin, OUTPUT);

  pinMode(buttonPin, INPUT);
//  pinMode(buttonPin2, INPUT);
//
//  pinMode(5, OUTPUT);
//  pinMode(7, OUTPUT);
//  pinMode(10, OUTPUT);
//  pinMode(12, OUTPUT);
  
  Serial.begin(9600);
  while (! Serial);
}

void loop(){    

  
  
  Serial.println(digitalRead(buttonPin));  

//      value =  cs_10_12.capacitiveSensorRaw(25);
//      Serial.print(value);
//      Serial.print("   ");
//      Serial.println(digitalRead(buttonPin));
      
//      if(digitalRead(buttonPin) == 1){
//        digitalWrite(motorPin, HIGH);
//        delay(1000);
//        digitalWrite(motorPin, LOW);
//      }
      delay(100);
//
//      if(value >=0 && value < 500){
//        digitalWrite(lP1, HIGH);
//      }else{digitalWrite(lP1, LOW);}
//
//      if(value >=500 && value < 2000){
//        digitalWrite(lP2, HIGH);
//      }else{digitalWrite(lP2, LOW);}
//
//      if(value >=2000 && value < 3000){
//        digitalWrite(lP3, HIGH);
//      }else{digitalWrite(lP3, LOW);}
//
//      if(value >=3000 && value < 4000){
//        digitalWrite(lP4, HIGH);
//      }else{digitalWrite(lP4, LOW);}
//
//      if(value >=4000 && value < 5000){
//        digitalWrite(lP5, HIGH);
//      }else{digitalWrite(lP5, LOW);}
//
//      if(value >=5000){  
//        digitalWrite(lP6, HIGH);
////        digitalWrite(motorPin, HIGH);
//      }else{
//        digitalWrite(lP6, LOW);
////        digitalWrite(motorPin, LOW);
//      }
      
//      digitalWrite(lP2, HIGH);
//      delay(500);
//      digitalWrite(lP3, HIGH);
//      delay(500);
//      digitalWrite(lP4, HIGH);
//      delay(500);
//      digitalWrite(lP5, HIGH);
//      delay(500);
//      digitalWrite(lP6, HIGH);
//      delay(500);
//
//      digitalWrite(lP1, LOW);
//      delay(500);
//      digitalWrite(lP2, LOW);
//      delay(500);
//      digitalWrite(lP3, LOW);
//      delay(500);
//      digitalWrite(lP4, LOW);
//      delay(500);
//      digitalWrite(lP5, LOW);
//      delay(500);
//      digitalWrite(lP6, LOW);
//      delay(500);

//        digitalWrite(motorPin, HIGH);
//        delay(1000);
//        digitalWrite(motorPin, LOW);
//        delay(2000);

//      if(value>1000){
//        digitalWrite(LED_BUILTIN, HIGH);
//        digitalWrite(motorPin, HIGH);
//        delay(1000);
//      }else{
//        digitalWrite(LED_BUILTIN, LOW);
//        digitalWrite(motorPin, LOW);
//        delay(1000);
//      }
//    digitalWrite(LED_BUILTIN, HIGH);
    
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(1000);

//    digitalWrite(ledPin, HIGH);
//    delay(1000);
//    digitalWrite(ledPin, LOW);
//    delay(1000);

//    if (total1 > 800){ //8500
//      int speed = Serial.parseInt();
//      Serial.println(speed);
//      if (speed >= 0 && speed <= 255){
//        digitalWrite(ledPin, HIGH);
//        digitalWrite(LED_BUILTIN, HIGH);
//        digitalWrite(motorPin, HIGH);
//      }else{
//        digitalWrite(LED_BUILTIN, LOW);
//        digitalWrite(ledPin, LOW);
//        digitalWrite(motorPin, LOW);
//      }
//    }
}
