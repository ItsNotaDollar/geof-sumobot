//typedef enum {SCAN, STALLING, HANDLE_MOVE, FRONT_RAM, BACK_RAM} States;
//typedef enum {SLOW_FORWARD, SLOW_BACKWARD, FAST_FORWARD, FAST_BACKWARD, 
//  SLOW_LEFT, SLOW_RIGHT, FAST_LEFT, FAST_RIGHT, FULL_STOP} Movements;
//
//States myState;
//Movements nextMove;
//
//void setUp() {
//  myState = SCAN;
//}
//
//void loop() {
//  switch(myState) {
//    case SCAN:
//      myState = HANDLE_MOVE;
//      nextMove = scan();
//      break;
//    case STALLING:
//      break;
//    case HANDLE_MOVE:
//      nextMove = SCAN;
//      break;
//    case FRONT_RAM:
//      // continue until no more pressure, or white line
//      break;
//    case BACK_RAM:
//      // continue until no more pressure, or white line
//      break;
//  }
//}
//
//Movements scan() {
//  //will actually return a Movements enum
//  return SLOW_FORWARD;
//}
//
//void moveRobot(Movements nextMove) {
//  // do that movement
//}
//
//void currentInterrupt() {
//  //current is interrupted
//  moveRobot(FULL_STOP);
//  myState = SCAN;
//}
//
//void qrdInterrupt() {
//  moveRobot(checkQrds());
//  myState = SCAN;
//}
//
//void checkQrds() {
//  // gets the value of the qrds, and says which way to move
//  return FAST_BACKWARD;
//}
