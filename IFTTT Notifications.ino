#include <ESP8266WiFi.h>
 
// Set WiFi credentials
#define WIFI_SSID "Pred@tor Gaming"
#define WIFI_PASS "19111998"
 
// Set IFTTT Webhooks event name and key
#define IFTTT_Key "API key here"
#define IFTTT_Event "notif" // or whatever you have chosen
#define IFTTT_Value1 "Moin, hier ist dein ESP8266!"
#define IFTTT_Value2 "25"
#define IFTTT_Value3 "value 3"
WiFiClient client;
 
void setup() {
  Serial.begin(9600); // Serial output only for information, you can also remove all Serial commands
  WiFi.begin(WIFI_SSID, WIFI_PASS); 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
  // Send Webook to IFTTT
  send_webhook();
}
 
void loop() {
  // empty
}
void send_webhook(){
  // construct the JSON payload
  String jsonString = "";
  jsonString += "{\"Value1\":\"";
  jsonString += IFTTT_Value1;
  jsonString += "\",\"Value2\":\"";
  jsonString += IFTTT_Value2;
  jsonString += "\",\"Value3\":\"";
  jsonString += IFTTT_Value3;
  jsonString += "\"}";
  int jsonLength = jsonString.length();  
  String lenString = String(jsonLength);
  // connect to the Maker event server
  client.connect("maker.ifttt.com", 80);
  // construct the POST request
  String postString = "";
  postString += "POST /trigger/";
  postString += IFTTT_Event;
  postString += "/json/with/key/";
  postString += IFTTT_Key;
  postString += " HTTP/1.1\r\n";
  postString += "Host: maker.ifttt.com\r\n";
  postString += "Content-Type: application/json\r\n";
  postString += "Content-Length: ";
  postString += lenString + "\r\n";
  postString += "\r\n";
  postString += jsonString; // combine post request and JSON
  Serial.println("Done");
  client.print(postString);
  delay(500);
  client.stop();
}
