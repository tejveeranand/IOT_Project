int pir = 13;  // Digital pin D7
const long interval = 5000; //5 sec
int flag=0;
void setup() {
  
  Serial.begin(9600);
  pinMode(pir, INPUT);   // declare sensor as input
}
void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    if(state == HIGH and flag==0){
      Serial.println("1"); //send data to mqtt
      flag=1;
      //codes of ldr and dht11 will come here
      }
    if(state == LOW and flag==1){
      Serial.println("0"); //send data to mqtt
      flag=0;
      //codes of ldr and dht11 will come here
      }
    previousMillis = currentMillis;  
    }
} 
