#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <stdlib.h>

unsigned long timeInMillis;

// Existing WiFi network
const char* ssid     = "FG889";
const char* password = "CFL37X33FVPV584N";

// Listen for HTTP requests on standard port 80
ESP8266WebServer server(80);

String httpStr;
String prototypeAction = "0";

int pumpPin = D3;
int pumpVal = 1023;
int pumpOnOff = 0;

long previousMillisInCycle = 0;   
long differenceInCheckedMillisInCycle = 0;

void doServerStuff(){
  buildHttpString();
  server.send(200, "text/html", httpStr); 
  delay(100);
}

void setPrototypeAction(){
  String protoAction = server.arg("prototypeAction");
  prototypeAction = protoAction;

  if(prototypeAction == "1" ) {   //Turn Pump On
    pumpOnOff = 1;        
    analogWrite(pumpPin, pumpVal);    
  }else{                                //Turn Motor Off
    pumpOnOff = 0;    
    analogWrite(pumpPin, 0);
  }
}

void setPumpVal() {
  String inString = server.arg("pumpVal");
  if ( inString == "" ) {return;};
  pumpVal = atoi(inString.c_str());  
}

void buildHttpString() {
  char numstr[21];
  String pumpValS = itoa(pumpVal, numstr, 10);
  
  String currentHS = itoa(getHours(), numstr, 10);
  String currentMS = itoa(getMinutes(), numstr, 10);
  String currentSS = itoa(getSeconds(), numstr, 10);
    
  httpStr =
    "<p>"
    "<center>"    
    "<form action=\"/prototypeAction\">\n"
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=0 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Pump Off</label>\n"
    "<label style=\"font-size: 50px;\"><input type=\"radio\" name=\"prototypeAction\" value=1 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Pump On</label>\n"                   
    "</form>\n"
    "</center>"

    "<p>"
    "<center>"
    "<h1>Pump Val: " + pumpValS + "</h1>"
    "<form action='pumpVal'><p><input type='text' name='pumpVal' size=50 autofocus> <input type='submit' value='Submit'></form>"    
    "</center>"

    "<p>"
    "<center>"
    "<h1>Time: " + currentHS + ":" + currentMS + ":" + currentSS + "</h1>"
    "<form action='hourVal'>Enter Current Hour: <input type='text' name='hourVal' size=50 autofocus> <input type='submit' value='Submit'></form>"
    "<form action='minuteVal'>Enter Current Minute: <input type='text' name='minuteVal' size=50 autofocus> <input type='submit' value='Submit'></form>";
               
    String brightStr = "value=" + prototypeAction + " style";
    String checkdStr = "value=" + prototypeAction + " checked style";
    httpStr.replace(brightStr, checkdStr);
}

void handle_root() {
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

void handle_pumpVal() {  
  setPumpVal();
  doServerStuff();
}

void handle_prototypeAction() {    
  setPrototypeAction();
  doServerStuff();
}

void setup(void)
{  
  //Pump
  pinMode(pumpPin, OUTPUT);
  analogWrite(pumpPin, 0);
  
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
  server.on("/pumpVal", handle_pumpVal);
  server.on("/prototypeAction", handle_prototypeAction);
      
  // Start the web server
  server.begin();
}

void loop(void)
{  
  server.handleClient();
  updateClock();  
  unsigned long currentMillisInCycle = millis();
  differenceInCheckedMillisInCycle = currentMillisInCycle - previousMillisInCycle;

}
