#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

constexpr float WHEEL_DIAMETER = 60.0f;
constexpr int   IMP_PER_ROTATE = 491;

constexpr float WHEEL_CIRCUMFERENCE = PI * WHEEL_DIAMETER;
constexpr float MM_PER_IMP          = WHEEL_CIRCUMFERENCE / IMP_PER_ROTATE;

constexpr float STOP_THRESHOLD_MM  = 3.0f;
constexpr long  STOP_THRESHOLD_IMP = (long)(STOP_THRESHOLD_MM / MM_PER_IMP);

#endif