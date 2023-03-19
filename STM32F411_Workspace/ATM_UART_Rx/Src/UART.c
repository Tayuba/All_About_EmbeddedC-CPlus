/*
 * UART.c
 *
 *  Created on: Mar 19, 2023
 *      Author: ayuba
 */
#include "UART.h"
#define GPIOAENR			(1U<<0)
#define UART2ENR			(1U<<17)

#define CR1_TE				(1U<<3)
#define CR1_RE				(1U<<2)
#define CR1_UE				(1U<<13)
#define SR_TXE				(1U<<7)
#define SR_RXNE				(1U<<5)

#define Sys_freq			16000000
#define APB1_Clk			Sys_freq

#define UART_Baudrate		115200


static void uart_baurate_set(USART_TypeDef *USARTx,uint32_t periphClk, uint32_t Baudrate);
static uint16_t compute_uart_BD(uint32_t periphClk, uint32_t Baudrate);
void UART2_Write(int at);


int __io_putchar(int at){
	UART2_Write(at);
	return at;
}
void UART2_RxTx_Init(void){
/**************Configure UART GPIO Pin*****************/
//	Enable clock to gpioa
	RCC->AHB1ENR |= GPIOAENR;

//	Set PA2 mode to alternate func mode
	GPIOA->MODER |=(1U<<5);
	GPIOA->MODER &= ~(1U<<4);
//	Set PA3 mode to alternate func mode
	GPIOA->MODER |=(1U<<7);
	GPIOA->MODER &= ~(1U<<6);

//	Set PA2 to alternate type to uart_tx that is AF07
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
//	Set PA3 to alternate type to uart_tx that is AF07
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);
/**************Configure UART module*****************/
//	Enable clock access to uart2
	RCC->APB1ENR |= (1U<<17);
//	config baudrate
	uart_baurate_set(USART2, APB1_Clk, UART_Baudrate);
//	config the transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);
//	Enable UART module
	USART2->CR1 |= CR1_UE;

}




void UART2_Tx_Init(void){
/**************Configure UART GPIO Pin*****************/
//	Enable clock to gpioa
	RCC->AHB1ENR |= GPIOAENR;
//	Set PA2 mode to alternate func mode
	GPIOA->MODER |=(1U<<5);
	GPIOA->MODER &= ~(1U<<4);
//	Set PA2 to alternate type to uart_tx that is AF07
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

/**************Configure UART module*****************/
//	Enable clock access to uart2
	RCC->APB1ENR |= (1U<<17);
//	config baudrate
	uart_baurate_set(USART2, APB1_Clk, UART_Baudrate);
//	config the transfer direction
	USART2->CR1 = CR1_TE;
//	Enable UART module
	USART2->CR1 |= CR1_UE;

}
char UART_Read(void){
//	check if receive data is not empty
	while (!(USART2->SR & SR_RXNE)){

	}
	return USART2->DR;
}

void UART2_Write(int at){
//	check if transmit data register is free or empty
	while (!(USART2->SR & SR_TXE)){

	}
//	write transmitter data
	USART2->DR = (at & 0xFF);

}

static void uart_baurate_set(USART_TypeDef *USARTx,uint32_t periphClk, uint32_t Baudrate){
	USARTx->BRR = compute_uart_BD(periphClk,Baudrate);
}

static uint16_t compute_uart_BD(uint32_t periphClk, uint32_t Baudrate){
	return (periphClk + (Baudrate / (2U))) / Baudrate ;

}
