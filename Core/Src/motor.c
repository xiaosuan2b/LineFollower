// tb6612

#include "motor.h"

#include "tim.h"
#include "config.h"
#include <math.h>   

int speed = 99;


int count1 = 0;
int count2 = 0;

void motor_Init(void)
{
    HAL_TIM_Encoder_Start(encoder1TIM, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(encoder2TIM, TIM_CHANNEL_ALL);

    HAL_TIM_PWM_Start(PWMA_TIM,PWMA_CH);
    HAL_TIM_PWM_Start(PWMB_TIM,PWMB_CH);

    // HAL_TIM_PWM_Start(PWMB_TIM, PWMB_CH);

}


// struct Whell
// {
//     /* In Ports */
//     GPIO_TypeDef *IN1_GPIO_Port, *IN2_GPIO_Port;
//     uint16_t IN1_Pin, IN2_Pin;
//     /* PWM TIM */
//     TIM_HandleTypeDef TIM;
//     unsigned int CHANNEL;

// };

void motor_set_duty(uint8_t whell, int duty)
{
    motor_set(whell, 100 * duty / MAX_DUTY);
}

void motor_set(uint8_t whell, int speed)
{


    GPIO_TypeDef *IN1_GPIO_Port, *IN2_GPIO_Port;
    uint16_t IN1_Pin, IN2_Pin;
    TIM_HandleTypeDef *TIM; unsigned int CHANNEL;

    if (speed > MAX_SPEED)
        speed = MAX_SPEED;
    else if (speed < -MAX_SPEED)
        speed = -MAX_SPEED;

    

    if (whell == 1) 
    {
        IN1_GPIO_Port = AIN1_GPIO_Port;    IN1_Pin = AIN1_Pin;
        IN2_GPIO_Port = AIN2_GPIO_Port;    IN2_Pin = AIN2_Pin;
        TIM = PWMA_TIM; CHANNEL = PWMA_CH;
    }else if (whell == 2) 
    {
        IN1_GPIO_Port = BIN1_GPIO_Port;    IN1_Pin = BIN1_Pin;
        IN2_GPIO_Port = BIN2_GPIO_Port;    IN2_Pin = BIN2_Pin;
        TIM = PWMB_TIM; CHANNEL = PWMB_CH;
    }

    /* Set Direction */
    if (speed >= 0) 
    {
        HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
        
    }else if (speed < 0) 
    {
        HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);
    }

    /* Set Speed */
    __HAL_TIM_SET_COMPARE(TIM, CHANNEL, speed >= 0 ? speed : -speed);




}

void encoder_get_count(void)
{
    count1 = __HAL_TIM_GetCounter(encoder1TIM);
		__HAL_TIM_SET_COUNTER(encoder1TIM, 0);
    count2 = __HAL_TIM_GetCounter(encoder2TIM);
		__HAL_TIM_SET_COUNTER(encoder2TIM, 0);


    if (count1 > (ARR_MAX/2)) 
    {
        count1 = ARR_MAX - count1;
    }
    if (count2 > (ARR_MAX/2)) 
    {
        count2 = ARR_MAX - count2;
    }
}

int get_speed(int motor_num)
{
    switch (motor_num) 
    {
        case 1: return count1; break;   
        case 2: return count2; break;

        default: return NAN; break;
    
    }
    
    
}

float get_phy_speed(int motor_num)
{
    /**
        @param int whell 轮胎编号
        @return int phy_speed 物理速度 (cm/s)

        电机减速比 30，GMR 编码器精度 500
        转一圈编码器读数 15000
        轮胎直径 65mm ，转一圈 204.2 mm
        * 编码器: 距离mm 73.456 : 1 mm
        10ms 采集一次数据 73.456 : 100 mm/s

        * 最终：编码器示数 1 对应 0.136135681655557707 cm/s
     */
     
    switch (motor_num) 
    {
        case 1: return count1 * 0.136135681; break;   
        case 2: return count2 * 0.136135681; break;

        default: return NAN; break;
    
    }
}




/* 按钮功能 */

void stop(void)
{
    motor_set(1, 0);
    motor_set(2, 0);

}

void forward(void)
{
    motor_set(1, DEFAULT_FORWARD_SPEED);
    motor_set(2, DEFAULT_FORWARD_SPEED);
}

void back(void)
{
    motor_set(1, DEFAULT_BACK_SPEED);
    motor_set(2, DEFAULT_BACK_SPEED);
}

void leftward(void)
{
    motor_set(1, DEFAULT_FORWARD_SPEED/2);
    motor_set(2, DEFAULT_FORWARD_SPEED);
}

void rightward(void)
{
    motor_set(1, DEFAULT_FORWARD_SPEED);
    motor_set(2, DEFAULT_FORWARD_SPEED/2);
}

void left(void)
{
    motor_set(1, 0);
    motor_set(2, DEFAULT_TURN_SPEED);
}

void right(void)
{
    motor_set(1, DEFAULT_TURN_SPEED);
    motor_set(2, 0);
}

