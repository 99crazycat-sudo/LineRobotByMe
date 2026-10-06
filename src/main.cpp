#include <Arduino.h>
#include "motor.h"
#include "sensor.h"
#include "encoder.h"
#include "config.h"
#include "main.h"

Encoder encoderL(PIN_ENC_L_A, PIN_ENC_L_B);
Encoder encoderR(PIN_ENC_R_A, PIN_ENC_R_B);

Motor motorL(PIN_IN1_L, PIN_IN2_L, PIN_EN_L, false, true,  encoderL);
Motor motorR(PIN_IN1_R, PIN_IN2_R, PIN_EN_R, true,  false, encoderR);

LineSensor sensorL(PIN_L_SENSOR, 40, 440, 0, 100);
LineSensor sensorR(PIN_R_SENSOR, 50, 350, 0, 100);

const int   Cross_Trig = 70;
const float Kp         = 1.0f;

void isrEncoderL() { encoderL.handleInterrupt(); }
void isrEncoderR() { encoderR.handleInterrupt(); }

void setup() {
  Serial.begin(115200);

  sensorR.begin();
  sensorL.begin();

  encoderL.begin();
  encoderR.begin();

  motorL.begin();
  motorR.begin();

  attachInterrupt(digitalPinToInterrupt(PIN_ENC_L_A), isrEncoderL, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_R_A), isrEncoderR, RISING);

  Serial.println("start");
  delay(2000);

  motorL.startMove(200.0f, 100);
  motorR.startMove(200.0f, 100);

  while (!motorL.isDone() || !motorR.isDone()) {
  }

  Serial.print("L="); Serial.print(encoderL.getCount());
  Serial.print(" R="); Serial.println(encoderR.getCount());
  Serial.println("finished");
}

void loop() {
}

StateLine_t Line(int speed) {
  int sensorLdata = sensorL.read();
  int sensorRdata = sensorR.read();

  StateLine_t State_return;

  if ((sensorLdata > Cross_Trig) && (sensorRdata > Cross_Trig)) {
    State_return = CROSS;
  }
  else if ((sensorLdata > Cross_Trig) && (sensorRdata < Cross_Trig)) {
    State_return = LEFT_G_CROSS;
  }
  else if ((sensorRdata > Cross_Trig) && (sensorLdata < Cross_Trig)) {
    State_return = RIGHT_G_CROSS;
  }
  else {
    State_return = LOST_LINE;
  }

  int err = (sensorLdata - sensorRdata);
  int SpeedL = (speed - err) * Kp;
  int SpeedR = (speed + err) * Kp;
  motorL.setSpeed(SpeedL);
  motorR.setSpeed(SpeedR);

  return State_return;
}

void StopMotors(void) {
  motorL.stop();
  motorR.stop();
}