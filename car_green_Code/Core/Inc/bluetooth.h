#ifndef _bluetooth_h

#define _bluetooth_h

#include "usart.h"

extern void bluetooth_Init(void);

void bluetooth_transmit(char *str);
void bluetooth_transmit_uint8_t(uint8_t dt);

extern void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);


#endif  

