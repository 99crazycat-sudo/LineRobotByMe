#include "motor.h"
#include "config.h"

Motor_t::Motor_t(motor_cfg_t& cfg, Encoder_t& encoder)
  : _conf(cfg),
    _encoder(encoder), 
    _targetCount(0) {}

void Motor_t::begin() {
  pinMode(_conf.pin_in1, OUTPUT);
  pinMode(_conf.pin_in2, OUTPUT);
  pinMode(_conf.pin_en,  OUTPUT);
}

void Motor_t::setSpeed(int speed) {
  _speed = speed;
}

void Motor_t::stop() {
  setSpeed(0);
}

void Motor_t::update(){
  if (_conf.invert) {
    _speed = -_speed;
  }

  uint8_t pwm = constrain(abs(_speed), 0, _conf.max_speed);

  if (_speed > 0) {
    digitalWrite(_conf.pin_in1, LOW);
    digitalWrite(_conf.pin_in2, HIGH);
  } else if (_speed < 0) {
    digitalWrite(_conf.pin_in1, HIGH);
    digitalWrite(_conf.pin_in2, LOW);
  } else {
    digitalWrite(_conf.pin_in1, LOW);
    digitalWrite(_conf.pin_in2, LOW);
  }

  analogWrite(_conf.pin_en, pwm);
}

// long Motor_t::getEncoderNorm() {
//   long c = _encoder.getCount();
//   if (_conf.invert) c = -c;
//   return c;
// }

// void Motor_t::Move(float mm, int speed) {
//   long start   = getEncoderNorm();
//   _targetCount = start + (long)(mm / MM_PER_IMP);

//   setSpeed(speed);
// }

// bool Motor_t::isDone() {
//   if (!_posMode) return true;

//   long remaining = _targetCount - getEncoderNorm();

//   if (abs(remaining) < STOP_THRESHOLD_IMP) {
//     stop();
//     return true;
//   }

//   return false;
// }