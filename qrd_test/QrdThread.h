#ifndef QrdThread_h
#define QrdThread_h

#include "Arduino.h"
#include "Thread.h"
#include "ThreadController.h"

class QrdThread : public Thread {
    public:
        QrdThread():Thread(){
          qrdState=0;
        }
        int qrdPin;
        int qrdState;

        void pinSetup(int qrdPin);
        void run();
    private:
        int qrd_Pin;
};

#endif
