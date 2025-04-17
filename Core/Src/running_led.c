#include "running_led.h"
#include "pin_config.h"

void make_single_led_run()
{
	static const PinConfig leds [] = {
		{.port = D2_GPIO_Port, .pin = D2_Pin},
		{.port = D3_GPIO_Port, .pin = D3_Pin},
		{.port = D4_GPIO_Port, .pin = D4_Pin},
	  };

	static const uint8_t number_of_leds = sizeof(leds)/sizeof(leds[0]);

	for(uint8_t i = 0; i < number_of_leds; i++)
	{
		const PinConfig *current_led = &leds[i];
		const PinConfig *previous_led = (i == 0) ? &leds[number_of_leds - 1] : & leds[i - 1];

		HAL_GPIO_WritePin(current_led->port, current_led->pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(previous_led->port, previous_led->pin, GPIO_PIN_SET);
		HAL_Delay(500);
	}

}
