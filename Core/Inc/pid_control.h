#ifndef _PID_CONTROL_H

#define _PID_CONTROL_H

#include "pid.h"

void pid_set_phy_speed(int whell, float phy_speed);

void pid_control_Init();

void pid_control();

#endif

