/*
 * pwm.c
 *
 * Created: 22.05.2022 21:21:32
 *  Author: Heinrich
 */ 

#include "pwm.h"

void pwm_init (void)
{
	// init COM1B1 as GPIO (PC1) and default low:
	// if bit COM1B1 is 0, then pc1 acts as gpio with original state (so, output and low)
	DDRC |= (1 << PC1);		// PC1 is an output
	PORTC &= ~(1 << PC1);	// and is low
	
	// pin pc1 (OC1B, Timer 1 output compare B) connected to sensor heater
	// fast pwm mode, prescaler 64,  top 0x03ff (1023) = 244Hz
	// pwm mode 7, 10-bit resolution
	// clear oc1b on compare match
	TCCR1A |= (1 << WGM11)|(1 << WGM10)|(1 << COM1B1);
	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
	pwm_setDuty(0);
	
	
	//pd1 is PWM too...
}

void pwm_setDuty (uint16_t duty)
{
	if (duty == 0)
	{
		TCCR1A &= (1 << COM1B1);
	}
	else
	{
		OCR1B = duty;
		if (!(TCCR1A |= (1 << COM1B1)))
		{
			TCCR1A |= (1 << COM1B1);
		}
	}
}

void pwm_shutdown (void)
 {
	 TCCR1A &= (1 << COM1B1);
 }