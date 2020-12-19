#include <Arduino.h>

int motor_A = 4;
int motor_B = 5;
int motor_Speed = 3;

void setup()
{
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
}

void loop()
{
  digitalWrite(motor_A, HIGH);
  digitalWrite(motor_B, LOW);

  analogWrite(motor_Speed, 100);
  delay (2000);

  analogWrite(motor_Speed, 200);
  delay (2000);

  analogWrite(motor_Speed, 0);
  delay (2000);

  digitalWrite(motor_A, LOW);
  digitalWrite(motor_B, HIGH);

  analogWrite(motor_Speed, 100);
  delay (2000);

  analogWrite(motor_Speed, 200);
  delay (2000);

  analogWrite(motor_Speed, 0);
  delay (2000);
}