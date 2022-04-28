#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//#include "DHTesp.h"

#define Relay1 R1;
#define Relay2 R2;
#define Relay3 R3; 
#define Relay4 R4;

// Update these with values suitable for your network.
const char* ssid        = "Realme 8pro";
const char* password    = "iamsiddy";
const char* mqtt_server = "3.214.158.175";
int         mqtt_port   = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// declare other variables, PINs, etc

//DHTesp dht;
//String pubString;
//char pubChars[100];

const int R1 = D1; //pin number 5
const int R2 = D2; //pin number 4
const int R3 = D5; //pin number 14
const int R4 = D6; //pin number 12

void setupWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500); 
    Serial.print(".");
  }
}

void setupMqtt() {
  mqttClient.setServer(mqtt_server, mqtt_port);
  // invoke "callback()" function when there is an incoming message
  mqttClient.setCallback(callback);   
}

void reconnect() {
   while (!mqttClient.connected())
   {
      String clientId = String(ESP.getChipId());
      if (mqttClient.connect(clientId.c_str())) {Serial.println("connected");}
      // subscribe to an MQTT topic     
      mqttClient.subscribe("Relays");
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  
  digitalWrite(R1, HIGH); // by default led will be low
  digitalWrite(R2, HIGH); // by default led will be low
  digitalWrite(R3, HIGH); // by default led will be low
  digitalWrite(R4, HIGH); // by default led will be low
  // dht
  //dht.setup(13, DHTesp::DHT11); // GPIO12(D7)
  //device id 
  //deviceid=ESP.getChipId();
  
  setupWifi();       // setup WiFi connection
  setupMqtt();       // setup mqtt connection
}

void loop() {
  if (!mqttClient.connected())
  {
    reconnect();
  }
  mqttClient.loop();
  delay(10);
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  payload[length] = '\0'; // terminate the incoming list of charas as a String

  // act on the incoming command
  if(strcmp(((char *)payload), "beam2offlight") == 0)  
  {
    digitalWrite(R1,HIGH);  // off the light
    digitalWrite(R2,HIGH);  // off the light
  }
  else if(strcmp(((char *)payload),"beam2onlight") == 0)
  {
    digitalWrite(R1,LOW); //on the light
    digitalWrite(R2,LOW); //on the light
  }
  else if(strcmp(((char *)payload),"beam2offfan") == 0)
  {
    digitalWrite(R3,HIGH);  // off the fan
    digitalWrite(R4,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"beam2onfan") == 0)
  {
    digitalWrite(R3,LOW);  // on the fan
    digitalWrite(R4,LOW);  // on the fan
  }
}

//void sendData(){
//                  pubString = "{\"deviceid\":" + String(deviceid);                          
//                          //dht11 data to mqtt
//                  float humidity = dht.getHumidity();
//                  float temperature = dht.getTemperature();
//                  Serial.print("Humidity(%) =  ");
//                  Serial.print(humidity, 1);
//                  Serial.print("; ");
//                  Serial.print("Temperature(C) = ");
//                  Serial.print(temperature, 1);
//                  Serial.println();
//                  String value_dhth = String(humidity);
//                  pubString += ",\"humidity\":" + value_dhth;
//                  String value_dhtt = String(temperature);
//                  pubString += ",\"temp(C)\":" + value_dhtt + "}";
//                            
//                            // publishing data
//                  
//                  pubString.toCharArray(pubChars, pubString.length() + 1);
//                  client.publish("Sensors", pubChars);
//  }
