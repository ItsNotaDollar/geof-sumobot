#include "Arduino.h"
#include "CurrentMonitor.h"

// todo: This needs to be calibrated for the voltage drop on the current sensor
const unsigned int CURRENT_THRESHOLD = 5000; //for 5000ma 

void CurrentMonitor::pinSetup(int currentPin_setUp){
  currentPin = currentPin_setUp;
  pinMode(currentPin, INPUT);
  hasToMuchCurrent = false;
};

void CurrentMonitor::run() {
  if (analogRead(currentPin) >= CURRENT_THRESHOLD) {
    hasToMuchCurrent = true;
  } else {
    hasToMuchCurrent = false;
  }
  runned();
};
