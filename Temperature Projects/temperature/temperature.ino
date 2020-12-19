#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 2

DHT dht11(DHTPIN, DHT11);

void setup() 
{
  Serial.begin(115200);
  Serial.println("Setup completed");

  dht11.begin();
}

void loop() 
{
  float dht11Humidity = doDht(dht11);
  delay(1000);
}

float doDht(DHT myDht)
{
  float humidity = myDht.readHumidity();
  float temp = myDht.readTemperature();
  
  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.println("°"); 

  return humidity;
}