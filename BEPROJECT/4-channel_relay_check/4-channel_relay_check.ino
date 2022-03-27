const int relayD1 = 5;
const int relayD2 = 4;
const int relayD6 = 13;
const int relayD7 = 14;


void setup() {
  Serial.begin(115200);
  pinMode(relayD1, OUTPUT);
  pinMode(relayD2, OUTPUT);
  pinMode(relayD6, OUTPUT);
  pinMode(relayD7, OUTPUT);
}

void loop() {
  // Normally Open configuration, send LOW signal to let current flow
  // (if you're usong Normally Closed configuration send HIGH signal)
  Serial.println("Current not Flowing");
  digitalWrite(relayD1, LOW);
   delay(1000);
  digitalWrite(relayD2, LOW);
   delay(1000);
  digitalWrite(relayD6, LOW);
   delay(1000);
  digitalWrite(relayD7, LOW);
   delay(1000);
  
 
  // Normally Open configuration, send HIGH signal stop current flow
  // (if you're usong Normally Closed configuration send LOW signal)
  Serial.println("Current not Flowing");
  digitalWrite(relayD1, HIGH);
   delay(1000);
  digitalWrite(relayD2, HIGH);
   delay(1000);
  digitalWrite(relayD6, HIGH);
   delay(1000);
  digitalWrite(relayD7, HIGH);
   delay(1000);
}
