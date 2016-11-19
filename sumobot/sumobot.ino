/*
 * This was written for the 2016 McMaster Sumobot Advanced competition. All of the code was written by
 * McMaster students. For more information about the club check out sumobot.ca for more information.
 *
 * Author: Braden Corbold
 * Program: Mechatronics Engineering Level IV - McMaster University
 * Date: November 5th 2016
 *
 * Dependencies:
 * This project three dependencies which can be found at the links provided below. Follow normal 
 * Arduino library workflow to import and use in other projects.
 * 
 * Ultrasonic -> http://tutorial.cytron.com.my/2012/10/11/testing-ultrasonic-ranging-module-sn-hc-sr04/
 * Thread     -> https://github.com/ivanseidel/ArduinoThread
 * TimerOne   -> http://playground.arduino.cc/Code/Timer1
 */

#include <Arduino.h>
#include <Ultrasonic.h>
#include <Thread.h>
#include <ThreadController.h>
#include <TimerOne.h>
#include "MotorController.h"
#include "sumobot.h"

#define NOT_AN_INTERRUPT -1

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                          Setting Up Pins                                           */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const unsigned int QRD_THRESHOLD        = 100;
const unsigned int CURRENT_THRESHOLD    = 13; // Calculated value when hitting 10A todo: this will need some calibration
const unsigned int SONAR_THRESHOLD      = 130; // ring is 154 - 4 (white lines) - 20 opponent = 130

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const unsigned int MOTOR_FULL = 255;
const unsigned int MOTOR_HALF = 127;
const unsigned int MOTOR_STOP = 0;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ultrasonic leftSonar(LEFT_SONAR_TX, LEFT_SONAR_RX);
Ultrasonic rightSonar(RIGHT_SONAR_TX, RIGHT_SONAR_RX);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

MotorController motors = MotorController(Left_Forward_Pin, Left_Backward_Pin, Right_Backward_Pin, Right_Forward_Pin);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Thread qrdThread = Thread();
Thread currentMonitorThread = Thread();
Thread pressureSensorThread = Thread();

ThreadController controller = ThreadController();

void runController() {
  controller.run();
}

// callback for qrdThread
void checkQrdValues() {
  //todo: the timing of these will need to be calibrated
  unsigned int f_l_val = analogRead(F_L_QRD_PIN) < QRD_THRESHOLD ? 1 : 0;
  unsigned int f_r_val = analogRead(F_R_QRD_PIN) < QRD_THRESHOLD ? 2 : 0;
  unsigned int b_l_val = analogRead(B_L_QRD_PIN) < QRD_THRESHOLD ? 4 : 0;
  unsigned int b_r_val = analogRead(B_R_QRD_PIN) < QRD_THRESHOLD ? 8 : 0;

  unsigned int qrdState = f_l_val + f_r_val + b_l_val + b_r_val;

  switch(qrdState) {
    // One Qrd Tripped
    case 1: // front left
      motors.slowBackward(300);
      motors.fastRight(400);
      break;
    case 2: // front right 
      motors.slowBackward(300);
      motors.fastLeft(400);
      break;
    case 4: // back left
      motors.slowForward(300);
      motors.fastRight(400);
      break;
    case 8: // back right
      motors.slowForward(300);
      motors.fastLeft(400);
      break;

    // 2 Qrds Tripped
    case 3: // front QRDs
      motors.fastBackward(500);
      break;
    case 12: // back QRDs
      motors.fastForward(500);
      break;
    case 5: // left QRDs
      motors.customMove(MOTOR_HALF, 0, MOTOR_FULL, 0, 300); //todo: will need lots of calibration
      break;
    case 10: // right QRDs
      motors.customMove(MOTOR_FULL, 0, MOTOR_HALF, 0, 300); //todo: will need lots of calibration
      break;

    // 0 Qrds tripped (geometry of the ring excludes 3 or 4 Qrds being tripped as a possibility)
    default:
      break;
  }
}

bool isQrdsTripped() {
  return (analogRead(F_L_QRD_PIN) > QRD_THRESHOLD) && 
            (analogRead(F_R_QRD_PIN) > QRD_THRESHOLD) && 
            (analogRead(B_L_QRD_PIN) > QRD_THRESHOLD) && 
            (analogRead(B_R_QRD_PIN) > QRD_THRESHOLD);
}

void checkCurrentUsage() {
  if (analogRead(CURRENT_SENSOR_PIN) >= CURRENT_THRESHOLD) {
    motors.timedStop(5, true);
    delay(10);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void frontInterrupt() {
  if (digitalRead(F_PRES_PIN) == HIGH) {
    motors.setFastForward();
    while(digitalRead((F_PRES_PIN) == HIGH) && !isQrdsTripped()) {  } //todo: ram function?
    motors.fullStop(false);
  }
}
void backInterrupt() {
  if (digitalRead(B_PRES_PIN) == HIGH) {
    motors.setFastBackward();
    while(digitalRead((B_PRES_PIN) == HIGH) && !isQrdsTripped()) {  } //todo: ram function?
    motors.fullStop(false);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Range valToRange(int val) {
  if (val <= 5) {
    return LESS_THAN_5;
  } else if (val <= 20) {
    return LESS_THAN_20;
  } else if (val <= 50) {
    return LESS_THAN_50;
  } else if (val <= 100) {
    return LESS_THAN_100;
  } else {
    return TOO_FAR;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                              setUp()                                               */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() {
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

  pinMode(LEFT_SONAR_TX, OUTPUT);
  pinMode(LEFT_SONAR_RX, INPUT);
  pinMode(RIGHT_SONAR_TX, OUTPUT);
  pinMode(RIGHT_SONAR_RX, INPUT);
  

  qrdThread.onRun(checkQrdValues);
  qrdThread.setInterval(100); //Want to run this every 100ms
  
  currentMonitorThread.onRun(checkCurrentUsage);
  currentMonitorThread.setInterval(20);

  pressureSensorThread
.onRun(frontInterrupt);
  pressureSensorThread
.setInterval(150);

  backPressureThread.onRun(backInterrupt);
  backPressureThread.setInterval(150);

  controller.add(&qrdThread);
  controller.add(&currentMonitorThread);
  controller.add(&pressureSensorThread
  );
  controller.add(&backPressureThread);
  
  Timer1.initialize(10000);//checks if threads need to be run every 10ms
  Timer1.attachInterrupt(runController); //todo: we may be able to Timer1.attachInterrupt(controller.run);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                              loop()                                                */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {
  // all the needs to be handled is sonar functions and movements
  int leftVal = leftSonar.Ranging(CM);
  int rightVal = rightSonar.Ranging(CM);

  Range leftRange = valToRange(leftVal);
  Range rightRange = valToRange(rightVal);

  int diff = leftVal - rightVal;
  //Note: +ve = closer to right, -ve = closer to left
  if (diff < 0) {
    // need to move left
    switch(leftRange) {
      case LESS_THAN_5:
        motors.fastForward(1000);
        break;
      case LESS_THAN_20:
      case LESS_THAN_50:
        motors.fastLeft(300);
        motors.fastForward(500);
        break;
      case LESS_THAN_100:
      case TOO_FAR:
        motors.slowLeft(500);
        motors.slowForward(300);
        break;
    }
  } else  {
    // need to move right
    switch(rightRange) {
      case LESS_THAN_5:
        motors.fastForward(1000);
        break;
      case LESS_THAN_20:
      case LESS_THAN_50:
        motors.fastRight(300);
        motors.fastForward(500);
        break;
      case LESS_THAN_100:
      case TOO_FAR:
        motors.slowRight(300);
        motors.slowForward(300);
        break;
    }
  }
}
