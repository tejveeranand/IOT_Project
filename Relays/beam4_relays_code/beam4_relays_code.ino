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

const int Relay13 = D1; //pin number 5
const int Relay14 = D2; //pin number 4
const int Relay15 = D5; //pin number 14
const int Relay16 = D6; //pin number 12

void setup() {
  
  pinMode(Relay13, OUTPUT);
  pinMode(Relay14, OUTPUT);
  pinMode(Relay15, OUTPUT);
  pinMode(Relay16, OUTPUT);
  
  digitalWrite(Relay13, HIGH); // by default led will be low
  digitalWrite(Relay14, HIGH); // by default led will be low
  digitalWrite(Relay15, HIGH); // by default led will be low
  digitalWrite(Relay16, HIGH); // by default led will be low
  
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
      mqttClient.subscribe("Beam4Relays");
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
  if(strcmp(((char *)payload), "beam4offlight") == 0)  
  {
    digitalWrite(Relay13,HIGH);  // off the light
    digitalWrite(Relay14,HIGH);  // off the light
  }
  else if(strcmp(((char *)payload),"beam4onlight") == 0)
  {
    digitalWrite(Relay13,LOW); //on the light
    digitalWrite(Relay14,LOW); //on the light
  }
  else if(strcmp(((char *)payload),"beam4offfan") == 0)
  {
    digitalWrite(Relay15,HIGH);  // off the fan
    digitalWrite(Relay16,HIGH);  // off the fan
  }
   else if(strcmp(((char *)payload),"beam4onfan") == 0)
  {
    digitalWrite(Relay15,LOW);  // on the fan
    digitalWrite(Relay16,LOW);  // on the fan
  }
}
