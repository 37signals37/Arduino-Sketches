#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// Existing WiFi network
const char* ssid     = "FG889";
const char* password = "CFL37X33FVPV584N";

// Listen for HTTP requests on standard port 80
ESP8266WebServer server(80);

String httpStr;

Servo myservo;
int servoPos = 90;
int servoPin = D2;
int servoStartPos = 0;
int servoEndPos = 180;
int servoStepIncrement = 3;
int servoDelayIncrement = 30;

String prototypeAction = "0";

int analogPin= A0;
int raw= 0;

void doServerStuff(){
  buildHttpString();
  server.send(200, "text/html", httpStr); 
  delay(100);
}

void setPrototypeAction(){
  if(prototypeAction == "0") {    //ServoSweep        
      servoSweep();
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
  String servoDelayIncrementS = itoa(servoDelayIncrement, numstr, 10);
      
  httpStr =
    "<p>"
    "<center>"    
    "<form action=\"/prototypeAction\">\n"             
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=0 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Servo Sweep</label><br>\n"                   
    "</form>\n"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Servo Position: " + servoPosS + "</h1>"
    "<form action='servoVal'><p>0-180: <input type='text' name='servoVal' size=50 autofocus> <input type='submit' value='Submit'></form>"    
    "</center>"

    "<p>"
    "<center>"
    "<h1>Stepper motor delay between steps (ms): " + servoDelayIncrementS + "</h1>"
    "<form action='servoDelayIncrement'><p><input type='text' name='servoDelayIncrement' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "</center>";
       
    String brightStr = "value=" + prototypeAction + " style";
    String checkdStr = "value=" + prototypeAction + " checked style";
    httpStr.replace(brightStr, checkdStr);
}

void handle_root() {
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
  server.on("/servoVal", handle_servoVal);
  server.on("/servoDelayIncrement", handle_servoDelayIncrement);
  server.on("/prototypeAction", handle_prototypeAction);  
    
  // Start the web server
  server.begin();
}

void loop(void)
{
  // Listen for http requests
  server.handleClient();

  raw= analogRead(analogPin);
  if(raw){
    Serial.println(raw);
    delay(500);
  }  
}
