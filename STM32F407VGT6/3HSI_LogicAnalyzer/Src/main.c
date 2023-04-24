#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define RCC_BASE_ADDR					 	0x40023800UL
#define RCC_CR_REG_OFFSET					0x00UL
#define RCC_CFGR_REG_OFFSET					0x08UL
#define GPIOA_BASE_ADDR					 	0x40020000UL
#define GPIOA_MODE_R_OFFSET					0x00UL
#define RCC_AHB1ENR_OFFSET					0x30UL
#define GPIOA_AFRH_OFFSET					0x24UL

#define RCC_CR_REG_ADDR						(RCC_BASE_ADDR + RCC_CR_REG_OFFSET)
#define RCC_CFGR_REG_ADDR					(RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define GPIOA_MODE_R_ADDR					(GPIOA_BASE_ADDR + GPIOA_MODE_R_OFFSET)
#define RCC_AHB1ENR_ADDR					(RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET)
#define GPIOA_AFRH_ADDR						(GPIOA_BASE_ADDR + GPIOA_AFRH_OFFSET)

int main()
{	//Pointer variable of RCC_CR clock configuration register
	uint32_t *pRCCCr = (uint32_t *)RCC_CR_REG_ADDR;
	//Pointer variable of RCC clock configuration register
	uint32_t *pRCCCrgrv = (uint32_t *)RCC_CFGR_REG_ADDR;

	//Enable HSI clock
	*pRCCCr  |= (1<<0);

	//Wait until HSI is ready
	while(!(*pRCCCr & (1<<1))){};

	//configure RCC_CFGR to select HSE
	*pRCCCrgrv  &= ~(0x3<<0);

	//configure to select HSI by clearing or setting bit 22 and 21 to zeros
	*pRCCCrgrv &= ~(0x3<<26);
	//configure MCO1 prescaler
	*pRCCCrgrv |= (1<<25);
	*pRCCCrgrv |= (1<<26);

	//Pointer variable of RCC AHB1 Enable
	uint32_t *pRCCAHB1ENR = (uint32_t *)RCC_AHB1ENR_ADDR;
	//Enable peripheral clock for GPIOA register
	*pRCCAHB1ENR |= (1<<0);

	//Pointer variable of GPIOA Mode Register
	uint32_t *pGPIOAModeReg = (uint32_t *)GPIOA_MODE_R_ADDR;
	//configure to make PA8 alternate function mode, by setting bit 16 to zero and bit 17 to one
	*pGPIOAModeReg &= ~(0x3<<16);   // first clear both bits to make sure it is clean
	*pGPIOAModeReg |= (0x2<<16);

	//Pointer variable of alternate function register H
	uint32_t *pGPIOAAfhrReg = (uint32_t *)GPIOA_AFRH_ADDR;
	//configure the alternate function AFRH to zeros
	*pGPIOAAfhrReg &= ~(0xf<<0);

	for(;;);
}
