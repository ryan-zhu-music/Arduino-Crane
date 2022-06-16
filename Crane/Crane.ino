
#include <Servo.h>

// create servo objects
Servo motors[2];

// potentiometer analog input pins
int motorPositions[2] = {90, 90};
int joystickPositions[2] = {512, 512};
int buttonIn = 2;
int buttonState = 0;
bool buttonPressed = false;
int angle1;
int angle2;

void setup()
{
  // attack servos to pins
  motors[0].attach(9);
  motors[1].attach(10);
  pinMode(buttonIn, INPUT);
  // Serial.begin(9600);
}

void moveMotor(int motorNumber, int inputPin, int maxAngle, int minAngle)
{
  joystickPositions[motorNumber] = analogRead(inputPin);
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

void checkButton()
{
  if (digitalRead(buttonIn) == HIGH)
  {
    buttonState = 1;
    if (!buttonPressed)
    {
      buttonPressed = true;
      angle1 = motorPositions[0];
      angle2 = motorPositions[1];
    }
    else
    {
      motors[0].write(angle1);
      motors[1].write(angle2);
    }
  }
  else
  {
    buttonState = 0;
  }
}

void loop()
{
  moveMotor(0, 0, 180, 0);
  moveMotor(1, 1, 129, 39);
  delay(10);
}
