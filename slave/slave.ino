/**************************************************************************************************/
/*                                     Setting Up Input Pins                                      */
/**************************************************************************************************/

/* Assigning analog pins for QRD and pressure sensors */
const unsigned int F_L_QRD_PIN = A0;
const unsigned int F_R_QRD_PIN = A1;
const unsigned int B_L_QRD_PIN = A2;
const unsigned int B_R_QRD_PIN = A3;

//These might be able to be configured as interrupts? _|-|_
const unsigned int F_PRES = A4; 
const unsigned int B_PRES = A5;

/**************************************************************************************************/
/*                                     Setting Up Output Pins                                     */
/**************************************************************************************************/

/* Assigning digital pins for QRD bits */
const unsigned int F_L_QRD_PIN_OUT = 0;
const unsigned int F_R_QRD_PIN_OUT = 1;
const unsigned int B_L_QRD_PIN_OUT = 2;
const unsigned int B_R_QRD_PIN_OUT = 3;

/* Assigning digital pins for pressure sensor bits */
const unsigned int F_PRES_PIN = 4;
const unsigned int B_PRES_PIN = 5;

const unsigned int QRD_THRESHOLD = 100; //todo: This is the value from last year, will need another
                                        //      calibration for actual code

bool qrdVal_FL, qrdVal_FR, qrdVal_BL, qrdVal_BR;
bool backPress, frontPress;

/**************************************************************************************************/
/*                                   The Method to the Maddness                                   */
/**************************************************************************************************/
void setup() {
  /*******************************/
  pinMode(F_L_QRD_PIN, INPUT);
  pinMode(F_R_QRD_PIN, INPUT);
  pinMode(B_L_QRD_PIN, INPUT);
  pinMode(B_R_QRD_PIN, INPUT);
  /*******************************/
  pinMode(F_PRES, INPUT);
  pinMode(B_PRES, INPUT);
  /*******************************/
  pinMode(F_L_QRD_PIN_OUT, OUTPUT);
  pinMode(F_R_QRD_PIN_OUT, OUTPUT);
  pinMode(B_L_QRD_PIN_OUT, OUTPUT);
  pinMode(B_R_QRD_PIN_OUT, OUTPUT);
  /*******************************/
  pinMode(F_PRES_PIN, OUTPUT);
  pinMode(B_PRES_PIN, OUTPUT);
  /*******************************/
}

void loop() {
  qrdCheck();
  pressureCheck();
}

void qrdCheck() {
  digitalWrite(F_L_QRD_PIN_OUT, (analogRead(F_L_QRD_PIN) < QRD_THRESHOLD));
  digitalWrite(F_R_QRD_PIN_OUT, (analogRead(F_R_QRD_PIN) < QRD_THRESHOLD));
  digitalWrite(B_L_QRD_PIN_OUT, (analogRead(B_L_QRD_PIN) < QRD_THRESHOLD));
  digitalWrite(B_R_QRD_PIN_OUT, (analogRead(B_R_QRD_PIN) < QRD_THRESHOLD));
}

