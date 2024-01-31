/*
 * TMR0_program.c
 *
 * Created: 10/8/2023 10:28:50 PM
 *  Author:  Autonomous Car Team
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "TMR0_private.h"

static void (*private_pCallBackCTC)(void)=NULL;

volatile static u16 private_ctcCounter;

void TMR0_init (void)
{
#if TMR0_MODE == TMR0_NORMAL_MODE
	//SET AS Normal Mode
	CLR_BIT(TCCR0,WGM00);   
	CLR_BIT(TCCR0,WGM01);

    TCNT0=TMR0_PRELOAD_VALUE;
	// ENABLE INTERRUPT OF OVERFLOW
	SET_BIT(TIMSK,TOIE0);
	
#elif TMR0_MODE == TMR0_CTC_MODE
    SET_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);
	// ENABLE INTERRUPT OF COMPARE MATCH
	SET_BIT(TIMSK,OCIE0);
	
	
#elif TMR0_MODE == TMR0_FAST_PWM_MODE
    SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
	
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
#endif
}


void TMR0_start  (void)
{
	// Select Prescaler Value = 64
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
}

void TMR0_stop                (void)
{
	// Select Prescaler Value = 0
	
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	
}


void TMR0_setCompareMatchValue(u8 compareValue)
{
	OCR0=compareValue;
}

void TMR0_setDelay_ms_usingCTC(u16 delay_ms) 
{
	// under condition tick time 4 MS
	OCR0 = 249;
	private_ctcCounter = delay_ms;
	
}

void TMR0_setDytyCycle        (u8 dytyCycle) 
{
	// under condition non inverting fast pwm
	if(dytyCycle<=100)
	{
		OCR0 = ((dytyCycle*256)/100)-1;
	}
}





void TMR0_setCallBackCTC(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackCTC = ptrToFun;
	}
}




void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
	static u16 ctcCounter = 0;
	ctcCounter++;
	
	if(private_ctcCounter == ctcCounter)
	{
		// Clear Counter
		ctcCounter = 0;
		
		//call action
		if(private_pCallBackCTC != NULL)
		{
			private_pCallBackCTC();
		}
	}
}

volatile u16 OvfCounter = 0;

void __vector_11(void)__attribute__((signal));
void __vector_11(void)
{
	OvfCounter++;
}
