#include "Arduino.h"
#include "MotorController.h"

const unsigned int MOTOR_FULL = 255;
const unsigned int MOTOR_HALF = 128;
const unsigned int MOTOR_STOP = 0;

MotorController::MotorController(){};

MotorController::MotorController(int lf_onPin, int lr_onPin, int lf_pwmPin, int lr_pwmPin, int rf_onPin, int rr_onPin, int rf_pwmPin, int rr_pwmPin) {

  _lf_onPin = lf_onPin;
  _lr_onPin = lr_onPin;
  _lf_pwmPin = lf_pwmPin;
  _lr_pwmPin = lr_pwmPin;

  _rf_onPin = rf_onPin;
  _rr_onPin = rr_onPin;
  _rf_pwmPin = rf_pwmPin;
  _rr_pwmPin = rr_pwmPin;

  pinMode(_lf_onPin , OUTPUT);
  pinMode(_lr_onPin , OUTPUT);
  pinMode(_lf_pwmPin , OUTPUT);
  pinMode(_lr_pwmPin , OUTPUT);

  pinMode(_rf_onPin , OUTPUT);
  pinMode(_rr_onPin , OUTPUT);
  pinMode(_rf_pwmPin , OUTPUT);
  pinMode(_rr_pwmPin , OUTPUT);
}

void MotorController::setUp(int lf_onPin, int lr_onPin, int lf_pwmPin, int lr_pwmPin, int rf_onPin, int rr_onPin, int rf_pwmPin, int rr_pwmPin) {
  _lf_onPin = lf_onPin;
  _lr_onPin = lr_onPin;
  _lf_pwmPin = lf_pwmPin;
  _lr_pwmPin = lr_pwmPin;

  _rf_onPin = rf_onPin;
  _rr_onPin = rr_onPin;
  _rf_pwmPin = rf_pwmPin;
  _rr_pwmPin = rr_pwmPin;

  pinMode(_lf_onPin , OUTPUT);
  pinMode(_lr_onPin , OUTPUT);
  pinMode(_lf_pwmPin , OUTPUT);
  pinMode(_lr_pwmPin , OUTPUT);

  pinMode(_rf_onPin , OUTPUT);
  pinMode(_rr_onPin , OUTPUT);
  pinMode(_rf_pwmPin , OUTPUT);
  pinMode(_rr_pwmPin , OUTPUT);
}

void MotorController::slowForward(int time) {
  digitalWrite(_lf_onPin   , HIGH);
  digitalWrite(_lr_onPin   , LOW);
  analogWrite(_lf_pwmPin   , MOTOR_HALF);
  analogWrite(_lr_pwmPin   , MOTOR_STOP);

  digitalWrite(_rf_onPin   , HIGH);
  digitalWrite(_rr_onPin   , LOW);
  analogWrite(_rf_pwmPin   , MOTOR_HALF);
  analogWrite(_rr_pwmPin   , MOTOR_STOP);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}

void MotorController::slowBackward(int time) {
  digitalWrite(_lf_onPin   , LOW);
  digitalWrite(_lr_onPin   , HIGH);
  analogWrite(_lf_pwmPin   , MOTOR_STOP);
  analogWrite(_lr_pwmPin   , MOTOR_HALF);

  digitalWrite(_rf_onPin   , LOW);
  digitalWrite(_rr_onPin   , HIGH);
  analogWrite(_rf_pwmPin   , MOTOR_STOP);
  analogWrite(_rr_pwmPin   , MOTOR_HALF);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}

void MotorController::fastForward(int time) {
  digitalWrite(_lf_onPin   , HIGH);
  digitalWrite(_lr_onPin   , LOW);
  analogWrite(_lf_pwmPin   , MOTOR_FULL);
  analogWrite(_lr_pwmPin   , MOTOR_STOP);

  digitalWrite(_rf_onPin   , HIGH);
  digitalWrite(_rr_onPin   , LOW);
  analogWrite(_rf_pwmPin   , MOTOR_FULL);
  analogWrite(_rr_pwmPin   , MOTOR_STOP);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}

void MotorController::fastBackward(int time) {
  digitalWrite(_lf_onPin   , LOW);
  digitalWrite(_lr_onPin   , HIGH);
  analogWrite(_lf_pwmPin   , MOTOR_STOP);
  analogWrite(_lr_pwmPin   , MOTOR_FULL);

  digitalWrite(_rf_onPin   , LOW);
  digitalWrite(_rr_onPin   , HIGH);
  analogWrite(_rf_pwmPin   , MOTOR_STOP);
  analogWrite(_rr_pwmPin   , MOTOR_FULL);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}

void MotorController::slowLeft(int time) {
  digitalWrite(_lf_onPin   , LOW);
  digitalWrite(_lr_onPin   , HIGH);
  analogWrite(_lf_pwmPin   , MOTOR_STOP);
  analogWrite(_lr_pwmPin   , MOTOR_HALF);

  digitalWrite(_rf_onPin   , HIGH);
  digitalWrite(_rr_onPin   , LOW);
  analogWrite(_rf_pwmPin   , MOTOR_HALF);
  analogWrite(_rr_pwmPin   , MOTOR_STOP);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}

void MotorController::slowRight(int time) {
  digitalWrite(_lf_onPin   , HIGH);
  digitalWrite(_lr_onPin   , LOW);
  analogWrite(_lf_pwmPin   , MOTOR_HALF);
  analogWrite(_lr_pwmPin   , MOTOR_STOP);

  digitalWrite(_rf_onPin   , LOW);
  digitalWrite(_rr_onPin   , HIGH);
  analogWrite(_rf_pwmPin   , MOTOR_STOP);
  analogWrite(_rr_pwmPin   , MOTOR_HALF);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}

void MotorController::fastLeft(int time) {
  digitalWrite(_lf_onPin   , LOW);
  digitalWrite(_lr_onPin   , HIGH);
  analogWrite(_lf_pwmPin   , MOTOR_STOP);
  analogWrite(_lr_pwmPin   , MOTOR_FULL);

  digitalWrite(_rf_onPin   , HIGH);
  digitalWrite(_rr_onPin   , LOW);
  analogWrite(_rf_pwmPin   , MOTOR_FULL);
  analogWrite(_rr_pwmPin   , MOTOR_STOP);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}

void MotorController::fastRight(int time) {
  digitalWrite(_lf_onPin   , HIGH);
  digitalWrite(_lr_onPin   , LOW);
  analogWrite(_lf_pwmPin   , MOTOR_FULL);
  analogWrite(_lr_pwmPin   , MOTOR_STOP);

  digitalWrite(_rf_onPin   , LOW);
  digitalWrite(_rr_onPin   , HIGH);
  analogWrite(_rf_pwmPin   , MOTOR_STOP);
  analogWrite(_rr_pwmPin   , MOTOR_FULL);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
    fullStop();
}

void MotorController::fullStop() {
  digitalWrite(_lf_onPin   , LOW);
  digitalWrite(_lr_onPin   , LOW);
  analogWrite(_lf_pwmPin   , MOTOR_STOP);
  analogWrite(_lr_pwmPin   , MOTOR_STOP);

  digitalWrite(_rf_onPin   , LOW);
  digitalWrite(_rr_onPin   , LOW);
  analogWrite(_rf_pwmPin   , MOTOR_STOP);
  analogWrite(_rr_pwmPin   , MOTOR_STOP);

}

void MotorController::customMove(int l_f_on, int l_r_on, int l_f_spd, int l_r_spd,
  int r_f_on, int r_r_on, int r_f_spd, int r_r_spd, int time) {
  digitalWrite(_lf_onPin   , l_f_on);
  digitalWrite(_lr_onPin   , l_r_on);
  analogWrite(_lf_pwmPin   , l_f_spd);
  analogWrite(_lr_pwmPin   , l_r_spd);

  digitalWrite(_rf_onPin   , r_f_on);
  digitalWrite(_rr_onPin   , r_r_on);
  analogWrite(_rf_pwmPin   , r_f_spd);
  analogWrite(_rr_pwmPin   , r_r_spd);

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= time){
    currentTime = millis();
  }
  fullStop();
}