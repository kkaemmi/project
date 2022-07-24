#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

char data;

int DCmotor();
int PINMODE();
int main(void)
{
	DCmotor();
	
	return 0;
}

int PINMODE()
{	
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << CS12);
		
	DDRB |= (1 << PINB0) | (1 << PINB1) | (1 << PINB2);
	DDRD |= (1 << PIND5) | (1 << PIND6) | (1 << PIND7) ;
	
	return 0;
}

int DCmotor()
{
	PINMODE();
	
	DDRB = 0xFF;
	DDRD = 0xFF;
		
	PORTB = 0x00;
	PORTD = 0x00;
	
	while(1)
	{
		UART_INIT();
		
		data = UART_receive();
		
		switch(data)
		{
			case '1':
			OCR1A = 0x03;
			break;
			case '2':
			OCR1B = 0x05;
			break;
			case '3':
			OCR0B = 0x60;
			break;
			case '4':
			OCR0A = 0xA0;
			break;
			case '0':
			OCR2A = 0x00;
			OCR2A = 0x00;
			break;
		}
	}
	return 0;
}