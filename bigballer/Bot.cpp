#include "Timers.h"

/*---------------- Includes ---------------------------------*/
#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif
#include "Bot.h"

#define TURN_LEFT_TIMER 10
#define TURN_RIGHT_TIMER 11
#define TIMER_UNSET 255
#define TURN_DUTY_CYCLE 60
#define TURN_DURATION 200 // in ms

/*---------------- Module Function Prototypes ---------------*/

/*---------------- Module Functions -------------------------*/
Bot::Bot(unsigned char enableLeft, unsigned char dirLeft, unsigned char enableRight, unsigned char dirRight) {
  leftMotor = new Motor(enableLeft, dirLeft);
  rightMotor = new Motor(enableRight, dirRight);
}

void Bot::moveForward(int dutyCycleR, int dutyCycleL) {
  leftMotor->moveForward(dutyCycleL);
  rightMotor->moveForward(dutyCycleR);
}

void Bot::moveBackward(int dutyCycleR, int dutyCycleL) {
  leftMotor->moveBackward(dutyCycleL);
  rightMotor->moveBackward(dutyCycleR);
}

void Bot::stop() {
  leftMotor->stop();
  rightMotor->stop();
}

bool Bot::hasFinishedLeftTurn() {
  bool timerExpired = TMRArd_IsTimerExpired(TURN_LEFT_TIMER) == TMRArd_EXPIRED;
  if (timerExpired) {
    TMRArd_ClearTimerExpired(TURN_LEFT_TIMER);
  }
  return timerExpired;
}

void Bot::turnLeft() {
  TMRArd_InitTimer(TURN_LEFT_TIMER, TURN_DURATION);
  leftMotor->moveBackward(TURN_DUTY_CYCLE);
  rightMotor->moveForward(TURN_DUTY_CYCLE);
}

bool Bot::hasFinishedRightTurn() {
  bool timerExpired = TMRArd_IsTimerExpired(TURN_RIGHT_TIMER) == TMRArd_EXPIRED;
  if (timerExpired) {
    TMRArd_ClearTimerExpired(TURN_RIGHT_TIMER);
  }
  return timerExpired;
}

void Bot::turnRight() {
  TMRArd_InitTimer(TURN_RIGHT_TIMER, TURN_DURATION);
  leftMotor->moveForward(TURN_DUTY_CYCLE);
  rightMotor->moveBackward(TURN_DUTY_CYCLE);
}

void Bot::makeSquare(){
  
  for (int i=0; i < 4; i++){
    moveForward(60, 70);
    delay(1000);
    turnRight();
    while(!hasFinishedRightTurn()){
      delay(5);
    }
    stop();
    delay(100);
  }

}
