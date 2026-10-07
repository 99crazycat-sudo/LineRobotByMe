#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "config.h"

class Encoder_t {
  public:
    Encoder_t(motor_cfg_t conf);

    void begin();
    long getCount();
    void reset();
    void handleInterrupt();

  private:
    volatile long _count;
    motor_cfg_t _conf;
};

#endif