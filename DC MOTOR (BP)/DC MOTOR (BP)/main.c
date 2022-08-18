#define F_CPU 16000000L

#include <avr/io.h>

char DC_MOTORB;
char DC_MOTORD;

int DCMotor(void);

int main(void)
{
	DCMotor();
	
	return 0;
}

int DCMotor(void)
{
	DDRB = 0xFF;
	DDRD = 0xFF;

	PORTB = 0x00;
	PORTD = 0x00;
	
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
	TCCR2B |= (1 << CS22);
	DDRB |= (1 << PINB3);
	DDRD |= (1 << PIND3);
	
	while(1)
	{
		PORTB = DC_MOTORB;
		PORTD = DC_MOTORD;

		if((PIND & 0x20) == 0x00)
		{
			OCR2A = 150;
			DC_MOTORB = 0x08;
		}
		
		if((PIND & 0x40) == 0x00)
		{
			OCR2B = 150;
			DC_MOTORD = 0x08;
		}
		
		if((PIND & 0x80) == 0x00)
		{
			DC_MOTORB = 0x00;
			DC_MOTORD = 0x00;
			OCR2A = 0;
			OCR2B = 0;
		}
	}
	return 0;
};