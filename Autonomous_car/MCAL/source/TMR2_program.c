/*
 * TMR2_program.c
 *
 * Created: 10/6/2023 2:20:07 PM
 *  Author:  Autonomous Car Team
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TMR2_interface.h"
#include "TMR2_private.h"
#include "TMR2_config.h"


void TMR2_init  (void)
{
	#if TMR2_MODE == TMR2_NORMAL_MODE
	// Select Normal mode
	CLR_BIT(TCCR2,WGM20);
	CLR_BIT(TCCR2,WGM21);
	
	// PRELOAD VALUE
	TCNT2 =TMR2_PRELOAD_VALUE;


	// enable TMR OVER FLOW INTURRUPT
	SET_BIT (TIMSK,TOIE2);
	
	#elif TMR2_MODE == TMR2_CTC_MODE
	// Select CTC mode
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	
	//ENABLE OC
	SET_BIT(TIMSK,OCIE2);
	
	
	#elif TMR2_MODE == TMR2_FAST_PWM_MODE
	// Select FAST PWM mode
	SET_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	
	// SELECT NON INVERTING MODE
	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
	
	
	
	
	#endif
	
}


void TMR2_start (void)
{
	//SET PRESCALER 64
	CLR_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
}


void TMR2_stop  (void)
{
	
	// STOP
	CLR_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	CLR_BIT(TCCR2,CS22);
	
}

static void(*private_pCallBackOVF)(void)=NULL;

static void(*private_pCallBackCTC)(void)=NULL;


void TMR2_setCallBackOVF(void(*ptrToFun)(void))
{
	
	if (ptrToFun!=NULL)
	{
		private_pCallBackOVF=ptrToFun;
	}
}



void __vector_5(void)__attribute__((signal));

void __vector_5(void)
{
	static u16 ovfCounter=0;
	
	ovfCounter++;
	
	if(TMR2_OVER_FLOW_COUNTER == ovfCounter)
	{
		TCNT2=TMR2_PRELOAD_VALUE;
		
		ovfCounter=0;
		if(private_pCallBackOVF!=NULL)
		{
			private_pCallBackOVF();
		}
	}
}



void TMR2_setCallBackCTC(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackCTC=ptrToFun;
	}
}


void TMR2_setCompareMatchValue(u8 compareValue)
{
	OCR2=compareValue;
}

volatile static u16 private_ctcCounter;

void __vector_4(void)__attribute__((signal));
			  
void __vector_4(void)
{
	static u16 ctcCounter=0;
	
	ctcCounter++;
	
	if(private_ctcCounter== ctcCounter)
	{
		
		ctcCounter=0;
		if(private_pCallBackCTC!=NULL)
		{
			private_pCallBackCTC();
		}
	}
}



void TMR2_setDelay_ms_usingCTC   (u16 delat_ms)
{
	// under condition ticktime 4 micro second
	OCR2=249;
	private_ctcCounter=delat_ms;
}


void TMR2_setDutyCycle           (u8 dutycylce)
{
	if (dutycylce<=100)
	{
		OCR2=((dutycylce*256)/100)-1;
	}
}
