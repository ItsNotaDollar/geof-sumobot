#include <"Ultrasonic.h">
/****************************************************************************************************/
/*                                         Setting Up Pins                                          */
/****************************************************************************************************/

const unsigned int RIGHT_SONAR_TX       = 10;
const unsigned int RIGHT_SONAR_RX       = 11;
const unsigned int LEFT_SONAR_TX        = 12;
const unsigned int LEFT_SONAR_RX        = 13;

Ultrasonic leftSonar(LEFT_SONAR_TX, LEFT_SONAR_RX);
Ultrasonic rightSonar(RIGHT_SONAR_TX, RIGHT_SONAR_RX);

void setup() {  }

void loop() {  }
