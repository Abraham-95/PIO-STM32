#include "Mode.h"
#include "Utility.h"
#include "Config.h"

TIM_HandleTypeDef htim1, htim3;
MotorDriver motorFL(&htim1, TIM_CHANNEL_1, &htim3, TIM_CHANNEL_1, GPIOD, GPIO_PIN_0);
MotorDriver motorFR(&htim1, TIM_CHANNEL_2, &htim3, TIM_CHANNEL_2, GPIOD, GPIO_PIN_1);
MotorDriver motorRL(&htim1, TIM_CHANNEL_3, &htim3, TIM_CHANNEL_3, GPIOD, GPIO_PIN_2);
MotorDriver motorRR(&htim1, TIM_CHANNEL_4, &htim3, TIM_CHANNEL_4, GPIOD, GPIO_PIN_3);

void CarMode::init() {
  USB_Printf("Car Mode Initialized");
  motorFL.begin(); motorFR.begin(); motorRL.begin(); motorRR.begin();
}

void CarMode::loop() {
  static uint32_t lastPhaseChange = 0; static uint8_t phase = 0;
  const uint32_t phaseDuration[] = {3000, 1000, 3000, 1000};
  const int8_t phaseSpeed[] = {80, 0, -80, 0};

  if (millis() - lastPhaseChange >= phaseDuration[phase]) {
    lastPhaseChange = millis(); phase = (phase + 1) % 4;
    USB_Printf("Motor FL phase %d, speed %d\r\n", phase, phaseSpeed[phase]);
  }
  motorFL.setSpeed(phaseSpeed[phase]);
}

void CarMode::exit() {
}
