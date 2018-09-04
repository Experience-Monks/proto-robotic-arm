#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define FINGER_MIN 320
#define FINGER_MAX 460
#define DELAY 2500

unsigned long timer;
unsigned long interval;
unsigned int fingers;

float angle = 0;
float val = 0;
float pulselen = 0;
float moveSpeed = 0;

void setup() {
  interval = FINGER_MAX - FINGER_MIN;
  fingers = 5;
  moveSpeed = 0.2;

  Serial.begin(9600);
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(1000);
}

void loop() {
  timer = millis();

  angle = (timer * moveSpeed) * PI / 180;
  for (uint8_t f=0; f < fingers; f++) {
    pulselen = FINGER_MIN + (interval * sin(angle + (f * 0.5)));
    pwm.setPWM(f, 0, pulselen);
  }
  
  //pulselen = FINGER_MIN + (interval * sin(angle + (0 * 0.5)));
  //pwm.setPWM(0, 0, pulselen);
  
  //for (uint16_t p = 0; p < 4096; p++) {
    //pwm.setPWM(3, 0, p);
  //}
  
  //delay(1000);
  //pwm.setPWM(15, 0, FINGER_MAX);
}
