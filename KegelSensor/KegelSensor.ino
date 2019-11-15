//http://www.instructables.com/id/How-To-Use-Touch-Sensors-With-Arduino/
#include <CapacitiveSensor.h>

//long listenTime = 0;
int debounce = 250;
int threshold = 100;
float average = 0;
int counts = 4;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired// To add more sensors...//CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor...    
   Serial.begin(9600);
}

void loop()                    
{
  for(int i = 0; i < counts; i++){
    long total1 =  cs_4_2.capacitiveSensor(250);
    average = average + total1;
        
    delay(250);
  }
  Serial.println(average/counts);
  average = 0;
  
}
