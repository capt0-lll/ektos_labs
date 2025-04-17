#include "display_binary_led.h"
#include "pin_config.h"

static GPIO_PinState determine_single_led_state(const uint8_t number, const uint8_t digit);

void display_binary(const uint8_t number)
{
	static const PinConfig leds [] = {
			{.port = D2_GPIO_Port, .pin = D2_Pin},
			{.port = D3_GPIO_Port, .pin = D3_Pin},
			{.port = D4_GPIO_Port, .pin = D4_Pin},
		  };
	static const uint8_t number_of_leds = sizeof(leds)/sizeof(leds[0]);


	for(uint8_t i = 0; i < number_of_leds; i++)
	{
		const GPIO_PinState led_state = determine_single_led_state(number, i);
		HAL_GPIO_WritePin(leds[i].port, leds[i].pin, led_state);
	}
}

static GPIO_PinState determine_single_led_state(const uint8_t number, const uint8_t digit)
{
	const uint8_t number_with_offset = number >> digit;
	const uint8_t mask = 1;
	return ((number_with_offset & mask) != 0) ? GPIO_PIN_RESET : GPIO_PIN_SET;

}
