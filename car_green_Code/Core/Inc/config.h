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

    #define ARR_MAX 65535

    #define MAX_DUTY 60000

    #define MAX_SPEED 999

    #define DEFAULT_FORWARD_SPEED 200
    #define DEFAULT_BACK_SPEED -150
    #define DEFAULT_TURN_SPEED 150

    #define SINGLE_ADJUST_STEP 25

    #define IR_SENSER_NUM 5


    extern const int ir_weight[];

    // #define BASIC_SPEED 20

    extern int BASIC_SPEED;

    extern float BASIC_PHY_SPEED;

    extern float Kp, Ki, Kd;

    


#endif

