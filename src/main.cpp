#include <Arduino.h>
#include "motor.h"
#include "sensor.h"
#include "main.h"

Motor motorL(PIN_IN1_L, PIN_IN2_L, PIN_EN_L, false);
Motor motorR(PIN_IN1_R, PIN_IN2_R, PIN_EN_R, true);

LineSensor sensorL(PIN_L_SENSOR, 40, 440, 0, 100);
LineSensor sensorR(PIN_R_SENSOR, 50, 350, 0, 100);

StateLine_t stateLine = ON_LINE;
State_t status = LINE;

void setup() {
  Serial.begin(115200);
  sensorR.begin();
  sensorL.begin();
  motorL.begin();
  motorR.begin();
}

void loop() {
  switch (STEP_PRG)
  {
  case 0:
    if(Line(70) != ON_LINE){
      STEP_PRG = 1;
    } 
    break;
  case 1:
    StopMotors();
    STEP_PRG = 2;
    break;
  }
}

StateLine_t Line(int speed) { 
  StateLine_t State_return;
  uint16_t sensorLdata = sensorL.read();
  uint16_t sensorRdata = sensorR.read();

  if ((sensorLdata > Cross_Trig) && (sensorRdata > Cross_Trig)){
    State_return = CROSS;
  }
  else if ((sensorLdata > Cross_Trig) && (sensorRdata < Cross_Trig)){
    State_return = LEFT_G_CROSS;
  }
  else if ((sensorRdata > Cross_Trig) && (sensorLdata < Cross_Trig)){
    State_return = RIGHT_G_CROSS;
  }

  int err = (sensorLdata - sensorRdata);
  int SpeedL = (speed - err) * Kp;
  int SpeedR = (speed + err) * Kp;
  motorL.setSpeed(SpeedL);
  motorR.setSpeed(SpeedR);

  return State_return;
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
