#include "timer.h"
#include "tim.h"
#include "config.h"
#include "motor.h"

#include "pid_control.h"

// #include "OLED.h"
#include "oled_display.h"

#include <stdio.h>

unsigned long long _currentMillis = 0;

int oledcnt = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// 每次 timerTIM 触发中断 （当前间隔设置为 10 ms）
	// 写 count，重置 arr
	if (htim == timerTIM) 
	{
		encoder_get_count();

		// pid_control();
		
		update10ms();

		// oledcnt++;

		// if (oledcnt >= 100) 
		// {
		// 	oled_display_max_phy_speed();
		// 	oledcnt = 0;
		// }
		

	
	}

}

void timer_Init(void)
{
	HAL_TIM_Base_Start_IT(timerTIM);
}

inline void update10ms(void)
{
    _currentMillis += 10;
}

inline unsigned long long millis(void)
{
    return _currentMillis;
}

