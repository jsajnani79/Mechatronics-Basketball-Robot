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


Bot* robot;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
int state;
int hasPaused;

void setup() {
  Serial.begin(9600);
  robot = new Bot(ENABLE_PIN_LEFT, DIR_PIN_LEFT, ENABLE_PIN_RIGHT, DIR_PIN_RIGHT);
//  robot->turnRight();
  state = 0;
  hasPaused = 1;
  robot->moveForward(65,65);
}

void loop() {
//  delay(2000);
//  robot->makeSquare();

//  delay(50);
//  if(state==1){
//    unsigned int uS = sonar.ping();
//    if((uS / US_ROUNDTRIP_CM) < 30){
//      state = 0;
//      robot->moveBackward(65,65);
//    }
//  }else{
//    unsigned int uS = sonar.ping();
//    if((uS / US_ROUNDTRIP_CM) > 200){
//      state = 1;
//      robot->moveForward(65,65);
//    }
//  }

//0 = bumper side
//1 = moving towards goal on long stretch
//2 = goal side
//3 = moving towards bumper on long stretch
  delay(50);
  Serial.println(state);
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  delay(50);
  if(state==0){
    unsigned int uS = sonar.ping();
    if((uS / US_ROUNDTRIP_CM) < 13){
      robot->turnRight();
      while(!robot->hasFinishedRightTurn()){
        delay(5);
      }
      robot->stop();
      robot->moveForward(65,65);
      state = 1;
    }
  }else if(state == 1){
    unsigned int uS = sonar.ping();
    if((uS / US_ROUNDTRIP_CM) < 13){
      robot->turnRight();
      while(!robot->hasFinishedRightTurn()){
        delay(5);
      }
      robot->stop();
      robot->moveForward(30,30);
      state = 2;
    }
  }else if(state == 2){
    unsigned int uS = sonar.ping();
    if(hasPaused == 0){
      if((uS / US_ROUNDTRIP_CM) < 62){
        robot->stop();
        delay(3000);
        robot->moveForward(65,65);
      }
    }else{
       if((uS / US_ROUNDTRIP_CM) < 13){
        robot->turnRight();
        while(!robot->hasFinishedRightTurn()){
          delay(5);
        }
        robot->stop();
        robot->moveForward(65,65);
        state = 3;
      }
    }
  }else if(state == 3){
    unsigned int uS = sonar.ping();
    if((uS / US_ROUNDTRIP_CM) < 13){
      robot->turnRight();
      while(!robot->hasFinishedRightTurn()){
        delay(5);
      }
      robot->stop();
      robot->moveForward(65,65);
      state = 0;
    }
  }      

  
//  if (robot->hasFinishedRightTurn()) {
//    robot->stop();
//    Serial.println("stopping");
//  }

  //ULTRASOUND
//  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
//  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
//  Serial.print("Ping: ");
//  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
//  Serial.println("cm");
  
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



