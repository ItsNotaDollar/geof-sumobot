#include "Arduino.h"
#define NOT_AN_INTERRUPT -1
/****************************************************************************************************/
/*                                         Setting Up Pins                                          */
/****************************************************************************************************/

const unsigned int F_PRES_PIN = 2;

bool frontInterruptIsLow = true;

void setup() {
  Serial.begin(9600);

  pinMode(F_PRES_PIN, INPUT);

  // Setting up Pressure sensors on the interrupts
  attachInterrupt(digitalPinToInterrupt(F_PRES_PIN), frontInterrupt, CHANGE);

  Serial.println("+------------------------------------------------+");
  Serial.println("|                Interrupt Logging               |");
  Serial.println("+------------------------------------------------+");
  Serial.println("");
  Serial.println("+------------------------------------------------+");
}

void loop() {  }

void frontInterrupt() {
  Serial.println("| *  frontInterrupt() is running!                |");
  if (frontInterruptIsLow) {
    Serial.println("| *  Rising edge.                                |");
    frontInterruptIsLow = false;
  } else {
    Serial.println("| *  Falling edge.                               |");
    frontInterruptIsLow = true;
  }
  Serial.println("+------------------------------------------------+");
}

