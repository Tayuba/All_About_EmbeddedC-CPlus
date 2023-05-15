/*
 * 6ATM_SPI_TX_Arduino.c
 *
 *  Created on: May 11, 2023
 *      Author: ayuba
 */


#include <stdint.h>
#include <string.h>
#include "../drivers/Inc/stm32f407xx.h"

void SPI2_GPIO_Init(void);
void SPI2_Init(void);
void BTN_GPIO_Ini(void);

void delay(void){
	for(uint32_t i = 0; i < 250000; i++){};
}

/*********************************************************SPI2*********************************************************************
 * If alternate function mode is configured as AF5
 * PB12 : NSS
 * PB13: SCLK
 * PB14: MISO
 * PB15: MOSI*/

int main(){
	// Sample data
	char my_data[] = "Using STM32F407 as master and Arduino Uno as slave!";

	// Initialize button
	BTN_GPIO_Ini();

	// Function that initialized GPIO pins to behave as SPI2
	SPI2_GPIO_Init();

	// Function that initialized  and configure SPI
	SPI2_Init();

	// Enable SSOE
	SPI_SSOE_Config(SPI2, ENABLE);
	while(1){
		while(! GPIO_ReadInputPin(GPIOA, GPIO_PIN_NO_0));
		delay();

		// Enable SPI
		SPI_Control(SPI2, ENABLE);

		// Inform slave device the number of byte to expect
		uint8_t data_len = strlen(my_data);
		SPI_Data_Send(SPI2, &data_len, 1);

		// Send data for testing API
		SPI_Data_Send(SPI2, (uint8_t *)my_data, strlen(my_data));
		// SPI not busy before disable SPI
		while(FlagStatus(SPI2, SPI_BSY_FLAG));
		// Disable SPI
		SPI_Control(SPI2, DISABLE);

	}


	return 0;
}

// GPIO Pin configurations for SPI2
void SPI2_GPIO_Init(void){
	GPIO_Handle_t GPIO_Pins;

	GPIO_Pins.pGPIOx = GPIOB;
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinMode  		= GPIO_MODE_ALTFUNC;
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinAlteFuncMode  = 5;
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinOPType 		= GPIO_OTY_PUSPUL;
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_NO;
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinSpeed 		= GPIO_OSPEED_H;

	// Serial clock configure SCLK
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_13;
	GPIO_Init(&GPIO_Pins);

	// Slave select configure NSS
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_12;
	GPIO_Init(&GPIO_Pins);

	// Master input slave output configure MISO
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_14;
	GPIO_Init(&GPIO_Pins);

	// Master output slave input configure MOSI
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_15;
	GPIO_Init(&GPIO_Pins);
}

// SPI2 Initialization
void SPI2_Init(void){
	SPI_Handle_t SPI2_Handle;

	SPI2_Handle.pSPIx								= SPI2;
	SPI2_Handle.pGPIO_PinConfig.SPI_DeviceMode		= MASTER_SDEVICE_MODE_SPI;
	SPI2_Handle.pGPIO_PinConfig.SPI_BusConfig_Com	= FULL_DUPLEX_SPI;
	SPI2_Handle.pGPIO_PinConfig.SPI_ClkSpeed		= SPI_CLK_FREQ_DIV8; // 2MHz
	SPI2_Handle.pGPIO_PinConfig.SPI_DFF				= SPI_DFF_8_BITS;
	SPI2_Handle.pGPIO_PinConfig.SPI_Cpol			= SPI_CPOL_LOW;
	SPI2_Handle.pGPIO_PinConfig.SPI_Cpha			= SPI_CPHA_LOW;
	SPI2_Handle.pGPIO_PinConfig.SPI_Ssm				= SPI_SSM_DI;		// Disable to use hardware, Arduino as slave

	SPI_Init(&SPI2_Handle);
}

void BTN_GPIO_Ini(void){
	GPIO_Handle_t GPIO_BTN;

	GPIO_BTN.pGPIOx = GPIOA;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_0;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinMode 			= GPIO_MODE_INPUT;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_H;
	GPIO_BTN.pGPIO_PinConfig.GPIO_PinPuPdControl 	= GPIO_PUPD_NO;


	GPIO_Init(&GPIO_BTN);
}
