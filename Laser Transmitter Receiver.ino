#define laser1 2
#define sensor1 3
#define laser2 4
#define sensor2 5
long int start=0,stop=0;

void setup() {
  Serial.begin(9600);
  pinMode(laser1, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(laser2, OUTPUT);
  pinMode(sensor2, INPUT);
  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);
}

void loop() {
  bool value1 = digitalRead(sensor1);
  bool value2 = digitalRead(sensor2);
  if (value1 == 0 and start==0) {
    start=millis();
    Serial.print("Start Time: ");
    Serial.println(start);
 } else if (value2 == 0 and stop==0 and start!=0) {
    stop=millis();
    Serial.print("Stop Time: ");
    Serial.println(stop);
    Serial.print("Total Time: ");
    Serial.println(stop-start);
  }
//  delay(100);
}
