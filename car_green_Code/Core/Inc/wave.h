// 超声波

#ifndef _wave_h
    #define _wave_h

    
#ifdef __cplusplus
extern "C" {
#endif

    extern int last_distance_count;

    extern void wave_Trig(void);

    extern void wave_echo_IRQHandle(void);

    extern int get_last_distance(void);

    
#ifdef __cplusplus
}
#endif


#endif

