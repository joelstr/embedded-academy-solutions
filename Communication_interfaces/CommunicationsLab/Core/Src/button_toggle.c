#include "button_toggle.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <uart_com.h>

#include "blink.h"

static void SendHeartbeat();

#define ON_THRESHOLD 2000 // [mV]
#define HIGH_ERROR_LIMIT 3000 // [mV]
#define ADREF 3300 // [mV]

uint8_t UartMsg[20];

void ButtonToggle()
{
	int16_t command = 0;
	int16_t value = 0;
	SendHeartbeat();
	UartRecieve(UartMsg, 20);
	if (UartMsg[0] != 0)
	{
		command = atoi((char*)UartMsg);
		int16_t i = 0;
		while (UartMsg[i] != '\t')
		{
			i++;
		}
		value = atoi((char*) &UartMsg[i+1]);
	}
	if (command == 2001)
	{
		SetToggleTime((uint16_t) value);
	}
	else if (command == 2002)
	{
		if (value)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
			ResetTimer();
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
			ResetTimer();
		}
	}

}

static void SendHeartbeat()
{
	char msg[10] = "1001\n";

	UartPrint(msg, strlen(msg));

}

