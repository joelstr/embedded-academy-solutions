#include "button_toggle.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>

#include "blink.h"
#include "uart_print.h"

static int16_t AdcHigh();

#define ON_THRESHOLD 2000 // [mV]
#define HIGH_ERROR_LIMIT 3000 // [mV]
#define ADREF 3300 // [mV]

void ButtonToggle()
{
	if (AdcHigh())
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

static int16_t AdcHigh()
{
	char msg[10];
	int16_t rawValue = 0;
	int16_t mV = 0;

	ADC1->CR |= ADC_CR_ADSTART;
	rawValue = ADC1->DR;

	mV = ADREF * rawValue >> 12;

	// Convert to string and print
	sprintf(msg, "%d\r\n", mV);
	UartPrint(msg, strlen(msg));

	return ((mV > ON_THRESHOLD) && (mV < HIGH_ERROR_LIMIT));
}

void AdcInit()
{
	__HAL_RCC_ADC1_CLK_ENABLE();

	ADC1->CR &= (ADC_CR_ADVREGEN_1);
	ADC1->CR &= (~ADC_CR_ADVREGEN);
	ADC1->CR |= ADC_CR_ADVREGEN_0;
	osDelay(1);

	ADC1->SQR1 = (ADC1->SQR1 & (~((((0x1FUL << (0U))) << (6U))))) | ((1U << (6U)));
	ADC1->CR |= (ADC_CR_ADEN);
	while (!(ADC1->ISR & ADC_ISR_ADRDY))
	{

	}
}