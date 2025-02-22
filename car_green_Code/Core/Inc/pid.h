#ifndef __PID_h_
#define __PID_h_
// #include "headfile.h"

   
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
enum
{
  POSITION_PID = 0,  // 位置式
  DELTA_PID,         // 增量式
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}pid_t;

void pid_cal(pid_t *pid);
void pid_set_target(pid_t *pid, float _tar);
void pid_init(pid_t *pid, uint32_t mode, float p, float i, float d);


extern pid_t angle;

   
#ifdef __cplusplus
}
#endif

#endif
