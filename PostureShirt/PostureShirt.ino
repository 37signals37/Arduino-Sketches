//http://www.instructables.com/id/How-To-Use-Touch-Sensors-With-Arduino/
#include <CapacitiveSensor.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int loopDelay = 300;

int value = 0;
const int numReadings = 50;

float readings[numReadings];      // the readings from the analog input
int readingsIter = 0;
float total = 0;                  // the running total
int average1 = 0;                // the average
//float average2 = 0;                // the average

float baseline1Total = 0;
int baseline1Average = 0;
float baseline1Sigma = 0;
int dispAve1 = 0;
int dispBLAve1 = 0;
int dispSigma1 = 0;
int dispLowerBound1 = 0;
int dispUpperBound1 = 0;

float baseline2Total = 0;
float baseline2Average = 0;
float baseline2Sigma = 0;
int dispAve2 = 0;
int dispBLAve2 = 0;
int dispLowerBound2 = 0;
int dispUpperBound2 = 0;

int touchThreshold = 3000;

int timeConstant = 250;
int threshold = 50;

int button1Pin=13;
//int button2Pin=4;
//int motorPin = 5;
CapacitiveSensor   cs1 = CapacitiveSensor(5,3);
//CapacitiveSensor   cs2 = CapacitiveSensor(10,12);

int calibrationDelay = 3000;
int graphSeparator = 80;
int stdMultiplier = 2;
int loopCounter = 0;

void setBaseline1ReadingsAndStats() {  

  baseline1Total = 0;  
  for (int i = 0; i < numReadings; i++) {
    baseline1Total = baseline1Total + readings[i];
  }
  baseline1Average = baseline1Total / numReadings;

  baseline1Sigma = 0;
  for (int i = 0; i < numReadings; i++) {    
    baseline1Sigma = baseline1Sigma + (readings[i] - baseline1Average) * (readings[i] - baseline1Average);
  }
  baseline1Sigma = baseline1Sigma/ (numReadings - 1);
  baseline1Sigma = sqrt(baseline1Sigma);
  dispSigma1 = baseline1Sigma;
//  
//  dispBLAve1 = baseline1Average;
  dispLowerBound1 = (baseline1Average - stdMultiplier * baseline1Sigma);
  dispUpperBound1 = (baseline1Average + stdMultiplier * baseline1Sigma);
}

//void setBaseline2ReadingsAndStats() {  
//  
//  baseline2Total = 0;  
//  for (int i = 0; i < numReadings; i++) {
//    value =  cs2.capacitiveSensorRaw(timeConstant);
//    readings[i] = value;
//    baseline2Total = baseline2Total + value;
//  }
//  baseline2Average = baseline2Total / numReadings;
//
//  baseline2Sigma = 0;
//  for (int i = 0; i < numReadings; i++) {    
//    baseline2Sigma = baseline2Sigma + (readings[i] - baseline2Average) * (readings[i] - baseline2Average);
//  }
//  baseline2Sigma = baseline2Sigma/ (numReadings - 1);
//  baseline2Sigma = sqrt(baseline2Sigma);
//
//  dispBLAve2 = baseline2Average;
//  dispLowerBound2 = (baseline2Average - stdMultiplier * baseline2Sigma);
//  dispUpperBound2 = (baseline2Average + stdMultiplier * baseline2Sigma);
//}

void setReadingsAndAverage1() {  
  total = 0;
  for (int i = 0; i < numReadings; i++) {
    value =  cs1.capacitiveSensorRaw(timeConstant);
    readings[i] = value;
    total = total + value;
  }
  average1 = total / numReadings;
}

//void setReadingsAndAverage2() { 
//  total = 0;
//  for (int i = 0; i < numReadings; i++) {
//    value =  cs2.capacitiveSensorRaw(timeConstant);
//    readings[i] = value;
//    total = total + value;
//  }
//  average2 = total / numReadings;
//}

void setup()
{
  pinMode(button1Pin, INPUT);
//  pinMode(button2Pin, INPUT);
//  pinMode(motorPin, OUTPUT);
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
//  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  
  Serial.begin(9600);
  while (! Serial);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
    
//  display.setTextSize(3);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  display.println("Posture");
//  display.println("Shirt!!");
//  display.display();
//  delay(2000);
//
//  display.clearDisplay();
//  display.display();
    
//  setBaselineReadingsAndStats();
}

void loop() {

      value =  cs1.capacitiveSensorRaw(timeConstant);      
      Serial.print(value);
      
      readings[readingsIter++] = value;
      if(readingsIter==numReadings){readingsIter = 0;}
      
//      Serial.print(" ");
//      Serial.print(baseline1Average);
//      Serial.print(" ");  
//      Serial.println(baseline1Sigma);
//      delay(250);
      
      
//    
//    setReadingsAndAverage2();

//    dispAve1 = average1;
//    dispAve2 = average2;

    if(loopCounter >= 25){
    
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
  
      display.println(dispLowerBound1);      
      display.print(baseline1Average); display.print("  "); display.println(baseline1Sigma);      
      display.println(value);      
      display.println(dispUpperBound1);
      display.display();

      loopCounter = 0;
    }
    loopCounter++;
//    display.print(dispLowerBound1); display.print(" "); display.println(dispLowerBound2);
//    display.print(dispAve1); display.print(" "); display.println(dispAve2);
//    display.print(dispUpperBound1); display.print(" "); display.println(dispUpperBound2);    
//    display.print(dispAve1); display.print(" "); display.print(dispLowerBound1); display.print(" "); display.println(dispUpperBound1);
//    display.print(dispAve2); display.print(" "); display.print(dispLowerBound2); display.print(" "); display.println(dispUpperBound2);
//    


//    Serial.print(average1);
//    Serial.print(" ");
//    Serial.print(average2+graphSeparator); //+ 
    
    


    if(digitalRead(button1Pin) == 1){
//      delay(calibrationDelay);
      setBaseline1ReadingsAndStats();
//      setBaseline2ReadingsAndStats();
    }
//    if(digitalRead(button2Pin) == 1){
//      setBaseline2ReadingsAndStats();
//    }
    
//      display.clearDisplay();
//      display.display();
//      digitalWrite(motorPin, HIGH);
//      delay(1000);
//      digitalWrite(motorPin, LOW);
//    }
    
  
  Serial.print(" ");
  Serial.print(baseline1Average);
  Serial.print(" ");
  Serial.print(baseline1Average + baseline1Sigma);
  Serial.print(" ");
  Serial.print(baseline1Average - baseline1Sigma);
  Serial.print(" ");  
  Serial.print(baseline1Average + 2* baseline1Sigma);
  Serial.print(" ");
  Serial.println(baseline1Average - 2* baseline1Sigma);

//  Serial.print(" ");
//  Serial.print(baseline2Average + graphSeparator);
//  Serial.print(" ");  
//  Serial.print(baseline2Average + baseline2Sigma + graphSeparator);
//  Serial.print(" ");
//  Serial.print(baseline2Average - baseline2Sigma + graphSeparator);
//  Serial.print(" ");  
//  Serial.print(baseline2Average + 2* baseline2Sigma + graphSeparator);
//  Serial.print(" ");
//  Serial.println(baseline2Average -2* baseline2Sigma + graphSeparator);

  //    delay(loopDelay);
}
