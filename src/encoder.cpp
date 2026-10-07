#include "encoder.h"

Encoder_t::Encoder_t(motor_cfg_t conf)
  : _conf(conf), _count(0) {}

void Encoder_t::begin() {
  pinMode(_conf.pin_enc_a, INPUT_PULLUP);
  pinMode(_conf.pin_enc_b, INPUT_PULLUP);
}

long Encoder_t::getCount() {
  noInterrupts();
  long c = _count;
  interrupts();
  if (_conf.invert) -c;
  return c;
}

void Encoder_t::reset() {
  noInterrupts();
  _count = 0;
  interrupts();
}

void Encoder_t::handleInterrupt() {
  if (digitalRead(_conf.pin_enc_b) == HIGH) {
    _count++;
  } else {
    _count--;
  }
}