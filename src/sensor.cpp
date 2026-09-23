#include "sensor.h"

LineSensor::LineSensor(int pin, int mapMin, int mapMax, int outMin, int outMax)
  : _pin(pin),
    _mapMin(mapMin), _mapMax(mapMax),
    _outMin(outMin), _outMax(outMax) {}

void LineSensor::begin() {
  pinMode(_pin, INPUT);
}

int LineSensor::read() {
  return map(analogRead(_pin), _mapMin, _mapMax, _outMin, _outMax);
}