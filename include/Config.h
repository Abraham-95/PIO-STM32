#pragma once
#include "stm32f4xx_hal.h"

#define LOOP_PERIOD 8000
#define TIME_TO_STANDBY 30000
/*
  =================== Motor Pin Config ====================
  Motor         | RPWM (TIM1)     | LPWM (TIM8)     | EN  |
  =========================================================
  Front Left    | TIM1_CH1 → PE9  | TIM8_CH1 → PC6  | PD0 |
  Front Right   | TIM1_CH2 → PE11 | TIM8_CH2 → PC7  | PD1 |
  Rear Left     | TIM1_CH3 → PE13 | TIM8_CH3 → PC8  | PD2 |
  Rear Right    | TIM1_CH4 → PE14 | TIM8_CH4 → PC9  | PD3 |
*/
class MotorDriver {
public:
  MotorDriver(TIM_HandleTypeDef* rpwmTimer, uint32_t rpwmChannel,
              TIM_HandleTypeDef* lpwmTimer, uint32_t lpwmChannel,
              GPIO_TypeDef* enPort, uint16_t enPin);

  void begin();
  void setSpeed(int8_t speed); // -127..127, minus = backward, 0 = stop
  void enable();
  void disable();

private:
  TIM_HandleTypeDef* rpwmTimer;
  uint32_t rpwmChannel;
  TIM_HandleTypeDef* lpwmTimer;
  uint32_t lpwmChannel;
  GPIO_TypeDef* enPort;
  uint16_t enPin;

  static const uint16_t MAX_DUTY = 839; // ARR timer CubeMX
};
