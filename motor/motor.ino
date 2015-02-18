#define ENABLE_PIN_A 2
#define DIR_PIN_A 3

struct motor{
  unsigned char enablePin;
  unsigned char dirPin;
  motor(unsigned char enable, unsigned char dir){
    enablePin = enable;
    dirPin = dir;
    pinMode(enablePin, OUTPUT);
    pinMode(dirPin, OUTPUT);
  }
};

motor motorA(ENABLE_PIN_A, DIR_PIN_A);

void setup() {
  Serial.begin(9600);

  digitalWrite(motorA.enablePin, HIGH);
}

void loop() {
  
  if (Serial.available()) {
    Serial.read();
    digitalWrite(motorA.enablePin, LOW);
  }
    
    double dutyCycle = 0;
    int motorSpeed = dutyCycle * 255;
    Serial.print("Motor Speed: ");
    Serial.println(motorSpeed);
    Serial.print("Enable Status: ");
    Serial.println(digitalRead(motorA.enablePin));
    analogWrite(motorA.dirPin, motorSpeed);
}

