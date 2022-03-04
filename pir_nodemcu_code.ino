int pirledpin = 4;  // Digital pin D2
int pir = 13;  // Digital pin D7
void setup() {

  pinMode(pir, INPUT);   // declare sensor as input
  pinMode(pirledpin, OUTPUT);  // declare LED as output
}
void loop() {

  long state = digitalRead(pir);
    if(state == HIGH) {
      digitalWrite (pirledpin, HIGH);
      Serial.println("Motion detected!");
      delay(1000);
    }
    else {
      digitalWrite (pirledpin, LOW);
      Serial.println("Motion absent!");
      delay(1000);
      }
}
