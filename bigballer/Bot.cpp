#include "Timers.h"

/*---------------- Includes ---------------------------------*/
#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif
#include "Bot.h"

#define TURN_TIMER 10
#define TIMER_UNSET 255
#define TURN_DUTY_CYCLE 100
#define TURN_DURATION 5000 // in ms

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

bool Bot::hasFinishedLeftTurn() {
  bool timerExpired = TMRArd_IsTimerExpired(TURN_TIMER) == TMRArd_EXPIRED;
  if (timerExpired) {
    TMRArd_ClearTimerExpired(TURN_TIMER);
  }
  return timerExpired;
}

void Bot::turnLeft() {
  TMRArd_InitTimer(TURN_TIMER, TURN_DURATION);
  leftMotor->moveBackward(TURN_DUTY_CYCLE);
  rightMotor->moveForward(TURN_DUTY_CYCLE);
}

void Bot::turnRight() {

}
