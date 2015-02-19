#include "Motor.h"

/**
 * MAIN INO FOR ROBOT.
 */

/*---------------- Includes ---------------------------------*/




/*---------------- Module Defines ---------------------------*/

//Motor motorA(ENABLE_PIN_A, DIR_PIN_A);
Motor* motorA;

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
void setup() {
  Serial.begin(9600);
  motorA = new Motor(ENABLE_PIN_A, DIR_PIN_A);
}

void loop() {
  Serial.println("100 forward");
  motorA->moveForward(100);
  delay(2000);

  Serial.println("stopped");
  motorA->stop();
  delay(2000);

  Serial.println("100 backward");
  motorA->moveBackward(100);
  delay(2000);
  
  Serial.println("0 forward")
  motorA->moveForward(0);
  delay(2000);
  
  Serial.println("0 backward")
  motorA->moveBackward(0);
  delay(2000);

}

/*---------------- Module Functions -------------------------*/



