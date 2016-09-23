/**************************************************************************************************/
/*                                     Setting Up Input Pins                                      */
/**************************************************************************************************/

/* Assigning digital pins for QRD bits */
const unsigned int F_L_QRD = 0;
const unsigned int F_R_QRD = 1;
const unsigned int B_L_QRD = 2;
const unsigned int B_R_QRD = 3;

/* Assigning digital pins for pressure sensor bits */
const unsigned int F_PRES = 4;
const unsigned int B_PRES = 5;

/* Assigning anaolog pins for sonar sensors bits */
const unsigned int LEFT_SONAR = A0;
const unsigned int RIGHT_SONAR = A1;

/* Assigning interrupt pins */
const unsigned int QRD_INTER = TX;
const unsigned int PRS_ITNER = RX;

/**************************************************************************************************/
/*                                     Setting Up Output Pins                                     */
/**************************************************************************************************/

/* Assigning motor pins */
const unsigned int LEFT_POS = 10; //PWM?
const unsigned int LEFT_NEG = 11;
const unsigned int RIGHT_POS = 5;
const unsigned int RIGHT_NEG = 6; //PWM?



void setup() {
  /* Input Pins */
  pinMode(F_L_QRD,INPUT);
  pinMode(F_R_QRD,INPUT);
  pinMode(B_L_QRD,INPUT);
  pinMode(B_R_QRD,INPUT);

  pinMode(F_PRES,INPUT);
  pinMode(B_PRES,INPUT);

  pinMode(LEFT_SONAR,INPUT);
  pinMode(RIGHT_SONAR,INPUT);

  pinMode(QRD_INTER,INPUT);
  pinMode(PRS_ITNER,INPUT);

  /* Output Pins */
  pinMode(motorR2,OUTPUT);
  pinMode(motorR2,OUTPUT);
  pinMode(motorR2,OUTPUT);
  pinMode(motorR2,OUTPUT);
}

void loop() {

}
