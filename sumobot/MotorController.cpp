#include "Arduino.h"
#include "MotorController.h"

const unsigned int MOTOR_FULL = 255;
const unsigned int MOTOR_HALF = 127;
const unsigned int MOTOR_STOP = 0;


// FULL_STOP, TIMED_STOP, INTERRUPTED, SLOW_FORWARD, SLOW_BACKWARD, FAST_FORWARD, FAST_BACKWARD, SLOW_LEFT, SLOW_RIGHT, FAST_LEFT, FAST_RIGHT
MotorController::MotorController(){};

MotorController::MotorController(int L_F_Pin, int L_B_Pin, int R_B_Pin, int R_F_Pin) {
  _L_F_Pin = L_F_Pin;
  _L_B_Pin = L_B_Pin;
  _R_B_Pin = R_B_Pin;
  _R_F_Pin = R_F_Pin;
}

void MotorController::fullStop(bool isInterrupt) {
  analogWrite(_L_F_Pin, LOW);
  analogWrite(_L_B_Pin, LOW);
  analogWrite(_R_F_Pin, LOW);
  analogWrite(_R_B_Pin, LOW);
  if (isInterrupt) {
    lastState = INTERRUPTED;
  } else {
    lastState = FULL_STOP;
  }
}

void MotorController::timedStop(int time, bool isInterrupt) {
  analogWrite(_L_F_Pin, LOW);
  analogWrite(_L_B_Pin, LOW);
  analogWrite(_R_F_Pin, LOW);
  analogWrite(_R_B_Pin, LOW);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  if (isInterrupt) {
    lastState = INTERRUPTED;
  } else {
    lastState = TIMED_STOP;
  }
}


void MotorController::setFastForward() {
  analogWrite(_L_B_Pin, MOTOR_STOP);
  analogWrite(_R_B_Pin, MOTOR_STOP);
  analogWrite(_L_F_Pin, MOTOR_FULL);
  analogWrite(_R_F_Pin, MOTOR_FULL);
}

void MotorController::setFastBackward() {
  analogWrite(_L_F_Pin, MOTOR_STOP);
  analogWrite(_R_F_Pin, MOTOR_STOP);
  analogWrite(_L_B_Pin, MOTOR_FULL);
  analogWrite(_R_B_Pin, MOTOR_FULL);
}

void MotorController::slowForward(int time) {
  analogWrite(_L_B_Pin   , MOTOR_STOP);
  analogWrite(_R_B_Pin   , MOTOR_STOP);
  analogWrite(_L_F_Pin   , MOTOR_HALF);
  analogWrite(_R_F_Pin   , MOTOR_HALF);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = SLOW_FORWARD;
  fullStop(false);
}

void MotorController::slowBackward(int time) {
  analogWrite(_L_F_Pin, MOTOR_STOP);
  analogWrite(_R_F_Pin, MOTOR_STOP);
  analogWrite(_L_B_Pin, MOTOR_HALF);
  analogWrite(_R_B_Pin, MOTOR_HALF);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = SLOW_BACKWARD;
  fullStop(false);
}

void MotorController::fastForward(int time) {
  analogWrite(_L_B_Pin, MOTOR_STOP);
  analogWrite(_R_B_Pin, MOTOR_STOP);
  analogWrite(_L_F_Pin, MOTOR_FULL);
  analogWrite(_R_F_Pin, MOTOR_FULL);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = FAST_FORWARD;
  fullStop(false);
}

void MotorController::fastBackward(int time) {
  analogWrite(_L_F_Pin, MOTOR_STOP);
  analogWrite(_R_F_Pin, MOTOR_STOP);
  analogWrite(_L_B_Pin, MOTOR_FULL);
  analogWrite(_R_B_Pin, MOTOR_FULL);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = FAST_BACKWARD;
  fullStop(false);
}

void MotorController::slowLeft(int time) {
  analogWrite(_L_F_Pin, MOTOR_STOP);
  analogWrite(_R_B_Pin, MOTOR_STOP);
  analogWrite(_L_B_Pin, MOTOR_HALF);
  analogWrite(_R_F_Pin, MOTOR_HALF);
 
  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = SLOW_LEFT;
  fullStop(false);
}

void MotorController::slowRight(int time) {
  analogWrite(_L_B_Pin, MOTOR_STOP);
  analogWrite(_R_F_Pin, MOTOR_STOP);
  analogWrite(_L_F_Pin, MOTOR_HALF);
  analogWrite(_R_B_Pin, MOTOR_HALF);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = SLOW_RIGHT;
  fullStop(false);
}

void MotorController::fastLeft(int time) {
  analogWrite(_L_F_Pin, MOTOR_STOP);
  analogWrite(_R_B_Pin, MOTOR_STOP);
  analogWrite(_L_B_Pin, MOTOR_FULL);
  analogWrite(_R_F_Pin, MOTOR_FULL);
  
  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = FAST_LEFT;
  fullStop(false);
}

void MotorController::fastRight(int time) {
  analogWrite(_L_B_Pin, MOTOR_STOP);
  analogWrite(_R_F_Pin, MOTOR_STOP);
  analogWrite(_L_F_Pin, MOTOR_FULL);
  analogWrite(_R_B_Pin, MOTOR_FULL);
 
  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = FAST_RIGHT;
  fullStop(false);
}

void MotorController::customMove(int _L_F_Spd, int _L_B_Spd, int _R_B_Spd, int _R_F_Spd, int time) {
  analogWrite(_L_F_Pin, _L_F_Spd);
  analogWrite(_L_B_Pin, _L_B_Spd);
  analogWrite(_R_B_Pin, _R_B_Spd);
  analogWrite(_R_F_Pin, _R_F_Spd);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  lastState = CUSTOM_MOVE;
  fullStop(false);
}
