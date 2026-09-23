#include "motor.h"

Motor::Motor(int pinIN1, int pinIN2, int pinEN, bool reverse)
  : _pinIN1(pinIN1), _pinIN2(pinIN2), _pinEN(pinEN), _reverse(reverse) {}

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
}