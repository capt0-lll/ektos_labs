#pragma once

#include <main.h>

typedef struct {
  	GPIO_TypeDef *port;
  	uint16_t pin;
  } PinConfig;

void make_single_led_run(void);
