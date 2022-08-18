#define F_CPU 16000000UL

#include "UART.h"
#include <avr/io.h>
#include <util/delay.h>

unsigned char data, receive;

int main(void)
{
	
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
	TCCR2B |= (1 << CS22);
	DDRD |= (1 << PIND3);
	DDRB |= (1 << PINB3);
	
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
	TCCR0B |= (1 << CS02);
	DDRD |= (1 << PIND5);
	DDRD |= (1 < <PIND6);

	while (1)
	{

		UART_INIT();
		
		data = UART_receive();
		
		if(data == '\0') //{PORTB = 0x00; PORTD = 0x00;}
		{
			DDRB = 0x00;
			DDRD = 0x00;
			
			PORTB = 0x00;
			PORTD = 0x00;
			
			if (data == 'q')
			{
				OCR2A = 200;
			}
			else if (data == 'w')
			{
				OCR2B = 200;
			}
			else if (data == 'e')
			{
				OCR0A = 200;
			}
			else if (data == 'r')
			{
				OCR0B = 200;
			}
			else if (data == 's')
			{
				OCR2B = 0;
				OCR2A = 0;
				OCR0B = 0;
				OCR0A = 0;
			}
		}
	}
}