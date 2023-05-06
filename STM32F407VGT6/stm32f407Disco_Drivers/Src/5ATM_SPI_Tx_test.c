/*
 * 5ATM_SPI_Tx_test.c
 *
 *  Created on: May 3, 2023
 *      Author: ayuba
 */


#include <stdint.h>
#include <string.h>
#include "../drivers/Inc/stm32f407xx.h"

void SPI2_GPIO_Init(void);
void SPI2_Init(void);
/*********************************************************SPI2*********************************************************************
 * If alternate function mode is configured as AF5
 * PB9 : NSS
 * PB13: SCLK
 * PB14: MISO
 * PB15: MOSI*/

int main(){
	// Sample data
	char my_data[] = "My name is Ayuba Tahiru Monnie!";

	// Function that initialized GPIO pins to behave as SPI2
	SPI2_GPIO_Init();

	// Function that initialized  and configure SPI
	SPI2_Init();

	// Enable SSI to allow SSM to function, this make NSS internal signal high
	SPI_SSI_Config(SPI2, ENABLE);

	// Enable SPI
	SPI_Control(SPI2, ENABLE);


	// Send data for testing API
	SPI_Data_Send(SPI2, (uint8_t *)my_data, strlen(my_data));

	// Disable SPI
		SPI_Control(SPI2, DISABLE);
	while(1){

	};

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

//	// Serial clock configure SCLK
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_13;
	GPIO_Init(&GPIO_Pins);

//	// Slave select configure NSS
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_9;
	GPIO_Init(&GPIO_Pins);

//	// Master input slave output configure MISO
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_14;
	GPIO_Init(&GPIO_Pins);

//	// Master output slave input configure MOSI
	GPIO_Pins.pGPIO_PinConfig.GPIO_PinNumber 		= GPIO_PIN_NO_15;
	GPIO_Init(&GPIO_Pins);
}

// SPI2 Initialization
void SPI2_Init(void){
	SPI_Handle_t SPI2_Handle;

	SPI2_Handle.pSPIx								= SPI2;
	SPI2_Handle.pGPIO_PinConfig.SPI_DeviceMode		= MASTER_SDEVICE_MODE_SPI;
	SPI2_Handle.pGPIO_PinConfig.SPI_BusConfig_Com	= FULL_DUPLEX_SPI;
	SPI2_Handle.pGPIO_PinConfig.SPI_ClkSpeed		= SPI_CLK_FREQ_DIV2;
	SPI2_Handle.pGPIO_PinConfig.SPI_DFF				= SPI_DFF_8_BITS;
	SPI2_Handle.pGPIO_PinConfig.SPI_Cpol			= SPI_CPOL_LOW;
	SPI2_Handle.pGPIO_PinConfig.SPI_Cpha			= SPI_CPHA_LOW;
	SPI2_Handle.pGPIO_PinConfig.SPI_Ssm				= SPI_SSM_EN;

	SPI_Init(&SPI2_Handle);
}
