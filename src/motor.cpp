#include "motor.h"
#include "config.h"

Motor::Motor(int pinIN1, int pinIN2, int pinEN,
             bool reverse, bool invertEnc,
             Encoder& encoder)
  : _pinIN1(pinIN1), _pinIN2(pinIN2), _pinEN(pinEN),
    _reverse(reverse), _invertEnc(invertEnc),
    _encoder(encoder),
    _posMode(false), _targetCount(0) {}

void Motor::begin() {
  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
  pinMode(_pinEN,  OUTPUT);
}

void Motor::setSpeed(int speed) {
  if (_reverse) {
    speed = -speed;
  }

  int pwm = constrain(abs(speed), 0, 255);

  if (speed > 0) {
    digitalWrite(_pinIN1, LOW);
    digitalWrite(_pinIN2, HIGH);
  } else if (speed < 0) {
    digitalWrite(_pinIN1, HIGH);
    digitalWrite(_pinIN2, LOW);
  } else {
    digitalWrite(_pinIN1, LOW);
    digitalWrite(_pinIN2, LOW);
  }

  analogWrite(_pinEN, pwm);
}

void Motor::stop() {
  setSpeed(0);
  _posMode = false;
}

long Motor::getEncoderNorm() {
  long c = _encoder.getCount();
  if (_invertEnc) c = -c;
  return c;
}

void Motor::startMove(float mm, int speed) {
  long start   = getEncoderNorm();
  _targetCount = start + (long)(mm / MM_PER_IMP);
  _posMode     = true;

  setSpeed(speed);
}

bool Motor::isDone() {
  if (!_posMode) return true;

  long remaining = _targetCount - getEncoderNorm();

  if (abs(remaining) < STOP_THRESHOLD_IMP) {
    stop();
    return true;
  }

  return false;
}