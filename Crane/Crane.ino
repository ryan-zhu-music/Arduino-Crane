
#include <Servo.h>

// create servo objects
Servo servo1;
Servo servo2;

// potentiometer analog input pins
int potpin1 = 0;
int potpin2 = 1;
int current1 = 511;
int current2 = 511;
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
  new1 = analogRead(potpin1);
  Serial.print("Motor 1: ");
  Serial.print(new1);
  if (new1 > 811)
  {
    current1++;
  }
  else if (new1 < 211)
  {
    current1--;
  }
  servo1.write(current1);
  new2 = analogRead(potpin2);
  Serial.print("\tMotor 2: ");
  Serial.println(new2);
  if (new2 > 811)
  {
    current2++;
  }
  else if (new2 < 211)
  {
    current2--;
  }
  servo2.write(current2);
  delay(30);
}
