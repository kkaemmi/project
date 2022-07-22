#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

#define F_CPU 16000000L
#define ROTATION_DELAY 2000
#define PULSE_MIN 2200
#define PULSE_MAX 3800
#define PULSE_MID 3000

//#define PULSE_00		1200
//#define PULSE_45		2100
//#define PULSE_90		3150
//#define PULSE_135		4000
//#define PULSE_180		5000

char data;

void INIT_TIMER(void)
{
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= (1 << CS11);
	ICR1 = 40000;
	TCCR1A |= (1<<COM1A1);
	DDRB |= (1 << PINB1) | (1 << PINB2);
	DDRD |= (1 << PIND5) | (1 << PIND6);
}

int main(void)
{
	INIT_TIMER();
	
	DDRB = 0xFF;
	DDRD = 0xFF;

	PORTB = 0x00;
	PORTD = 0x00;                                                                                                                                                                                                                                                                                                                                    
	
	while (1)
	{
		UART_INIT();

		data = UART_receive();
		
		switch(data)
		{
// ¿À¸¥ÂÊ
			case 'A' :
			OCR1A = PULSE_MIN;
			OCR1B = PULSE_MIN;
			break;

			case 'B' :
			OCR1A = PULSE_MAX;
			OCR1B = PULSE_MAX;
			break;
			
			case 'C' :
			OCR1A = PULSE_MID;
			OCR1B = PULSE_MID;
			break;
// ¿ÞÂÊ
			case 'D' :
			OCR0A = PULSE_MIN;
			OCR0B = PULSE_MIN;
			break;

			case 'E' :
			OCR0A = PULSE_MAX;
			OCR0B = PULSE_MAX;
			break;
			
			case 'F' :
			OCR0A = PULSE_MID;
			OCR0B = PULSE_MID;
			break;
			
			default :
			break;
		}
	}
	return 0;
}