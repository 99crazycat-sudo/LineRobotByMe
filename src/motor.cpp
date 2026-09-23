#include "motor.h"

Motor::Motor(int pinIN1, int pinIN2, int pinEN, bool revers)
  : _pinIN1(pinIN1), _pinIN2(pinIN2), _pinEN(pinEN), _revers(revers) {}

void Motor::begin() {
  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
  pinMode(_pinEN,  OUTPUT);
}

void Motor::setSpeed(int mSpeed, int dir) {
  int _dir = dir * (_revers) ? -1 : 1;
  if (_dir > 0) {
    digitalWrite(_pinIN2, HIGH);
    digitalWrite(_pinIN1, LOW);
    analogWrite(_pinEN, mSpeed);
  } else {
    digitalWrite(_pinIN2, LOW);
    digitalWrite(_pinIN1, HIGH);
    analogWrite(_pinEN, mSpeed);
  }
}

void Motor::stop() {
  setSpeed(0, 1);
}