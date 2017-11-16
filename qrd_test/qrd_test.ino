const unsigned int qrdPin = A1;

void getQrdValue(){
  Serial.print("QRD Value: ");
  Serial.println(analogRead(qrdPin));
}

void setup(){
  pinMode(qrdPin, INPUT);

  Serial.begin(9600);
}

void loop(){
  getQrdValue();
  delay(500);
}
