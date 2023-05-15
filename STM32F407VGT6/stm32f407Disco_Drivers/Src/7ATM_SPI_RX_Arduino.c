/*
 * 7ATM_SPI_RX_Arduino.c
 *
 *  Created on: May 14, 2023
 *      Author: ayuba
 */


#include <stdint.h>
#include <string.h>
#include "../drivers/Inc/stm32f407xx.h"

void SPI2_GPIO_Init(void);
void SPI2_Init(void);
void BTN_GPIO_Ini(void);
uint8_t SPI_ConfirmResponse(uint8_t dataACK);

void delay(uint32_t div){
	for(uint32_t i = 0; i < 250000/div; i++){};
}

//Command codes
#define COMMAND_LED_CTRL          0x50
#define COMMAND_SENSOR_READ       0x51
#define COMMAND_LED_READ          0x52
#define COMMAND_PRINT             0x53
#define COMMAND_ID_READ           0x54

//Command to trigger LED
#define LED_ON        			  1
#define LED_OFF    				  0

//Pin of LED connected to
#define LED_PIN 	   			  9

//Arduino Uno analog pins
#define ANALOG_PIN0   			  0
#define ANALOG_PIN1   			  1
#define ANALOG_PIN2   			  2
#define ANALOG_PIN3   			  3
#define ANALOG_PIN4   			  4



/*********************************************************SPI2*********************************************************************
 * If alternate function mode is configured as AF5
 * PB12 : NSS
 * PB13: SCLK
 * PB14: MISO
 * PB15: MOSI*/

int main(){
	uint8_t dummy_read;
	uint8_t dummy = 0xFF;
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
		//Delay to handle button debounce
		delay(1);

		// Enable SPI
		SPI_Control(SPI2, ENABLE);
/****************************LED ON or OFF Command****************************************/
		uint8_t cmdCode = COMMAND_LED_CTRL;
		uint8_t args[2];
		uint8_t dataACK;

		// Send command
		SPI_Data_Send(SPI2, &cmdCode, 1);

		//Read the sent led command into dummy variable to clear RXNE
		SPI_Data_Receive(SPI2, &dummy_read, 1);

		//Send one byte of dummy bits to fetch the response from slave
		SPI_Data_Send(SPI2, &dummy, 1);

		//Receive data send by slave to master
		SPI_Data_Receive(SPI2, &dataACK, 1);

		//Confirm if right data received is the same as data sent
		if(SPI_ConfirmResponse(dataACK)){
			//Send arguments to slave
			args[0] = LED_PIN;
			args[1] = LED_ON;
//			args[1] = LED_OFF;
			//Send these args to turn LED On
			SPI_Data_Send(SPI2, args, 2);
		}


/*********************************Sensor Read Command********************************************/
		while(! GPIO_ReadInputPin(GPIOA, GPIO_PIN_NO_0));
		//Delay to handle button debounce
		delay(1);

		cmdCode = COMMAND_SENSOR_READ;
		// Send command
		SPI_Data_Send(SPI2, &cmdCode, 1);

		//Read the sent led command into dummy variable to clear RXNE
		SPI_Data_Receive(SPI2, &dummy_read, 1);

		//Send one byte of dummy bits to fetch the response from slave
		SPI_Data_Send(SPI2, &dummy, 1);

		//Receive data send by slave to master
		SPI_Data_Receive(SPI2, &dataACK, 1);

		//Confirm if right data received is the same as data sent
		if(SPI_ConfirmResponse(dataACK)){
			//Send arguments to slave
			args[0] = ANALOG_PIN1;

			//Send these args
			SPI_Data_Send(SPI2, args, 1);
		}
		//Read the sent led command into dummy variable to clear RXNE
		SPI_Data_Receive(SPI2, &dummy_read, 1);

		//delay to allow slave to process data
		delay(100);
		//Send one byte of dummy bits to fetch the response from slave
		SPI_Data_Send(SPI2, &dummy, 1);

		//Receive data send by slave to master
		uint8_t Analog_Read;
		SPI_Data_Receive(SPI2, &Analog_Read, 1);

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


uint8_t SPI_ConfirmResponse(uint8_t dataACK){
	if(dataACK == (uint8_t)0xF5){
		// Response acknowledged
		return 1;
	}
	// Response not confirmed
	return 0;

}
