/*
 * TMR1_program.c
 *
 * Created: 10/13/2023 8:22:05 PM
 *  Author:  Autonomous Car Team
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TMR1_interface.h"
#include "TMR1_config.h"
#include "TMR1_private.h"



void TMR1_init (void)
{
	//FAST PWM MODE
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	// Select Non Inverting Mode
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	
	
}
void TMR1_start(void)
{
	//PRESCALLER  64
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	
}
void TMR1_stop (void)
{
	CLR_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	
}


void TMR1_setCompareMatchValueA (u16 compareValue)
{
	
	OCR1A_u16=compareValue;

}


void TMR1_setFastPWM_usingMode14(f32 dytyCycle, u16 frequency_hz)
{
	if(dytyCycle <= 100)
	{
		// under condition non inverting fast pwm & tick time 4 MS
		
		ICR1_u16  = ((1000000UL/frequency_hz)/4)-1;
		
		OCR1A_u16 = ((dytyCycle*(ICR1_u16+1))/100.0)-1;
	}
}