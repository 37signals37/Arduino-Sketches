#include <dht.h>
#include <cactus_io_AM2302.h>

dht DHT1;
dht DHT2;

#define DHT11_PIN 7
#define DHT12_PIN 8
#define AM2302_PIN 4

AM2302 DHT3(AM2302_PIN);

void setup(){
  Serial.begin(9600);
  DHT3.begin();
}

void loop()
{
  int chk1 = DHT1.read11(DHT11_PIN);
  delay(2500);
  int chk2 = DHT2.read11(DHT12_PIN);
  delay(2500);
  DHT3.readHumidity();
  DHT3.readTemperature();
  
  Serial.print("T1: ");
  Serial.print(DHT1.temperature);
  Serial.print("  H1: ");
  Serial.print(DHT1.humidity);
  Serial.print("\t");
  Serial.print("T2: ");
  Serial.print(DHT2.temperature);
  Serial.print("  H2: ");
  Serial.print(DHT2.humidity);
  Serial.print("\t");
  Serial.print("T3: ");
  Serial.print(DHT3.temperature_C);
  Serial.print("  H3: ");
  Serial.println(DHT3.humidity);
  delayMicroseconds(10);
  
  delay(2500);
}
