#ifndef UART_PRINT_H
#define UART_PRINT_H

#include "cmsis_os.h"

void UartInit();
void UartPrint(char *msg, uint16_t size);
void UartRecieve(uint8_t *msg, uint16_t size);

#endif
