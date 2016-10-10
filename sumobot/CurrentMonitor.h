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

#ifndef CurrentMonitor_h
#define CurrentMonitor_h

#include "Arduino.h"
#include "Thread.h"
#include "ThreadController.h"

class CurrentMonitor : public Thread {
    public:
        void pinSetup(int currentPin_setUp);
        void run();
    private:
        int currentPin;
        bool hasToMuchCurrent;
};

#endif
