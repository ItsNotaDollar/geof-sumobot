/*
 Information:
 This was written for the 2016 McMaster Sumobot Senior competition. All of the code was written by
 McMaster students. For more information about the club check out sumobot.ca for more information.
 
 This is the the object in which all motor controls are defined. Having this allows simple references
 in the robot logic. The objects set up all the pins themselves, so all that is needed to configure 
 the pins correctly is to pass in valid pins (pwm pins are needed).

 Author: Braden Corbold
 Program: Mechatronics Engineering Level III - McMaster University
 Date: November 1st 2016
*/

#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

enum State {FULL_STOP, TIMED_STOP, INTERRUPTED, SLOW_FORWARD, SLOW_BACKWARD, FAST_FORWARD, FAST_BACKWARD, SLOW_LEFT, SLOW_RIGHT, FAST_LEFT, FAST_RIGHT, CUSTOM_MOVE};

class MotorController {
  public:
    // Constructor
    MotorController();
    MotorController(int _L_F_Pin, int _L_B_Pin, int _R_B_Pin, int _R_F_Pin);
   
    // Methods
    void fullStop(bool isInterrupt);
    void timedStop(int time, bool isInterrupt);

    void slowForward(int time);
    void slowBackward(int time);
    void fastForward(int time);
    void fastBackward(int time);
    void slowLeft(int time);
    void slowRight(int time);
    void fastLeft(int time);
    void fastRight(int time);
    void customMove(int _L_F_Spd, int _L_B_Spd, int _R_B_Spd, int _R_F_Spd, int time);

  private:
    int _L_F_Pin;
    int _L_B_Pin;
    int _R_B_Pin;
    int _R_F_Pin;

    State lastState;
};

#endif
