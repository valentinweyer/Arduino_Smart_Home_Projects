#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define orangeLED 7
#define greenLED 4
#define redLED 8
#define DHTPIN 2

DHT dht11(DHTPIN, DHT11);

void setup() 
{
  Serial.begin(115200);
  Serial.println("Setup completed");
  dht11.begin();
  pinMode(orangeLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() 
{
  float humidity = doDht(dht11);

  if (humidity >= 40 && humidity <= 60) 
  {
   good();
  } 
  else if ((humidity > 30 && humidity < 40) || (humidity < 70 && humidity > 60)) 
  {
    medium();
  } 
  else 
  {
    bad();
  }
  
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

void good()
{
  digitalWrite(redLED, LOW);
  digitalWrite(orangeLED, LOW);
  digitalWrite(greenLED, HIGH);
  Serial.println("good");
}

void medium()
{
  digitalWrite(redLED, LOW);
  digitalWrite(orangeLED, HIGH);
  digitalWrite(greenLED, LOW);
  Serial.println("medium");
}

void bad()
{
  digitalWrite(redLED, HIGH);
  digitalWrite(orangeLED, LOW);
  digitalWrite(greenLED, LOW);
  Serial.println("bad");
}