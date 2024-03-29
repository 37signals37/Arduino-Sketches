//https://learn.adafruit.com/adafruit-micro-sd-breakout-board-card-tutorial?view=all
//http://playground.arduino.cc/Code/Time

#include <stdlib.h>
#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library
#include <TimeLib.h>

unsigned long timeInMillis;
long previousMillisInCycle = 0;   
long differenceInCheckedMillisInCycle = 0;

#define SERIESRESISTOR 10000
#define AMBIENTTHERMISTORPIN A0
#define PANELTHERMISTORPIN A5

int pumpPin = 2;
int valvePin = 4;
int pumpInPin = 5;
int valveInPin = 6;

int pumpOnOff = 0;
int valveOnOff = 0;

//chart has 30 values, starts at 20oC and ends at 50oC, 12.47-3.593
float chart[] = {12.47,11.92,11.41,10.91,10.45,10.00,9.575,9.170,8.784,8.416,8.064,7.730,7.410,7.106,6.815,6.538,6.273,6.020,5.778,5.548,5.327,5.117,4.915,4.723,4.539,4.363,4.195,4.034,3.880,3.733,3.592};
float tempDiffLimit = 8.0;
float coolTempDiffLimit = 1.0;

//Values taken from https://cdn-shop.adafruit.com/datasheets/103_3950_lookuptable.pdf
//float chart[] = {-40,277.2,1,30.25,42,4.915,83,1.128,124,0.3434,165,0.1265,
//-39,263.6,2,28.82,43,4.723,84,1.093,125,0.3341,166,0.1239,
//-38,250.1,3,27.45,44,4.539,85,1.059,126,0.3253,167,0.1213,
//-37,236.8,4,26.16,45,4.363,86,1.027,127,0.3167,168,0.1187,
//-36,224.0,5,24.94,46,4.195,87,0.9955,128,0.3083,169,0.1163,
//-35,211.5,6,23.77,47,4.034,88,0.9654,129,0.3002,170,0.1139,
//-34,199.6,7,22.67,48,3.880,89,0.9363,130,0.2924,171,0.1115,
//-33,188.1,8,21.62,49,3.733,90,0.9083,131,0.2848,172,0.1092,
//-32,177.3,9,20.63,50,3.592,91,0.8812,132,0.2774,173,0.1070,
//-31,167.0,10,19.68,51,3.457,92,0.8550,133,0.2702,174,0.1048,
//-30,157.2,11,18.78,52,3.328,93,0.8297,134,0.2633,175,0.1027,
//-29,148.1,12,17.93,53,3.204,94,0.8052,135,0.2565,176,0.1006,
//-28,139.4,13,17.12,54,3.086,95,0.7816,136,0.2500,177,0.0986,
//-27,131.3,14,16.35,55,2.972,96,0.7587,137,0.2437,178,0.0966,
//-26,123.7,15,15.62,56,2.863,97,0.7366,138,0.2375,179,0.0947,
//-25,116.6,16,14.93,57,2.759,98,0.7152,139,0.2316,180,0.0928,
//-24,110.0,17,14.26,58,2.659,99,0.6945,140,0.2258,181,0.0909,
//-23,103.7,18,13.63,59,2.564,100,0.6744,141,0.2202,182,0.0891,
//-22,97.9,19,13.04,60,2.472,101,0.6558,142,0.2148,183,0.0873,
//-21,92.50,20,12.47,61,2.384,102,0.6376,143,0.2095,184,0.0856,
//-20,87.43,21,11.92,62,2.299,103,0.6199,144,0.2044,185,0.0839,
//-19,82.79,22,11.41,63,2.218,104,0.6026,145,0.1994,186,0.0822,
//-18,78.44,23,10.91,64,2.141,105,0.5858,146,0.1946,187,0.0806,
//-17,74.36,24,10.45,65,2.066,106,0.5694,147,0.1900,188,0.0790,
//-16,70.53,25,10.00,66,1.994,107,0.5535,148,0.1855,189,0.0774,
//-15,66.92,26,9.575,67,1.926,108,0.5380,149,0.1811,190,0.0759,
//-14,63.54,27,9.170,68,1.860,109,0.5229,150,0.1769,191,0.0743,
//-13,60.34,28,8.784,69,1.796,110,0.5083,151,0.1728,192,0.0729,
//-12,57.33,29,8.416,70,1.735,111,0.4941,152,0.1688,193,0.0714,
//-11,54.50,30,8.064,71,1.677,112,0.4803,153,0.1650,194,0.0700,
//-10,51.82,31,7.730,72,1.621,113,0.4669,154,0.1612,195,0.0686,
//-9,49.28,32,7.410,73,1.567,114,0.4539,155,0.1576,196,0.0672,
//-8,46.89,33,7.106,74,1.515,115,0.4412,156,0.1541,197,0.0658,
//-7,44.62,34,6.815,75,1.465,116,0.4290,157,0.1507,198,0.0645,
//-6,42.48,35,6.538,76,1.417,117,0.4171,158,0.1474,199,0.0631,
//-5,40.45,36,6.273,77,1.371,118,0.4055,159,0.1441,200,0.0619,
//-4,38.53,37,6.020,78,1.326,119,0.3944,160,0.1410,
//-3,36.70,38,5.778,79,1.284,120,0.3835,161,0.1379,
//-2,34.97,39,5.548,80,1.243,121,0.3730,162,0.1350,
//-1,33.33,40,5.327,81,1.203,122,0.3628,163,0.1321,
//0,31.77,41,5.117,82,1.165,123,0.3530,164,0.1293};

const int chipSelect = 10;
Sd2Card card;
File myFile; //Data object you will write your sensor data to
int test = 0;

void setup(void)
{  
  Serial.begin(9600);
  
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
  pinMode(valvePin, OUTPUT);
  digitalWrite(valvePin, LOW);

  pinMode(pumpInPin, INPUT);
  pinMode(valveInPin, INPUT);
  
  startSDcard();
  setTime(11,13,0,25,6,2018); //setTime(hr,min,sec,day,month,yr);
}

void startSDcard(){
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

float getTemperature(float in){
  
  if(in>chart[0]){return 19;}
  if(in<chart[30]){return 51;}

  for(int i = 0; i <= 30; i++){
    if(in<chart[i] && in>chart[i+1]){
      return i+20;      
    }
  }  
}

float getAmbientTemp(){
  float ambientReading = analogRead(AMBIENTTHERMISTORPIN);  
  ambientReading = (1023 / ambientReading) - 1;     // (1023/ADC - 1) 
  ambientReading = SERIESRESISTOR / ambientReading/1000;  // 10K / (1023/ADC - 1)
  return getTemperature(ambientReading);
}

float getPanelTemp(){
  float panelReading = analogRead(PANELTHERMISTORPIN);
  panelReading = (1023 / panelReading) - 1;     // (1023/ADC - 1) 
  panelReading = SERIESRESISTOR / panelReading /1000;  // 10K / (1023/ADC - 1)    
  return getTemperature(panelReading);    
}

void writeDataToSD(float ambient, float panel){
  Serial.println("Writing to SD Card 1");
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {// if the card is available, write to it:
    Serial.println("Card Removed");
    return;
  } else {
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (!dataFile){
      Serial.println("Reopening datafile.");
      startSDcard();
      dataFile = SD.open("datalog.txt", FILE_WRITE);
    }
    
    if (dataFile){// if the file is available, write to it:
      Serial.println("Writing to SD Card");
      dataFile.print(year());
      dataFile.print("-");
      dataFile.print(month());
      dataFile.print("-");
      dataFile.print(day());
      dataFile.print(" ");
      dataFile.print(hour());
      dataFile.print(":");
      dataFile.print(minute());
      dataFile.print(":");
      dataFile.print(second());  
      dataFile.print("\tPanel: ");
      dataFile.print(panel);
      dataFile.print("\tAmbient: ");
      dataFile.println(ambient);      
      dataFile.close();
            
    } else { // if the file isn't open, pop up an error:
      Serial.println("error opening datalog.txt");
    }
  }  
}

void loop(void)
{  

  float panelTemp;
  float ambientTemp;
  
  pumpOnOff = digitalRead(pumpInPin);
  valveOnOff = digitalRead(valveInPin);
  
  if(pumpOnOff == HIGH) {digitalWrite(pumpPin, HIGH);}
  else{digitalWrite(pumpPin, LOW);}
  
  if(valveOnOff == HIGH) {digitalWrite(valvePin, HIGH);}
  else {digitalWrite(valvePin, LOW);}

//  panelTemp = 10.5;  //Testing
//  ambientTemp = 8.8; //Testing

  panelTemp = getPanelTemp(); //Testing
  ambientTemp = getAmbientTemp(); //Testing
    
  if(panelTemp-ambientTemp >= tempDiffLimit){
    writeDataToSD(ambientTemp, panelTemp);
    digitalWrite(valvePin, HIGH);
    while(getPanelTemp()-getAmbientTemp() >= coolTempDiffLimit){};            
    digitalWrite(valvePin, LOW);    
  }
  
  delay(5000);
}
