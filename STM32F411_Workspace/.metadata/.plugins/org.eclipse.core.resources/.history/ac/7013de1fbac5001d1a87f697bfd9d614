/* Goal Turn on LED On Nucleo
 From the nucleo board user guide, it states that LED is connected to
 Port: A
 Pin : 5*/

//Peripheral base address from the board
#define Periph_Base 						(0x40000000UL)

//AHB1 base address
#define AHB1_Periph_Offset			(0x20000L)
#define AHB1_Base							(Periph_Base + AHB1_Periph_Offset)

//LED2 base address
#define GPIOA_Offset						(0x0UL)
#define GPIOA_Base						(AHB1_Base + GPIOA_Offset)

//Reset and clock control(RCC)
#define RCC_Offset 						(0x3800UL)
#define RCC_Base							(AHB1_Base + RCC_Offset)

//RCC enable clock address
#define RCC_AHBEN_R_Offset		(0x30)
#define RCC_AHBEN_R		            (*(volatile unsigned int *)(RCC_Base + RCC_AHBEN_R_Offset))

//Set port A to 1
#define GPIOA_EN							(1U<<0)

//Address of Mode
#define Mode_R_Offset 					(0x00UL)
#define GPIOA_Mode_R					(*(volatile unsigned int *)(GPIOA_Base + Mode_R_Offset))

//Output data register address
#define GPIO_R_ODR_Offset			(0x14UL)
#define GPIO_R_ODR						(*(volatile unsigned int *)(GPIOA_Base + GPIO_R_ODR_Offset))

//Setting Pin 5 to 1
#define Pin5										(1UL<<5)
#define LED_PIN								Pin5


int main(void)
{
	RCC_AHBEN_R  |= GPIOA_EN;
	GPIOA_Mode_R	  |=  (1U<<10);
	GPIOA_Mode_R	  &=  ~(1U<<11);

//	Enable clock
//	Set PA5 as output
	while(1)
	{
		//		Turn on LED
		GPIO_R_ODR	 ^=  LED_PIN;
		for (int i =0; i<100000; i++){}



	}
}
