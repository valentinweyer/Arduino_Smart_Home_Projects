#include "Keypad.h"

#include "BLEKeyboard.h"

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
byte rowPins[ROWS] = {D1, D2, D3, D4}; 
byte colPins[COLS] = {D5, D6, D7, D8}; 

// For ESP32 Microcontroller
//byte rowPins[ROWS] = {23, 22, 3, 21}; 
//byte colPins[COLS] = {19, 18, 5, 17};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() 
{
  Serial.begin(115200);
}

void sendMacroCommand(uint8_t key) 
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
}

void loop() 
{
  char key = keypad.getKey();

  if (key)
  {
    Serial.println(key);
  }
}

if (key) 
{
    Serial.println(key);
    switch (key) {
      case '1':
        sendMacroCommand(KEY_F1);
        break;
      case '2':
        sendMacroCommand(KEY_F2);
        break;
      case '3':
        sendMacroCommand(KEY_F3);
        break;
      case '4':
        sendMacroCommand(KEY_F4);
        break;
      case '5':
        sendMacroCommand(KEY_F5);
        break;
      case '6':
        sendMacroCommand(KEY_F6);
        break;
      case '7':
        sendMacroCommand(KEY_F7);
        break;
      case '8':
        sendMacroCommand(KEY_F8);
        break;
      case '9':
        sendMacroCommand(KEY_F9);
        break;
      case '0':
        sendMacroCommand(KEY_F10);
        break;
      case '*':
        sendMacroCommand(KEY_F11);
        break;
      case '#':
        sendMacroCommand(KEY_F12);
        break;
      case 'A':
        sendMacroCommand('a');
        break;
      case 'B':
        sendMacroCommand('b');
        break;
      case 'C':
        sendMacroCommand('c');
        break;
      case 'D':
        sendMacroCommand('d');
        break;
    }

    delay(100);
    Keyboard.releaseAll(); // this releases the buttons
  }
}