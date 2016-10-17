/*
  Information:
  This was written for the 2016 McMaster Sumobot Senior competition. All of the code was written by
  McMaster students. For more information about the club check out sumobot.ca for more information.

  Author: Braden Corbold
  Program: Mechatronics Engineering Level IV - McMaster University
  Date: October 8th 2016

  Dependencies:
  This class extends the ArduinoThread which can be found at the link below.
  https://github.com/ivanseidel/ArduinoThread
*/

#ifndef QrdThread_h
#define QrdThread_h

#include "Arduino.h"
#include "Thread.h"
#include "ThreadController.h"

class QrdThread : public Thread {
    public:
        int f_LBitValue;
        int f_RBitValue;
        int b_LBitValue;
        int b_RBitValue;

        int qrdState = 0;

        void pinSetup(int f_LPinSetup, int f_RPinSetup, int b_LPinSetup, int b_RPinSetup);
        void run();
    private:
        int f_LPin;
        int f_RPin;
        int b_LPin;
        int b_RPin;
};

#endif
