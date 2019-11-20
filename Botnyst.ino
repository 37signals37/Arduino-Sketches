#include <ESP8266WiFi.h>

//GLOBAL VARIABLES SECTION
//const char* ssid = "FG889"; //SWITCH YOUR NETWORK NAME AND PASSWORD HERE
//const char* password = "CFL37X33FVPV584N";

const char* ssid = "DMS Member"; //COMMENT THIS NETWORK OUT WHEN YOURE NOT A DMS
const char* password = "dms--109238";

int p5 = D5;//Mister
int p6 = D6;//Dispenser
int p7 = D7;//Mixer
int p8 = D8;//Supposed to be lights
int count = 2; //reset to zero after initial trial

WiFiServer server(80);

//INITIAL FUNCTION IN PROGRAM
void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(p5, OUTPUT); //Setting up Pin5
//  digitalWrite(p5, LOW);
  analogWrite(p5, 0);

  pinMode(p6, OUTPUT);
//  digitalWrite(p6, LOW);
  analogWrite(p6, 0);

  pinMode(p7, OUTPUT);
//  digitalWrite(p7, LOW);
  analogWrite(p7, 0);

  pinMode(p8, OUTPUT);
  digitalWrite(p8, LOW);
//  analogWrite(p8, 0);
 
  // CONNECTING TO WIFI NETWORK
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

  int iii = 0; 
  // Match the request 
  int p5val = LOW;
  int p6val = LOW;
  int p7val = LOW;
  int p8val = LOW;
 
void loop() {
  analogWrite(p5, 1024);    
  delay(10000);
  analogWrite(p5, 0);    
             
  for(int iii=0; iii<300; iii++){
    delay(1000);
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  

  //Mister Motor   
  if (request.indexOf("/P5=ON") != -1) {
    analogWrite(p5, 1024);
    p5val = HIGH;
    
    delay(5000);
    analogWrite(p5, 0);
    p5val = LOW;    
  } 
  if (request.indexOf("/P5=OFF") != -1){
    analogWrite(p5, 0);
    p5val = LOW;
  }

  //Dispenser Motor
  if (request.indexOf("/P6=ON") != -1) {    
    analogWrite(p6, 900);    
    p6val = HIGH;
    
    delay(2000);
    analogWrite(p6, 0);        
    p6val = LOW;
  } 
  if (request.indexOf("/P6=OFF") != -1){    
    analogWrite(p6, 0);
    p6val = LOW;
  }

  if (request.indexOf("/P7=ON") != -1) {
   analogWrite(p7, 900);    
    p7val = HIGH;
    
    delay(2000);
    analogWrite(p7, 0);        
    p7val = LOW;
  } 
  if (request.indexOf("/P7=OFF") != -1){
    analogWrite(p7, 0);    
    p7val = LOW;
  }

  if (request.indexOf("/P8=ON") != -1) {
//    iii=500;
//    while(iii<=1024){
//      analogWrite(p8, iii);
      digitalWrite(p8, HIGH);
//      delay(10);
//      iii++;
//    }
    p8val = HIGH;
    
    delay(1500);
//    while(iii>=0){
//      analogWrite(p8, iii);
    digitalWrite(p8, LOW);
//      delay(10);
//      iii--;
//    }
    p8val = LOW;
  }
  
  if (request.indexOf("/P8=OFF") != -1){
//    analogWrite(p8, 0);
    digitalWrite(p8, LOW);
    p8val = LOW;
  }
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("p5 is now: ");
  if(p5val == HIGH) {
    client.println("On<br>");  
  } else {
    client.println("Off<br>");
  }
  
  client.print("P6 is now: ");
  if(p6val == HIGH) {
    client.println("On<br>");  
  } else {
    client.println("Off<br>");
  }

  client.print("P7 is now: ");
  if(p7val == HIGH) {
    client.println("On<br>");  
  } else {
    client.println("Off<br>");
  }

  client.print("P8 is now: ");
  if(p8val == HIGH) {
    client.println("On<br>");  
  } else {
    client.println("Off<br>");
  }

  client.println("<br><br>");
  client.println("Click <a href=\"/P5=ON\">here</a> turn ON pin 5<br>");
  client.println("Click <a href=\"/P5=OFF\">here</a> turn OFF pin 5<br>");
  client.println("</html>");

  client.println("<br><br>");
  client.println("Click <a href=\"/P6=ON\">here</a> turn ON pin 6<br>");
  client.println("Click <a href=\"/P6=OFF\">here</a> turn OFF pin 6<br>");
  client.println("</html>");

  client.println("<br><br>");
  client.println("Click <a href=\"/P7=ON\">here</a> turn ON pin 7<br>");
  client.println("Click <a href=\"/P7=OFF\">here</a> turn OFF pin 7<br>");
  client.println("</html>");

  client.println("<br><br>");
  client.println("Click <a href=\"/P8=ON\">here</a> turn ON pin 8<br>");
  client.println("Click <a href=\"/P8=OFF\">here</a> turn OFF pin 8<br>");
  client.println("</html>");

  Serial.println(count); 

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
