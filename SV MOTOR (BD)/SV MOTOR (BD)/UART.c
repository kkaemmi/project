#include "UART.h"

void UART_INIT(void)
{
	UCSR0A |= (1 << U2X0);   // 2배속 모드
	
	UBRR0H = 0x00;           // 통신 속도 설정2
	UBRR0L = 16;
	
	UCSR0B |= (1 << RXEN0);   // 송수신 가능
	UCSR0B |= (1 << TXEN0);	
}

unsigned char UART_receive(void)
{
	while( !(UCSR0A & (1 << RXC0)) );   // 데이터 수신 대기
	return UDR0;
}

void UART_transmit(unsigned char data)
{
	while( !(UCSR0A & (1 << UDRE0)) );   // 송신 가능 대기
	UDR0 = data;                         // 데이터 전송
}

void UART_printString(char *str)         // 문자열 송신
{
	for(int i = 0; str[i]; i++)          // '\0' 문자를 만날떄 까지 반복
	UART_transmit(str[i]);               // 바이트 단위 출력
}
