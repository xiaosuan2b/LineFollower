// 超声波
#include "wave.h"
#include "config.h"
#include "tim.h"          

int last_distance_count = 0;  // dis = last_distance_count * 340 / 2;
int last_rizing_edge_cnt = 0;


// void wave_Init(void)
// {

//     HAL_TIM_IC_Start_IT(timerTIM, TIM_CHANNEL_3);
//     HAL_TIM_IC_Start_IT(timerTIM, TIM_CHANNEL_4);

// }

void wave_Trig(void)
{
    HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_RESET);
}

void wave_echo_IRQHandle(void)
{
    
    if (HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == GPIO_PIN_SET) 
    {   // 上升沿中断
        last_rizing_edge_cnt = __HAL_TIM_GET_COUNTER(timerTIM);

    }else if (HAL_GPIO_ReadPin(Echo_GPIO_Port, Echo_Pin) == GPIO_PIN_RESET) 
    {
        // 下降沿中断
        int last_falling_edge_cnt = __HAL_TIM_GET_COUNTER(timerTIM);

        if (last_falling_edge_cnt >= last_rizing_edge_cnt) 
        {
            last_distance_count = (last_falling_edge_cnt - last_rizing_edge_cnt) ;
        }
        
    }


}

int get_last_distance(void)
{
    // 单位： 0.001 mm
    return last_distance_count * 340 / 2;
}

