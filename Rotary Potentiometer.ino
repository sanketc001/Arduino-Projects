#define POTENTIOMETER_PIN A0
void setup() 
{
  Serial.begin(9600);
}
void loop()
{
  double x=analogRead(POTENTIOMETER_PIN);
  x=x/1023;
  x=x*270;
  x=x-135;
  Serial.println(x);
  delay(100);
}
