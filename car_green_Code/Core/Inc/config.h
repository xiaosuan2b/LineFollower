#ifndef _config_h

    #define _config_h

    #define BTUART &huart3
    #define BTDMA_USART_RX &hdma_usart3_rx

    #define timerTIM &htim1

    #define PWMA_TIM &htim2
    #define PWMB_TIM &htim2

    #define PWMA_CH TIM_CHANNEL_1
    #define PWMB_CH TIM_CHANNEL_2
    
    #define encoder1TIM &htim3

    #define encoder2TIM &htim4

    #define MAX_DUTY 60000

    #define DEFAULT_FORWARD_SPEED 50
    #define DEFAULT_BACK_SPEED -30
    #define DEFAULT_TURN_SPEED 30

    #define IR_SENSER_NUM 10

    extern const int ir_weight[];

    


#endif

