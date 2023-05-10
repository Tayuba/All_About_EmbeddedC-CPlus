/*
 * stm32f407_SPI_Driver.h
 *
 *  Created on: Apr 30, 2023
 *      Author: ayuba
 */

#ifndef INC_STM32F407_SPI_DRIVER_H_
#define INC_STM32F407_SPI_DRIVER_H_

#include "stm32f407xx.h"
/*
 * SPI pin configurable
 * */
typedef struct{
	uint8_t SPI_DeviceMode;							// Possible values from @SPI_DEVICE_MODE
	uint8_t SPI_BusConfig_Com;						// Possible values from @SPI_BUS_CONFIG_COMMUNICATION
	uint8_t SPI_DFF;								// Possible values from @SPI_DFF
	uint8_t SPI_Cpha;								// Possible values from @SPI_CPHA
	uint8_t SPI_Cpol;;								// Possible values from @SPI_CPOL
	uint8_t SPI_Ssm;								// Possible values from @SPI_SSM
	uint8_t SPI_ClkSpeed;							// Possible values from @SPI__CLOCK_SPEED
}SPI_Config;
/*
 * SPIx Handle Structure*
 */
typedef struct {
	SPI_Reg_t 			*pSPIx;   					// Holds base address of SPI to which the pin belongs
	SPI_Config		pGPIO_PinConfig;				// Holds SPI pin configuration settings
	uint8_t			*pTxBuffer;						// Store Tx Buffer address
	uint8_t			*pRxBuffer;						// Store Rx Buffer address
	uint8_t			 TxLen;							// Store length of Tx
	uint8_t			 RxLen;							// Store length of Rx
	uint8_t			 TxState;						// Store State of Tx
	uint8_t			 RxState;						// Store State of Rx
}SPI_Handle_t;

/*************************************************************************************************************************
 * 													APIs Support Driver
 * ***********************************************************************************************************************/

//Peripheral clock setup
void SPI_PeriphControl(SPI_Reg_t *pSPIx, uint8_t EnrDis);

// SPI Flag Status check
uint8_t FlagStatus(SPI_Reg_t *pSPIx, uint32_t FlagType);

// SPI Control Enable or Disable
void SPI_Control(SPI_Reg_t *pSPIx, uint8_t EnrDis);

// Initialize and De-Initialize
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Reg_t *pSPIx);

// SSI Enable
void SPI_SSI_Config(SPI_Reg_t *pSPIx, uint8_t EnrDis);

// Receive and Send data
void SPI_Data_Send(SPI_Reg_t *pSPIx, uint8_t *pTxBuffer, uint32_t byte_len);
void SPI_Data_Receive(SPI_Reg_t *pSPIx, uint8_t *pRxBuffer, uint32_t byte_len);

uint8_t SPI_Data_SendIntp(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t byte_len);
uint8_t SPI_Data_ReceiveIntp(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t byte_len);

// Interrupt Configuration and Interrupt Service Routine Handling
void SPI_InterruptConfig(uint8_t IRQNum, uint8_t EnrDis);
void SPI_IRQHandler(SPI_Handle_t *pSPIHandle);
void SPI_InterruptPriorityConfig(uint8_t IRQNum ,uint32_t IRQ_Priority);

// OVR clear
void SPI_OVR_Clear(SPI_Reg_t *pSPIx);

// Close and Finish transmission
void SPI_Close_Finish_Transmission(SPI_Handle_t *pSPIHandle);

// Close and Finish reception
void SPI_Close_Finish_Reception(SPI_Handle_t *pSPIHandle);

// Application call back
void spi_appEvencallBack(SPI_Handle_t *pSPIHandle, uint8_t Event);

//@SPI_DEVICE_MODE
#define SLAVE_DEVICE_MODE_SPI				0
#define MASTER_SDEVICE_MODE_SPI				1

//@SPI_BUS_CONFIG_COMMUNICATION
#define FULL_DUPLEX_SPI						1
#define HALF_DUPLEX_SPI						2
#define SIMPLEX_DUPLEX_SPI_RX				3


//@SPI__CLOCK_SPEED
#define SPI_CLK_FREQ_DIV2					0
#define SPI_CLK_FREQ_DIV4					1
#define SPI_CLK_FREQ_DIV8					2
#define SPI_CLK_FREQ_DIV16					3
#define SPI_CLK_FREQ_DIV32					4
#define SPI_CLK_FREQ_DIV64					5
#define SPI_CLK_FREQ_DIV128					6
#define SPI_CLK_FREQ_DIV256					7

//@SPI_DFF
#define SPI_DFF_8_BITS						0
#define SPI_DFF_16_BITS						1

//@SPI_CPOL
#define SPI_CPOL_LOW						0
#define SPI_CPOL_HIGH						1

//@SPI_CPHA
#define SPI_CPHA_LOW						0
#define SPI_CPHA_HIGH						1

//@SPI_SSM
#define SPI_SSM_DI							0
#define SPI_SSM_EN							1

// SPI Status Flags
#define SPI_TXE_FLAG						(1 << SPI_SR_BIT_POS_TXE)
#define SPI_RXNE_FLAG						(1 << SPI_SR_BIT_POS_RXNE)
#define SPI_BSY_FLAG						(1 << SPI_SR_BIT_POS_BSY)

// SPI Application States
#define SPI_READY							0
#define SPI_BUSY_IN_RX						1
#define SPI_BUSY_IN_TX						2

// SPI Events
#define TE_COMPLT							0
#define RE_COMPLT							1
#define OVR_COMPLT							2

#endif /* INC_STM32F407_SPI_DRIVER_H_ */
