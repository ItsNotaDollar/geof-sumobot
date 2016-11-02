/*
 * Information:
 * This was written for the 2016 McMaster Sumobot Senior competition. All of the code was written by
 * McMaster students. For more information about the club check out sumobot.ca for more information.
 *
 * Author: Braden Corbold
 * Program: Mechatronics Engineering Level IV - McMaster University
 * Date: November 1st 2016
 *
 * Dependencies:
 * This project three dependencies which can be found at the links provided below. Follow normal 
 * Arduino library workflow to import and use in other projects.
 * 
 * Ultrasonic -> http://tutorial.cytron.com.my/2012/10/11/testing-ultrasonic-ranging-module-sn-hc-sr04/
 * Thread     -> https://github.com/ivanseidel/ArduinoThread
 * TimerOne   -> http://playground.arduino.cc/Code/Timer1
 */

//#include <"Ultrasonic.h">
#include "Thread.h"
#include "ThreadController.h"
#include "TimerOne.h"
#include "sumobot.h"
#include "MotorController.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                         Setting Up Pins                                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const unsigned int F_L_QRD_PIN          = A0;
const unsigned int F_R_QRD_PIN          = A1;
const unsigned int B_L_QRD_PIN          = A2;
const unsigned int B_R_QRD_PIN          = A3;

const unsigned int X_AXIS_PIN           = A4;
const unsigned int Y_AXIS_PIN           = A5;

const unsigned int CURRENT_SENSOR_PIN   = A6;

const unsigned int F_PRES_PIN           = 2;
const unsigned int B_PRES_PIN           = 4;

const unsigned int Left_Forward_Pin     = 3;
const unsigned int Left_Backward_Pin    = 5;
const unsigned int Right_Backward_Pin   = 6;
const unsigned int Right_Forward_Pin    = 9;

const unsigned int RIGHT_SONAR_TX       = 10;
const unsigned int RIGHT_SONAR_RX       = 11;
const unsigned int LEFT_SONAR_TX        = 12;
const unsigned int LEFT_SONAR_RX        = 13;

const unsigned int QRD_THRESHOLD        = 100;
const unsigned int CURRENT_THRESHOLD    = 13; // Calculated value when hitting 10A
// todo: this will need some calibration

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
MotorController motors = MotorController(Left_Forward_Pin, Left_Backward_Pin, Right_Backward_Pin, Right_Forward_Pin);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Thread qrdThread = Thread();
Thread currentMonitorThread = Thread();

ThreadController controller = ThreadController();

void runController(){
  controller.run();
}

// callback for qrdThread
void checkQrdValues(){
  //todo: implement qrd logic here
  unsigned int f_l_val = analogRead(F_L_QRD_PIN) < QRD_THRESHOLD ? 1 : 0;
  unsigned int f_r_val = analogRead(F_R_QRD_PIN) < QRD_THRESHOLD ? 2 : 0;
  unsigned int b_l_val = analogRead(B_L_QRD_PIN) < QRD_THRESHOLD ? 4 : 0;
  unsigned int b_r_val = analogRead(B_R_QRD_PIN) < QRD_THRESHOLD ? 8 : 0;

  unsigned int qrdState = f_l_val + f_r_val + b_l_val + b_r_val;

  switch(qrdState) {
    // One Qrd Tripped
    case 1: 
      break;
    case 2:
      break;
    case 4:
      break;
    case 8:
      break;

    // 2 Qrds Tripped
    case 3:
      break;
    case 12:
      break;
    case 5:
      break;
    case 10:
      break;

    // 0 Qrds tripped (geometry of the ring excludes 3 or 4 Qrds being tripped as a possibility)
    default:
      break;
  }
}

void checkCurrentUsage(){
  if (analogRead(CURRENT_SENSOR_PIN) >= CURRENT_THRESHOLD) {
    motors.timedStop(10, true);
    delay(10);
  }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void setup() {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
pinMode(F_L_QRD_PIN, INPUT);
pinMode(F_R_QRD_PIN, INPUT);
pinMode(B_L_QRD_PIN, INPUT);
pinMode(B_R_QRD_PIN, INPUT);

pinMode(X_AXIS_PIN, INPUT);
pinMode(Y_AXIS_PIN, INPUT);

pinMode(CURRENT_SENSOR_PIN, INPUT);

pinMode(F_PRES_PIN, INPUT);
pinMode(B_PRES_PIN, INPUT);

pinMode(Left_Forward_Pin, OUTPUT);
pinMode(Left_Backward_Pin, OUTPUT);
pinMode(Right_Backward_Pin, OUTPUT);
pinMode(Right_Forward_Pin, OUTPUT);

pinMode(RIGHT_SONAR_TX, OUTPUT);
pinMode(RIGHT_SONAR_RX, INPUT);
pinMode(LEFT_SONAR_TX, OUTPUT);
pinMode(LEFT_SONAR_RX, INPUT);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  qrdThread.onRun(checkQrdValues);
  qrdThread.setInterval(100); //Want to run this every 100ms
  
  currentMonitorThread.onRun(checkCurrentUsage);
  currentMonitorThread.setInterval(20);

  controller.add(&qrdThread);
  controller.add(&currentMonitorThread);
  
  Timer1.initialize(10000);//checks if threads need to be run every 10ms
  Timer1.attachInterrupt(runController); //todo: we may be able to Timer1.attachInterrupt(controller.run);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}

void loop() {}



























