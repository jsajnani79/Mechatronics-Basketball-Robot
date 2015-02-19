/*---------------- Includes ---------------------------------*/
#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif
#include "Motor.h"

/*---------------- Module Function Prototypes ---------------*/


/*---------------- Arduino Main Functions -------------------*/
// void setup() {
//   Serial.begin(9600);

//   digitalWrite(motorA.enablePin, HIGH);
// }

// void loop() {
  
//   if (Serial.available()) {
//     Serial.read();
//     digitalWrite(motorA.enablePin, LOW);
//   }
    
//     double dutyCycle = 0;
//     int motorSpeed = dutyCycle * 255;
//     Serial.print("Motor Speed: ");
//     Serial.println(motorSpeed);
//     Serial.print("Enable Status: ");
//     Serial.println(digitalRead(motorA.enablePin));
//     analogWrite(motorA.dirPin, motorSpeed);
// }

/*---------------- Module Functions -------------------------*/

Motor::Motor(unsigned char enable, unsigned char dir){
  enablePin = enable;
  dirPin = dir;
  pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void Motor::moveForward(int dutyCycle) {
  digitalWrite(motorA.enablePin, HIGH);
  analogWrite(dirPin, (dutyCycle * 255) / 100);
}

void Motor::reverse() {
  analogWrite(dirPin, 0);
}

void Motor::stop() {
  digitalWrite(motorA.enablePin, LOW);
}
