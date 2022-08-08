#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define TRIGGER_PIN D1
#define ECHO_PIN   D2
const char* ssid     ="Pred@tor Gaming";
const char* password ="19111998";
const char* host = "192.168.1.207";
WiFiClient client;
String url;
long duration, inches;
unsigned long timeout;
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(TRIGGER_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);
  WiFi.mode(WIFI_AP);
//name for the access point and 8 character password
  WiFi.softAP("NodeMCU", "nodemcur");
  delay(200);
    while (WiFi.softAPgetStationNum() !=1){ //loop here while no AP is connected to this station
      Serial.print(".");
      delay(100);                           
      }
// We start by connecting to a WiFi network
//Serial.println();
//Serial.println();
//Serial.print("Connecting to ");
//Serial.println(ssid);
//WiFi.mode (WIFI_STA);
//WiFi.begin(ssid, password);
//while (WiFi.status()!= WL_CONNECTED){
//  delay(500);
//  Serial.println("WiFi Not connected");
//  Serial.print(".");
//}
//Serial.println("");
//Serial.println("WiFi connected");
//Serial.println("IP address: ");
//Serial.println(WiFi.localIP());
}
float ultrasonic () {
  digitalWrite(TRIGGER_PIN, LOW); // Added this line 
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH); 
  inches = microsecondsToInches(duration);
  Serial.print(inches);
  Serial.println(" inches");
  return inches;
}
void loop() {
  Serial.print("distance of ");
  float in=float(ultrasonic());
    Serial.print("connected "); 
    Serial.println (host);
HTTPClient http;
// String buf = "inches=", in;
String buf;
  buf += F("inches=");
  buf += String(in, 0);
    Serial.println(buf);
// Connect to host where MySQL database is hosted, with IPv4 address of our NodeMCU
//http.begin("http://192.168.1.207:3306/nindex.php");
http.begin(client, "http://192.168.4.2/phpwrite.php");
//Specify content-type header
http.addHeader("Content-Type", "application/x-www-form-urlencoded");       
// Send POST request to php file and store server response code in variable named httpCode
int httpCode = http.POST(buf);
    Serial.println(buf);
if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode);
    String webpage = http.getString();  // Get html webpage output and store it in a string
    Serial.println(webpage + "\n");
  } else {
    // if failed to connect then return and restart
    Serial.println(httpCode);
    Serial.println("Failed to upload values. \n");
    http.end();
    return;
  }
// Use WiFiClient class to create TCP connections
//
//  WiFiClient client;
//  const int httpPort = 3306;
//  if (!client.connect (host, httpPort)) {
//  Serial.println("connection failed");
//  Serial.println(String("GET http://localhost/test/connect.php")+ 
//    ("&inches=") + inches + 
//    "HTTP/1.1\r\n" + 
//    "Host: " + host + "\r\n" + 
//    "Connection: close\r\n\r\n");
//  return;
//  }
//
//  // This will send the request to the server
//  client.print(String("GET http://localhost/test/connect.php")+ 
//    ("&inches=") + inches + 
//    "HTTP/1.1\r\n" + 
//    "Host: " + host + "\r\n" + 
//    "Connection: close\r\n\r\n");
//    
//    unsigned long timeout= millis();
//    while (client.available() == 0) {
//    if (millis() - timeout >1000) {
//    Serial.println(">>> client Timeout !"); 
//    client.stop();
//    return;
//
//    }
//  }
//
//
//// Read all the lines of the reply from server and print them to Serial 
//while (client.available()) { 
//  String line = client.readStringUntil('\r');
//  Serial.print(line);
//
//}
//
//      Serial.println();
//      Serial.println("closing connection");
}
long microsecondsToInches(long microseconds)
{
  return microseconds /74 /2;
}
