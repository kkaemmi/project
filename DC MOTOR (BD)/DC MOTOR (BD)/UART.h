#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>

void UART_INIT(void);						// UART 초기화
unsigned char UART_receive(void);			// 1바이트 수신
void UART_transmit(unsigned char data);		// 1바이트 송신

#endif