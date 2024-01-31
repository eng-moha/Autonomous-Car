/*
 * DCM_program.c
 *
 * Created: 10/13/2023 6:10:55 PM
 *  Author: Autonomous Car Team
 */ 
#define  F_CPU 16000000UL
#include <util/delay.h>
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "TMR2_interface.h"
/**/
#include "DCM_interface.h"
#include "DCM_config.h"

void DCM_init(u8 motorId)
{
	DIO_setPinDirection(DMC_EN1_PORT,DMC_EN1_PIN,DIO_PIN_OUTPUT);    //H_EN1
	DIO_setPinDirection(DMC_EN2_PORT,DMC_EN2_PIN,DIO_PIN_OUTPUT);     //H_EN2
	
	DIO_setPinDirection(DMC_IN1_PORT,DMC_IN1_PIN,DIO_PIN_OUTPUT);     //H_A1
	DIO_setPinDirection(DMC_IN2_PORT,DMC_IN2_PIN,DIO_PIN_OUTPUT);      //H_A2
	
	DIO_setPinDirection(DMC_IN3_PORT,DMC_IN3_PIN,DIO_PIN_OUTPUT);       //H_A3
	DIO_setPinDirection(DMC_IN4_PORT,DMC_IN4_PIN,DIO_PIN_OUTPUT);       //H_A4
	
	TMR2_init();
	TMR2_start();
	
	switch(motorId)
	{
		
		case DCM_A :
		DIO_setPinValue(DMC_EN1_PORT,DMC_EN1_PIN,DIO_PIN_HIGH);
		break;
		
		case DCM_B :
		DIO_setPinValue(DMC_EN2_PORT,DMC_EN2_PIN,DIO_PIN_HIGH);
		break;
	}
	
	
}
void DCM_on(u8 motorId ,u8 motorDirection)
{  switch(motorId)
	{
		case DCM_A :
		switch(motorDirection)
		{
			case  DCM_CLOCK_WISE :
			DIO_setPinValue (DMC_IN1_PORT,DMC_IN1_PIN,DIO_PIN_HIGH);
			DIO_setPinValue(DMC_IN2_PORT,DMC_IN2_PIN,DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_setPinValue(DMC_IN2_PORT,DMC_IN2_PIN,DIO_PIN_HIGH);
			DIO_setPinValue(DMC_IN1_PORT,DMC_IN1_PIN,DIO_PIN_LOW);
			break;
		}
		
		break;
		
		case DCM_B:
		switch(motorDirection)
		{
			case  DCM_CLOCK_WISE :
			DIO_setPinValue(DMC_IN3_PORT,DMC_IN3_PIN,DIO_PIN_HIGH);
			DIO_setPinValue(DMC_IN4_PORT,DMC_IN4_PIN,DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_setPinValue(DMC_IN4_PORT,DMC_IN4_PIN,DIO_PIN_HIGH);
			DIO_setPinValue(DMC_IN3_PORT,DMC_IN3_PIN,DIO_PIN_LOW);
			break;
		}
		break;
	}
	
}
void DCM_onControlSpeed(u8 motorId,u8 motorDirection, u8 motorSpeed)
{
	DIO_setPinDirection(DIO_PORTD,DIO_PIN7,DIO_PIN_OUTPUT);       // OC2 TIMERS PIN SHOULD COMMECT WITH ENABLE PIN
	
	TMR2_setDutyCycle(motorSpeed);
	switch(motorId)
	{
		case DCM_A :
		
		switch(motorDirection)
		{
			case  DCM_CLOCK_WISE :
			DIO_setPinValue (DMC_IN1_PORT,DMC_IN1_PIN,DIO_PIN_HIGH);
			DIO_setPinValue (DMC_IN2_PORT,DMC_IN2_PIN,DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_setPinValue (DMC_IN2_PORT,DMC_IN2_PIN,DIO_PIN_HIGH);
			DIO_setPinValue (DMC_IN1_PORT,DMC_IN1_PIN,DIO_PIN_LOW);
			break;
		}
		
		break;
		case DCM_B:
		switch(motorDirection)
		{
			case  DCM_CLOCK_WISE :
			DIO_setPinValue (DMC_IN3_PORT,DMC_IN3_PIN,DIO_PIN_HIGH);
			DIO_setPinValue (DMC_IN4_PORT,DMC_IN4_PIN,DIO_PIN_LOW);
			break;
			
			case DCM_COUNTER_CLOCK_WISE:
			DIO_setPinValue (DMC_IN4_PORT,DMC_IN4_PIN,DIO_PIN_HIGH);
			DIO_setPinValue (DMC_IN3_PORT,DMC_IN3_PIN,DIO_PIN_LOW);
			break;
		}
		break;
	}
	
	
	
	
}
void DCM_off(u8 motorId)
{
	switch(motorId)
	{
		case DCM_A :
		DIO_setPinValue (DMC_IN1_PORT,DMC_IN1_PIN,DIO_PIN_LOW);
		DIO_setPinValue (DMC_IN2_PORT,DMC_IN2_PIN,DIO_PIN_LOW);
		break;
		
		case DCM_B:
		DIO_setPinValue (DMC_IN3_PORT,DMC_IN3_PIN,DIO_PIN_LOW);
		DIO_setPinValue (DMC_IN4_PORT,DMC_IN4_PIN,DIO_PIN_LOW);
		break;
	}
	
}
void DCM_Car_Stop(void)
{
	DCM_off(DCM_A);
	DCM_off(DCM_B);
}
void DCM_Car_Move_Forward(void)
{
	DCM_on(DCM_A ,DCM_CLOCK_WISE);
	DCM_on(DCM_B ,DCM_CLOCK_WISE);
}

void DCM_Car_Move_Right_90(void)
{
	DCM_on(DCM_A ,DCM_CLOCK_WISE);
	DCM_off(DCM_B);
	_delay_ms(1000);
	DCM_off(DCM_A);
	DCM_off(DCM_B);
}
void DCM_Car_Move_Left_90(void)
{
	DCM_on(DCM_B ,DCM_CLOCK_WISE);
	DCM_off(DCM_A);
	_delay_ms(1000);
	DCM_off(DCM_A);
	DCM_off(DCM_B);
}
void DCM_Car_Move_Back(void)
{
	DCM_on(DCM_A ,DCM_COUNTER_CLOCK_WISE);
	DCM_on(DCM_B ,DCM_COUNTER_CLOCK_WISE);
}
