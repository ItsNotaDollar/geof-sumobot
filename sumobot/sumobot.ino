/*
 * Information:
 * This was written for the 2016 McMaster Sumobot Senior competition. All of the code was written by
 * McMaster students. For more information about the club check out sumobot.ca for more information.
 *
 * Author: Braden Corbold
 * Program: Mechatronics Engineering Level IV - McMaster University
 * Date: October 10th 2016
 *
 * Dependencies:
 * This project three dependencies which can be found at the links provided below. Follow normal 
 * Arduino library workflow to import and used in other projects.
 * 
 * Ultrasonic -> http://tutorial.cytron.com.my/2012/10/11/testing-ultrasonic-ranging-module-sn-hc-sr04/
 * Thread     -> https://github.com/ivanseidel/ArduinoThread
 * TimerOne   -> http://playground.arduino.cc/Code/Timer1
 */

//todo: This is our testing schedule for each component, getting more and more complicated as things come together
// 1.   Make a QRD test file
// 2.   Make a sonar test file
// 3.   Make a thread test file (very simple)
// 4.   Simple Motor controller file (Drive square, and then reverse square?)
// 5.   Test reading the current values
// 6.   Test interrupts
// 7.   QRD thread + Current thread
// 8.   Sonar + motor + Current
// 9.   Sonar + qrd
// 10.  Sonar + motor + current + qrd
// 11.  Motor + current + pressure
// 12.  full test

/*TODO -> Thoughts on current sensor
            - it would be sweet if the current sensor could be configured as an interrupt
            - this is really what we want so we dont have to poll it constantly
*/

#include "Ultrasonic.h"
#include "Thread.h"
#include "ThreadController.h"
#include "TimerOne.h"
#include "sumobot.h"
#include "MotorController.h"
#include "QrdThread.h"
#include "CurrentMonitor.h"

/****************************************************************************************************/
/*                                         Setting Up Pins                                          */
/****************************************************************************************************/
const unsigned int F_L_QRD_PIN          = A0;
const unsigned int F_R_QRD_PIN          = A1;
const unsigned int B_L_QRD_PIN          = A2;
const unsigned int B_R_QRD_PIN          = A3;

// const unsigned int X_AXIS_PIN           = A4; // +ve -> Right
// const unsigned int Y_AXIS_PIN           = A5; // +ve -> Forward

const unsigned int CURRENT_SENSOR_PIN   = A6;

const unsigned int F_PRES_PIN           = 0;
const unsigned int B_PRES_PIN           = 1;

// TODO: These have yet to be properly implemented in the motor controller
const unsigned int Left_Forward_Pin     = 3;
const unsigned int Left_Backward_Pin    = 5;
const unsigned int Right_Backward_Pin   = 6;
const unsigned int Right_Forward_Pin    = 9;


// TODO: These need to be removed from the motor controller and updated witht he new values
// @Deprecated
// const unsigned int LEFT_FRWD_ON_PIN     = 2;
// const unsigned int LEFT_FRWD_PWM_PIN    = 3;
// const unsigned int LEFT_REV_ON_PIN      = 4;
// const unsigned int LEFT_REV_PWM_PIN     = 5;

// @Deprecated
// const unsigned int RIGHT_REV_PWM_PIN    = 6;
// const unsigned int RIGHT_REV_ON_PIN     = 7;
// const unsigned int RIGHT_FRWD_ON_PIN    = 8;
// const unsigned int RIGHT_FRWD_PWM_PIN   = 9;

const unsigned int SONAR_RIGHT_TX       = 10; // Relative to arduino
const unsigned int SONAR_RIGHT_RX       = 11; // Relative to arduino
const unsigned int SONAR_LEFT_TX        = 12; // Relative to arduino
const unsigned int SONAR_LEFT_RX        = 13; // Relative to arduino

Ultrasonic rightSonar(10, 11);
Ultrasonic  leftSonar(12, 13);

MotorController  motors;
QrdThread        qrdThread;
TimerOne         qrdTimer;
CurrentMonitor   currentMonitor;
TimerOne         currentMonitorTimer;
ThreadController controller = ThreadController();

bool frontInterruptIsLow = true;
bool  backInterruptIsLow = true;

void setup() {
  // pinMode(X_AXIS_PIN, INPUT);
  // pinMode(Y_AXIS_PIN, INPUT);

  pinMode(CURRENT_SENSOR_PIN, INPUT);

  pinMode(F_PRES_PIN, INPUT); // These are our interrupt pins
  pinMode(B_PRES_PIN, INPUT);

  pinMode(SONAR_RIGHT_TX, OUTPUT);
  pinMode(SONAR_RIGHT_RX, INPUT);
  pinMode(SONAR_LEFT_TX, OUTPUT);
  pinMode(SONAR_LEFT_RX, INPUT);

  // Setting up the motor controller
  motors.setUp(LEFT_FRWD_ON_PIN, LEFT_REV_ON_PIN, LEFT_FRWD_PWM_PIN, LEFT_REV_PWM_PIN, RIGHT_FRWD_ON_PIN, RIGHT_REV_ON_PIN, RIGHT_FRWD_PWM_PIN, RIGHT_REV_PWM_PIN);
  
  // Setting up the QRD thread
  qrdThread.pinSetup(F_L_QRD_PIN, F_R_QRD_PIN, B_L_QRD_PIN, B_R_QRD_PIN);
  qrdThread.setInterval(100);
  controller.add(&qrdThread);
  qrdTimer.initialize(100000); // 100 ms
  qrdTimer.attachInterrupt(qrdCheck); // Starting the qrd thread to convert vals every 100ms
  qrdTimer.start();

  // todo: This may not be needed if we can do it with a interrupt?
  //          -> Every cicle write to out pin (coneected directly to interrupt pin)
  //          -> On rising edge then we know that the current has spiked
  // Setting up the current sensing thread.
  currentMonitor.pinSetup(CURRENT_SENSOR_PIN);
  currentMonitor.setInterval(10); //todo: need to test if this is going to be overkill or not
  controller.add(&currentMonitor);

  // Setting up Pressure sensors on the interrupts
  attachInterrupt(digitalPinToInterrupt(F_PRES_PIN), frontInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(B_PRES_PIN),  backInterrupt, CHANGE);

  unsigned long previousTime = millis();
  unsigned long  currentTime = millis();
  while((previousTime - currentTime) >= 5000){
    currentTime = millis();
    //todo: we can added some scans in here to "formulate" a plan
  }
}

/* This function is the main logic for the sumobot logic.
 * It calls the following methods:
 *    - handleQrdValues()
 *    - sonarCheck()
 * @return: void
 */
void loop() {
  handleQrdValues(); // state handled by qrdThread

  sonarCheck(); // looks for opponent, and then moves accordingly
}


void qrdCheck(){
  // Runs the thread at the specified interval
  controller.run();
}

void handleQrdValues(){ // todo: This will need some more work
    switch(qrdThread.qrdState) {
      case 0:
        // no qrds tripped
        // Do nothing
        break;
      case 1:
        // just front left
        motors.slowRight(300);
        break;
      case 2:
        // just front right
        motors.slowLeft(300);
        break;
      case 4:
        // just back left
        motors.slowRight(300);
        break;
      case 8:
        // just back right
        motors.slowLeft(300);
        break;
      case 3:
        // both front
        motors.fastBackward(500);
        motors.fastLeft(300); //Try to calibrate for a 180
        break;
      case 12:
        // both back
        motors.fastForward(500); // Most likely are being rammed, go full foward
        break;
      case 5:
        // both left
        break;
      case 10:
        // both right
        break;
      default:
        break;
    }
}

void sonarCheck(){}

// todo: These are the points where we have to be really carefull about the current going through our motors
void frontInterrupt() {
  // todo: Create a good way to handle getting hit from the fron
  // todo: Should we enter a seperate logic to poll for white line values?
  /* 1. Set move speed forward (no time limit)
   * 2. Continue to move forward till falling edge, or white line (do Ernest spazz ram)
   *
   */
  motors.fastForward(1000);
}

void backInterrupt() {
  // todo: same as frontInterrupt but, well, oposite


}


