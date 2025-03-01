#ifndef _motor_h
    #define _motor_h

    
#ifdef __cplusplus
extern "C" {
#endif

    #include <stdint.h>

    extern int count1; // 电机1 
    extern int count2; // 电机2 
        
    
    /**
    * @brief 初始化motor
    */
    extern void motor_Init(void);

    /**
    * @brief 设置电机运转状态
    * @param uint8_t whell 电机编号
    * @param int speed 速度 正负控制方向
    */
    extern void motor_set(uint8_t whell, int speed);

    extern void encoder_get_count(void);
    int get_speed(int motor_num);

    
    extern void motor_set_test(uint8_t whell, int speed);
    float get_phy_speed(int motor_num);


    /* 按钮功能*/
    void stop(void);
    void forward(void);
    void back(void);
    void leftward(void);
    void rightward(void);
    void left(void);
    void right(void);



#ifdef __cplusplus
}
#endif
    
#endif

