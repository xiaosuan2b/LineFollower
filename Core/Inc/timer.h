#ifndef _timer_h

#define _timer_h


#ifdef __cplusplus
extern "C" {
#endif

// extern unsigned long long currentMillis;

extern void timer_Init(void);

extern inline void update10ms(void);

extern inline unsigned long long millis(void);


#ifdef __cplusplus
}
#endif

#endif

