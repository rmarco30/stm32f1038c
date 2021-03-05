#include "stm32f10x.h"
#include "systick-delay.h"

void gpio_ports_enable(void);


int main() {
    
    systick_init(SystemCoreClock / 1000000);		// initialize SysTick
		gpio_ports_enable();												// initialize GPIO ports to be used
	
	while(1) {
		
		GPIOC->BSRR = 1UL << 13;										// set bit 13 of BSRR register, turns on the LED
		delay_ms(150);															// delay
		GPIOC->BSRR = 1UL << 29;										// set bit 29 of BSRR register, turns off the LED
		delay_ms(150);															// delay
		
	}
}


void gpio_ports_enable(void){
	
	RCC->APB2ENR |= 1UL << 4;											// enable GPIOC's clock
	GPIOC->CRH |=  ((1UL << 20) | (1UL << 21));		// output mode 50MHz
	GPIOC->CRH &= ~((1UL << 22) | (1UL << 23));		// push-pull output
	
}
