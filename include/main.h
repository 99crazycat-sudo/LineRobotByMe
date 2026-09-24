#ifndef MAIN_H
#define MAIN_H

// --- Датчики линии ---
#define PIN_R_SENSOR   A3
#define PIN_L_SENSOR   A2

// --- Левый мотор ---
#define PIN_IN1_L       8
#define PIN_IN2_L       7
#define PIN_EN_L        6
//#define PIN_ENC_L_A     2          // фаза A, прерывание
//#define PIN_ENC_L_B     4          // фаза B, направление

// --- Правый мотор ---
#define PIN_IN1_R      10
#define PIN_IN2_R       9
#define PIN_EN_R        5
//#define PIN_ENC_R_A     3          // фаза A, прерывание
//#define PIN_ENC_R_B    11          // фаза B, направление

const int Cross_Trig = 80;
const float Kp = 1.0f;

uint8_t STEP_PRG = 0;

enum State_t : uint8_t {
  LINE = 0,
  //CROSS
};

enum StateLine_t : uint8_t {
  ON_LINE = 0,
  LEFT_G_CROSS,
  RIGHT_G_CROSS,
  CROSS
};

void ReadSensors(void);
StateLine_t Line(int speed);
bool Cross(void);
void StopMotors(void);

#endif