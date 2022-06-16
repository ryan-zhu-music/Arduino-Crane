
#include <Servo.h>

// create servo objects
Servo motors[2];

// potentiometer analog input pins
int inputPins[2] = {0, 1};
int motorPositions[2] = {90, 90};
int joystickPositions[2] = {512, 512};

void setup()
{
  // attack servos to pins
  motors[0].attach(9);
  motors[1].attach(10);
  // Serial.begin(9600);
}

void moveMotor(int motorNumber, int inputPin, int maxAngle, int minAngle)
{
  joystickPositions[motorNumber] = analogRead(inputPins[motorNumber]);
  /*
  Serial.print("Motor " + String(motorNumber) + ": ");
  Serial.print(joystickPositions[motorNumber]);
  Serial.print(" Position: ");
  Serial.print(motorPositions[motorNumber]);
  */
  if (motorPositions[motorNumber] <= maxAngle && motorPositions >= minAngle)
  {
    if (joystickPositions[motorNumber] > 811)
    {
      motorPositions[motorNumber]++;
    }
    else if (joystickPositions[motorNumber] < 211)
    {
      motorPositions[motorNumber]--;
    }
  }
  motors[motorNumber].write(motorPositions[motorNumber]);
}

void loop()
{
  moveMotor(0, 0, 180, 0);
  moveMotor(1, 1, 129, 39);
  delay(10);
}
