//int offPin = 7;
int onPin = 8;
int switchPin = 9;
int ledPin = 10;
int state = 0;
int sonicatorCycleTime = 240; //seconds

void setup() {
  Serial.begin(9600);
//  pinMode(offPin, INPUT);
  pinMode(onPin, INPUT);
  pinMode(switchPin, OUTPUT);
  digitalWrite(switchPin, LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  state = digitalRead(onPin);
  Serial.println(state);

  if(state == 1){
    digitalWrite(ledPin, HIGH);
    for(int i = 0; i < 96; i++){
      Serial.print("Count: ");
      Serial.print(i);
      digitalWrite(switchPin, HIGH);
      Serial.print(" On");
      delay(25);
      digitalWrite(switchPin, LOW);
      Serial.println(" Off");
      for(int j = 0; j < 1000; j++){
        delay(sonicatorCycleTime);
      }
      Serial.print("Ready for next cycle");
    }
    digitalWrite(ledPin, LOW);
    state = 0;
  }
  delay(1000);
}

