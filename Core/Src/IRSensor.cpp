#include "IRSensor.h"
#include "config.h"
#include "gpio.h"

// #include <vector>

GPIO_TypeDef* IRPorts[] = {IR1_GPIO_Port, IR2_GPIO_Port,
                            IR3_GPIO_Port, IR4_GPIO_Port,
                            IR5_GPIO_Port, IR6_GPIO_Port,
                            IR7_GPIO_Port, IR8_GPIO_Port,
                            IR9_GPIO_Port, IR10_GPIO_Port};

uint16_t IRPins[] = {IR1_Pin, IR2_Pin, IR3_Pin,
                        IR4_Pin, IR5_Pin, IR6_Pin,
                        IR7_Pin, IR8_Pin, IR9_Pin,
                        IR10_Pin};


std::vector<bool> get_IR(void)
{
    // std::vector<bool> ir_states[IR_SENSER_NUM]= {0};
    std::vector<bool> ir_states(IR_SENSER_NUM, 0);

    int cnt = sizeof(IRPorts) / sizeof(IRPorts[0]);

    for (int i = 0; i < cnt; i++) 
    {
        ir_states[i] = (HAL_GPIO_ReadPin(IRPorts[i], IRPins[i])
                        == GPIO_PIN_RESET) ? 1 : 0;
    
    }


    return ir_states;

}

int get_IR_Int(void)
{
    
    auto ir_states = get_IR();
    
    for (int i = 0; i < ir_states.size(); i++)
    {
        if (ir_states[i])
        {
            return (i + 1) * 1000;
        }
        
    }
    

    return 0;
    
}


