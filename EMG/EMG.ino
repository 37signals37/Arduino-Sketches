int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue5 = 0;
int sensorValue7 = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  sensorValue3 = analogRead(A3);
  Serial.print(100);
  Serial.print(" ");
  Serial.print(150);
  Serial.print(" ");
  Serial.print(200);
  Serial.print(" ");
  Serial.print(250);
  Serial.print(" ");
  Serial.println(sensorValue3);
}
