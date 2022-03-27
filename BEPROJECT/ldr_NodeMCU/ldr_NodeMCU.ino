const int ldrPin = A0;
const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 1023;    // sensor maximum, discovered through experiment
void setup() {

Serial.begin(9600);
pinMode(ldrPin, INPUT);

}

void loop() {
 int sensorReading = analogRead(ldrPin);
  // map the sensor range to a range of four options:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 1);
  Serial.print(sensorReading);
  Serial.print("\n");
  // do something different depending on the range value:
  switch (range) {
    case 0:    // your hand is on the sensor
      Serial.println("dark");
      break;
    case 1:    // your hand is close to the sensor
      Serial.println("dim");
      break;
  }
  delay(5000);        // delay in between reads for stability
}
