/*
 * 1ATM_LED_toggle.c
 *
 *  Created on: Apr 26, 2023
 *      Author: ayuba
 */


#include <stdint.h>
#include "../drivers/Inc/stm32f407xx.h"

void delay(void){
	for(uint32_t i = 0; i < 100000; i++){};
}

int main(void)
{
	GPIO_Handle_t GPIO_LED;
	GPIO_LED.pGPIOx = GPIOD;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_12;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_OUTPUT;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinOPType 		= GPIO_OTY_PUSPUL;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_PULUP;

	GPIO_PeriphControl(GPIOD, ENABLE);
	GPIO_Init(&GPIO_LED);
    /* Loop forever */
	while(1){
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		delay();
	}
}
