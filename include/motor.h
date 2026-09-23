#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  public:
    Motor(int pinIN1, int pinIN2, int pinEN);

    void begin();
    void setSpeed(int mSpeed, int dir);
    void stop();

  private:
    int _pinIN1;
    int _pinIN2;
    int _pinEN;
};

#endif