#include "switch_led.h"
#include "pin_config.h"
#include <stdbool.h>

static void switch_led(void);
static bool check_button_pressed(void);


static void switch_led(void)
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
	HAL_Delay(100);
}

void switch_led_on_button_press(void)
{

	 if(check_button_pressed())
	{
		HAL_Delay(20);
		if(check_button_pressed()){
			switch_led();
			while(check_button_pressed())
			{
				HAL_Delay(20);
			}
		}
	}
}

static bool check_button_pressed(void)
{
	const PinConfig button = {.port = S1_GPIO_Port, .pin = S1_Pin};
	return HAL_GPIO_ReadPin(button.port, button.pin) == GPIO_PIN_RESET;
}

