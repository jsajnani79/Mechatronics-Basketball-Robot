/*---------------- Module Defines ---------------------------*/
#ifndef Motor_h
#define Motor_h

typedef enum {
  MOVING, STOPPED
} motorState;


class Motor 
{
  public:
    /** Motor starts off switched on */
    Motor(unsigned char enable, unsigned char dir);
    void moveForward(int dutyCycle);
    void moveBackward(int dutyCycle);
    void stop();
    motorState getState();

  private:
    unsigned char enablePin;
    unsigned char dirPin;
    motorState state;
};

#endif
