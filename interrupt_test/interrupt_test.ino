#include "Thread.h"
#include "ThreadController.h"
#include "TimerOne.h"

/****************************************************************************************************/
/*                                         Setting Up Pins                                          */
/****************************************************************************************************/

const unsigned int F_PRES_PIN           = 0;
const unsigned int B_PRES_PIN           = 1;

bool frontInterruptIsLow = true;
bool  backInterruptIsLow = true;

void setup() {
  Serial.begin(9600);

  pinMode(F_PRES_PIN, INPUT);
  pinMode(B_PRES_PIN, INPUT);

  // Setting up Pressure sensors on the interrupts
  attachInterrupt(digitalPinToInterrupt(F_PRES_PIN), frontInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(B_PRES_PIN),  backInterrupt, CHANGE);

  Serial.println("+------------------------------------------------+");
  Serial.println("|                Interrupt Loggin                |");
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

void backInterrupt() {
  Serial.println(" *  backInterrupt() is running!");
  if (backInterruptIsLow) {
    Serial.println("| *  Rising edge.                                |");
    backInterruptIsLow = false;
  } else {
    Serial.println("| *  Falling edge.                               |");
    backInterruptIsLow = true;
  }
  Serial.println("+------------------------------------------------+");
}
