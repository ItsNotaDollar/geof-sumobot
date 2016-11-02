#include <Thread.h>
#include <ThreadController.h>
#include <TimerOne.h>

const unsigned int qrdPin = A0;

//My simple Thread
Thread myThread = Thread();
ThreadController controller = ThreadController();

void timerCallback(){
  Serial.println("timerCallback()");
  controller.run();
}

// callback for myThread
void niceCallback(){
  Serial.print("QRD Value");
  Serial.println(analogRead(qrdPin));
}

void setup(){
  Serial.begin(9600);
  
  pinMode(qrdPin, INPUT);
  myThread.onRun(niceCallback);
  myThread.setInterval(500);
  
  controller.add(&myThread);
  
  Timer1.initialize(100000);
  Timer1.attachInterrupt(timerCallback);
}

void loop(){}
