const unsigned int Left_Forward_Pin     = 3;
const unsigned int Left_Backward_Pin    = 5;
const unsigned int Right_Backward_Pin   = 6;
const unsigned int Right_Forward_Pin    = 9;

void setup() {
  pinMode(Left_Forward_Pin, OUTPUT);
  pinMode(Left_Backward_Pin, OUTPUT);
  pinMode(Right_Backward_Pin, OUTPUT);
  pinMode(Right_Forward_Pin, OUTPUT);

}

void loop() {
  delay(1000);
  analogWrite(Left_Backward_Pin, 0);
  delay(5);
  analogWrite(Left_Forward_Pin, 255);

  delay(1000);
  analogWrite(Left_Forward_Pin, 0);
  delay(5);`
  analogWrite(Left_Backward_Pin, 255);

}