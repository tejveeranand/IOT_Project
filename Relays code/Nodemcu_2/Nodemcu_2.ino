/* Sketch to receive message from MQTT Broker on Cloud */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define Relay4 R4;
#define Relay5 R5;
#define Relay6 R6;
#define Relay7 R7;
#define Relay8 R8;
#define Relay9 R9;
// Update these with values suitable for your network.
const char* ssid        = "Realme 8pro";
const char* password    = "iamsiddy";
const char* mqtt_server = "3.214.158.175";
int         mqtt_port   = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// declare other variables, PINs, etc

const int R4 = D2; //pin number 4
const int R5 = D3; //pin number 0
const int R6 = D4; //pin number 2
const int R7 = D5; //pin number 14
const int R8 = D6; //pin number 12
const int R9 = D7; //pin number 13

void setup() {
  
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);

  digitalWrite(R4, HIGH); // by default led will be low
  digitalWrite(R5, HIGH); // by default led will be low
  digitalWrite(R6, HIGH); // by default led will be low
  digitalWrite(R7, HIGH); // by default led will be low
  digitalWrite(R8, HIGH); // by default led will be low
  digitalWrite(R9, HIGH); // by default led will be low
  Serial.begin(115200);
  setupWifi();       // setup WiFi connection
  setupMqtt();       // setup mqtt connection
}

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
  if(strcmp(((char *)payload), "l1off") == 0)  
  {
    digitalWrite(R4,HIGH);  // off the light
    digitalWrite(R5,HIGH);  // off the light
  }
  else if(strcmp(((char *)payload),"l1on") == 0)
  {
    digitalWrite(R4,LOW); //on the light
    digitalWrite(R5,LOW); //on the light
  }
  else if(strcmp(((char *)payload),"f1off") == 0)
  {
    digitalWrite(R6,HIGH);  // off the fan
    digitalWrite(R7,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"f1on") == 0)
  {
    digitalWrite(R6,LOW);  // on the fan
    digitalWrite(R7,LOW);  // on the fan
  }
  else if(strcmp(((char *)payload),"l2off") == 0)
  {
    digitalWrite(R8,HIGH);  // off the fan
    digitalWrite(R9,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"l2on") == 0)
  {
    digitalWrite(R8,LOW);  // on the fan
    digitalWrite(R9,LOW);  // on the fan
  }
}
