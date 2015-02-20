/*---------------- Module Defines ---------------------------*/
#ifndef Bot_h
#define Bot_h

#include "Motor.h"

class Bot 
{
  public:
    Bot(unsigned char enableLeft, unsigned char dirLeft, unsigned char enableRight, unsigned char dirRight);
    void moveForward(int dutyCycle);
    void moveBackward(int dutyCycle);
    void stop();
    void turnLeft();
    void turnRight();

  private:
    Motor* leftMotor;
    Motor* rightMotor;

};

#endif
