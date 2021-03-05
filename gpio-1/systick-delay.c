#include "systick-delay.h"

static volatile uint32_t time_delay = 0;

void SysTick_Handler(void) {
    if(time_delay > 0 )
        time_delay--;               															// every SysTick interrupt decrement global variable time_delay
}

void delay_us(uint32_t us) {																			// us specifies the delay time length in microseconds
	time_delay = us;																								// time_delay must be declared volatile
	while(time_delay != 0);																					// wait here until SysTick_Handler decrements time_delay to 0
}

void delay_ms(uint32_t ms) {																			// ms specifies the delay time length in milliseconds
	while(ms--) {																										// decrement ms every 1000 us
        delay_us(1000);
    }
}

void systick_init(uint32_t ticks) {
    
	SysTick->CTRL = 0;																							// disable SysTick
	SysTick->LOAD = ticks - 1;																			// set reload register
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);		// set interrupt priority of SysTick to least urgency (i.e., largest priority value)
	SysTick->VAL = 0;																								// reset the SysTick counter value
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;												// Select processor clock: 1 = processor clock; 0 = external clock
	SysTick->CTRL |= SysTick_CTRL_TICKINT;													// enables SysTick interrupt, 1 = enable, 0 = disable
	SysTick->CTRL |= SysTick_CTRL_ENABLE;														// enable SysTick
	
//  SysTick_Config(SystemCoreClock / 1000000);										// CMSIS' implementation of SysTick initialization
}
