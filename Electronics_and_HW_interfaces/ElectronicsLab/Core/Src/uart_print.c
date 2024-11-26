#include "uart_print.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"

UART_HandleTypeDef huart2;

void UartInit()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 38400;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		__disable_irq();
		while(1)
		{
			// Error
		}
	}
}

void UartPrint(char *msg, uint16_t size)
{
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, size, HAL_MAX_DELAY);
}
