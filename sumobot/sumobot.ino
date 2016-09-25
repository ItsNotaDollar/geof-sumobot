/*
  Information:
  This was written for the 2016 McMaster Sumobot Senior competition. All of the code was written by
  McMaster students. For more information about the club check out sumobot.ca for more information.

  Author: Braden Corbold
  Program: Mechatronics Engineering - McMaster University
  Date: September 25th 2016

  Dependencies:
  This project three dependencies which can be found at the links provided below. Follow normal 
  Arduino library workflow to import and used in other projects.

  Ultrasonic -> http://tutorial.cytron.com.my/2012/10/11/testing-ultrasonic-ranging-module-sn-hc-sr04/
  Thread     -> https://github.com/ivanseidel/ArduinoThread
  TimerOne   -> http://playground.arduino.cc/Code/Timer1
*/


#include "Ultrasonic.h"
#include "Thread.h"
#include "ThreadController.h"
#include "TimerOne.h"

/****************************************************************************************************/
/*                                         Setting Up Pins                                          */
/****************************************************************************************************/
const unsigned int F_L_QRD_PIN = A0;
const unsigned int F_R_QRD_PIN = A1;
const unsigned int B_L_QRD_PIN = A2;
const unsigned int B_R_QRD_PIN = A3;

const unsigned int X_AXIS_PIN = A4; // +ve => Right
const unsigned int Y_AXIS_PIN = A5; // +ve => Forward

const unsigned int CURRENT_SENSOR_PIN = A6;

const unsigned int F_PRES_PIN = 0;
const unsigned int B_PRES_PIN = 1;

const unsigned int LEFT_FRWD_ON_PIN = 2;
const unsigned int LEFT_FRWD_PWM_PIN = 3;
const unsigned int LEFT_REV_ON_PIN = 4;
const unsigned int LEFT_REV_PWM_PIN = 5;

const unsigned int RIGHT_REV_PWM_PIN = 6;
const unsigned int RIGHT_REV_ON_PIN = 7;
const unsigned int RIGHT_FRWD_ON_PIN = 8;
const unsigned int RIGHT_FRWD_PWM_PIN = 9;

const unsigned int SONAR_RIGHT_TX = 10; //Relative to arduino
const unsigned int SONAR_RIGHT_RX = 11; //Relative to arduino
const unsigned int SONAR_LEFT_TX = 12; //Relative to arduino
const unsigned int SONAR_LEFT_RX = 13; //Relative to arduino

typedef enum {SCAN, FRONT_RAM, BACK_RAM} States;

class QRDThread: public Thread {
    public:
        const unsigned int THRESHOLD = 100;
        int f_LBitValue;
        int f_RBitValue;
        int b_LBitValue;
        int b_RBitValue;

        int f_LPin;
        int f_RPin;
        int b_LPin;
        int b_RPin;

        int qrdState = 0;

        void pinSetup(int f_LPinSetup, int f_RPinSetup, int b_LPinSetup, int b_RPinSetup) {
          f_LPin = f_LPinSetup;
          f_RPin = f_RPinSetup;
          b_LPin = b_LPinSetup;
          b_RPin = b_RPinSetup;
        }

        void run() { //white = 0, black = 255
          f_LBitValue = analogRead(f_LPin) < THRESHOLD ? 1 : 0;
          f_RBitValue = analogRead(f_RPin) < THRESHOLD ? 2 : 0;
          b_LBitValue = analogRead(b_LPin) < THRESHOLD ? 4 : 0;
          b_RBitValue = analogRead(b_RPin) < THRESHOLD ? 8 : 0;
          qrdState = f_LBitValue + f_RBitValue + b_LBitValue + b_RBitValue;
          runned();
        }
};

Ultrasonic rightSonar(10,11);
Ultrasonic  leftSonar(12,13);

QRDThread qrdThread = QRDThread();
ThreadController controller = ThreadController();

void setup() {
  pinMode(F_L_QRD_PIN,INPUT);
  pinMode(F_R_QRD_PIN,INPUT);
  pinMode(B_L_QRD_PIN,INPUT);
  pinMode(B_R_QRD_PIN,INPUT);

  pinMode(X_AXIS_PIN,INPUT);
  pinMode(Y_AXIS_PIN,INPUT);

  pinMode(CURRENT_SENSOR_PIN,INPUT);

  pinMode(F_PRES_PIN,INPUT);
  pinMode(B_PRES_PIN,INPUT);

  pinMode(LEFT_FRWD_ON_PIN,OUTPUT);
  pinMode(LEFT_FRWD_PWM_PIN,OUTPUT);
  pinMode(LEFT_REV_ON_PIN,OUTPUT);
  pinMode(LEFT_REV_PWM_PIN,OUTPUT);

  pinMode(RIGHT_REV_PWM_PIN,OUTPUT);
  pinMode(RIGHT_REV_ON_PIN,OUTPUT);
  pinMode(RIGHT_FRWD_ON_PIN,OUTPUT);
  pinMode(RIGHT_FRWD_PWM_PIN,OUTPUT);

  pinMode(SONAR_RIGHT_TX,OUTPUT);
  pinMode(SONAR_RIGHT_RX,INPUT);
  pinMode(SONAR_LEFT_TX,OUTPUT);
  pinMode(SONAR_LEFT_RX,INPUT);

  qrdThread.pinSetup(F_L_QRD_PIN, F_R_QRD_PIN, B_L_QRD_PIN, B_R_QRD_PIN);
  qrdThread.setInterval(100);
  controller.add(&qrdThread);

  Timer1.initialize(10000); // 10 ms
  Timer1.attachInterrupt(qrdCheck); // Starting the qrd thread to convert vals
  Timer1.start();

  unsigned long previousTime = millis();
  unsigned long currentTime = millis();
  while((previousTime - currentTime) >= 5000){
    currentTime = millis();
  }
}

void loop() {
  handleQrdValues();
}

void qrdCheck(){
  controller.run();
}

void handleQrdValues(){
    switch (qrdThread.qrdState) {
      case 0:
        // no qrds tripped
        break;
      case 1:
        // just front left
        break;
      case 2:
        // just front right
        break;
      case 4:
        // just back left
        break;
      case 8:
        // just back right
        break;
      case 3:
        // both front
        break;
      case 12:
        // both back
        break;
      case 5:
        // both left
        break;
      case 10:
        // both right
        break;
    }
}