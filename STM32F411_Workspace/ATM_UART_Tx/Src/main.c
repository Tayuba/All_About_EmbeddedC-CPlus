#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "UART.h"


int main(void) {
	UART2_Tx_Init();
	while(1){
//		UART2_Write('Y');
		printf("Hello From Ayuba Tahiru Monnie!..................\n\r");
	}

}

