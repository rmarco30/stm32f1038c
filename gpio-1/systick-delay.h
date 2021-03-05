#ifndef __SYSTICK_DELAY_H
#define __SYSTICK_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f10x.h"

void SysTick_Handler(void);
void systick_init(uint32_t ticks);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);


#ifdef __cplusplus
}
#endif

#endif
