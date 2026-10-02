#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  public:
    Motor(int pinIN1, int pinIN2, int pinEN, bool reverse);

    void begin();
    void setSpeed(int speed);
    void stop();

    bool stopFor(unsigned long ms);

    bool driveFor(int speed, unsigned long ms);

  private:
    int  _pinIN1;
    int  _pinIN2;
    int  _pinEN;
    bool _reverse;

    unsigned long _stopStart;
    unsigned long _stopDur;
    bool          _stopActive;

    unsigned long _driveStart;
    unsigned long _driveDur;
    bool          _driveActive;
};

#endif