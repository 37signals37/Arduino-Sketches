#include <CapacitiveSensor.h>

int tled1 = 11;
int tled2 = 10;
int tled3 = 9;  
int sled1 = 13;  
int sled2 = 8;  
int sled3 = 12; 

int tCounter = 0;
int tThreshold = 100;
int tCountThreshold = 3;
boolean tExceed = false;
int tLEDs = 0;

int sCounter = 0;
int sThreshold = 50;
int sCountThreshold = 3;
boolean sExceed = false;
int sLEDs = 0;

CapacitiveSensor   cs_7_6 = CapacitiveSensor(7,6);  // 10M resistor between pins 7 & 6, pin 6 is sensor pin
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);  // 10M resistor between pins 7 & 6, pin 6 is sensor pin

void setup()                    
{
  pinMode(tled1, OUTPUT);
  pinMode(tled2, OUTPUT);
  pinMode(tled3, OUTPUT);
  pinMode(sled1, OUTPUT);
  pinMode(sled2, OUTPUT);
  pinMode(sled3, OUTPUT);

  digitalWrite(tled1, LOW);
  digitalWrite(tled2, LOW);
  digitalWrite(tled3, LOW);
  digitalWrite(sled1, LOW);
  digitalWrite(sled2, LOW);
  digitalWrite(sled3, LOW);
   
   cs_7_6.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long tVal =  cs_7_6.capacitiveSensor(250);
    long sVal =  cs_4_2.capacitiveSensor(350);

    Serial.print(tVal);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(sVal);                  // print sensor output 1
    Serial.println("\t");

    delay(10);                             // arbitrary delay to limit data to serial port 

    if(tVal >= tThreshold){
      tCounter++;  
      tExceed = true; 
    }

    if(tVal < tThreshold){
      tExceed = false;
    }

    if(tCounter >= tCountThreshold && !tExceed){
      tLEDs = tLEDs + 1;
      if(tLEDs==4){
        tLEDs = 0;  
      }
      tCounter=0;
    }

    if(tLEDs == 0){
      digitalWrite(tled1, LOW);
      digitalWrite(tled2, LOW);
      digitalWrite(tled3, LOW);
    }else if(tLEDs == 1){
      digitalWrite(tled1, HIGH);
      digitalWrite(tled2, LOW);
      digitalWrite(tled3, LOW);
    }else if(tLEDs == 2){
      digitalWrite(tled1, HIGH);
      digitalWrite(tled2, HIGH);
      digitalWrite(tled3, LOW);
    }else if(tLEDs == 3){
      digitalWrite(tled1, HIGH);
      digitalWrite(tled2, HIGH);
      digitalWrite(tled3, HIGH);
    }


    //Sense block
    if(sVal >= sThreshold){
      sCounter++;  
      sExceed = true; 
    }

    if(sVal < sThreshold){
      sExceed = false;
    }

    if(sCounter >= sCountThreshold && !sExceed){
      sLEDs = sLEDs + 1;
      if(sLEDs==4){
        sLEDs = 0;  
      }
      sCounter=0;
    }

    if(sLEDs == 0){
      digitalWrite(sled1, LOW);
      digitalWrite(sled2, LOW);
      digitalWrite(sled3, LOW);
    }else if(sLEDs == 1){
      digitalWrite(sled1, HIGH);
      digitalWrite(sled2, LOW);
      digitalWrite(sled3, LOW);
    }else if(sLEDs == 2){
      digitalWrite(sled1, HIGH);
      digitalWrite(sled2, HIGH);
      digitalWrite(sled3, LOW);
    }else if(sLEDs == 3){
      digitalWrite(sled1, HIGH);
      digitalWrite(sled2, HIGH);
      digitalWrite(sled3, HIGH);
    }

    

    
}



