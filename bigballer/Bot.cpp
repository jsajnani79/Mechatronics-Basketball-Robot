/*---------------- Includes ---------------------------------*/
#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif
#include "Bot.h"

/*---------------- Module Function Prototypes ---------------*/

/*---------------- Module Functions -------------------------*/
Bot::Bot(unsigned char enableLeft, unsigned char dirLeft, unsigned char enableRight, unsigned char dirRight) {
  leftMotor = new Motor(enableLeft, dirLeft);
  rightMotor = new Motor(enableRight, dirRight);
}

void Bot::moveForward(int dutyCycle) {
  leftMotor->moveForward(dutyCycle);
  rightMotor->moveForward(dutyCycle);
}

void Bot::moveBackward(int dutyCycle) {
  leftMotor->moveBackward(dutyCycle);
  rightMotor->moveBackward(dutyCycle);
}

void Bot::stop() {
  leftMotor->stop();
  rightMotor->stop();
}

void Bot::turnLeft() {

}

void Bot::turnRight() {

}
