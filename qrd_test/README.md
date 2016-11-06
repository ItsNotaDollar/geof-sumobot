#**QRD & Thread Test**

###Program Overview
This code is used for testing the QRD sensors in a thread outside of the main loop. This is used for polling a QRD reading outside of the main arduino loop. The library for arduino threads can be found [here](https://github.com/ivanseidel/ArduinoThread) and the Timer1 library [here](http://playground.arduino.cc/Code/Timer1). 

**Note:** Depending on which arduino you are using you may need a different timer library, more information can be found at the link provided above.

###Timer1 Configuration
In order to create a working Timer1 you will need 2 things:
- the time interval that the timer should trigger an interrupt at (in microseconds)
- the method that will be called whenever this interval is reached
```
Timer1.initialize(TIMER_INTERVAL);
Timer1.attachInterrupt(timerCallbackMethod);

void timerCallbackMethod() {
  //do stuff here
}
```

###Thread Configuration
Creating a thread instance will work very similarly to Timer1. You again only need 2 parameters:
- a callback method for when the thread is run
- a time interval to let the controller know when the thread SHOULD be run. This does not actually run it, this is why we need Timer1
```
myThread.onRun(threadCallBack);
myThread.setInterval(QRD_CHECK_INTERVAL);

void threadCallBack() {
  //do stuff here
}
```
In addition to configuring your thread, you will want to add this to a ThreadController (also included in the thread library). This allows you to link the Timer1 interrupt function to your threads and have multiple threads get checked on one timer call!

###Basic Configuration
Below is a very generic outline of how threads should be set up in your program using the arduino thread library and Timer1
```
#include <Thread.h>
#include <ThreadController.h>
#include <TimerOne.h>

const unsigned int THREAD_INTERVAL = 500;
const unsigned int TIMER_INTERVAL = 100000;

Thread myThread = Thread();
ThreadController controller = ThreadController();

void setup(){
  myThread.onRun(threadCallBack);
  myThread.setInterval(THREAD_INTERVAL);
  
  controller.add(&myThread);
  //if you have more threads you can add them here too!
  
  Timer1.initialize(TIMER_INTERVAL);
  Timer1.attachInterrupt(timerCallback);
}

void loop(){
//do stuff here. Threads will interrupt this code when Timer1 gets to it's interval
}

void timerCallback(){
  controller.run(); //checks all the threads on controller to see if they need to be run and if so, they are run
}

void threadCallBack(){
//do stuff here based on threads
}
```