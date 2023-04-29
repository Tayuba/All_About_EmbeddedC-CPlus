/*
 * 3ATM_BTN_LED_ExON.c
 *
 *  Created on: Apr 26, 2023
 *      Author: ayuba
 */


#include <stdint.h>
#include "../drivers/Inc/stm32f407xx.h"

#define LOW			0
#define BTNPRESSED 	LOW

void delay(void){
	for(uint32_t i = 0; i < 500000; i++){};
}

int main(void)
{
	GPIO_Handle_t GPIO_LED, GPIO_BTN;
	GPIO_LED.pGPIOx = GPIOA;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_7;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_OUTPUT;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinOPType 		= GPIO_OTY_PUSPUL;
	GPIO_LED.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_NO;

	GPIO_PeriphControl(GPIOA, ENABLE);
	GPIO_Init(&GPIO_LED);

	GPIO_BTN.pGPIOx = GPIOD;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_5;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_INPUT;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_PULUP;


	GPIO_PeriphControl(GPIOD, ENABLE);
	GPIO_Init(&GPIO_BTN);

    /* Loop forever */
	while(1){

		if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_NO_5) == BTNPRESSED){
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_7);

		}

	}
	return 0;
}
