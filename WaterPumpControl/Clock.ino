long previousMillis = 0;
long differenceInCheckedMillis = 0;
int differenceInCheckedSecs = 0;

int secondCounter = 0;

int currentH = 14;
int currentM = 45;
int currentS = 0;
int milliSecRemainder;

int addH = 0;
int addM = 0;
int addS = 0;


String inLine;
int integerIn = 7;

int getHours() {
  return currentH;
}

int getMinutes() {
  return currentM;
}

int getSeconds() {
  return currentS;
}

int setMinutes(int inMinutes){
  currentM = inMinutes;  
}

int setHour(int inHours){
  currentH = inHours;  
}

void updateClock() {
  unsigned long currentMillis = millis();
  differenceInCheckedMillis = currentMillis - previousMillis;
  differenceInCheckedSecs = differenceInCheckedMillis / 1000;

  if (Serial.available()) {
    inLine = Serial.readString();
    integerIn = atoi(inLine.c_str());
  }

  addH = differenceInCheckedSecs / 3600;
  addM = (differenceInCheckedSecs - (addH * 3600)) / 60;
  addS = (differenceInCheckedSecs - (addH * 3600) - (addM * 60));

  milliSecRemainder = milliSecRemainder + differenceInCheckedMillis - addH * 360000 - addM * 60000 - addS * 1000;

  if (milliSecRemainder > 1000) {
    milliSecRemainder = milliSecRemainder - 1000;
    addS = addS + 1;
  }

  currentS = currentS + addS;
  if (currentS > 60) {
    currentS = currentS % 60;
    currentM = currentM + 1;
  }

  currentM = currentM + addM;
  if (currentM > 60) {
    currentM = currentM % 60;
    currentH = currentH + 1;
  }

  currentH = currentH + addH;
  if (currentH > 23) {
    currentH = currentH % 24;
  }

  //  Serial.println(integerIn);
  //
  //  Serial.print("Add Hour: ");
  //  Serial.print(addH);
  //  Serial.print("\t Add Min: ");
  //  Serial.print(addM);
  //  Serial.print("\t Add Sec: ");
  //  Serial.println(addS);

  //  Serial.print(currentH);
  //  Serial.print(":");
  //  Serial.print(currentM);
  //  Serial.print(":");
  //  Serial.println(currentS);
  //  Serial.println();


  previousMillis = currentMillis;






  //  if(currentMillis - previousMillis > interval) {
  //    // save the last time you blinked the LED
  //    previousMillis = currentMillis;
  //  }
}
