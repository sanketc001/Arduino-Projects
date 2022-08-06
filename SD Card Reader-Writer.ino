#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 53;
void setup() {
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } 
  else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  myFile = SD.open("test3.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Testing text 1, 2 ,3...");
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  else {
    Serial.println("error opening test.txt");
  }
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("error opening test.txt");
  }
}
void loop() {
}
