#include <CapacitiveSensor.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
void setup(){
   Serial.begin(9600);
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
}

void loop(){
  long total =  cs_4_2.capacitiveSensor(5);
  Serial.println(total);
}
