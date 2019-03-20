//BALLROTATION by Michelle//

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

bool sensor_passed = false;
#define METAL_DETECTED 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor_ball = digitalRead(5);
  int sensor_motor = digitalRead(6);

  if (sensor_motor != METAL_DETECTED) {    //no metal detected
    pwm.setPWM(0, 1024, 3072);   //move the inner disc at a certain speed
  }
  else {    // here, sensor_motor is detecting metal
    if (sensor_ball == METAL_DETECTED) { //metal is detected
      sensor_passed = true;
      while (sensor_passed == true) {
        pwm.setPWM(0, 1024, 3072);
        delay(400);   //move motor outside of range of sensor_ball
        Serial.println("Delay ran");
        if (sensor_motor == METAL_DETECTED) {    //this will check if the disc has moved a full rotation
          sensor_passed = false;
        }
      }
      pwm.setPWM(0, 0, 4096);
    }
    else {
      pwm.setPWM(0, 0, 4096);
    }
  }
}

