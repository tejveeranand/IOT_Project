#include "DHTesp.h"
DHTesp dht;
void setup()
{
Serial.begin(9600);
Serial.println();
Serial.println("Status\t\tHumidity (%)\t\tTemperature (C)\t");
dht.setup(12, DHTesp::DHT11); // GPIO12(D6)
}
void loop()
{
//delay(dht.getMinimumSamplingPeriod() + 100);
delay(1500);
float humidity = dht.getHumidity();
float temperature = dht.getTemperature();
Serial.print("Humidity (%): ");
Serial.print(humidity, 1);
Serial.print("\t");
Serial.print("Temperature (C): ");
Serial.print(temperature, 1);
Serial.print("\t");
Serial.println();
} 
