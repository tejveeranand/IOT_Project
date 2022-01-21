/*
* Interface LDR with NodeMCU
* measure the voltage reading(analog reading to range of voltage values) of LDR sensor on nodemcu
*/
void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
}

void loop() {
// read the input on analog pin 0:
int sensorValue = analogRead(A0);

// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
float voltage = sensorValue * (5.0 / 1023.0);

// print out the value you read:
Serial.println(voltage);
}
