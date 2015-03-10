/**
 * MAIN INO FOR ROBOT.
 */

/*---------------- Includes ---------------------------------*/

#include "Bot.h"
#include "NewPing.h"
#include "Timers.h"s
#include <Servo.h>

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
#define GATE_CLOSE_ANGLE 0
#define GATE_OPEN_ANGLE 100
#define ARM_UP_ANGLE 85
#define ARM_DOWN_ANGLE 180

//ULTRASOUND FRONT
#define TRIGGER_PIN_F  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_F     13  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_F 230 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//ULTRASOUND RIGHT
#define TRIGGER_PIN_R  10  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_R     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_R 230 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define RIGHT_DISTANCE 49
#define LEFT_SPEED 63  // needs to be calibrated to make bot move in straight line
#define RIGHT_SPEED 61  // needs to be calibrated to make bot move in straight line
#define DRIFT_MARGIN 2

#define COLLECTION_LEFT_SPEED 52
#define COLLECTION_RIGHT_SPEED 50

#define TURN_START 15
#define BASKET_PROXIMITY 6
#define BUMPER_PROXIMITY 203
#define NUM_BALLS_TO_COLLECT 3

//Timers
#define GAME_TIMER  1
#define GAME_DURATION 120000

typedef enum {
  BALL_COLLECTION, TO_BASKET, FROM_BASKET, FINISHED, TEST
} robotState;

Bot* robot;
Servo gateServo;
Servo armServo;
NewPing sonarFront(TRIGGER_PIN_F, ECHO_PIN_F, MAX_DISTANCE_F); // NewPing setup of pins and maximum distance.
NewPing sonarRight(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE_R); // NewPing setup of pins and maximum distance.
static robotState state;
static int ballsCollected;

/*---------------- Arduino Main Functions -------------------*/

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Big Ballers booting up...");
  #endif

  robot = new Bot(ENABLE_PIN_LEFT, DIR_PIN_LEFT, ENABLE_PIN_RIGHT, DIR_PIN_RIGHT);
  
  
  gateServo.attach(GATE_PIN);
  gateServo.write(GATE_CLOSE_ANGLE);
  armServo.attach(ARM_PIN);
  armServo.write(180);
  armServo.write(ARM_UP_ANGLE);
    
  ballsCollected = 0;
  state = BALL_COLLECTION;
  TMRArd_InitTimer(GAME_TIMER, GAME_DURATION);
}

void loop() {
  bool timerExpired = TMRArd_IsTimerExpired(GAME_TIMER) == TMRArd_EXPIRED;
  if (timerExpired) {  /* Round is over */
    TMRArd_ClearTimerExpired(GAME_TIMER);
    robot->hardStop();
    state = FINISHED;
  }
  
  /* Hit and release the bumper to collect balls */
  if (state == BALL_COLLECTION) {
    robot->moveBackward(COLLECTION_LEFT_SPEED, COLLECTION_RIGHT_SPEED+1);
    delay(1100);
    robot->moveForward(COLLECTION_LEFT_SPEED + 1, COLLECTION_RIGHT_SPEED );
    delay(600);
    robot->hardStop();
    delay(2000);
    ballsCollected++;
    if (ballsCollected >= NUM_BALLS_TO_COLLECT) {
      state = TO_BASKET;
      ballsCollected = 0;
      robot->moveForward(LEFT_SPEED,RIGHT_SPEED);
    }
  }

  /* Go to the 1-point basket */
  if(state==TO_BASKET){
    unsigned int forwardDistance = sonarFront.ping() / US_ROUNDTRIP_CM;
    unsigned int rightDistance = sonarRight.ping() / US_ROUNDTRIP_CM;

    /* If we have reached the basket */
    if(forwardDistance < BASKET_PROXIMITY){
      delay(50);
      forwardDistance = sonarFront.ping() / US_ROUNDTRIP_CM;
      if(forwardDistance < BASKET_PROXIMITY){
        robot->hardStop();
        state = FROM_BASKET;
        gateServo.write(GATE_OPEN_ANGLE); /* Open the gate to let balls into the basket */
        delay(2000);
        gateServo.write(GATE_CLOSE_ANGLE);
        state = FROM_BASKET;
        robot->moveBackward(LEFT_SPEED, RIGHT_SPEED + 2);
      }

    } else if(rightDistance > (RIGHT_DISTANCE - DRIFT_MARGIN) && rightDistance < (RIGHT_DISTANCE + DRIFT_MARGIN)){
      #ifdef DEBUG
        Serial.print(0);
      #endif
      
      /* Robot is centered along black tape */
      
    } else if(rightDistance < (RIGHT_DISTANCE - DRIFT_MARGIN)){
      /* too close to the right wall, so turn left and then straighten */
      #ifdef DEBUG
        Serial.print(1);
      #endif
      robot->moveForward(0, RIGHT_SPEED+3);
      delay(170);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      delay(280);
      robot->moveForward(LEFT_SPEED+3,0);
      delay(145);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      
    } else if(rightDistance > (RIGHT_DISTANCE + DRIFT_MARGIN)){
      /* too far from the right wall, so turn right and then straighten */
      #ifdef DEBUG
        Serial.print(2);
      #endif
      robot->moveForward(LEFT_SPEED+2, 0);
      delay(190);
      robot->moveForward(LEFT_SPEED+1, RIGHT_SPEED);
      delay(310);
      robot->moveForward(0,RIGHT_SPEED+2);
      delay(187);
      robot->moveForward(LEFT_SPEED, RIGHT_SPEED);
      
    }
  }
  
  /* Return to the bumper from the basket to collect more balls */
  if(state==FROM_BASKET){
    unsigned int forwardDistance = sonarFront.ping() / US_ROUNDTRIP_CM;
    unsigned int rightDistance = sonarRight.ping() / US_ROUNDTRIP_CM;
    if(forwardDistance > BUMPER_PROXIMITY){
      state = BALL_COLLECTION;
     
    } else if(rightDistance > (RIGHT_DISTANCE - DRIFT_MARGIN) && rightDistance < (RIGHT_DISTANCE + DRIFT_MARGIN)){
      #ifdef DEBUG
        Serial.print(0);
      #endif
      
      /* Robot is centered along black tape */
      
    } else if(rightDistance < (RIGHT_DISTANCE - DRIFT_MARGIN)){
      /* too close to the right wall, so turn left and then straighten */
      #ifdef DEBUG
        Serial.print(1);
      #endif
      robot->moveBackward(0, RIGHT_SPEED+3);
      delay(180);
      robot->moveBackward(LEFT_SPEED, RIGHT_SPEED+2);
      delay(200);
      robot->moveBackward(LEFT_SPEED+3,0);
      delay(150);
      robot->moveBackward(LEFT_SPEED, RIGHT_SPEED+3);
      
    } else if(rightDistance > (RIGHT_DISTANCE + DRIFT_MARGIN)){
      /* too far from the right wall, so turn right and then straighten */
      #ifdef DEBUG
        Serial.print(2);
      #endif
      robot->moveBackward(LEFT_SPEED+3, 0);
      delay(180);
      robot->moveBackward(LEFT_SPEED, RIGHT_SPEED+2);
      delay(200);
      robot->moveBackward(0,RIGHT_SPEED+3);
      delay(190);
      robot->moveBackward(LEFT_SPEED, RIGHT_SPEED+4);
      
    }
  }
  
  

}
