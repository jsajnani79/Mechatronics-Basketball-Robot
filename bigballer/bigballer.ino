#include "Bot.h"
#include "NewPing.h"

/**
 * MAIN INO FOR ROBOT.
 */
 
/*---------------- Includes ---------------------------------*/




/*---------------- Module Defines ---------------------------*/

//MOTORS
#define ENABLE_PIN_LEFT 4
#define DIR_PIN_LEFT 5
#define ENABLE_PIN_RIGHT 2
#define DIR_PIN_RIGHT 3

//ULTRASOUND
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     13  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 230 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define TURN_START 15

Bot* robot;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
int state;

void setup() {
  Serial.begin(9600);
  robot = new Bot(ENABLE_PIN_LEFT, DIR_PIN_LEFT, ENABLE_PIN_RIGHT, DIR_PIN_RIGHT);
  state = 1;
  robot->moveForward(50,50);
}

void loop() { 
  if(state==1){
    delay(50);
    unsigned int uS = sonar.ping();
    if((uS / US_ROUNDTRIP_CM) < 40){
      state = 0;
      robot->moveBackward(50,50);
      delay(5);
//      robot->stop();
    }
  } else if (state == 0) {
      state = 2;
      robot->turnRight(); // right now left and right are mixed in the circuitry
  } else if (state == 2) {
      if (robot->hasFinishedRightTurn()) {
        state = 1;
        robot->moveForward(50, 50);
      }
  }

}

/*---------------- Module Functions -------------------------*/



