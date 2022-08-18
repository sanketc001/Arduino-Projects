#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define TRIGGER_PIN D1
#define ECHO_PIN   D2
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
String buf;
  buf += F("inches=");
  buf += String(in, 0);
    Serial.println(buf);
// Connect to host where MySQL database is hosted, with IPv4 address of our NodeMCU
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
}
long microsecondsToInches(long microseconds)
{
  return microseconds /74 /2;
}
