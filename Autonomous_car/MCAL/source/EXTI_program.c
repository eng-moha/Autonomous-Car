/*
 * EXTI_program.c
 *
 * Created: 9/25/2023 12:37:23 PM
 *  Author:  Autonomous Car Team
 */

 
/*----UTILES_LIB----*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*---- MCAL----*/
#include "EXTI_interface.h"
#include "EXTI_private.h"


static void (*private_pCallBackEXTI)(void)=NULL;



void EXTI_enable (EXTI_source interruptSource,EXTI_trigger interruptTriggerEdge)
{
	switch(interruptSource)
	{
		case EXTI_INT0:      
		switch(interruptTriggerEdge)    //interrupt trigger edge INT0
		{
			case EXTI_RISING_EDGE:
			  SET_BIT (MCUCR,ISC00);
			  SET_BIT (MCUCR,ISC01);
			break;
			
			case EXTI_FALLING_EDGE:
			  CLR_BIT (MCUCR,ISC00);
			  SET_BIT (MCUCR,ISC01);
			break;
			
			case EXTI_LOW_LEVEL:
			  CLR_BIT (MCUCR,ISC00);
			  CLR_BIT (MCUCR,ISC01);
			break;
			
			case EXTI_ANY_LOGICAL_CHANGE:
			  SET_BIT (MCUCR,ISC00);
			  CLR_BIT (MCUCR,ISC01);
			break;
		}
		SET_BIT(GICR,INT0);  //Enable INT0
		break;
		
		case EXTI_INT1:
		 switch(interruptTriggerEdge)    //interrupt trigger edge INT1
		 {
			 case EXTI_RISING_EDGE:
			  SET_BIT (MCUCR,ISC10);
			  SET_BIT (MCUCR,ISC11);
			break;
			
			case EXTI_FALLING_EDGE:
			  CLR_BIT (MCUCR,ISC10);
			  SET_BIT (MCUCR,ISC11);
			break;
			
			case EXTI_LOW_LEVEL:
			  CLR_BIT (MCUCR,ISC10);
			  CLR_BIT (MCUCR,ISC11);
			break;
			
			case EXTI_ANY_LOGICAL_CHANGE:
			  SET_BIT (MCUCR,ISC10);
			  CLR_BIT (MCUCR,ISC11);
			break;
			 
		 }
		 SET_BIT(GICR,INT1);  //Enable INT1
		break;
		
		case EXTI_INT2:
		switch(interruptTriggerEdge)
		{
			case EXTI_RISING_EDGE:
			  SET_BIT (MCUCSR,ISC2);
			break;
			
			case EXTI_FALLING_EDGE:
			  CLR_BIT (MCUCSR,ISC2);
			break;
		}
		SET_BIT(GICR,INT2);  //Enable INT2
		break;
		
		
	}
	
	
	
}
void EXTI_disable(EXTI_source interruptSource)
{
	switch(interruptSource)
	{
		case EXTI_INT0:
		CLR_BIT(GICR,INT0);
		break;
		case EXTI_INT1:
		CLR_BIT(GICR,INT1);
		break;
		case EXTI_INT2:
		CLR_BIT(GICR,INT2);
		break;
	
	}
	
}


void EXTI_setCallBack(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackEXTI = ptrToFun;
	}
}



void __vector_1(void)__attribute__((signal));
void __vector_1(void)
{
	
	
	//call action
	if(private_pCallBackEXTI != NULL)
	{
		private_pCallBackEXTI();
	}
	
	

}