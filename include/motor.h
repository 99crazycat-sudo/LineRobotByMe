#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  public:
    Motor(int pinIN1, int pinIN2, int pinEN, bool reverse);

    void begin();
    void setSpeed(int speed);
    void stop();

  private:
    int  _pinIN1;
    int  _pinIN2;
    int  _pinEN;
    bool _reverse;
};

#endif