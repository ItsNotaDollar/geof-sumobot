#include "Arduino.h"
#include "QrdThread.h"

const unsigned int THRESHOLD = 100;

void QrdThread::pinSetup(int qrdPin){
  qrd_Pin = qrdPin;
//  qrdState = 0;
};

void QrdThread::run() {
  qrdState = analogRead(qrd_Pin) < THRESHOLD ? 1 : 0;
  runned();
};
