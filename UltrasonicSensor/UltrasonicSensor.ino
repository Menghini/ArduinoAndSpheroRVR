#include <SpheroRVR.h> //Always needed if using a SpheroRVR


static uint32_t ledGroup; //Specifically for the lights
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor


void setup() {
  Serial.begin(9600); // Starting Serial Terminal

  // set up communication with the RVR.
  rvr.configUART(&Serial); //Do not remove or change this line. Always needed if using a SpheroRVR
  
  // setting up the led group for both headlights. 
  ledGroup = 0; //Do not remove or change this line
  ledGroup |= (1 << static_cast<uint8_t>(LEDs::rightHeadlightRed)); //Do not remove or change this line
  ledGroup |= (1 << static_cast<uint8_t>(LEDs::rightHeadlightGreen)); //Do not remove or change this line
  ledGroup |= (1 << static_cast<uint8_t>(LEDs::rightHeadlightBlue)); //Do not remove or change this line
  ledGroup |= (1 << static_cast<uint8_t>(LEDs::leftHeadlightRed)); //Do not remove or change this line
  ledGroup |= (1 << static_cast<uint8_t>(LEDs::leftHeadlightGreen)); //Do not remove or change this line
  ledGroup |= (1 << static_cast<uint8_t>(LEDs::leftHeadlightBlue)); //Do not remove or change this line
}

void loop() {
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  if(inches < 2){
    // set headlights to red
    uint8_t redArray[] = {0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00};
    rvr.setAllLeds(ledGroup, redArray, sizeof(redArray) / sizeof(redArray[0]));
  }else{
    // set headlights to green
    uint8_t greenArray[] = {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00};
    rvr.setAllLeds(ledGroup, greenArray, sizeof(greenArray) / sizeof(greenArray[0]));
  }
  cm = microsecondsToCentimeters(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
