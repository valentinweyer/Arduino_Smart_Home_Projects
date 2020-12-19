#include <Arduino.h>

#define Stepperpin_1 8
#define Stepperpin_2 7
#define Stepperpin_3 6
#define Stepperpin_4 5

int step = 0;

void setup()
{
  pinMode(Stepperpin_1, OUTPUT);
  pinMode(Stepperpin_2, OUTPUT);
  pinMode(Stepperpin_3, OUTPUT);
  pinMode(Stepperpin_4, OUTPUT);
}

void oneStep()
{
  switch (step++)
  {
    case 0:
      digitalWrite(Stepperpin_1, HIGH);
      digitalWrite(Stepperpin_2, LOW);
      digitalWrite(Stepperpin_3, LOW);
      digitalWrite(Stepperpin_4, LOW);
      break;
    
    case 1:
      digitalWrite(Stepperpin_1, LOW);
      digitalWrite(Stepperpin_2, HIGH);
      digitalWrite(Stepperpin_3, LOW);
      digitalWrite(Stepperpin_4, LOW);
      break;
    case 2:
      digitalWrite(Stepperpin_1, LOW);
      digitalWrite(Stepperpin_2, LOW);
      digitalWrite(Stepperpin_3, HIGH);
      digitalWrite(Stepperpin_4, LOW);
      break;
    case 3:
      digitalWrite(Stepperpin_1, LOW);
      digitalWrite(Stepperpin_2, LOW);
      digitalWrite(Stepperpin_3, LOW);
      digitalWrite(Stepperpin_4, HIGH);
      break;
  }
}

void loop()
{
  oneStep();
  delay(5);
}