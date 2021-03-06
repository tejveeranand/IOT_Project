/* Sketch to receive message from MQTT Broker on Cloud */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define Relay10 R10;
#define Relay11 R11;
#define Relay12 R12;
#define Relay13 R13;
#define Relay14 R14;
#define Relay15 R15;
#define Relay16 R16;

// Update these with values suitable for your network.
const char* ssid        = "Realme 8pro";
const char* password    = "iamsiddy";
const char* mqtt_server = "3.214.158.175";
int         mqtt_port   = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// declare other variables, PINs, etc

const int R10 = D1; //pin number 5
const int R11 = D2; //pin number 4
const int R12 = D3; //pin number 0
const int R13 = D4; //pin number 2
const int R14 = D5; //pin number 14
const int R15 = D6; //pin number 12
const int R16 = D7; //pin number 13

void setup() {
  
  pinMode(R10, OUTPUT);
  pinMode(R11, OUTPUT);
  pinMode(R12, OUTPUT);
  pinMode(R13, OUTPUT);
  pinMode(R14, OUTPUT);
  pinMode(R15, OUTPUT);
  pinMode(R16, OUTPUT);
  digitalWrite(R10, HIGH); // by default led will be low
  digitalWrite(R11, HIGH); // by default led will be low
  digitalWrite(R12, HIGH); // by default led will be low
  digitalWrite(R13, HIGH); // by default led will be low
  digitalWrite(R14, HIGH); // by default led will be low
  digitalWrite(R15, HIGH); // by default led will be low
  digitalWrite(R16, HIGH); // by default led will be low
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
  if(strcmp(((char *)payload), "l3off") == 0)  
  {
    digitalWrite(R10,HIGH);  // off the light
    digitalWrite(R11,HIGH);  // off the light
  }
  else if(strcmp(((char *)payload),"l3on") == 0)
  {
    digitalWrite(R10,LOW); //on the light
    digitalWrite(R11,LOW); //on the light
  }
  else if(strcmp(((char *)payload),"f3off") == 0)
  {
    digitalWrite(R12,HIGH);  // off the fan
    digitalWrite(R13,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"f3on") == 0)
  {
    digitalWrite(R12,LOW);  // on the fan
    digitalWrite(R13,LOW);  // on the fan
  }
  else if(strcmp(((char *)payload),"l4off") == 0)
  {
    digitalWrite(R14,HIGH);  // off the fan
    digitalWrite(R15,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"l4on") == 0)
  {
    digitalWrite(R14,LOW);  // on the fan
    digitalWrite(R15,LOW);  // on the fan
  }
    else if(strcmp(((char *)payload),"beam2offfan") == 0)
  {
    digitalWrite(R16,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"beam2onfan") == 0)
  {
    digitalWrite(R16,LOW);  // on the fan
  }
}
