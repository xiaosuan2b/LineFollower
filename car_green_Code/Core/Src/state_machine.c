#include "state_machine.h"

#include <stdio.h>
#include "motor.h"
#include "usart.h"
#include "string.h"

int _state = 0;
// 0: stop
// 1: follow
// 2：button_control
// 9: debug_get_count


void next(void)
{

    switch (_state) 
    {
        case 0: _standby(); break;
        case 9: _debug_get_count(); break;
        case 2: _control(); break;

        default: _standby(); break;
    }

}


void go_standby(void)
{
    _state = 0;
}

void go_follow(void)
{
    _state = 1;
}


void go_control(void)
{
    _state = 2;
}

void _standby(void)
{
    stop();
    HAL_Delay(1000);

}

void _control(void)
{
    HAL_Delay(1000);
}

void _debug_get_count(void)
{
    
    char str[50];

    // itoa((count1), str, 10);
    sprintf(str, "count1: %d, count2: %d", count1, count2);

    HAL_UART_Transmit_DMA(&huart3, (uint8_t*)str, strlen(str));

    HAL_Delay(1000);
		
}
