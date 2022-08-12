#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);
String str;
void setup(){
Serial.begin(115200);
espSerial.begin(115200);
delay(2000);
}
void loop()
{
str =String("coming from arduino");
espSerial.println(str);
delay(1000);
}
