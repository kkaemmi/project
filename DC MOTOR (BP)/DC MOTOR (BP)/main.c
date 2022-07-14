#define F_CPU 160000000L
#include <avr/io.h>
#include <util/delay.h>

char DC_MOTOR;
char state = 0;

int DCMotor(void);
int main(void)
{
	DCMotor();
	
	return 0;
}

int DCMotor(void)
{
	DDRB = 0xFF;
	DDRD = 0x00;

	PORTB = 0x00;
	PORTD = 0xC0;
	
	while(1)
	{
		PORTB = DC_MOTOR;
		
		if((PIND & 0x40) == 0x00 && state == 0)
		{
			DC_MOTOR = 0x03;
			state = 1;
		}
		if((PIND & 0x40) == 0x00 && state == 1)
		{
			DC_MOTOR = 0x05 ;
			state = 0;
		}
		if((PIND & 0x80) == 0x00)
		{
			DC_MOTOR = 0x00;
		}
	}
	return 0;
};