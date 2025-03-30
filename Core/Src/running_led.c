#include <running_led.h>

void make_single_led_run(const PinConfig* _led_pins, const uint8_t number_of_leds)
{
	for(uint8_t i = 0; i < number_of_leds; i++)
	{
		PinConfig current_led = _led_pins[i];
		PinConfig previous_led;
		if(i == 0)
		{
			previous_led = _led_pins[number_of_leds - 1];
		}
		else
		{
			previous_led = _led_pins[i - 1];
		}
		HAL_GPIO_WritePin(current_led.port, current_led.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(previous_led.port, previous_led.pin, GPIO_PIN_SET);
		HAL_Delay(500);
	}

}
