#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

#define pirPin D6
int pirState = 0;
int val = 0;                   

WiFiClient net;
PubSubClient client (net);

const char* mqtt_server = "192.168.178.39";
const char* ssid = "JoshuaPlaysAGame";
const char* pswd = "R64Xrt}adds;";

void connect()
{
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pswd);
    }

    Serial.println(WiFi.localIP());
}

void setup()
{
  pinMode (pirPin, INPUT);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, pswd);

  connect();

  client.setServer(mqtt_server, 1883);

  Serial.begin(115200);
}

void reconnect() {
  while (!client.connected()) 
  {
    Serial.println("Attempting MQTT connection...");
    String clientId = "WemosD1Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), "openhabian", "wKo8c2p$"))
    {
      Serial.println("connected");
      client.publish("outTopic", "hello world");
      client.subscribe("inTopic");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}


void loop()
{
  //Serial.println("Motion detection running!");
  val = digitalRead(pirPin);  // read input value
  if (val == HIGH) 
  {            // check if the input is HIGH
    if (pirState == LOW) 
    {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } 
  else 
  {
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  int pirState1 = pirState;
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  
  // Per MQTT-Daten versenden
  //char bufferPIR[10];
  //sprintf(bufferPIR, "%lu", "Open");

  if (pirState == 1)
  {
      client.publish("/SmartHome/Arduino/PIR/MotionDetection", "OPEN");
      Serial.println("Open");
  }
  else
  {
      client.publish("/SmartHome/Arduino/PIR/MotionDetection", "CLOSED");
      Serial.println("Closed");
  }
  

  //Serial.println(bufferPIR);

  delay(100);
  
}