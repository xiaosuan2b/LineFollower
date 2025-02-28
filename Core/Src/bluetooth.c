#include "bluetooth.h"  

#include "config.h"
#include "motor.h"
#include "string.h"

#include "state_machine.h"
#include "oled_display.h"

// const int N = 50;

uint8_t BTMessage[1];
uint8_t BTReceiveData[50]; // blue tooth

void bluetooth_Init(void)
{
    
	HAL_UARTEx_ReceiveToIdle_DMA(BTUART, BTReceiveData, sizeof(BTReceiveData));
	__HAL_DMA_DISABLE_IT(BTDMA_USART_RX, DMA_IT_HT);

}

void bluetooth_transmit(char *str)
{
    HAL_UART_Transmit_DMA(BTUART, (uint8_t*)str, strlen(str));
}

void bluetooth_transmit_uint8_t(uint8_t dt)
{
    BTMessage[0] = dt;
    HAL_UART_Transmit_DMA(BTUART, BTMessage, 1);
}





void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) 
{

    char *command = (char*)BTReceiveData;



	if (huart == BTUART) 
	{

        if (command[0] == 'A') // 循迹模式
        {
            go_follow();
            
        
        }else if (command[0] == 'C') // 按钮模式
        {
            go_control();
            
            switch (command[1]) 
            {
                case 'W': forward(); break;
                case 'S': back(); break;
                case 'Q': leftward(); break;
                case 'E': rightward(); break;
                case 'A': left(); break;
                case 'D': right(); break;
                case 'P': stop(); break;

                default: stop(); break;
            }

        
        }else if (command[0] == 'J') // 调整模式
        {
            switch (command[1]) 
            {
                case 'U': if(BASIC_SPEED + SINGLE_ADJUST_STEP < MAX_SPEED) BASIC_SPEED += SINGLE_ADJUST_STEP; break;
                case 'D': if(BASIC_SPEED - SINGLE_ADJUST_STEP > 0) BASIC_SPEED -= SINGLE_ADJUST_STEP; break;
                case 'R': reset_max_speed_cnt();
            }
        
        }


	// if (BTReceiveData[0] == '1') // 1: 正转
	// {
	// 	speed = (BTReceiveData[1] -'0') * 100 + (BTReceiveData[2] -'0') * 10 + (BTReceiveData[3] -'0');

	// } else if (BTReceiveData[0] == '0') // 0: 倒转
	// {
	// 	speed =
	// 		-((BTReceiveData[1] -'0') * 100 + (BTReceiveData[2] -'0') * 10 + (BTReceiveData[3] -'0'));
	// }


	HAL_UART_Transmit_DMA(&huart3, (uint8_t*)command, strlen(command));

	HAL_UARTEx_ReceiveToIdle_DMA(BTUART, BTReceiveData, sizeof(BTReceiveData));
	__HAL_DMA_DISABLE_IT(BTDMA_USART_RX, DMA_IT_HT);
	}


}

