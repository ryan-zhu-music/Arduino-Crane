/* The crane consists of 2 motors, one controlling vertical movement and the other controlling horizontal movement
 *  It is controlled by a joystick, with each axis controlling 1 motor.
 *  When the joystick is pressed down, it remembers its current position, and subsequent presses bring it to the saved position
 * The arm is monted on a corkboard platform
 * Coded in C++ using Arduino
 */
#include <Servo.h>
#include <EEPROM.h>

// create servo objects
Servo motors[2];

// potentiometer analog input pins
int motorPins[2] = {9, 10};
int motorPositions[2] = {90, 90};
int joystickPositions[2] = {512, 512};
int savedPositions[2] = {90, 90};

int buttonIn = 2;
int buttonState = 0;
bool buttonPressed = false;
int angle1 = 0;
int angle2 = 0;

void setup()
{
  pinMode(buttonIn, INPUT_PULLUP);
  for (int i = 0; i < 2; i++)
  {
    savedPositions[i] = EEPROM.read(i);
    motors[i].write(savedPositions[i]);
    motors[i].attach(motorPins[i]);
  }
  if (savedPositions[0] <= 180 && savedPositions[1] <= 180)
  {
    // move motors slowly to intial position
    for (int i = 1; i >=0; i--)
    {
      //motors[i].write(savedPositions[i]);
      while (savedPositions[i] != 90)
      {
        if (savedPositions[i] > 90)
        {
          savedPositions[i]--;
        }
        else
        {
          savedPositions[i]++;
        }
        motors[i].write(savedPositions[i]);
        delay(50);
      }
      delay(1000);
    }
  }
  // motors[0].write(90);
  // motors[1].write(90);
}

// general function for moving the motor using the joystick
void moveMotor(int motorNumber, int inputPin, int maxAngle, int minAngle, int direction)
{
  // read the joystick analog position from the input pin
  joystickPositions[motorNumber] = analogRead(inputPin);

  // move the motor if it is within the movement range
  if (motorPositions[motorNumber] <= maxAngle && motorPositions[motorNumber] >= minAngle)
  {
    if (joystickPositions[motorNumber] > 811)
    {
      // move in the "positive direction"
      motorPositions[motorNumber] += direction;
    }
    else if (joystickPositions[motorNumber] < 211)
    {
      // move in the "negative direction"
      motorPositions[motorNumber] -= direction;
    }
  }
  // if the motor somehow finds itself outside of its range, move it back inside
  else if (motorPositions[motorNumber] > maxAngle)
  {
    motorPositions[motorNumber]--;
  }
  else if (motorPositions[motorNumber] < minAngle)
  {
    motorPositions[motorNumber]++;
  }
  // move the servo the target location
  motors[motorNumber].write(motorPositions[motorNumber]);
  // update EEPROM
  EEPROM.update(motorNumber, motorPositions[motorNumber]);
}

// function for the joystick pushbutton
void checkButton()
{
  // if the button is being pressed
  if (digitalRead(buttonIn) == LOW)
  {
    buttonState = 1;
    // buttonPressed is a boolean that gets set to true the first time the button is pressed
    // so if the button has not been pressed before, we save the position that the arm is currently in
    if (!buttonPressed)
    {
      // set buttonPressed to true so we do not overwrite the values next time
      buttonPressed = true;
      // save the current motor positions into variables
      angle1 = motorPositions[0];
      angle2 = motorPositions[1];
    }
    // if button has already been pressed before, move to the saved location
    else
    {
      // get the target location and move there
      motorPositions[1] = angle2;
      motorPositions[0] = angle1;
      motors[1].write(motorPositions[1]);
      delay(2000);
      motors[0].write(motorPositions[0]);
    }
  }
  else
  {
    // button not pressed
    buttonState = 0;
  }
}

void loop()
{
  // main function, we move both motors sequentially
  // if the joystick is not being pushed, the moveMotor function will not make the motor move
  moveMotor(0, 0, 137, 0, 1);
  moveMotor(1, 1, 129, 39, -1);
  // check if the button is being pressed, and act accordingly
  checkButton();
  /*Serial.print("Button: " + String(buttonState) + " ");
  Serial.print("Angle 1: " + String(angle1) + " Angle 2: " + String(angle2));
  Serial.println();*/
  delay(30);
}
