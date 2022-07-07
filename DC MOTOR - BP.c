#define F_CPU 160000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	char MOTOR = 0x00;
	char state = 0;
	
	DDRB = 0xFF;
	DDRD = 0x00;
	
	PORTD = 0xC0;
	
	while(1)
	{
		PORTB = MOTOR;
		if((PIND & 0x40) == 0x00 && state == 0)
		{
			MOTOR = 0x05;
			state =1;
		}
		if((PIND & 0x40) == 0x00 && state == 1)
		{
			MOTOR = 0x03;
			state =0;
		}
		if((PIND & 0x80) == 0x00)
		{
			MOTOR = 0x00;
		}
	}
}