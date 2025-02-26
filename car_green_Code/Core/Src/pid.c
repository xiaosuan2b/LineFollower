#include "pid.h"
#include "config.h"
#include "motor.h"





void pid_init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
	pid->target = 0;

	// pid_set_target(&motorA, 0);
	// pid_set_target(&motorB, 0);
}

void pid_set_now(pid_t *pid, float _now)
{
	pid->now = _now;
}

void pid_set_target(pid_t *pid, float _tar)
{
	pid->target	= _tar;
}

float pid_get_out(pid_t *pid)
{
	return pid->out;
}

void pid_set_target_speed(pid_t *pid, float _tar)
{
	pid->target	= _tar;
}


void pid_cal(pid_t *pid)
{
	// 计算当前偏差
	pid->error[0] = pid->target - pid->now;

	// 计算输出
	if(pid->pid_mode == DELTA_PID)  // 增量式
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  // 位置式
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout += pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	// 记录前两次偏差
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];

	// 输出限幅
	if(pid->out>=MAX_SPEED)	
		pid->out=MAX_SPEED;
	if(pid->out<=0)	
		pid->out=0;
	
}


