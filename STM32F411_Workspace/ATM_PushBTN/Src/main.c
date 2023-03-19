#include "stm32f4xx.h"


#define GPIOAENR			(1U<<0)
#define GPIOCENR			(1U<<2)


#define PIN5				(1U<<5)
#define PIN13				(1U<<13)

#define LED_PIN				 PIN5
#define BTN_Push			 PIN13



int main(void) {
	RCC->AHB1ENR |= GPIOAENR;
	RCC->AHB1ENR |= GPIOCENR;

//	SET PA5 AS OUTPUT PIN
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

//	SET PA13 AS INPUT PIN
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	while(1){

		if (GPIOC->IDR & BTN_Push){
		GPIOA->BSRR = LED_PIN;

		}
		else{
		GPIOA->BSRR = (1U<<21);

		}

	}

}
