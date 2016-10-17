#include "Thread.h"
#include "ThreadController.h"
#include "TimerOne.h"
#include "QrdThread.h"

/****************************************************************************************************/
/*                                         Setting Up Pins                                          */
/****************************************************************************************************/
const unsigned int F_L_QRD_PIN  = A0;
const unsigned int F_R_QRD_PIN  = A1;
const unsigned int B_L_QRD_PIN  = A2;
const unsigned int B_R_QRD_PIN  = A3;

QrdThread qrdThread;
TimerOne  qrdTimer;

ThreadController controller = ThreadController();

void setup() {
  Serial.begin(9600);

  // Setting up the QRD thread
  qrdThread.pinSetup(F_L_QRD_PIN, F_R_QRD_PIN, B_L_QRD_PIN, B_R_QRD_PIN);
  qrdThread.setInterval(100); // runs check every 100ms

  controller.add(&qrdThread);

  qrdTimer.initialize(1000000); // 1sec
  qrdTimer.attachInterrupt(qrdCheck); // Starting the qrd thread to convert vals every 100ms
  qrdTimer.start();

  Serial.println("+------------------------------------------------+-------+");
  Serial.println("|                 QRD Value Test                 | Value |");
  Serial.println("+------------------------------------------------+-------+");
  Serial.println("");
  Serial.println("");
  Serial.println("+------------------------------------------------+-------+");
}

void loop() {
  // Nothing here becuase threads are awesome!
}

void qrdCheck(){
  // Runs the thread at the specified interval
  controller.run();
  switch(qrdThread.qrdState) {
    case 0:
      Serial.println("| *  No QRDs have been tripped!                  |   0   |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 1:
      Serial.println("| *  Front Left QRD has been tripped.            |   1   |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 2:
      Serial.println("| *  Front Right QRD has been tripped.           |   2   |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 4:
      Serial.println("| *  Back Left QRD has been tripped.             |   4   |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 8:
      Serial.println("| *  Back Right QRD has been tripped.            |   8   |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 3:
      Serial.println("| *  Both Front QRDs has been tripped.           |   3   |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 12:
      Serial.println("| *  Both Back QRDs has been tripped.            |   12  |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 5:
      Serial.println("| *  Both Left QRDs has been tripped.            |   5   |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    case 10:
      Serial.println("| *  Both Right QRDs has been tripped.           |   10  |");
      Serial.println("+------------------------------------------------+-------+");
      break;

    default:
      Serial.print("| *  Default case hit... Should never see this   |   ");
      Serial.print(qrdThread.qrdState);
      Serial.print("   |");
      Serial.println("+------------------------------------------------+-------+");
      break;
  }
}
