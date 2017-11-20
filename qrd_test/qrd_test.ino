const unsigned int B_R_QRD_PIN = A0;
const unsigned int F_R_QRD_PIN = A1;
const unsigned int F_L_QRD_PIN = A3;
const unsigned int B_L_QRD_PIN = A2;


void setup(){
  pinMode(F_L_QRD_PIN, INPUT);
  pinMode(F_R_QRD_PIN, INPUT);
  pinMode(B_L_QRD_PIN, INPUT);
  pinMode(B_R_QRD_PIN, INPUT);

  Serial.begin(9600);
}

void loop(){
  getQrdState();
  delay(500);
}


void getQrdState() {
  unsigned int f_l_val = analogRead(F_L_QRD_PIN);
  unsigned int f_r_val = analogRead(F_R_QRD_PIN);
  unsigned int b_l_val = analogRead(B_L_QRD_PIN);
  unsigned int b_r_val = analogRead(B_R_QRD_PIN);

  Serial.println(f_l_val);
  Serial.println(f_r_val);
  Serial.println(b_l_val);
  Serial.println(b_r_val);
}