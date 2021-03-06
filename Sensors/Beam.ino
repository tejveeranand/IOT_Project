#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid        = "Realme 8pro";
const char* password    = "iamsiddy";
const char* mqtt_server = "3.214.158.175";
int         mqtt_port   = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const long interval = 5000;       //5 sec non-blocking delay
unsigned long previousMillis = 0;
int flag=0;
int deviceid =0;

String pubString;
char pubChars[100];

int ldr = A0;  // Analog pin A0
long ldrValue = 0;
int pir = 13;  // Digital pin D7


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
  client.setServer(mqtt_server, mqtt_port);
  //code for pir
  pinMode(pir, INPUT);   // declare pir sensor as input
  //device id
  deviceid=ESP.getChipId();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  //client.loop();
  readSensor();
}
void sendData(){
                  pubString = "{\"deviceid\":" + String(deviceid);
                  long state_pir = digitalRead(pir);
                  Serial.print("pir_Sensor_value = ");
                  Serial.print(state_pir);
                  Serial.print("; ");
                  String value_pir = String(state_pir);
                  pubString += ",\"pir\":" + value_pir;       
                          
                           //ldr data to mqtt
                  
                  int ldrValue = analogRead(ldr);
                  //sensorValue = map(sensorValue, 0, 1024, 0, 100);
                  Serial.print("ldr_Sensor_value = ");
                  Serial.print(ldrValue);
                  Serial.println("; ");
                  String value_ldr = String(ldrValue);
                  pubString += ",\"ldr\":" + value_ldr+ "}";        
                  
                            // publishing data
                  
                  pubString.toCharArray(pubChars, pubString.length() + 1);
                  client.publish("Sensors", pubChars);
  }
void readSensor(){

            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= interval)
            {
                    long state_pir = digitalRead(pir);
                    if(state_pir == HIGH and flag==0)
                    {
                               flag=1;
                              //pir data to mqtt
                              sendData();
                    }
                    if(state_pir == LOW and flag==1)
                    {
                              flag=0;
                              //pir data to mqtt
                              sendData();
                    }
            previousMillis = currentMillis;  
          }
}
