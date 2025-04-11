#include <running_led.h>

#include <stdbool.h>

static void make_pause_on_button_press(void);
static bool button_pressed(void);

void make_single_led_run(void)
{
	static const PinConfig leds [] = {
		{.port = D2_GPIO_Port, .pin = D2_Pin},
		{.port = D3_GPIO_Port, .pin = D3_Pin},
		{.port = D4_GPIO_Port, .pin = D4_Pin},
	  };

	static const uint8_t number_of_leds = sizeof(leds)/sizeof(leds[0]);

	for(uint8_t i = 0; i < number_of_leds; i++)
	{
		make_pause_on_button_press();
		PinConfig current_led = leds[i];
		PinConfig previous_led = (i == 0) ? leds[number_of_leds - 1] : leds[i - 1];

		HAL_GPIO_WritePin(current_led.port, current_led.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(previous_led.port, previous_led.pin, GPIO_PIN_SET);

		HAL_Delay(500);
	}

}

static void make_pause_on_button_press(void)
{
	static const uint8_t debounce_delay = 20;
	const uint32_t start_time = HAL_GetTick();
	while(button_pressed() || HAL_GetTick() - start_time < debounce_delay)
	{

	}
}

static bool button_pressed(void)
{
	static const PinConfig button = {.port = S1_GPIO_Port, .pin = S1_Pin};
	return !HAL_GPIO_ReadPin(button.port, button.pin);
}
