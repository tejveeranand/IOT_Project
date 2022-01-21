#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Realme 8pro";
const char* password = "iamsiddy";
const char* mqtt_server = "3.214.158.175";
int         mqtt_port   = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

int Status = 12;  // Digital pin D6
int sensor = 13;  // Digital pin D7

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {Serial.print((char)payload[i]);}
  Serial.println();

  payload[length] = '\0'; // terminate the incoming list of charas as a String

  // act on the incoming command
  if(strcmp(((char *)payload), "Bye Siddhant") == 0)  {
    Serial.println("MQTT Working Fine Received Bye Siddhant");
  }
  else if(strcmp(((char*)payload),"Hello Tejveer") == 0){
    Serial.println("I said Hello to Siddhant not tejveer");
    }
  
  //else{Serial.println("Unexpected message");}
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("authrequest", "hello world");
      // ... and resubscribe
      client.subscribe("mess_from_nodered");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);                                              // Init MFRC522 card
  Serial.println(F("SYSTEM STARTED..."));                                    //shows in serial that it is ready to read
  delay(100);

  pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output
  
}

void loop() {
   if (!client.connected()) {
    reconnect();
  }
  client.loop();
  String sid;
  long state = digitalRead(sensor);
  if(state == HIGH){
    sid="HIGH";
    requestAuth(sid);
  }
  else{
    sid="LOW";
    requestAuth(sid);
  }
  delay(1000);
}

  
   /* if(state == HIGH) {
      digitalWrite (Status, HIGH);
      Serial.println("Motion detected!");
      delay(1000);
    }
    else {
      digitalWrite (Status, LOW);
      Serial.println("Motion absent!");
      delay(1000);
      }
}*/

void requestAuth(String UID){
  client.publish("mess_to_nodered",UID.c_str());
 }
 
