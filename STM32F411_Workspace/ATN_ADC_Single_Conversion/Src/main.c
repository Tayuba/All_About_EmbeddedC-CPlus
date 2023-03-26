#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "UART.h"
#include "adc.h"

uint32_t sensor_value;

int main(void) {
	pa1_adc_init();

	UART2_Tx_Init();
	while(1){
		start_conversion();
		sensor_value = adc_read();
		printf("Sensor value is %d\n\r", (int)sensor_value);

	}
}

