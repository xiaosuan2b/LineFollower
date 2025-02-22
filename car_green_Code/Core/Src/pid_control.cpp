#include "pid_control.h"

#include "motor.h"
#include "config.h"


pid_t motorA;
pid_t motorB;

void pid_control_Init()
{
	pid_init(&motorA, DELTA_PID, Kp, Ki, Kd);
	pid_init(&motorB, DELTA_PID, Kp, Ki, Kd);
}

void pid_set_phy_speed(int whell, float phy_speed)
{
    /**
        @param int whell 轮胎编号
        @param int phy_speed 物理速度 (mm/s)

        电机减速比 30，GMR 编码器精度 500
        转一圈编码器读数 15000
        轮胎直径 65mm ，转一圈 204.2 mm
        * 编码器: 距离mm 725 : 1 mm
        10ms 采集一次数据 725 : 100 mm/s

        * 最终：1mm/s 对应编码器读数：7.25
     */

	if (whell == 1) 
	{
		pid_set_target(&motorA, 7.25 * phy_speed);
	}else if (whell == 2) 
	{
		pid_set_target(&motorB, 7.25 * phy_speed);
	}

    
    

}




void pid_control()
{
	
	// 速度环
	// 1.根据灰度传感器信息 设定目标速度
	// track();
	// 2.获取当前速度
	motorA.now = get_speed(1);
	motorB.now = get_speed(2);

	// 3.输入PID控制器进行计算
	pid_cal(&motorA);
	pid_cal(&motorB);
	
	// 4.PID的输出值 输入给电机
	motor_set(1, motorA.out);
	motor_set(2, motorB.out);
	
//	datavision_send();
}
