#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

unsigned long timeInMillis;

// Existing WiFi network
const char* ssid     = "FG889";
const char* password = "CFL37X33FVPV584N";

// Listen for HTTP requests on standard port 80
ESP8266WebServer server(80);

String httpStr;

Servo myservo;
int servoPos = 90;    // variable to store the servo position
int motorVal = 1023;
//int motorValIncrement = 3; //millisecond delay between increasing motorVal increments
int motorPin = D6;

int servoPin = D2;

int servoStartPos = 0;
int servoEndPos = 180;
int servoStepIncrement = 3;
int servoDelayIncrement = 30;

int cycleDelay = 300;
String prototypeAction = "0";
int motorOnOff = 0;
int cycleOnOff = 0;
int lightsOnOff = 0;

int lightPin = D7;
int lightsVal = 1023;

int dutyCycleOnTime = 10;
int dutyCycleOffTime = 0;        
int lightStartHour =8;
int lightEndHour = 22;

boolean runMotor = false;

long previousMillisInCycle = 0;   
long differenceInCheckedMillisInCycle = 0;

void checkString(){
  
}

void doServerStuff(){
  buildHttpString();
  server.send(200, "text/html", httpStr); 
  delay(100);
}

//void rampUpMotor(){
//    for(int i = 0; i <= motorVal; i++ ){
//      analogWrite(motorPin, i);  
//      delay(motorValIncrement);
//    }
//}

void setCycleDelay() {
  String inString = server.arg("cycleDelay");
  if ( inString == "" ) {return;};
  cycleDelay = atoi(inString.c_str());
}

void setDutyCycleOnTime(){
  String inString = server.arg("dutyCycleOnTime");
  if ( inString == "" ) {return;};
  dutyCycleOnTime= atoi(inString.c_str());  
}

void setDutyCycleOffTime(){
  String inString = server.arg("dutyCycleOffTime");
  if ( inString == "" ) {return;};
  dutyCycleOffTime= atoi(inString.c_str());  
}


void setPrototypeAction(){
  String protoAction = server.arg("prototypeAction");
  prototypeAction = protoAction;

  if(prototypeAction == "5" ) {         //Lights Off
    lightsOnOff = 0;
    analogWrite(lightPin, 0);
    delay(10);
    Serial.println(lightsVal);
  }else if(prototypeAction == "4" ) {         //Lights On    
    lightsOnOff = 1;
    analogWrite(lightPin, lightsVal);
    delay(10);    
    Serial.println(lightsVal);
  }else if(prototypeAction == "3" ) {         //Cycle On    
    cycleOnOff = 1;
    motorOnOff = 0;
  }else if(prototypeAction == "2" ) {    //ServoSweep    
    cycleOnOff = 0;
    servoSweep();
  }else if(prototypeAction == "1" ) {   //Turn Motor On    
    cycleOnOff = 0;
    motorOnOff = 1;        
    analogWrite(motorPin, motorVal);  
    delay(25);
//    rampUpMotor();  
  }else{                                //Turn Motor Off
    cycleOnOff = 0;
    motorOnOff = 0;
    analogWrite(motorPin, 0);    
  }
}


void setServoVal() {  
  String inString = server.arg("servoVal");     
  if ( inString == "" ) {return;};
  
  servoPos = atoi(inString.c_str());

  if(servoPos > servoEndPos){
    servoPos = servoEndPos;  
  }

  myservo.write(servoPos);   
}

void setMotorVal() {
  String inString = server.arg("motorVal");
  if ( inString == "" ) {return;};
  
  motorVal = atoi(inString.c_str());

  if(motorOnOff == 1) {
    analogWrite(motorPin, motorVal);  
    delay(25);
  }else{
    analogWrite(motorPin, 0);    
  }
}

void setLightsVal() {
  String inString = server.arg("lightsVal");
  if ( inString == "" ) {return;};
  lightsVal = atoi(inString.c_str());

  if(lightsOnOff == 1) {
    analogWrite(lightPin, lightsVal);    
  }else{
    analogWrite(lightPin, 0);    
  }
}

void setServoIncrementValue() {
  String inString = server.arg("servoDelayIncrement");
  if ( inString == "" ) {return;};
  servoDelayIncrement = atoi(inString.c_str());
}


void servoSweep() {    
  myservo.write(servoStartPos);
  delay(250);
  
  for(int i = servoStartPos; i <= servoEndPos; i = i + servoStepIncrement){
    myservo.write(i);
    delay(servoDelayIncrement);
  }

  delay(100);
  
  for(int i = servoEndPos; i >= servoStartPos; i = i - servoStepIncrement){
    myservo.write(i);
    delay(servoDelayIncrement);
  }  

  delay(100);

  myservo.write(servoPos);
  delay(250);
  
}


void buildHttpString() {
  char numstr[21];
  String servoPosS = itoa(servoPos, numstr, 10);
  String motorValS = itoa(motorVal, numstr, 10);
  String lightsValS = itoa(lightsVal, numstr, 10);
  String servoDelayIncrementS = itoa(servoDelayIncrement, numstr, 10);
  String cycleDelayS = itoa(cycleDelay, numstr, 10);
  String dutyCycleOnTimeS = itoa(dutyCycleOnTime, numstr, 10);
  String dutyCycleOffTimeS = itoa(dutyCycleOffTime, numstr, 10);
  
  String currentHS = itoa(getHours(), numstr, 10);
  String currentMS = itoa(getMinutes(), numstr, 10);
  String currentSS = itoa(getSeconds(), numstr, 10);
    
  httpStr =
    "<p>"
    "<center>"    
    "<form action=\"/prototypeAction\">\n"
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=0 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Motor Off</label>\n"
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=1 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Motor On</label>\n"                   
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=2 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Servo Sweep</label><br>\n"                   
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=3 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Cycle On</label>\n"                   
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=4 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Lights On</label>\n"                   
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=5 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Lights Off</label><br>\n"                   
    "</form>\n"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Time: " + currentHS + ":" + currentMS + ":" + currentSS + "</h1>"
    "<form action='hourVal'>Enter Current Hour: <input type='text' name='hourVal' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "<form action='minuteVal'>Enter Current Minute: <input type='text' name='minuteVal' size=50 autofocus> <input type='submit' value='Submit'></form>"
    
    "<p>"
    "<center>"
    "<h1>Servo Position: " + servoPosS + "</h1>"
    "<form action='servoVal'><p>0-180: <input type='text' name='servoVal' size=50 autofocus> <input type='submit' value='Submit'></form>"    
    "</center>"
    
    "<p>"
    "<center>"
    "<h1>Motor Value: " + motorValS + "</h1>"
    "<form action='motorVal'><p>0-1024: <input type='text' name='motorVal' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Light Value: " + lightsValS + "</h1>"
    "<form action='lightsVal'><p>0-1024: <input type='text' name='lightsVal' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Stepper motor delay between steps (ms): " + servoDelayIncrementS + "</h1>"
    "<form action='servoDelayIncrement'><p><input type='text' name='servoDelayIncrement' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Cycle Delay Time (s): " + cycleDelayS + "</h1>"
    "<form action='cycleDelay'><p><input type='text' name='cycleDelay' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Duty Cycle On Time(ms): " + dutyCycleOnTimeS + "</h1>"
    "<form action='dutyCycleOnTime'><p><input type='text' name='dutyCycleOnTime' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Duty Cycle Off Time(ms): " + dutyCycleOffTimeS + "</h1>"
    "<form action='dutyCycleOffTime'><p><input type='text' name='dutyCycleOffTime' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "</center>";


       
    String brightStr = "value=" + prototypeAction + " style";
    String checkdStr = "value=" + prototypeAction + " checked style";
    httpStr.replace(brightStr, checkdStr);
}

void handle_root() {
  doServerStuff();
}

void handle_cycleDelay() {  
  setCycleDelay();
  doServerStuff();
}

void handle_dutyCycleOnTime() {  
  setDutyCycleOnTime();
  doServerStuff();
}

void handle_dutyCycleOffTime() {  
  setDutyCycleOffTime();
  doServerStuff();
}

void handle_hourVal() {  
  String inString = server.arg("hourVal");
  if (inString == "" ) {
    return;
  }
  int hourVal = atoi(inString.c_str());
  
  setHour(hourVal);
  doServerStuff();
}

void handle_minuteVal() {  
  String inString = server.arg("minuteVal");
  if (inString == "" ) {
    return;
  }
  
  int minVal = atoi(inString.c_str());      
  setMinutes(minVal);
  doServerStuff();
}

void handle_motorVal() {  
  setMotorVal();
  doServerStuff();
}

void handle_lightsVal() {  
  setLightsVal();
  doServerStuff();
}

void handle_servoVal() {
  setServoVal();
  doServerStuff();
}

void handle_servoDelayIncrement() {
  setServoIncrementValue();
  doServerStuff();
}

void handle_prototypeAction() {    
  setPrototypeAction();
  doServerStuff();
}

void setup(void)
{
  myservo.attach(servoPin);

  //Mister Motor
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);

  //Lighting
  pinMode(lightPin, OUTPUT);
  analogWrite(lightPin, 0);

  
  // Open the Arduino IDE Serial Monitor to see what the code is doing
  Serial.begin(9600);
  Serial.println("WeMos Server");
  Serial.println("");

  // Connect to your WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  // Wait for successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
   
  // Handle http requests
  server.on("/", handle_root);
  server.on("/hourVal", handle_hourVal);
  server.on("/minuteVal", handle_minuteVal);
  server.on("/cycleDelay", handle_cycleDelay);
  server.on("/servoVal", handle_servoVal);
  server.on("/motorVal", handle_motorVal);
  server.on("/lightsVal", handle_lightsVal);
  server.on("/servoDelayIncrement", handle_servoDelayIncrement);
  server.on("/prototypeAction", handle_prototypeAction);
  server.on("/dutyCycleOnTime", handle_dutyCycleOnTime);
  server.on("/dutyCycleOffTime", handle_dutyCycleOffTime);
  
    
  // Start the web server
  server.begin();
}

void loop(void)
{
  // Listen for http requests
  server.handleClient();
  
  updateClock();  

  unsigned long currentMillisInCycle = millis();
  differenceInCheckedMillisInCycle = currentMillisInCycle - previousMillisInCycle;
  
  if(differenceInCheckedMillisInCycle/1000 > cycleDelay){
    runMotor = true;
    previousMillisInCycle = currentMillisInCycle;
  }else{
    runMotor = false;  
  }
  
  
  if (cycleOnOff == 1){

    if(runMotor){
      myservo.write(servoStartPos);     
      delay(200);

      analogWrite(motorPin, motorVal);            
                
      for(int i = servoStartPos; i <= servoEndPos; i = i + servoStepIncrement){
        myservo.write(i);
        delay(servoDelayIncrement);            
      }      
      
      for(int i = servoEndPos; i >= servoStartPos; i = i - servoStepIncrement){
        myservo.write(i);
        delay(servoDelayIncrement);  
      }

      analogWrite(motorPin, 0);
      delay(50);
      myservo.write(servoPos);
            
    }

    if(getHours() >= lightStartHour && getHours() < lightEndHour){
      analogWrite(lightPin, lightsVal);
      delay(dutyCycleOnTime);
      analogWrite(lightPin, 0);
      delay(dutyCycleOffTime);
    }   
  }  
}
