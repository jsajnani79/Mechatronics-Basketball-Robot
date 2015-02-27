#include "Bot.h"
#include "NewPing.h"

/**
 * MAIN INO FOR ROBOT.
 */
 
/*---------------- Includes ---------------------------------*/




/*---------------- Module Defines ---------------------------*/
#define DEBUG

//MOTORS
#define ENABLE_PIN_LEFT 4
#define DIR_PIN_LEFT 5
#define ENABLE_PIN_RIGHT 2
#define DIR_PIN_RIGHT 3

//ULTRASOUND FRONT
#define TRIGGER_PIN_F  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_F     13  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_F 230 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//ULTRASOUND RIGHT
#define TRIGGER_PIN_R  10  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_R     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_R 230 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define RIGHT_DISTANCE 49
#define MOTOR_LEFT 64
#define MOTOR_RIGHT 60
#define DRIFT_MARGIN 2

#define TURN_START 15

Bot* robot;
NewPing sonarFront(TRIGGER_PIN_F, ECHO_PIN_F, MAX_DISTANCE_F); // NewPing setup of pins and maximum distance.
NewPing sonarRight(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE_R); // NewPing setup of pins and maximum distance.

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
int state;

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Big Ballers booting up");
  #endif
  robot = new Bot(ENABLE_PIN_LEFT, DIR_PIN_LEFT, ENABLE_PIN_RIGHT, DIR_PIN_RIGHT);
  state = 1;
//  robot->moveForward(50,53);
  robot->moveForward(MOTOR_LEFT,MOTOR_RIGHT);
}

void loop() { 
//  if(state==1){
//    delay(50);
//    unsigned int uS_F = sonarFront.ping();
//    Serial.print(uS_F);
//    if((uS_F / US_ROUNDTRIP_CM) < 12){
//      state = 0;
//      robot->hardStop();
//      delay(500);
//    }
//  } else if (state == 0) {
//      state = 2;
//      robot->turnRight();
//  } else if (state == 2) {
//      if (robot->hasFinishedRightTurn()) {
//        state = 1;
//        robot->hardStop();
//        delay(500);
//        robot->moveForward(50, 53);
//      }
//  }

//RIGHT UPLTRASOUND TESTING
  if(state==1){
//    Serial.println("Front: ");
    unsigned int uS_F = sonarFront.ping();
//    Serial.println(uS_F/US_ROUNDTRIP_CM);
    unsigned int uS_R = sonarRight.ping();
//    Serial.print(", Right: ");
//    Serial.println(uS_R/US_ROUNDTRIP_CM);
    if((uS_F / US_ROUNDTRIP_CM) < 10){
      robot->hardStop();
      state = 0;
    } else if(((uS_R / US_ROUNDTRIP_CM) > (RIGHT_DISTANCE-DRIFT_MARGIN)) && ((uS_R / US_ROUNDTRIP_CM) < (RIGHT_DISTANCE+DRIFT_MARGIN))){
      Serial.println(0);
      robot->moveForward(MOTOR_LEFT, MOTOR_RIGHT);
      delay(50);
    } else if(((uS_R / US_ROUNDTRIP_CM) < (RIGHT_DISTANCE-DRIFT_MARGIN))){
      // too close, turn left
      Serial.println(1);
      robot->moveForward(0, MOTOR_RIGHT+3);
      delay(160);
      robot->moveForward(MOTOR_LEFT, MOTOR_RIGHT);
      delay(250);
      robot->moveForward(MOTOR_LEFT+3,0);
      delay(120);
      robot->moveForward(MOTOR_LEFT, MOTOR_RIGHT);
    } else if(((uS_R / US_ROUNDTRIP_CM) > (RIGHT_DISTANCE+4))){
      // too far, turn right
      Serial.println(2);
      robot->moveForward(MOTOR_LEFT+3, 0);
      delay(160);
      robot->moveForward(MOTOR_LEFT, MOTOR_RIGHT);
      delay(250);
      robot->moveForward(0,MOTOR_RIGHT+3);
      delay(160);
      robot->moveForward(MOTOR_LEFT, MOTOR_RIGHT);
      
    }
  }


}

/*---------------- Module Functions -------------------------*/



