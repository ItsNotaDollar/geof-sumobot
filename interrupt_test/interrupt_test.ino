/****************************************************************************************************/
/*                                         Setting Up Pins                                          */
/****************************************************************************************************/
#define NOT_AN_INTERRUPT -1
const unsigned int F_PRES_PIN = 0;

boolean led = false;

void setup() {
  pinMode(F_PRES_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // Setting up Pressure sensors on the interrupts
  attachInterrupt(digitalPinToInterrupt(F_PRES_PIN), frontInterrupt, CHANGE);
}

void loop() {  }

void frontInterrupt() {
  led = !led;
  if(led){
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

