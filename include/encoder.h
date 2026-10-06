#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
  public:
    Encoder(int pinA, int pinB);

    void begin();
    long getCount();
    void reset();
    void handleInterrupt();

  private:
    int _pinA;
    int _pinB;
    volatile long _count;
};

#endif