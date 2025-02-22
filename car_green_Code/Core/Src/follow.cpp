
typedef bool _Bool;

// #include <map>
// #include <utility>

#include "follow.h" 
#include "bluetooth.h"
#include "stdio.h"
#include "IRSensor.h"
#include "motor.h"
#include "timer.h"
#include "config.h"
#include <stdlib.h>

#include "pid.h"    
#include "pid_control.h"


char irmsg[50];
int circle = 0;

float dire = 0;


// 存储状态对应的电机动力百分比
// 状态用二进制数表示，左右电机百分比用 pair
// eg:  0b00000100 : 80 80
// std::map<uint8_t, std::pair<int, int> > m;

// std::map<int, int> m;

// void follow_Init(void)
// {
//     m[0b00100] = {80, 80};
//     m[0b01000] = {60, 80};
//     m[0b10000] = {40, 80};

// }

void follow_Init()
{
    pid_control_Init();
}


void reportIR(void)
{
    // _Bool *irs = get_IR();
    auto irs = get_IR();
    // sprintf(irmsg, "irstate: %d %d %d %d %d", irs[0], irs[1], irs[2], irs[3], irs[4]);
    sprintf(irmsg, "dire = %lf", dire );

    bluetooth_transmit(irmsg);


}

void reset_circle(void)
{
    circle = 0;
}

unsigned long long lastDetectedMillis = 0;

bool ready_continue(void)
{
    if (circle > 3) 
    {
         return false;
    }

    unsigned long long currentMillis = millis();

    if (currentMillis - lastDetectedMillis < 500) 
    {
        return true;
    }

    

    auto irs = get_IR();

    int hx_cnt = 0;  // 传感器检测到的黑线数量

    for (int i = 0; i < IR_SENSER_NUM; i++) 
    {
        if (irs[i]) hx_cnt++;
    }

    if (hx_cnt > 4) 
    {
        circle++; // 检测到横线，圈数++
        lastDetectedMillis = currentMillis;
    }

    return true;

}


void follow(void)
{

    // if (!ready_continue()) 
    // {
    //     return;
    //     HAL_Delay(1000);
    // }

    // dire = 0; // 方向

    // _Bool *irstate = get_IR();
    auto irstate = get_IR();

    for (uint8_t i = 0; i < IR_SENSER_NUM; i++) 
    {
        dire += ir_weight[i] * irstate[i];
    }

    dire = (dire + 100) /100;

    if (dire < 0) 
    {
        motor_set(1, BASIC_SPEED);
        motor_set(2, BASIC_SPEED * abs(dire));
    
    }else if (dire == 0) 
    {
        motor_set(1, BASIC_SPEED );
        motor_set(2, BASIC_SPEED);
    
    }else if (dire > 0 ) 
    {
        motor_set(1, BASIC_SPEED* (dire));
        motor_set(2, BASIC_SPEED);
    }
    


}

void follow2(void)
{

    auto irstate = get_IR();

    if (irstate[0] != irstate[4]) 
    {
        if (irstate[0]) // 1 0 0 0 0
        {
            motor_set(1, BASIC_SPEED);
            motor_set(2, BASIC_SPEED * 3 );
        }else   // 0 0 0 0 1
        {
            motor_set(1, BASIC_SPEED * 3);
            motor_set(2, BASIC_SPEED );
        }

        HAL_Delay(20);
    
    }else if (irstate[1] != irstate[3]) 
    {
        if (irstate[1]) // 0 1 0 0 0
        {
            motor_set(1, BASIC_SPEED);
            motor_set(2, BASIC_SPEED + BASIC_SPEED /2);
        }else   // 0 0 0 1 0
        {
            motor_set(1, BASIC_SPEED + BASIC_SPEED /2);
            motor_set(2, BASIC_SPEED);
        }

        HAL_Delay(10);
    }
    else 
    {
        motor_set(1, BASIC_SPEED*2);
        motor_set(2, BASIC_SPEED*2);
        
    }


    

}

void follow3(void)
{

    if (!ready_continue()) 
    {
        motor_set(1, 0);
        motor_set(2, 0);
        HAL_Delay(1000);
        return;
    }


    auto irstate = get_IR();

    if (irstate[0] != irstate[4]) 
    {
        if (irstate[0]) // 1 0 0 0 0
        {
            motor_set(1, BASIC_SPEED);
            motor_set(2, BASIC_SPEED * 3 );
        }else   // 0 0 0 0 1
        {
            motor_set(1, BASIC_SPEED * 3);
            motor_set(2, BASIC_SPEED );
        }

        // HAL_Delay(20);
    
    }else if (irstate[1] != irstate[3]) 
    {
        if (irstate[1]) // 0 1 0 0 0
        {
            motor_set(1, BASIC_SPEED * 2);
            motor_set(2, BASIC_SPEED * 3);
        }else   // 0 0 0 1 0
        {
            motor_set(1, BASIC_SPEED * 3);
            motor_set(2, BASIC_SPEED * 2);
        }

        // HAL_Delay(10);
    }
    else if (irstate[2]) 
    {
        motor_set(1, BASIC_SPEED * 4.5);
        motor_set(2, BASIC_SPEED * 4.5);
    }
    
}


void follow_pid(void)
{

    auto irstate = get_IR();

    if (irstate[0] != irstate[4]) 
    {
        if (irstate[0]) // 1 0 0 0 0
        {
            pid_set_phy_speed(1, BASIC_PHY_SPEED);
            pid_set_phy_speed(2, BASIC_PHY_SPEED * 3 );
        }else   // 0 0 0 0 1
        {
            pid_set_phy_speed(1, BASIC_PHY_SPEED * 3);
            pid_set_phy_speed(2, BASIC_PHY_SPEED );
        }

        HAL_Delay(20);
    
    }else if (irstate[1] != irstate[3]) 
    {
        if (irstate[1]) // 0 1 0 0 0
        {
            pid_set_phy_speed(1, BASIC_PHY_SPEED);
            pid_set_phy_speed(2, BASIC_PHY_SPEED + BASIC_PHY_SPEED / 2);
        }else   // 0 0 0 1 0
        {
            pid_set_phy_speed(1, BASIC_PHY_SPEED + BASIC_PHY_SPEED /2);
            pid_set_phy_speed(2, BASIC_PHY_SPEED);
        }
    }
    else 
    {
        pid_set_phy_speed(1, BASIC_PHY_SPEED);
        pid_set_phy_speed(2, BASIC_PHY_SPEED);
        
    }


    

}

