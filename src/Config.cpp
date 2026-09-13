#include "Config.h"

MotorDriver::MotorDriver(TIM_HandleTypeDef* rpwmTimer, uint32_t rpwmChannel,
                          TIM_HandleTypeDef* lpwmTimer, uint32_t lpwmChannel,
                          GPIO_TypeDef* enPort, uint16_t enPin)
  : rpwmTimer(rpwmTimer), rpwmChannel(rpwmChannel),
    lpwmTimer(lpwmTimer), lpwmChannel(lpwmChannel),
    enPort(enPort), enPin(enPin) {}

void MotorDriver::begin() {
  HAL_TIM_PWM_Start(rpwmTimer, rpwmChannel);
  HAL_TIM_PWM_Start(lpwmTimer, lpwmChannel);
  enable(); setSpeed(0);
}

void MotorDriver::setSpeed(int8_t speed) {
  if (speed > 0) {
    uint16_t duty = (uint16_t)((int32_t)speed * MAX_DUTY / 127);
    __HAL_TIM_SET_COMPARE(rpwmTimer, rpwmChannel, duty);
    __HAL_TIM_SET_COMPARE(lpwmTimer, lpwmChannel, 0);
  } else if (speed < 0) {
    uint16_t duty = (uint16_t)((int32_t)(-speed) * MAX_DUTY / 127);
    __HAL_TIM_SET_COMPARE(rpwmTimer, rpwmChannel, 0);
    __HAL_TIM_SET_COMPARE(lpwmTimer, lpwmChannel, duty);
  } else {
    __HAL_TIM_SET_COMPARE(rpwmTimer, rpwmChannel, 0);
    __HAL_TIM_SET_COMPARE(lpwmTimer, lpwmChannel, 0);
  }
}

void MotorDriver::enable()  { HAL_GPIO_WritePin(enPort, enPin, GPIO_PIN_SET); }
void MotorDriver::disable() { HAL_GPIO_WritePin(enPort, enPin, GPIO_PIN_RESET); }
