#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "encoder.h"

class Motor_t {
  public:
    Motor_t(motor_cfg_t& cfg, Encoder_t& encoder);

    void begin(); //Инициализация пинов
    void setSpeed(int speed); //Установка скорости
    void stop(); //Остановка 

    // long getEncoderNorm();
    void update();
    // void Move(float mm, int speed);
    // bool isDone();

  private:
    int _speed;
    long _targetCount;
    Encoder_t& _encoder;
    motor_cfg_t& _conf;
};

#endif