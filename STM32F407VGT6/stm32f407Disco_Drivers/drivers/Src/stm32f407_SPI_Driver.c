/*
 * stm32f407_SPI_Driver.c
 *
 *  Created on: Apr 30, 2023
 *      Author: ayuba
 */
#include "stm32f407_SPI_Driver.h"
static void spi_rxneInterrupt_Handle(SPI_Handle_t *pSPIHandle);;
static void spi_txeInterrupt_Handle(SPI_Handle_t *pSPIHandle);
static void spi_ovrInterrupt_Handle(SPI_Handle_t *pSPIHandle);
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
 *@param2								- Buffer Transmitted
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

// Send data With Interrupt capability
/************************************************************************************************
 *@func name							- SPI_Data_SendIntp
 *
 *@brief								- Function Send data for SPI with interrupt
 *
 *@param1								- Base Address of SPI Handle
 *@param2								- Buffer Transmitted
 *@param3								- Number of Byte to Transmit
 *
 *@return								- none
 *
 *@Note									- none
 */
uint8_t SPI_Data_SendIntp(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t byte_len){
	// Check state first
	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX){
		// Save Tx Buffer address
		pSPIHandle->pTxBuffer   = pTxBuffer;
		// Save Byte length
		pSPIHandle->TxLen	    = byte_len;
		// Mark the SPI transmission as busy
	    pSPIHandle->TxState	    = SPI_BUSY_IN_TX;
		// Enable TXEIE
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_BIT_POS_TXEIE);
	}
	return state;

}

// Receive data With Interrupt capability
/************************************************************************************************
 *@func name							- SPI_Data_ReceiveIntp
 *
 *@brief								- Function Receive data for SPI
 *
 *@param1								- Base Address of SPI Handle
 *@param2								- Received Buffer
 *@param3								- Number of Byte to Receive
 *
 *@return								- none
 *
 *@Note									- none
 */
uint8_t SPI_Data_ReceiveIntp(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t byte_len){
	// Check state first
	uint8_t state = pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX){
		// Save Tx Buffer address
		pSPIHandle->pRxBuffer   = pRxBuffer;
		// Save Byte length
		pSPIHandle->RxLen 	    = byte_len;
		// Mark the SPI transmission as busy
		pSPIHandle->RxState	    = SPI_BUSY_IN_RX;
		// Enable TXEIE
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_BIT_POS_RXNEIE);
	}
	return state;

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
	if(EnrDis == ENABLE){
		if(IRQNum <= 31){
			// ISRE0 Register is to be programmed
			*(NVIC_ISERO) |= (1 << IRQNum);

		} else if(IRQNum >= 31 && IRQNum <64){
			// ISRE1 Register is to be programmed
			*(NVIC_ISER1) |= (1 << (IRQNum % 32));

		} else if(IRQNum >= 64 && IRQNum <96){
			// ISRE2 Register is to be programmed
			*(NVIC_ISER2) |= (1 << (IRQNum % 64));
		}
	}else{
		if(IRQNum <= 31){
			// ICRE0 Register is to be programmed
			*(NVIC_ICERO) |= (1 << (IRQNum % 32));

		} else if(IRQNum >= 31 && IRQNum <64){
			// ICRE1 Register is to be programmed
			*(NVIC_ICER1) |= (1 << (IRQNum % 32));

		} else if(IRQNum >= 64 && IRQNum <96){
			// ICRE2 Register is to be programmed
			*(NVIC_ICER2) |= (1 << (IRQNum % 64));
		}
	}
}

// OVR clear
void SPI_OVR_Clear(SPI_Reg_t *pSPIx){
	uint8_t tempRead;
	tempRead = pSPIx->DR;
	tempRead = pSPIx->SR;
	(void)tempRead;
}

// Close and Finish transmission
void SPI_Close_Finish_Transmission(SPI_Handle_t *pSPIHandle){
	/*  Finished spi transmission */
	// Buffer empty, hence no more data to send
	pSPIHandle->pSPIx->SR &= ~(1 << SPI_CR2_BIT_POS_TXEIE);
	pSPIHandle->pTxBuffer  = NULL;
	pSPIHandle->TxLen  	   = 0;
	pSPIHandle->TxState    = SPI_READY;

}

// Close and Finish reception
void SPI_Close_Finish_Reception(SPI_Handle_t *pSPIHandle){
	/* Finished spi reception */
	// Buffer empty, hence no more data to send
	pSPIHandle->pSPIx->SR &= ~(1 << SPI_CR2_BIT_POS_RXNEIE);
	pSPIHandle->pRxBuffer  = NULL;
	pSPIHandle->RxLen  	   = 0;
	pSPIHandle->RxState    = SPI_READY;
}




// IRQ Helping Functions
static void spi_rxneInterrupt_Handle(SPI_Handle_t *pSPIHandle){
	// Check DFF bits
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_BIT_POS_DFF)){
		*((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->RxLen--;
		(uint16_t*)pSPIHandle->pRxBuffer--;
	}else{
		*(pSPIHandle->pRxBuffer) = (uint8_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		(uint8_t*)pSPIHandle->pRxBuffer--;
	}

	if(!(pSPIHandle->RxLen)){
		/* Finished spi reception */
		// Buffer empty, hence no more data to send
		SPI_Close_Finish_Reception(pSPIHandle);
		spi_appEvencallBack(pSPIHandle, RE_COMPLT);
	}
}
static void spi_txeInterrupt_Handle(SPI_Handle_t *pSPIHandle){
	// Check DFF bits
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_BIT_POS_DFF)){
		// 16 Bits
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;

	}else{
		// 8 Bits
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
		pSPIHandle->TxLen--;
		pSPIHandle->pTxBuffer++;
	}

	if(!(pSPIHandle->TxLen)){
		/*  Finished spi transmission */
		// Buffer empty, hence no more data to send
		SPI_Close_Finish_Transmission(pSPIHandle);
		spi_appEvencallBack(pSPIHandle, TE_COMPLT);
	}

}
static void spi_ovrInterrupt_Handle(SPI_Handle_t *pSPIHandle){
	// clear OVR flag and send information to application
	uint8_t tempRead;
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX){
		tempRead = pSPIHandle->pSPIx->DR;
		tempRead = pSPIHandle->pSPIx->SR;
	}(void)tempRead;

	spi_appEvencallBack(pSPIHandle, OVR_COMPLT);
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
	/* Check where interrupt occurred */
	uint8_t temp1, temp2;
	// At RXNE?
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_BIT_POS_RXNE);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_BIT_POS_RXNEIE);

	if(temp1 && temp2){
		// Then Handle RXNE
		spi_rxneInterrupt_Handle(pSPIHandle);
	}

	// At TXE?
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_BIT_POS_TXE);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_BIT_POS_TXEIE);

	if(temp1 && temp2){
		// Then Handle TXE
		spi_txeInterrupt_Handle(pSPIHandle);
	}


	// At OVR?
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_BIT_POS_OVR);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_BIT_POS_RXNEIE);

	if(temp1 && temp2){
		// Then Handle OVR
		spi_ovrInterrupt_Handle(pSPIHandle);
	}

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
	uint8_t iprx 		 = IRQNum / 4; 																			// To select interrupt priority register
	uint8_t iprx_section  = IRQNum % 4;       																	// To select section of selected interrupt priority register above
	uint8_t amount_shift = (8 * iprx_section) + (8 - STM32F407_PR_BIT_IMPLEMENTED); 							// STM32F407_PR_BIT_IMPLEMENTED has 4 bit implementation of priority, MCU such as TI.
	*(NVIC_IPR_BASE_ADDR + iprx) |= (IRQ_Priority << amount_shift);
}


__attribute__((weak)) void spi_appEvencallBack(SPI_Handle_t *pSPIHandle, uint8_t Event){

}
