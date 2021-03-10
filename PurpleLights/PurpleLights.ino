#include <SpheroRVR.h> //Always needed if using a SpheroRVR

static uint32_t ledGroup; //Specifically for the lights

void setup() {
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
    // set headlights to purple
    uint8_t purpleArray[] = {0x8C, 0x0A, 0xFF, 0x8C, 0x0A, 0xFF};
    rvr.setAllLeds(ledGroup, purpleArray, sizeof(purpleArray) / sizeof(purpleArray[0]));
}
