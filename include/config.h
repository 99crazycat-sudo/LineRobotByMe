#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

constexpr float WHEEL_DIAMETER = 60.0f;
constexpr int   IMP_PER_ROTATE = 491;

constexpr float WHEEL_CIRCUMFERENCE = PI * WHEEL_DIAMETER;
constexpr float MM_PER_IMP          = WHEEL_CIRCUMFERENCE / IMP_PER_ROTATE;

constexpr float STOP_THRESHOLD_MM  = 3.0f;
constexpr long  STOP_THRESHOLD_IMP = (long)(STOP_THRESHOLD_MM / MM_PER_IMP);

// ============================================================
// ПИД-регулятор.
// Используется в моторах и в LineController.
// ============================================================
struct pid_cfg_t {
    float kp;
    float ki;
    float kd;
    float min_out;
    float max_out;
};

// ============================================================
// Мотор.
// Содержит всё про один мотор, включая его ПИД.
// ============================================================
struct motor_cfg_t {
    uint8_t pin_in1;
    uint8_t pin_in2;
    uint8_t pin_en;
    uint8_t pin_enc_a;
    uint8_t pin_enc_b;
    bool    invert;         // true — инвертировать знак энкодера и PWM
    int     max_speed;      // максимальная скорость мотора, мм/с
    uint8_t dead_zone;      // порог PWM мёртвой зоны
    pid_cfg_t pid;          // ПИД этого мотора
};

// ============================================================
// Общая конфигурация.
// ============================================================
struct config_t {
    //motion_cfg_t motion;
    motor_cfg_t  motor_L;
    motor_cfg_t  motor_R;
    //line_cfg_t   line;
};

// Геттер доступа к конфигу.
extern config_t& GetConfig(void);

#endif