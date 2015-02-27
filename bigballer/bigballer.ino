#include "Bot.h"
#include "NewPing.h"
#include <Servo.h>


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

//SERVOS
#define GATE_PIN 8
#define ARM_PIN 9
#define GATE_CLOSE_ANGLE 160
#define GATE_OPEN_ANGLE 90
#define ARM_UP_ANGLE 20
#define ARM_DOWN_ANGLE 100

//ULTRASOUND FRONT
#define TRIGGER_PIN_F  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_F     13  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_F 230 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//ULTRASOUND RIGHT
#define TRIGGER_PIN_R  10  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_R     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_R 230 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define RIGHT_DISTANCE 49
#define LEFT_SPEED 64  // needs to be calibrated to make bot move in straight line
#define RIGHT_SPEED 60  // needs to be calibrated to make bot move in straight line
#define DRIFT_MARGIN 2

#define TURN_START 15
#define BASKET_PROXIMITY 10

Bot* robot;
Servo gateServo;
Servo armServo;
NewPing sonarFront(TRIGGER_PIN_F, ECHO_PIN_F, MAX_DISTANCE_F); // NewPing setup of pins and maximum distance.
NewPing sonarRight(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE_R); // NewPing setup of pins and maximum distance.

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
static int state;

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Big Ballers booting up");
  #endif

  robot = new Bot(ENABLE_PIN_LEFT, DIR_PIN_LEFT, ENABLE_PIN_RIGHT, DIR_PIN_RIGHT);
//  gateServo.attach(GATE_PIN);
//  gateServo.write(GATE_CLOSE_ANGLE);
//  armServo.attach(ARM_PIN);
//  armServo.write(ARM_UP_ANGLE);
  state = 1;
  robot->moveForward(LEFT_SPEED,RIGHT_SPEED);
}

void loop() { 

  if(state==1){
//    Serial.println("Front: ");
    unsigned int forwardDistance = sonarFront.ping() / US_ROUNDTRIP_CM;
//    Serial.println(forwardDistance);
    unsigned int rightDistance = sonarRight.ping() / US_ROUNDTRIP_CM;
//    Serial.print(", Right: ");
//    Serial.println(rightDistance);
    if(forwardDistance < BASKET_PROXIMITY){
      robot->hardStop();
      state = 0;
     
    } else if(rightDistance > (RIGHT_DISTANCE - DRIFT_MARGIN) && rightDistance < (RIGHT_DISTANCE + DRIFT_MARGIN)){
      Serial.println(0);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      delay(50);
      
    } else if(rightDistance < (RIGHT_DISTANCE - DRIFT_MARGIN)){
      // too close, turn left
      Serial.println(1);
      robot->moveForward(0, RIGHT_SPEED+3);
      delay(160);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      delay(250);
      robot->moveForward(LEFT_SPEED+3,0);
      delay(120);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      
    } else if(rightDistance > (RIGHT_DISTANCE+4)){
      // too far, turn right
      Serial.println(2);
      robot->moveForward(LEFT_SPEED+3, 0);
      delay(160);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      delay(250);
      robot->moveForward(0,RIGHT_SPEED+3);
      delay(160);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      
    }
  }


}

/*---------------- Module Functions -------------------------*/



