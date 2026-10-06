#include "encoder.h"

Encoder::Encoder(int pinA, int pinB)
  : _pinA(pinA), _pinB(pinB), _count(0) {}

void Encoder::begin() {
  pinMode(_pinA, INPUT_PULLUP);
  pinMode(_pinB, INPUT_PULLUP);
}

long Encoder::getCount() {
  noInterrupts();
  long c = _count;
  interrupts();
  return c;
}

void Encoder::reset() {
  noInterrupts();
  _count = 0;
  interrupts();
}

void Encoder::handleInterrupt() {
  if (digitalRead(_pinB) == HIGH) {
    _count++;
  } else {
    _count--;
  }
}