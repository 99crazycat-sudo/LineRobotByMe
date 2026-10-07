#include <Arduino.h>
#include "motor.h"
#include "sensor.h"
#include "encoder.h"
#include "config.h"
#include "main.h"

config_t config;

config_t& GetConfig(void){
  return config;
}

Encoder_t encoderL(GetConfig().motor_L);
Encoder_t encoderR(GetConfig().motor_R);

Motor_t motorL(GetConfig().motor_L, encoderL);
Motor_t motorR(GetConfig().motor_R, encoderR);

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

  motorL.Move(200.0f, 100);
  motorR.Move(200.0f, 100);

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

void SetDefConf(void) {
  //L motor
  config.motor_L.pin_in1 = PIN_IN1_L;
  config.motor_L.pin_in2 = PIN_IN2_L;
  config.motor_L.pin_en = PIN_EN_L;
  config.motor_L.pin_enc_a = PIN_ENC_L_A;
  config.motor_L.pin_enc_b = PIN_ENC_L_B;
  config.motor_L.invert = false;
  config.motor_L.max_speed = 255;
  config.motor_L.pid.kp = 1.0f;
  config.motor_L.pid.ki = 0.0f;
  config.motor_L.pid.kd = 0.0f;
  //R motor
  config.motor_R.pin_in1 = PIN_IN1_R;
  config.motor_R.pin_in2 = PIN_IN2_R;
  config.motor_R.pin_en = PIN_EN_R;
  config.motor_R.pin_enc_a = PIN_ENC_R_A;
  config.motor_R.pin_enc_b = PIN_ENC_R_B;
  config.motor_R.invert = true;
  config.motor_R.max_speed = 255;
  config.motor_R.pid.kp = 1.0f;
  config.motor_R.pid.ki = 0.0f;
  config.motor_R.pid.kd = 0.0f;
}

// #define PIN_IN1_L       8
// #define PIN_IN2_L       7
// #define PIN_EN_L        6
// #define PIN_ENC_L_A     2
// #define PIN_ENC_L_B     4

// #define PIN_IN1_R      10
// #define PIN_IN2_R       9
// #define PIN_EN_R        5
// #define PIN_ENC_R_A     3
// #define PIN_ENC_R_B    11