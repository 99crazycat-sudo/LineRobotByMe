#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class LineSensor {
  public:
    LineSensor(int pin, int mapMin, int mapMax, int outMin, int outMax);

    void begin();
    int  read();

  private:
    int _pin;
    int _mapMin;
    int _mapMax;
    int _outMin;
    int _outMax;
};

#endif