/*
 * EXTI_interface.h
 *
 * Created: 9/25/2023 12:38:11 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


typedef enum 
{
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2	
}EXTI_source;

typedef enum 
{
	EXTI_RISING_EDGE,
	EXTI_FALLING_EDGE,
	EXTI_LOW_LEVEL,
    EXTI_ANY_LOGICAL_CHANGE	
}EXTI_trigger;

void EXTI_enable (EXTI_source interruptSource,EXTI_trigger interruptTriggerEdge);
void EXTI_disable(EXTI_source interruptSource);
void EXTI_setCallBack(void(*ptrToFun)(void));

#endif /* EXTI_INTERFACE_H_ */