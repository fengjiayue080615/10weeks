#include "stm32f10x_reg.h"

extern volatile unsigned char flag;

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & (1 << 0)) {
        // 清标志位
        EXTI->PR = (1 << 0);
        
        // 简陋消抖
        for(int i = 0; i < 2000; i++); 
        
        flag = !flag;
    }
}
