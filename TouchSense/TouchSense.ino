//http://www.instructables.com/id/How-To-Use-Touch-Sensors-With-Arduino/
#include <CapacitiveSensor.h>

int led7 = 7;
int led9 = 9;
int led11 = 11;
int led13 = 13;

long time = 0;
int state = HIGH;
boolean yes;
boolean previous = false;

int debounce = 250;
int threshold = 100;

CapacitiveSensor   cs_5_2 = CapacitiveSensor(8,12);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired// To add more sensors...//CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
void setup()                    
{
   cs_5_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
//   pinMode(led7, OUTPUT);
//   pinMode(led9, OUTPUT);
//   pinMode(led11, OUTPUT);
//   pinMode(led13, OUTPUT);
   Serial.begin(9600);
}

void loop()                    
{
    
    long total1 =  cs_5_2.capacitiveSensorRaw(1000);
    Serial.println(total1);
//
//    if(total1 > 3800){
//      digitalWrite(led7, HIGH);      
//    }else{
//      digitalWrite(led7, LOW);
//    }

//    if(total1 > 6000){
//      digitalWrite(led9, HIGH);
//    }else{
//      digitalWrite(led9, LOW);
//    }
//
//    if(total1 > 10000){
//      digitalWrite(led11, HIGH);
//    }else{
//      digitalWrite(led11, LOW);
//    }
//
//    if(total1 > 15000){
//      digitalWrite(led13, HIGH);
//    }else{
//      digitalWrite(led13, LOW);
//    }
    
//    if (total1 > threshold){yes = true;}
//    else {yes = false;}    
//    
//    // to toggle the state of state
//    if(yes == true && previous  == false && millis() - time>debounce){
//      
//       if(state == LOW){
//         state = HIGH;
//       }
//       else 
//         state = LOW;
//         time = millis();     
//       
//    }
       
   
//      digitalWrite(led, state);
//      previous = yes;

//      Serial.println(millis()-time);
      delay(1);
}


