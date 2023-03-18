#include <stdint.h>
//Peripheral base address from the board
#define Periph_Base 						(0x40000000UL)

//AHB1 base address
#define AHB1_Periph_Offset					(0x20000L)
#define AHB1_Base							(Periph_Base + AHB1_Periph_Offset)

//LED2 base address
#define GPIOA_Offset						(0x0UL)
#define GPIOA_Base							(AHB1_Base + GPIOA_Offset)

//Reset and clock control(RCC)
#define RCC_Offset 					    	(0x3800UL)
#define RCC_Base							(AHB1_Base + RCC_Offset)

//Set port A to 1
#define GPIOA_EN						    (1U<<0)

//Setting Pin 5 to 1
#define Pin5								(1UL<<5)
#define LED_PIN								Pin5

typedef struct
{
	volatile uint32_t Dummy[12];
	volatile uint32_t AHBIENR;
}RCC_TypeDef;


typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t Dummy[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;

#define RCC 								((RCC_TypeDef*)RCC_Base)
#define GPIOA 								((GPIO_TypeDef*)GPIOA_Base)
int main(void)
{
	RCC->AHBIENR  |= GPIOA_EN;
	GPIOA->MODER  |=  (1U<<10);
//	GPIOA->MODER  &=  ~(1U<<11);


//	Enable clock
//	Set PA5 as output
	while(1)
	{

		GPIOA->ODR ^=  LED_PIN;
		for (int i =0; i<100000; i++){}

	}
}
