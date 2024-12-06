#include "blink.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"


uint16_t TOGGLE_TIME = 10000; // [ms]

static uint32_t lastToggle = 0;

void BlinkLed()
{
	uint32_t currentTime = HAL_GetTick();
	if (lastToggle + TOGGLE_TIME < currentTime)
	{
		lastToggle = currentTime;
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
	}
}

void ResetTimer()
{
	lastToggle = HAL_GetTick();
}

void SetToggleTime(uint16_t time)
{
	TOGGLE_TIME = time;
}
