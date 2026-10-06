#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "encoder.h"

class Motor {
  public:
    Motor(int pinIN1, int pinIN2, int pinEN,
          bool reverse, bool invertEnc,
          Encoder& encoder);

    void begin();
    void setSpeed(int speed);
    void stop();

    long getEncoderNorm();

    void startMove(float mm, int speed);
    bool isDone();

  private:
    int  _pinIN1;
    int  _pinIN2;
    int  _pinEN;
    bool _reverse;
    bool _invertEnc;

    Encoder& _encoder;

    bool _posMode;
    long _targetCount;
};

#endif