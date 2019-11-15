#include <CapacitiveSensor.h>
#define PIN1 13
#define PIN2 4

CapacitiveSensor   cs_10_12 = CapacitiveSensor(PIN1,PIN2);
int value = 0;

void setup() {
  Serial.begin(9600);
  while (! Serial);
  cs_10_12.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop() {  
  
  value =  cs_10_12.capacitiveSensorRaw(1000);
  Serial.println(value);
  delay(100);
}
