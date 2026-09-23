#include <Arduino.h>
#include "motor.h"

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

Motor motorL(PIN_IN1_L, PIN_IN2_L, PIN_EN_L);
Motor motorR(PIN_IN2_R, PIN_IN1_R, PIN_EN_R);

int RSensData;
int LSensData;
int GoalSpeed = 50;
int DirL = 1;
int DirR = 1;
const int Cross_Trig = 70;
const float Kp = 1.0f;

enum State : int {
  LINE = 0,
  CROSS
};

State status = LINE;

void ReadSensors(void);
bool Line(void);
bool Cross(void);
void StopMotors(void);
void SetSpeedL(int mSpeed, int dirL);
void SetSpeedR(int mSpeed, int dirR);

void SetSpeedL(int mSpeed, int dirL){
  if (dirL > 0){
    digitalWrite(PIN_IN2_L, HIGH);
    digitalWrite(PIN_IN1_L, LOW);
    analogWrite(PIN_EN_L, mSpeed);
  } else{
    digitalWrite(PIN_IN2_L, LOW);
    digitalWrite(PIN_IN1_L, HIGH);
    analogWrite(PIN_EN_L, mSpeed);
  }
}

void SetSpeedR(int mSpeed, int dirR){
  if (dirR > 0){
    digitalWrite(PIN_IN2_R, LOW);
    digitalWrite(PIN_IN1_R, HIGH);
    analogWrite(PIN_EN_R, mSpeed);
  } else{
    digitalWrite(PIN_IN2_R, HIGH);
    digitalWrite(PIN_IN1_R, LOW);
    analogWrite(PIN_EN_R, mSpeed);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_R_SENSOR, INPUT);
  pinMode(PIN_L_SENSOR, INPUT);
  motorL.begin();
  motorR.begin();
}

void loop() {
  ReadSensors();

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

void ReadSensors(void) {
  RSensData = map(analogRead(PIN_R_SENSOR), 50, 350, 0, 100);
  LSensData = map(analogRead(PIN_L_SENSOR), 40, 440, 0, 100);
}

bool Line(void){
  int err = (LSensData - RSensData);
  int SpeedL = (GoalSpeed - err) * Kp;
  int SpeedR = (GoalSpeed + err) * Kp;
  SpeedL = (SpeedL > 255)? 255 : SpeedL;
  SpeedR = (SpeedR > 255)? 255 : SpeedR;
  if (SpeedL < 0){
    motorL.setSpeed(abs(SpeedL), 0);
  } else{
    motorL.setSpeed(abs(SpeedL), 1);
  }
  if (SpeedR < 0){
    motorR.setSpeed(abs(SpeedR), 0);
  } else{
    motorR.setSpeed(abs(SpeedR), 1);
  }
  return true;
}

bool Cross(void) {
  return (RSensData > Cross_Trig) && (LSensData > Cross_Trig);
}

void StopMotors(void) {
  motorL.setSpeed(0, 1);
  motorR.setSpeed(0, 1);
}