#include "stm32f10x.h"
#include "systick-delay.h"

void gpio_ports_enable(void);


int main() {
    
    systick_init(SystemCoreClock / 1000000);			// initialize SysTick
		gpio_ports_enable();													// initialize GPIO ports to be used
		GPIOA->ODR = 1 << 0;
		uint8_t direction = 0;
	
	while(1) {
		
		delay_ms(50);
		
		if(direction == 0) {
			
			GPIOA->ODR = GPIOA->ODR << 1;
			
			if((GPIOA->ODR > 0x80)) {
				GPIOA->ODR = 1 << 8;
				direction = 1;
			}
		}
		
		if(direction == 1) {
			
			GPIOA->ODR = GPIOA->ODR >> 1;
			
			if((GPIOA->ODR < 0x01)) {
				GPIOA->ODR = 1 << 0;
				direction = 0;
			}
		}
	}
}


void gpio_ports_enable(void){
	
	RCC->APB2ENR |= 1UL << 2;												// enable GPIOA's clock
	for(uint8_t i=0, j=2; i<32; i+=4, j+=4) {			
		
		GPIOA->CRL |=  (1UL << i) | (1UL << (i+1));		// configure GPIOA<7:0> as output mode 50MHz
		GPIOA->CRL &= ~(1UL << j) | (1UL << (j+1));		// configure GPIOA<7:0> as push-pull output
	}
}
