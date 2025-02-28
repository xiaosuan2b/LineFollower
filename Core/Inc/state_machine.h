#ifndef _state_machine_h

#define _state_machine_h


#ifdef __cplusplus
extern "C" {
#endif

void go_standby(void);
void go_follow(void);
void go_control(void);

void next(void);


#ifdef __cplusplus
}
#endif

#endif

