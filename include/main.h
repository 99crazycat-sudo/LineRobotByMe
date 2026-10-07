#ifndef MAIN_H
#define MAIN_H

#define PIN_R_SENSOR   A3
#define PIN_L_SENSOR   A2

#define PIN_IN1_L       8
#define PIN_IN2_L       7
#define PIN_EN_L        6
#define PIN_ENC_L_A     2
#define PIN_ENC_L_B     4

#define PIN_IN1_R      10
#define PIN_IN2_R       9
#define PIN_EN_R        5
#define PIN_ENC_R_A     3
#define PIN_ENC_R_B    11

enum StateLine_t : uint8_t {
  ON_LINE = 0,
  LEFT_G_CROSS,
  RIGHT_G_CROSS,
  CROSS,
  LOST_LINE
};

StateLine_t Line(int speed);
void StopMotors(void);
void SetDefConf(void);

#endif