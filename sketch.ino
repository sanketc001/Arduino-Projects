const int stepPin = 4;
const int dirPin = 3;
void setup() {
  // put your setup code here, to run once:
pinMode(stepPin, OUTPUT);
pinMode(dirPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 test();
}

void test(){
 digitalWrite(dirPin, HIGH);
  // Makes 200 pulses for making one full cycle rotation
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000); // 5 thousand
    //Serial.println("we did it!.");
  }
}
