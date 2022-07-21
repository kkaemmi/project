#define F_CPU 160000000L

#include <avr/io.h>

char DC_MOTOR;

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
	PORTD = 0xE0;
	
	TCCR1A |= (1 << WGM11) | (1 << WGM10);        // High speed PWM mode
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);      // Set none-inverting mode
	TCCR1B |= (1 << CS12);                        // CSB 64
	DDRB |= (1 << PINB1) | (1 << PINB2);          // Use Pin
	
	while(1)
	{
		PORTB = DC_MOTOR;
		
		if((PIND & 0x20) == 0x00)   // Á¤¹æÇâ (SW = PD5, EN1 = PB0, IN1 = PB1)
		{
			OCR1A = 200;
			DC_MOTOR = 0x03;
		}
		
		if((PIND & 0x40) == 0x00)   // ¿ª¹æÇâ (W = PD6, IN2 = PB2)
		{
			OCR1B = 200;
			DC_MOTOR = 0x05;
		}
		
		if((PIND & 0x80) == 0x00)   // ¸ØÃã (SW = PD7)
		{
			DC_MOTOR = 0x00;
			OCR1A = 0;
			OCR1B = 0;
		}
	}
	return 0;
};