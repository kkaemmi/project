#define F_CPU 16000000UL

#include <avr/io.h>
#include "UART.h"

unsigned char data, receive;
char DC_MOTOR;

int DCMotor(void);
int motor__init__(void);
int main(void)
{
	DCMotor();
	
	return 0;
}

int DCMotor(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << CS21);
	DDRB |= (1 << PINB0) | (1 << PINB1) | (1 << PINB2);
	
	UART_INIT();
	
	while (1)
	{
		data = UART_receive();
		
		PORTB = DC_MOTOR;
		
		motor__init__();

		if (data == 'q')
		{
			OCR1A = 200;
			OCR1B = 0;

			DC_MOTOR = 0x03; // 0000 0011
		}
		else if (data == 'w')
		{
			OCR1A = 0;
			OCR1B = 200;

			DC_MOTOR = 0x05; // 0000 0101
		}
		else if (data == 'e')
		{
			OCR1A = 0;
			OCR1A = 0;
			
			DC_MOTOR = 0x00;
		}
	}
	return 0;
};

int motor__init__()
{
	OCR1B = 0;
	
	return 0;
}