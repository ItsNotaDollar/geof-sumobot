#include "Arduino.h"
#include "QrdThread.h"

const unsigned int THRESHOLD = 100;

void QrdThread::pinSetup(int f_LPinSetup, int f_RPinSetup, int b_LPinSetup, int b_RPinSetup){
  f_LPin = f_LPinSetup;
  f_RPin = f_RPinSetup;
  b_LPin = b_LPinSetup;
  b_RPin = b_RPinSetup;

  pinMode(f_LPin,INPUT);
  pinMode(f_RPin,INPUT);
  pinMode(b_LPin,INPUT);
  pinMode(b_RPin,INPUT);
};

void QrdThread::run() {
  f_LBitValue = analogRead(f_LPin) < THRESHOLD ? 1 : 0;
  f_RBitValue = analogRead(f_RPin) < THRESHOLD ? 2 : 0;
  b_LBitValue = analogRead(b_LPin) < THRESHOLD ? 4 : 0;
  b_RBitValue = analogRead(b_RPin) < THRESHOLD ? 8 : 0;
  qrdState = f_LBitValue + f_RBitValue + b_LBitValue + b_RBitValue;
  runned();
};
