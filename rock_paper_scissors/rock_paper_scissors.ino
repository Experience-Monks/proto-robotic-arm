/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  250 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  460 // this is the 'maximum' pulse length count (out of 4096)
#define DELAY 1500 

unsigned long topLoop;
typedef void (*hand)();

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(1000);
}

void paper() {
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(0, 0, pulselen + pulselen/2);
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
    pwm.setPWM(3, 0, pulselen);
    pwm.setPWM(4, 0, pulselen);
    pulselen = pulselen + 5;
  }
  delay(DELAY);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(0, 0, pulselen + pulselen/2);
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
    pwm.setPWM(3, 0, pulselen);
    pwm.setPWM(4, 0, pulselen);
  }
  delay(DELAY);
}

void scissors() {
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(3, 0, pulselen);
    pwm.setPWM(4, 0, pulselen);
    pulselen = pulselen + 5;
    
  }
  delay(DELAY);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(3, 0, pulselen);
    pwm.setPWM(4, 0, pulselen);
  }
  delay(DELAY);
}

void rock() {
  delay(DELAY * 2);
}

hand table[3] = {
  [](){ rock(); },
  [](){ paper(); },
  [](){ scissors(); }
};

void loop() {
  static unsigned long lastSecond;
  topLoop = millis();
  if (topLoop - lastSecond >= 1000) {
    lastSecond = topLoop;
    table[random(3)]();
  }
}
