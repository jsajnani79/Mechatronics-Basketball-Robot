#include "Bot.h"

/**
 * MAIN INO FOR ROBOT.
 */
 
/*---------------- Includes ---------------------------------*/




/*---------------- Module Defines ---------------------------*/

#define ENABLE_PIN_LEFT 4
#define DIR_PIN_LEFT 5
#define ENABLE_PIN_RIGHT 2
#define DIR_PIN_RIGHT 3

Bot* robot;

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
void setup() {
  Serial.begin(9600);
  robot = new Bot(ENABLE_PIN_LEFT, DIR_PIN_LEFT, ENABLE_PIN_RIGHT, DIR_PIN_RIGHT);
  robot->turnLeft();
}

void loop() {
  if (robot->hasFinishedLeftTurn()) {
    robot->stop();
    Serial.println("stopping");
  }
  
//  Serial.println("100 forward");
//  robot->moveForward(100);
//  delay(2000);
//
//  Serial.println("stopped");
//  robot->stop();
//  delay(2000);
//
//  Serial.println("100 backward");
//  motorA->moveBackward(100);
//  delay(2000);
//  
//  Serial.println("0 forward");
//  motorA->moveForward(0);
//  delay(2000);
//  
//  Serial.println("0 backward");
//  motorA->moveBackward(0);
//  delay(2000);

}

/*---------------- Module Functions -------------------------*/



