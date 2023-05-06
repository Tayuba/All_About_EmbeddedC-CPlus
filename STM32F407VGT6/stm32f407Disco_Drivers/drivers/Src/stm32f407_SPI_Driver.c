/*
 * stm32f407_SPI_Driver.c
 *
 *  Created on: Apr 30, 2023
 *      Author: ayuba
 */
#include "stm32f407_SPI_Driver.h"

// SPI Flag Status check
/************************************************************************************************
 *@func name							- FlagStatus
 *
 *@brief								- Function to enable or disable SPI
 *
 *@param1								- Base Address of SPI Handle
 *@param2								- Takes flag information to access whether is set or rest
 *
 *@return								- Returns True or False
 *
 *@Note									- none
 */
uint8_t FlagStatus(SPI_Reg_t *pSPIx, uint32_t FlagType){
	// Check Flag status of the Flag Type requested
	if(pSPIx->SR & FlagType){
		return FLAG_SET;
	}

	return FLAG_RESET;
}
// Enable or Disable SPI
/************************************************************************************************
 *@func name							- SPI_Control
 *
 *@brief								- Function to enable or disable SPI
 *
 *@param1								- Base Address of SPI Handle
 *@param2								- Enable or Disable macro
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_Control(SPI_Reg_t *pSPIx, uint8_t EnrDis){
	if(EnrDis == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_BIT_POS_SPE);
	}else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_BIT_POS_SPE);
	}
}

// Enable SSI
/************************************************************************************************
 *@func name							- SPI_SSI_Config
 *
 *@brief								- Function is used when SSM is set
 *
 *@param1								- Base Address of SPI Handle
 *@param2								- Enable or Disable macro
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_SSI_Config(SPI_Reg_t *pSPIx, uint8_t EnrDis){
	if(EnrDis == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_BIT_POS_SSI);
	}else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_BIT_POS_SSI);
	}
}



//Peripheral clock setup
/************************************************************************************************
 *@func name							- SPI_PeriphControl
 *
 *@brief								- Function to enable or disable peripherals clock for SPI
 *
 *@param1								- Base Address of SPI Handle
 *@param2								- Enable or Disable macro
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_PeriphControl(SPI_Reg_t *pSPIx, uint8_t EnrDis){
	if(EnrDis == ENABLE){
		if(pSPIx == SPI1){
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3){
			SPI3_PCLK_EN();
		}
	}else{
		if(pSPIx == SPI1){
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3){
			SPI3_PCLK_DI();
		}
	}
}

// Initialize
/************************************************************************************************
 *@func name							- SPI_Init
 *
 *@brief								- Function initialize peripherals for SPI
 *
 *@param1								- Base Address of SPI Handle
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_Init(SPI_Handle_t *pSPIHandle){
	// Enable SPI Peripheral clock
	SPI_PeriphControl(pSPIHandle->pSPIx, ENABLE);

	uint32_t temp = 0;
	// Configure device to be Master or Slave. MSTR in SPI_CR1 bit 2
	temp |= (pSPIHandle->pGPIO_PinConfig.SPI_DeviceMode << SPI_CR1_BIT_POS_MSTR);

	// Configure Communication type eg. full duplex ...
	if(pSPIHandle->pGPIO_PinConfig.SPI_BusConfig_Com == FULL_DUPLEX_SPI){
		// Clear BIDIMODE
		temp &= ~(1<< SPI_CR1_BIT_POS_BIDIMODE);

	}else if(pSPIHandle->pGPIO_PinConfig.SPI_BusConfig_Com == HALF_DUPLEX_SPI){
		// Set BIDIMODE
		temp |= (1 << SPI_CR1_BIT_POS_BIDIMODE);

	}else if(pSPIHandle->pGPIO_PinConfig.SPI_BusConfig_Com == SIMPLEX_DUPLEX_SPI_RX){
		// Clear BIDIMODE and Set RXONLY
		temp &= ~(1 << SPI_CR1_BIT_POS_BIDIMODE);
		temp |=  (1 << SPI_CR1_BIT_POS_RXONLY);
	}
	// Configure DFF
	temp |=(pSPIHandle->pGPIO_PinConfig.SPI_DFF << SPI_CR1_BIT_POS_DFF);

	// Configure CPHA
	temp |= (pSPIHandle->pGPIO_PinConfig.SPI_Cpha << SPI_CR1_BIT_POS_CPHA);

	// Configure CPOL
	temp |= (pSPIHandle->pGPIO_PinConfig.SPI_Cpha << SPI_CR1_BIT_POS_CPOL);

	// Configure SSM
	temp |= (pSPIHandle->pGPIO_PinConfig.SPI_Ssm << SPI_CR1_BIT_POS_SSM);

	// Configure SPEED (BR)
	temp |= (pSPIHandle->pGPIO_PinConfig.SPI_ClkSpeed << SPI_CR1_BIT_POS_BR);

	pSPIHandle->pSPIx->CR1 |= temp;
}

// De-Initialize
/************************************************************************************************
 *@func name							- SPI_DeInit
 *
 *@brief								- Function De-Initialize peripherals for SPI
 *
 *@param1								- Base Address of SPI peripheral
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_DeInit(SPI_Reg_t *pSPIx){
	if(pSPIx == SPI1){
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2){
		SPI2_REG_RESET();
	}
	else if(pSPIx == SPI3){
		SPI3_REG_RESET();
	}
}


// Send data
/************************************************************************************************
 *@func name							- SPI_Data_Send
 *
 *@brief								- Function Send data for SPI
 *
 *@param1								- Base Address of SPI peripheral
 *@param2								- Transmitted Buffer
 *@param3								- Number of Byte to Transmit
 *
 *@return								- none
 *
 *@Note									- This Function is a blocking call also known as polling base call
 */
void SPI_Data_Send(SPI_Reg_t *pSPIx, uint8_t *pTxBuffer, uint32_t byte_len){
	// Check the data byte length user want send
	while(byte_len > 0){
		// Wait until Tx Buffer is empty
		while((FlagStatus(pSPIx, SPI_TXE_FLAG)) == FLAG_RESET){};
			// Check DFF bits
			if((pSPIx->CR1 & (1 << SPI_CR1_BIT_POS_DFF))){
				// 16 Bits
				pSPIx->DR = *((uint16_t*)pTxBuffer);
				byte_len --;
				byte_len --;
				(uint16_t*)pTxBuffer++;
			}else{
				// 8 Bits
				pSPIx->DR = *pTxBuffer;
				byte_len --;
				pTxBuffer++;

			}

	}
}

// Receive data
/************************************************************************************************
 *@func name							- SPI_Data_Receive
 *
 *@brief								- Function Receive data for SPI
 *
 *@param1								- Base Address of SPI peripheral
 *@param2								- Received Buffer
 *@param3								- Number of Byte to Receive
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_Data_Receive(SPI_Reg_t *pSPIx, uint8_t *pRxBuffer, uint32_t dyte_len){

}

// Interrupt Configuration
/************************************************************************************************
 *@func name							- SPI_InterruptConfig
 *
 *@brief								- Function Configure Interrupt for SPI
 *
 *@param1								- Interrupt number
 *@param2								- Enable or Disable Interrupt
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_InterruptConfig(uint8_t IRQNum, uint8_t EnrDis){

}

// Interrupt Service Routine Handling
/************************************************************************************************
 *@func name							- SPI_IRQHandler
 *
 *@brief								- Function Handle Interrupt Service Routine for SPI
 *
 *@param1								- Base Address of SPI Handle
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_IRQHandler(SPI_Handle_t *pSPIHandle){

}

// Configuration Interrupt Service Priority
/************************************************************************************************
 *@func name							- SPI_InterruptPriorityConfig
 *
 *@brief								- Function Configure Interrupt for SPI
 *
 *@param1								- Interrupt number
 *@param2								- Priority of Interrupt
 *
 *@return								- none
 *
 *@Note									- none
 */
void SPI_InterruptPriorityConfig(uint8_t IRQNum ,uint32_t IRQ_Priority){

}
