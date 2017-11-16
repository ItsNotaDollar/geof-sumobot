#include <Arduino.h>
#include <Ultrasonic.h>

const unsigned int B_R_QRD_PIN = A0;
const unsigned int F_R_QRD_PIN = A1;
const unsigned int F_L_QRD_PIN = A3;
const unsigned int B_L_QRD_PIN = A2;

const unsigned int Left_Forward_Pin = 9;
const unsigned int Left_Backward_Pin = 6;
const unsigned int Right_Backward_Pin = 3;
const unsigned int Right_Forward_Pin = 5;

const unsigned int RIGHT_SONAR_TX = 10;
const unsigned int RIGHT_SONAR_RX = 11;
const unsigned int LEFT_SONAR_TX = 12;
const unsigned int LEFT_SONAR_RX = 13;

// todo: Check these constant on the new rings
const unsigned int F_L_THRES = 650;
const unsigned int F_R_THRES = 650;
const unsigned int B_L_THRES = 150;
const unsigned int B_R_THRES = 475;

const unsigned int NEAR_DISTANCE = 30;
const unsigned int FAR_DISTANCE = 70;
const unsigned int THRESHOLD_DISTANCE = 130;

// todo: These need to be tested and calibrated
const unsigned int TURN_180 = 500;
const unsigned int TURN_90 = 250;


Ultrasonic leftSonar(LEFT_SONAR_TX, LEFT_SONAR_RX);
Ultrasonic rightSonar(RIGHT_SONAR_TX, RIGHT_SONAR_RX);


void fullStop() {
  digitalWrite(Left_Forward_Pin, LOW);
  digitalWrite(Left_Backward_Pin, LOW);
  digitalWrite(Right_Forward_Pin, LOW);
  digitalWrite(Right_Backward_Pin, LOW);
}

int setForward() {
  fullStop();
  delay(50);

  digitalWrite(Left_Backward_Pin , LOW);
  digitalWrite(Right_Backward_Pin, LOW);
  digitalWrite(Left_Forward_Pin  , HIGH);
  digitalWrite(Right_Forward_Pin , HIGH);

  unsigned int qrdState = 0;

  while(qrdState == 0) {
    qrdState = getQrdState();
  }

  return qrdState;
}

int forward(unsigned long time) {
  fullStop();
  delay(50);

  digitalWrite(Left_Backward_Pin , LOW);
  digitalWrite(Right_Backward_Pin, LOW);
  digitalWrite(Left_Forward_Pin  , HIGH);
  digitalWrite(Right_Forward_Pin , HIGH);

  return scanningTimer(time);
}

int backward(unsigned long time) {
  fullStop();
  delay(50);

  digitalWrite(Left_Forward_Pin  , LOW);
  digitalWrite(Right_Forward_Pin , LOW);
  digitalWrite(Left_Backward_Pin , HIGH);
  digitalWrite(Right_Backward_Pin, HIGH);

  return scanningTimer(time);
}

int left(unsigned long time) {
  fullStop();
  delay(50);

  digitalWrite(Left_Forward_Pin  , LOW);
  digitalWrite(Right_Backward_Pin, LOW);
  digitalWrite(Left_Backward_Pin , HIGH);
  digitalWrite(Right_Forward_Pin , HIGH);

  return scanningTimer(time);
}

int right(unsigned long time) {
  fullStop();
  delay(50);

  digitalWrite(Left_Backward_Pin , LOW);
  digitalWrite(Right_Forward_Pin , LOW);
  digitalWrite(Left_Forward_Pin  , HIGH);
  digitalWrite(Right_Backward_Pin, HIGH);

  return scanningTimer(time);
}

unsigned int getQrdState() {
  unsigned int f_l_val = analogRead(F_L_QRD_PIN) < F_L_THRES ? 1 : 0;
  unsigned int f_r_val = analogRead(F_R_QRD_PIN) < F_R_THRES ? 2 : 0;
  unsigned int b_l_val = analogRead(B_L_QRD_PIN) < B_L_THRES ? 4 : 0;
  unsigned int b_r_val = analogRead(B_R_QRD_PIN) < B_R_THRES ? 8 : 0;

  return f_l_val + f_r_val + b_l_val + b_r_val;
}

int scanningTimer(unsigned long duration) { // todo: Rename
  unsigned long endTime = millis() + duration;
  unsigned int qrdState = 0;

  while (millis() < endTime) {
    qrdState = getQrdState();

    if (qrdState != 0) {
      return qrdState;
    }
  }

  return 0;
}

int shouldMoveForward(int leftVal, int rightVal) { // todo: can this be reduced?
  int difference = leftVal - rightVal;
  int absDifference = abs(difference);

  if (absDifference <= 10) {
    if (leftVal >= THRESHOLD_DISTANCE && rightVal >= THRESHOLD_DISTANCE) {
      return -1;
    }

    return 1;
  }

  return 0;
}


void setup() {
  pinMode(F_L_QRD_PIN, INPUT);
  pinMode(F_R_QRD_PIN, INPUT);
  pinMode(B_L_QRD_PIN, INPUT);
  pinMode(B_R_QRD_PIN, INPUT);

  pinMode(Left_Forward_Pin, OUTPUT);
  pinMode(Left_Backward_Pin, OUTPUT);
  pinMode(Right_Backward_Pin, OUTPUT);
  pinMode(Right_Forward_Pin, OUTPUT);

  pinMode(LEFT_SONAR_TX, OUTPUT);
  pinMode(LEFT_SONAR_RX, INPUT);
  pinMode(RIGHT_SONAR_TX, OUTPUT);
  pinMode(RIGHT_SONAR_RX, INPUT);

  delay(5000); // todo: Could do something usefull here?
}

void loop() {
  int leftVal = leftSonar.Ranging(CM);
  int rightVal = rightSonar.Ranging(CM);

  int movementStatus = 0;
  int isMovingForward = shouldMoveForward(leftVal, rightVal); // todo: rename

  if (isMovingForward == 1) {
    movementStatus = setForward();
  } else if (isMovingForward == -1) {
    movementStatus = left(1000);
  } else {
    if (rightVal > leftVal) {
      movementStatus = right(500);
    } else {
      movementStatus = left(500);
    }
  }

  fullStop();

  // check return status
  while(movementStatus != 0) {
    switch(movementStatus) {
      case 1: {
          movementStatus = backward(500);
          if (movementStatus == 0) {
            movementStatus = right(500);
          }
        }
        break;
      case 2: {
          movementStatus = backward(500);
          if (movementStatus == 0) {
            movementStatus = left(500);
          }
        }
        break;
      case 3: {
          movementStatus = backward(500);
          if (movementStatus == 0) {
            movementStatus = left(1000);
          }
        }
        break;
      case 4: {
          movementStatus = forward(500);
          if (movementStatus == 0) {
            movementStatus = right(500);
          }
        }
        break;
      case 5: {
          movementStatus = right(500);
          if (movementStatus == 0) {
            movementStatus = forward(500);
          }
        }
        break;
      case 8: {
          movementStatus = forward(500);
          if (movementStatus == 0) {
            movementStatus = left(500);
          }
        }
        break;
      case 10: {
          movementStatus = left(500);
          if (movementStatus == 0) {
            movementStatus = forward(500);
          }
        }
        break;
      case 12: {
          movementStatus = forward(500);
        }
        break;
      default:
        break;
    }

    movementStatus = getQrdState();
  }

  fullStop();
}
