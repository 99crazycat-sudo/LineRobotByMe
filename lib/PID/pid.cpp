#include "pid.h"

PID_t::PID_t(pid_cfg_t &ref_conf)
    : conf(ref_conf),
      prev_err(0.0f),
      P(0.0f), I(0.0f), D(0.0f),
      integral(0.0f),
      diff(0.0f),
      out(0.0f) { };

float PID_t::calc(float err, float dt) {
    // ==================== P ====================
    P = err * conf.kp;
    
    // ==================== D ====================
    if (dt > 1e-6f)  {
        diff = (err - prev_err) / dt;
    }
    else  {
        diff = 0.0f;
    }
    D = diff  * conf.kd;

    // ==================== I (текущее значение) ====================
    I = integral * conf.ki;

    // ==================== Проверка насыщения ====================
    // Считаем "пробный" выход без накопления новой порции интеграла.
    float out_try = P + I + D;

    bool sat_high = (out_try >= conf.max_out);
    bool sat_low  = (out_try <= conf.min_out);

    // Интегрируем только если это не уводит выход дальше в насыщение.
    // - при насыщении сверху копим только при err < 0 (интеграл уменьшается)
    // - при насыщении снизу  копим только при err > 0 (интеграл растёт)
    bool allow_integrate = !(sat_high && err > 0.0f) && !(sat_low  && err < 0.0f);

    if (allow_integrate && dt > 1e-6f) {
        integral += err * dt;
        I = integral * conf.ki;
    }


    // ==================== Выход ====================
    out = P + I + D;
    prev_err = err;
    return out;
}

void PID_t::reset() {
    integral = 0.0f;
    prev_err = 0.0f;
    P = 0.0f;
    I = 0.0f;
    D = 0.0f;
 }

