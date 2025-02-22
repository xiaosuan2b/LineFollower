#include "oled_display.h"
#include "OLED.h"
#include "stdio.h"  
#include "string.h"
#include "motor.h"


char oled_message1[16];
char oled_message2[16];

void oled_display_phy_speed(void)
{
    
    sprintf(oled_message1, "L: %.2f mm/s", get_phy_speed(1));
    sprintf(oled_message2, "R: %.2f mm/s", get_phy_speed(2));

    OLED_Clear();
    OLED_ShowString(1, 1, "currend speed");
    OLED_ShowString(2, 1, oled_message1);
    OLED_ShowString(3, 1, oled_message2);
}

