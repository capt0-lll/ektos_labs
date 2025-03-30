#pragma once

#include "stm32f4xx_hal.h"

typedef struct {
  	GPIO_TypeDef *port;
  	uint16_t pin;
  } PinConfig;

void make_single_led_run(const PinConfig* LedPins, const uint8_t number_of_leds);
