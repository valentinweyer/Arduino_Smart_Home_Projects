#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

#define SS_PIN D8
#define RST_PIN D3

#define BUZZER_PIN D4

MFRC522 mfrc522(SS_PIN, RST_PIN);

WiFiClient net;
PubSubClient client (net);

const char* mqtt_server = "192.168.178.39";
const char* ssid = "JoshuaPlaysAGame";
const char* pswd = "R64Xrt}adds;";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, pswd);

  connect();
  client.setServer(mqtt_server, 1883);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

void connect()
{
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    WiFi.begin(ssid, pswd);
  }

  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
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
  unsigned long cardId;

  do 
  {
    cardId = getId();
    delay(0);
  } while (!cardId);

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);

  // Per MQTT-Daten versenden
  char bufferRFID[10];
  sprintf(bufferRFID, "%lu", cardId);
  client.publish("/SmartHome/Arduino/RFID", bufferRFID);

  Serial.println(cardId);
}

unsigned long getId() {
  if (!mfrc522.PICC_IsNewCardPresent()) 
  {
    return 0;
  }

  if (!mfrc522.PICC_ReadCardSerial()) 
  {
    return 0;
  }

  byte readCard[4];
  for (int i = 0; i < 4; i++) 
  {
    readCard[i] = mfrc522.uid.uidByte[i];
  }

  mfrc522.PICC_HaltA();

  return (unsigned long)readCard[0] << 24
    | (unsigned long)readCard[1] << 16
    | (unsigned long)readCard[2] << 8
    | (unsigned long)readCard[3];
}
