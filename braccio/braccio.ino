#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {
  Braccio.begin();

  Serial.begin(9600);
  //pwm.begin();
  //pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(1000);
}

void loop() {

  //pwm.setPWM(0, 0, 460);
  Braccio.ServoMovement(20, 0, 15, 180, 170, 0,  73);  
  delay(1000);

  //pwm.setPWM(0, 0, 320);
  Braccio.ServoMovement(20, 180, 165, 0, 0, 180,  10);  
  delay(1000);
}
