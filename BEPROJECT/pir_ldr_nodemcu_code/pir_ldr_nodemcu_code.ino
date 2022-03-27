int pirledpin = 4;  // Digital pin D2
int pir = 13;  // Digital pin D7
const int ldrledpin = 5; //digital pin D1
const int ldr = A0; //Analog pin A0

void setup() {
  pinMode(pir, INPUT);   // declare pir sensor as input
  pinMode(pirledpin, OUTPUT);  // declare pir sensor LED as output
  pinMode(ldr, INPUT);  // declare pir sensor as input
  pinMode(ldrledpin, OUTPUT); // declare ldr sensor LED as output
  Serial.begin(9600);
}


void loop() {
  
  int ldrStatus = analogRead(ldr);
  
  if (ldrStatus <=250) //DARK----------------------- 
  {
    Serial.print("Its Dark outside with light intensity:- ");
    Serial.println(ldrStatus);
    long state = digitalRead(pir);
    if(state == HIGH) //MOTION DETECTED--------------
    {
    Serial.println("Motion detected ");
    digitalWrite(ldrledpin, HIGH);
    digitalWrite(pirledpin, HIGH);
    Serial.println("LDR and PIR LED is ON"); // red and green led
    delay(5000);
    digitalWrite(ldrledpin, LOW);
    digitalWrite(pirledpin, LOW);
    delay(5000);
    }
  }
  else{   //BRIGHT---------------------------------
          Serial.print("Its Bright outside with light intensity:- ");
          Serial.println(ldrStatus);
          long state1 = digitalRead(pir);
          if(state1 == HIGH) //MOTION DETECTED-----------------
          {
          Serial.println("Motion detected ");
          digitalWrite (pirledpin, HIGH); 
          Serial.println("PIR LED is ON"); //red led
          delay(5000);
          digitalWrite(pirledpin, LOW);
          }
          else
          {
            Serial.println("Motion not detected and ldr is greater than 250");
            delay(5000);
          }
  }
}
