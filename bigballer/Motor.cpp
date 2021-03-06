/*---------------- Includes ---------------------------------*/
#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif
#include "Motor.h"

/*---------------- Module Function Prototypes ---------------*/

/*---------------- Module Functions -------------------------*/
Motor::Motor(unsigned char enable, unsigned char dir){
  enablePin = enable;
  dirPin = dir;
  pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  state = STOPPED;
  digitalWrite(enablePin, LOW);
}

void Motor::moveForward(int dutyCycle) {
  if (state == STOPPED) {
    digitalWrite(enablePin, HIGH);
    state = MOVING;
  }
  
  analogWrite(dirPin, map(dutyCycle, 0, 100, 128, 255));
}

void Motor::moveBackward(int dutyCycle) {
  if (state == STOPPED) {
    digitalWrite(enablePin, HIGH);
    state = MOVING;
  }
  
  analogWrite(dirPin, map(dutyCycle, 0, 100, 127, 0));
}

void Motor::stop() {
  if (state == MOVING) {
    digitalWrite(enablePin, LOW);
    state = STOPPED;
  }
}

motorState Motor::getState() {
  return state;
}

void Motor::test() {
  Serial.println("100 forward");
  moveForward(100);
  delay(2000);

  Serial.println("stopped");
  stop();
  delay(2000);

  Serial.println("100 backward");
  moveBackward(100);
  delay(2000);
  
  Serial.println("0 forward");
  moveForward(0);
  delay(2000);
  
  Serial.println("0 backward");
  moveBackward(0);
  delay(2000);
}
