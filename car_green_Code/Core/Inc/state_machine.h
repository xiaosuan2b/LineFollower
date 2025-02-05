#ifndef _state_machine_h

#define _state_machine_h

void go_standby(void);
void go_follow(void);

void next(void);

void _standby(void);
void _control(void);
void _debug_get_count(void);

#endif

