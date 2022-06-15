
#include <Servo.h>

// create servo objects
Servo servo1;
Servo servo2;

// potentiometer analog input pins
int inputpin1 = 0;
int inputpin2 = 1;
int motorPos1 = 90;
int motorPos2 = 90;
int new1;
int new2;

void setup()
{
  // attack servos to pins
  servo1.attach(9);
  servo2.attach(10);
  Serial.begin(9600);
}

void loop()
{
  // read and scale input from 0-1023 to 0-180
  new1 = analogRead(inputpin1);
  Serial.print("Motor 1: ");
  Serial.print(new1);
  Serial.print(" Position: ");
  Serial.print(motorPos1);
  if (new1 > 811&&motorPos1<=129)
  {
    motorPos1++;
  }
  else if (new1 < 211&&motorPos1>=39)
  {
    motorPos1--;
  }
  servo1.write(motorPos1);
  new2 = analogRead(inputpin2);
  Serial.print("\tMotor 2: ");
  Serial.print(new2);
  Serial.print(" Position: ");
  Serial.println(motorPos2);
  if (new2 > 811&&motorPos2>=0)
  {
    motorPos2--;
  }
  else if (new2 < 211&&motorPos2<=180)
  {
    motorPos2++;
  }
  servo2.write(motorPos2);
  delay(10);
}
