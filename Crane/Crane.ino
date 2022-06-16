
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
  pinMode(buttonIn, INPUT_PULLUP);
  //Serial.begin(9600);
}

void moveMotor(int motorNumber, int inputPin, int maxAngle, int minAngle, int direction)
{
  joystickPositions[motorNumber] = analogRead(inputPin);
  
  /*Serial.print("Motor " + String(motorNumber) + ": ");
  Serial.print(joystickPositions[motorNumber]);
  Serial.print(" Position: ");
  Serial.print(String(motorPositions[motorNumber])+" ");*/
  
  if (motorPositions[motorNumber] <= maxAngle && motorPositions[motorNumber] >= minAngle)
  {
    if (joystickPositions[motorNumber] > 811)
    {
      motorPositions[motorNumber]+=direction;
    }
    else if (joystickPositions[motorNumber] < 211)
    {
      motorPositions[motorNumber]-=direction;
    }
  } 
  else if(motorPositions[motorNumber] > maxAngle)
  {
    motorPositions[motorNumber]--;
  } 
  else if(motorPositions[motorNumber] < minAngle)
  {
    motorPositions[motorNumber]++;
  }
  motors[motorNumber].write(motorPositions[motorNumber]);
}

void checkButton()
{
  if (digitalRead(buttonIn) == LOW)
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
      motorPositions[1]=angle2;
      motorPositions[0]=angle1;
      motors[1].write(angle2);
      delay(100);
      motors[0].write(angle1);
    }
  }
  else
  {
    buttonState = 0;
  }
}

void loop()
{
  moveMotor(0, 0, 137, 0, 1);
  moveMotor(1, 1, 129, 39, -1);
  checkButton();
  /*Serial.print("Button: "+String(buttonState)+" ");
  Serial.print("Angle 1: "+String(angle1)+" Angle 2: "+String(angle2));
  Serial.println();*/
  delay(50);
}
