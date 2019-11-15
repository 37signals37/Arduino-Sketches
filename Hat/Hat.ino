#include <CapacitiveSensor.h>

int pwmPin = 3;
int cycleDelay = 100;
int cycleCounter = 0;
int state = 0; //0: not worn  1: not worn, being tapped  2: being worn  3: being worn, being tapped
int prevState = 0;
int mode = 3; //1:off  2:flashing  3:perm on
boolean indicating = false; //indicating mode through flashes
int pwmVal = 135;
int pwmMin = 0;
int beingWornThreshold = 350;

CapacitiveSensor   cs_5_2 = CapacitiveSensor(8,12);

void setup()
{
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);

  analogWrite(pwmPin, 0);
  delay(2000);
  analogWrite(pwmPin, pwmVal);
  delay(2500);
  analogWrite(pwmPin, 0);
}

void loop(){

  long total =  cs_5_2.capacitiveSensor(500);
                                                
  if(total < 175){state = 0;}  //!worn, !tapped
  if(total >= 175){state = 1;} //worn or tapped  
//  if(total >= 750){state = 2;} //worn and tapped  

  Serial.println(total);
//  Serial.print("   CycleCounter: ");
//  Serial.print(cycleCounter);
//  Serial.print("   State: ");
//  Serial.print(state);
//  Serial.print("   PrevState: ");
//  Serial.println(prevState);


  if(state == 0 && prevState > 0){
    analogWrite(pwmPin, 0);    
    if(cycleCounter <5){
      mode = mode+1;
      if(mode == 5){mode = 1;}    
      for(int i = 0; i<mode; i++){
        Serial.println("FLASH");
        analogWrite(pwmPin, pwmVal);
        delay(400);
        analogWrite(pwmPin, 0);
        delay(400);
      }
    }
    analogWrite(pwmPin, 0);
    cycleCounter = 0;
  }

  if(state == 1 && prevState == 0){
    cycleCounter = 1;
  }

  if(state >= 1 && prevState >= 1 && total >= beingWornThreshold){
    cycleCounter++;
    if(cycleCounter > 15){
      Serial.println("BEING WORN");
      
      if(mode==1){
        analogWrite(pwmPin, 0);
//        Serial.println("Light Off");
      }
      if(mode==2){
        if(total<900){
          analogWrite(pwmPin, pwmVal);                    
        }else if(total <1200){
          analogWrite(pwmPin, 0);
        }else if(total <1600){
          analogWrite(pwmPin, 20);
        }else{
          analogWrite(pwmPin, pwmVal);
        }                               
        Serial.print("Light On ");
      }
      if(mode==3){
        if(total<900){
          analogWrite(pwmPin, 0);
        }else if(total <1200){
          analogWrite(pwmPin, 20);
        }else if(total <1600){
          analogWrite(pwmPin, 40);
        }else{
          analogWrite(pwmPin, pwmVal);
        }
        Serial.print("Mode 3: Light Off except when touched ");
      }
      if(mode==4){
        for(int i=0;i<pwmVal;i++){
          analogWrite(pwmPin, i);
          delay(12);
        }

        delay(750);
        
        for(int i=pwmVal;i>0;i=i-1){
          analogWrite(pwmPin, i);
          delay(12);
        }
        analogWrite(pwmPin, 0);
        delay(1500);
        Serial.println("Blinking");
      }      
    }
  }

  prevState = state;
  delay(cycleDelay);  
}
