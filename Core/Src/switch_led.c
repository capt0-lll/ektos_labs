#include "switch_led.h"
#include "pin_config.h"

static char read_button(void);

void switch_led(void)
{
	static uint8_t led_number = 0;

	static const PinConfig leds [] = {
		{.port = D2_GPIO_Port, .pin = D2_Pin},
		{.port = D3_GPIO_Port, .pin = D3_Pin},
		{.port = D4_GPIO_Port, .pin = D4_Pin},
	  };

	static const uint8_t number_of_leds = sizeof(leds)/sizeof(leds[0]);

	const PinConfig *current_led = &leds[led_number];
	const PinConfig *previous_led = (led_number == 0) ? &leds[number_of_leds - 1] : &leds[led_number - 1];

	HAL_GPIO_WritePin(current_led->port, current_led->pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(previous_led->port, previous_led->pin, GPIO_PIN_SET);

	led_number = (led_number + 1) % number_of_leds;
}

void switch_led_on_button_press(void)
{

	if(read_button())
	{
		HAL_Delay(30);
		if(read_button()){
			switch_led();
			while(read_button())
			{
				HAL_Delay(20);
			}
		}
	}
}

static char read_button(void)
{
	PinConfig button = {.port = S1_GPIO_Port, .pin = S1_Pin};
	char result = HAL_GPIO_ReadPin(button.port, button.pin) == GPIO_PIN_SET;
	return result;
}

