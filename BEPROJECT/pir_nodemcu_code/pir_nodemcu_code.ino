 int pir = 13;  // Digital pin D7
void setup() {
  Serial.begin(9600);
  pinMode(pir, INPUT);   // declare sensor as input
}
void loop() {

  long state = digitalRead(pir);
    if(state == HIGH) {
      Serial.println("Motion detected!");
      delay(1000);
    }
    else {
      Serial.println("Motion absent!");
      delay(1000);
      }
}
