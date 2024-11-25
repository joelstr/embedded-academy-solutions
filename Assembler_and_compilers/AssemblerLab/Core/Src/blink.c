#include "blink.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"

const int32_t TOGGLE_TIME = 10000; // [ms]

static uint32_t ticks = 0;
static int32_t ToggleLed();

void BlinkLed()
{
	if(ToggleLed())
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
	}
}


static int32_t ToggleLed()
{
    int32_t toggle = 0; // Set to non-zero if we should toggle the led

	asm(
		"       mov r1, %[ticks]    	\n\t"
		"		add r3, r1, #1			\n\t"
		" 		cmp r3, %[TOGGLE_TIME] 	\n\t"
		" 		ble .jump 				\n\t"
		"		mov %[toggle], #1		\n\t"
		"		mov %[ticks], #0		\n\t"
		"		b .end					\n\t"
		"	.jump:						\n\t"
		"       mov %[ticks], r3    	\n\t"
		"		mov %[toggle], #0		\n\t"
		"	.end:						\n\t"
		: [ticks] "+r" (ticks),
		  [toggle] "=r" (toggle)
		: [TOGGLE_TIME] "r" (TOGGLE_TIME)
	);

    return toggle;
}


void ResetTimer()
{
	ticks = 0;
}

