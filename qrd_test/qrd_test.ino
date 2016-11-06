#include <Thread.h>
#include <ThreadController.h>
#include <TimerOne.h>

const unsigned int qrdPin = A0;

const unsigned int QRD_CHECK_INTERVAL = 500; // tells the controller the thread should be run every 500ms
const unsigned int TIMER_INTERVAL = 100000; // sets an interrupt for every 100 000us for the controller to check
                                            // which threads need to be run or not.

//My simple Thread
Thread myThread = Thread();
ThreadController controller = ThreadController();

void timerCallback(){
  controller.run();
}

void getQrdValue(){
  Serial.print("QRD Value");
  Serial.println(analogRead(qrdPin));
}

void setup(){
  Serial.begin(9600);
  
  pinMode(qrdPin, INPUT);
  myThread.onRun(getQrdValue);
  myThread.setInterval(QRD_CHECK_INTERVAL);
  
  controller.add(&myThread);
  
  Timer1.initialize(TIMER_INTERVAL);
  Timer1.attachInterrupt(timerCallback);
}

void loop(){}
