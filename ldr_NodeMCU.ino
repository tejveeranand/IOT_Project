const int ledPin = 5; //D1
const int ldrPin = A0;

void setup() {

Serial.begin(9600);

pinMode(ledPin, OUTPUT);

pinMode(ldrPin, INPUT);

}

void loop() {

int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <=400) {

  digitalWrite(ledPin, HIGH);
  Serial.print(ldrStatus);
  Serial.println("LDR is DARK, LED is ON");

  }

  else {

  digitalWrite(ledPin, LOW);
  Serial.print(ldrStatus);
  Serial.println("LED is OFF");

  }

}
