#include <Motor.h>

/**
 * MAIN INO FOR ROBOT.
 */

/*---------------- Includes ---------------------------------*/




/*---------------- Module Defines ---------------------------*/

Motor motorA(ENABLE_PIN_A, DIR_PIN_A);

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
void setup() {
  Serial.begin(9600);
  motorA.moveForward(100);
}

void loop() {
  
  if (Serial.available()) {
    Serial.read();
    motorA.stop();
  }
}

/*---------------- Module Functions -------------------------*/



