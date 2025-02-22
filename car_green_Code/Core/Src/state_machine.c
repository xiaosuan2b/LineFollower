#include "state_machine.h"

#include <stdio.h>
#include "motor.h"
#include "usart.h"
#include "string.h"
#include "follow.h" 
#include "OLED.h"
#include "config.h"

int _state = 0;
// 0: stop
// 1: follow
// 2：button_control
// 9: debug_get_count


/* Private functions Declaration */
void _standby_state(void);
void _control_state(void);
void _debug_get_count_state(void);
void _follow_state(void);

void next(void)
{
    // _debug_get_count_state();

    switch (_state) 
    {
        case 0: _standby_state(); break;
        case 1: _follow_state(); break;
        case 2: _control_state(); break;
        case 9: _debug_get_count_state(); break;


        default: _standby_state(); break;
    }

}


void go_standby(void)
{
    _state = 0;
}

void go_follow(void)
{
    reset_circle();
    motor_set(1, BASIC_SPEED);
    motor_set(2, BASIC_SPEED);
    _state = 1;
}


void go_control(void)
{
    _state = 2;
}

void _standby_state(void)
{
    
    stop();
    HAL_Delay(1000);

}

void _follow_state(void)
{
    follow3();
}

void _control_state(void)
{
    HAL_Delay(1000);
}

void _debug_get_count_state(void)
{
    
    char str[50];

    // itoa((count1), str, 10);
    sprintf(str, "count1: %d, count2: %d", count1, count2);

    HAL_UART_Transmit_DMA(&huart3, (uint8_t*)str, strlen(str));

    HAL_Delay(1000);
		
}
