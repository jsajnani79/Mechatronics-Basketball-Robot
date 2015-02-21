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
#define MAX_DISTANCE 30 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


Bot* robot;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
void setup() {
  Serial.begin(9600);
  robot = new Bot(ENABLE_PIN_LEFT, DIR_PIN_LEFT, ENABLE_PIN_RIGHT, DIR_PIN_RIGHT);
  robot->turnRight();
}

void loop() {
  if (robot->hasFinishedRightTurn()) {
    robot->stop();
    Serial.println("stopping");
  }
  
  //ULTRASOUND
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
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



