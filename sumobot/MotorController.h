/*
  Information:
  This was written for the 2016 McMaster Sumobot Senior competition. All of the code was written by
  McMaster students. For more information about the club check out sumobot.ca for more information.
  
  This is the the object in which all motor controls are defined. Having this allows simple references
  in the robot logic. The objects set up all the pins themselves, so all that is needed to configure 
  the pins correctly is to pass in valid pins (pwm pins are needed).

  Author: Braden Corbold
  Program: Mechatronics Engineering Level III - McMaster University
  Date: September 25th 2016
*/

#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

class MotorController {
  public:
    // Constructor
    MotorController();
    MotorController(int lf_onPin, int lr_onPin, int lf_pwmPin, int lr_pwmPin, int rf_onPin, int rr_onPin, int rf_pwmPin, int rr_pwmPin);
    
    // Methods
    void setUp(int lf_onPin, int lr_onPin, int lf_pwmPin, int lr_pwmPin, int rf_onPin, int rr_onPin, int rf_pwmPin, int rr_pwmPin);
    void slowForward(int time);
    void slowBackward(int time);
    void fastForward(int time);
    void fastBackward(int time);
    void slowLeft(int time);
    void slowRight(int time);
    void fastLeft(int time);
    void fastRight(int time);
    void fullStop();
    void customMove(int l_f_on, int l_r_on, int l_f_spd, int l_r_spd, int r_f_on, int r_r_on, int r_f_spd, int r_r_spd, int time);

  private:
    unsigned int _lf_onPin;
    unsigned int _lr_onPin;
    unsigned int _lf_pwmPin;
    unsigned int _lr_pwmPin;

    unsigned int _rf_onPin;
    unsigned int _rr_onPin;
    unsigned int _rf_pwmPin;
    unsigned int _rr_pwmPin;
};

#endif
