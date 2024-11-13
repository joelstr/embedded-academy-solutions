#include "button_toggle.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"

#include "blink.h"

void ButtonToggle()
{
	static uint8_t buttonPressed = 0;
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && !buttonPressed)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		ResetTimer();
	}
	buttonPressed = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
}
