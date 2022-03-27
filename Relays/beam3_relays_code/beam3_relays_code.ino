/* Sketch to receive message from MQTT Broker on Cloud */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
const char* ssid        = "Realme 8pro";
const char* password    = "iamsiddy";
const char* mqtt_server = "3.214.158.175";
int         mqtt_port   = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// declare other variables, PINs, etc

const int Relay9 = D1; //pin number 5
const int Relay10 = D2; //pin number 4
const int Relay11 = D5; //pin number 14
const int Relay12 = D6; //pin number 12

void setup() {
  
  pinMode(Relay9, OUTPUT);
  pinMode(Relay10, OUTPUT);
  pinMode(Relay11, OUTPUT);
  pinMode(Relay12, OUTPUT);
  
  digitalWrite(Relay9, HIGH); // by default led will be low
  digitalWrite(Relay10, HIGH); // by default led will be low
  digitalWrite(Relay11, HIGH); // by default led will be low
  digitalWrite(Relay12, HIGH); // by default led will be low
  
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
      mqttClient.subscribe("Beam3Relays");
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
  if(strcmp(((char *)payload), "beam3offlight") == 0)  
  {
    digitalWrite(Relay9,HIGH);  // off the light
    digitalWrite(Relay10,HIGH);  // off the light
  }
  else if(strcmp(((char *)payload),"beam3onlight") == 0)
  {
    digitalWrite(Relay9,LOW); //on the light
    digitalWrite(Relay10,LOW); //on the light
  }
  else if(strcmp(((char *)payload),"beam3offfan") == 0)
  {
    digitalWrite(Relay11,HIGH);  // off the fan
    digitalWrite(Relay12,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"beam3onfan") == 0)
  {
    digitalWrite(Relay11,LOW);  // on the fan
    digitalWrite(Relay12,LOW);  // on the fan
  }
}
