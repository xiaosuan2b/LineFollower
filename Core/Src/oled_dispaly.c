#include "oled_display.h"
#include "OLED.h"
#include "stdio.h"  
#include "string.h"
#include "motor.h"


char oled_message1[16];
char oled_message2[16];

float max_phy_speed1 = 0.0;
float max_phy_speed2 = 0.0;

void oled_display_phy_speed(void)
{
    
    sprintf(oled_message1, "L: %.2f cm/s", get_phy_speed(1));
    sprintf(oled_message2, "R: %.2f cm/s", get_phy_speed(2));

    OLED_Clear();
    OLED_ShowString(1, 1, "currend speed");
    OLED_ShowString(2, 1, oled_message1);
    OLED_ShowString(3, 1, oled_message2);
}

int _max(float a, float b)
{
    return a > b ? a : b;
}

void reset_max_speed_cnt(void)
{
    max_phy_speed1 = 0.0;
    max_phy_speed2 = 0.0;
}

void oled_display_max_phy_speed(void)
{

    max_phy_speed1 = _max(max_phy_speed1, get_phy_speed(1));
    max_phy_speed2 = _max(max_phy_speed2, get_phy_speed(2));
    
    sprintf(oled_message1, "L: %.2f cm/s", max_phy_speed1);
    sprintf(oled_message2, "R: %.2f cm/s", max_phy_speed2);

    OLED_Clear();
    OLED_ShowString(1, 1, "max speed:");
    OLED_ShowString(2, 1, oled_message1);
    OLED_ShowString(3, 1, oled_message2);
}

