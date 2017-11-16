#include <Ultrasonic.h>

const unsigned int RIGHT_SONAR_TX       = 10;
const unsigned int RIGHT_SONAR_RX       = 11;
const unsigned int LEFT_SONAR_TX        = 12;
const unsigned int LEFT_SONAR_RX        = 13;

const bool FOR_CSV                      = false; // set false if would like an easy to read output
const unsigned int DELAY_TIME           = 500; // amount of delay inbetween loops

Ultrasonic leftSonar(LEFT_SONAR_TX, LEFT_SONAR_RX);
Ultrasonic rightSonar(RIGHT_SONAR_TX, RIGHT_SONAR_RX);

void setup() {
  pinMode(LEFT_SONAR_TX, OUTPUT);
  pinMode(LEFT_SONAR_RX, INPUT);
  pinMode(RIGHT_SONAR_TX, OUTPUT);
  pinMode(RIGHT_SONAR_RX, INPUT);

  Serial.begin(9600);

  Serial.println("Sonar Readings");
  if (FOR_CSV) {
    Serial.println("Left Sonar,Right Sonar");
  }
}

void loop() {
  int leftVal = leftSonar.Ranging(CM);
  int rightVal = rightSonar.Ranging(CM);

  if (FOR_CSV) {
    Serial.print(leftVal);
    Serial.print(",");
    Serial.println(rightVal);
  } else {
    Serial.println("+---------------------------------------+");
    Serial.print("Left Value: ");
    Serial.println(leftVal);
    Serial.print("Right Value: ");
    Serial.println(rightVal);
  }
  
}
