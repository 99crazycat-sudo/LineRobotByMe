#include <Arduino.h>
#include "motor.h"
#include "sensor.h"

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

Motor motorL(PIN_IN1_L, PIN_IN2_L, PIN_EN_L, false);
Motor motorR(PIN_IN1_R, PIN_IN2_R, PIN_EN_R, true);

LineSensor sensorL(PIN_L_SENSOR, 40, 440, 0, 100);
LineSensor sensorR(PIN_R_SENSOR, 50, 350, 0, 100);

int GoalSpeed = 100;
const int Cross_Trig = 70;
const float Kp = 1.0f;

enum State : int {
  LINE = 0,
  CROSS
};

State status = LINE;

void ReadSensors(void);
void Line(void);
bool Cross(void);
void StopMotors(void);
void SetSpeedL(int mSpeed, int dirL);
void SetSpeedR(int mSpeed, int dirR);

void setup() {
  Serial.begin(115200);
  sensorR.begin();
  sensorL.begin();
  motorL.begin();
  motorR.begin();
}

void loop() {
  switch (status) {
    case LINE:
      if (Cross()) {
        StopMotors();
        status = CROSS;
      } else {
        Line();
      }
      break;

    case CROSS:
      break;
  }
}

void Line(void) {
  int err = (sensorL.read() - sensorR.read());
  int SpeedL = (GoalSpeed - err) * Kp;
  int SpeedR = (GoalSpeed + err) * Kp;

  motorL.setSpeed(SpeedL);
  motorR.setSpeed(SpeedR);
}

bool Cross(void) {
  return (sensorL.read() > Cross_Trig) && (sensorR.read() > Cross_Trig);
}

void StopMotors(void) {
  motorL.stop();
  motorR.stop();
}


// bool prev_in;
// prev_in = 0;
// bool out;
// bool R_Ttrig(bool in) {
//   if (!prev_in && in ) {
//     out = true;
//   }
//   prev_in = in;
//   return out;
// };
