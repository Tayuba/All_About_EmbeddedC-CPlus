#include "stm32f4xx.h"
#include "adc.h"
/*
 * adc.c
 *
 *  Created on: Mar 26, 2023
 *      Author: ayuba
 */


#define ADCENR				(1U<<8)
#define ADCCH1				(1U<<0)
#define GPIOAENR			(1U<<0)
#define SR_EOC				(1U<<1)

void pa1_adc_init(void){
//	 Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAENR;
//	Set the mode of PA1 to Analog
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);


//	Enable clock access to ADC module
	RCC->APB2ENR|= ADCENR;
/*	Configure ADC parameters */
//	Conversion sequence start
	ADC1->SQR3 = ADCCH1;
//	Conversion sequence length
	ADC1->SQR1 = 0x0;
//	Enable ADC module
	ADC1->CR2 |= (1U<<0);
}

void start_conversion(void){
//	Start ADC conversion
	ADC1->CR2 |= (1U<<30);
}

uint32_t adc_read(void){
//	wait for conversion to be complete
	while (!(ADC1->SR & SR_EOC)){};
//	read converted
	return (ADC1->DR);
}
