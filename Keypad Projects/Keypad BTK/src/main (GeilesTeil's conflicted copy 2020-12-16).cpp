#include <Arduino.h>

#include "Keypad.h"

#include "BLEKeyboard.h"

BleKeyboard bleKeyboard;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// For Arduino Microcontroller
//byte rowPins[ROWS] = {9, 8, 7, 6}; 
//byte colPins[COLS] = {5, 4, 3, 2}; 

// For ESP8266 Microcontroller
//byte rowPins[ROWS] = {D1, D2, D3, D4}; 
//byte colPins[COLS] = {D5, D6, D7, D8}; 

// For ESP32 Microcontroller
byte rowPins[ROWS] = {23, 22, 4, 21}; 
byte colPins[COLS] = {19, 18, 2, 17};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() 
{
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}
//uint8_t key
void sendMacroCommand(uint8_t key)
{
  Serial.println("OBS Szene 1");
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(key);

  delay(100);
  bleKeyboard.releaseAll();
}

void loop() 
{
  char key = (int)keypad.getKey();

  if (key)
  {
    Serial.println(key);
  }

  if(bleKeyboard.isConnected()) 
  {
    switch (key)
    {
    case '1':
      sendMacroCommand(KEY_INSERT);
      break;
    case '2':
      sendMacroCommand(KEY_LEFT_ARROW);
      break;
    }
  }

  if (bleKeyboard.isConnected())
  {
    Serial.println("Connected");
  }
  else
  {
    //Serial.println("Not Connected");
  } 
}