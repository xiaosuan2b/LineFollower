// tb6612

#include "motor.h"

#include "tim.h"
#include "config.h"


#define MAX_SPEED 100

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
		// __HAL_TIM_SET_COUNTER(encoder1TIM, 0);
    count2 = __HAL_TIM_GetCounter(encoder2TIM);
		// __HAL_TIM_SET_COUNTER(encoder2TIM, 0);
}



void motor_set_test(uint8_t whell, int speed)
{
    

    if (speed > MAX_SPEED)
        speed = MAX_SPEED;
    else if (speed < -MAX_SPEED)
        speed = -MAX_SPEED;

    /* Set Direction */
    if (speed >= 0)
    {
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
        
    }else if (speed < 0) 
    {
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
    }

    /* Set Speed */
    __HAL_TIM_SET_COMPARE(PWMA_TIM, PWMA_CH, speed >= 0 ? speed : -speed);




}


