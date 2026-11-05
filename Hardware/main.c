#include "stm32f10x_reg.h"

// 全局变量，生命周期到程序结束
volatile unsigned char flag = 0; 

// 瞎写的延时
void delay(volatile unsigned int cnt) {
    while(cnt--);
}

void My_EXTI_Init(void) {
    // 开时钟
    RCC_APB2ENR |= (1 << 4) | (1 << 2) | (1 << 0);

    // PC13 推挽输出
    GPIOC->CRH &= ~(0x0F << 20); 
    GPIOC->CRH |=  (0x03 << 20); 

    // PA0 上拉输入
    GPIOA->CRL &= ~(0x0F << 0);
    GPIOA->CRL |=  (0x08 << 0);
    GPIOA->ODR |= (1 << 0);

    // AFIO 映射
    AFIO->EXTICR[0] &= ~(0x0F << 0);

    // EXTI 下降沿，解除屏蔽
    EXTI->FTSR |= (1 << 0);
    EXTI->IMR  |= (1 << 0);

    // NVIC 使能中断通道6 (地址硬编码)
    *(volatile unsigned int *)0xE000E100 |= (1 << 6); 
}

int main(void) {
    My_EXTI_Init();
    
    while(1) {
        if (flag == 1) {
            GPIOC->ODR &= ~(1 << 13);
        } else {
            GPIOC->ODR |= (1 << 13);
        }
        delay(100000);
    }
}
