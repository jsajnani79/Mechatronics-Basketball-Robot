/*---------------- Module Defines ---------------------------*/
#ifndef Bot_h
#define Bot_h

#include "Motor.h"

class Bot 
{
  public:
    Bot(unsigned char enableLeft, unsigned char dirLeft, unsigned char enableRight, unsigned char dirRight);
    void moveForward(int dutyCycleR, int dutyCycleL);
    void moveBackward(int dutyCycleR, int dutyCycleL);
    void stop();
    bool hasFinishedLeftTurn();
    void turnLeft();
    bool hasFinishedRightTurn();
    void turnRight();
    void makeSquare();

  private:
    Motor* leftMotor;
    Motor* rightMotor;
    unsigned char turnTimer;

};

#endif
