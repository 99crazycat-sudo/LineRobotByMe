//pid.h
#ifndef PID_H // include guard
#define PID_H

#include "Arduino.h"
#include "config.h"


class PID_t {
private:
    pid_cfg_t &conf;  // ссылка на структуру PID_t регулятора

    // Локальные поля для внутренней логики ПИД
    float prev_err; // предыдущая ошибка
    float P, I, D;
    float integral;       // интегральная ошибка
    float diff;     // скорость изменения ошибки
    float out;         // pid

public:
    PID_t(pid_cfg_t &ref_conf);
    float calc(float err, float dt);
    void reset();
      
};

#endif /* PID_H */

