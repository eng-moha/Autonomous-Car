/*
 * ultrasonic_program.c
 *
 * Created: 10/29/2023 5:51:16 PM
 *  Author: Autonomous Car Team
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/*----UTILES_LIB----*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*---- MCAL----*/
#include "EXTI_interface.h"
#include "DIO_interface.h"
#include "TMR0_private.h"
#include "ultrasonic_interface.h"
#include "ultrasonic_config.h"
#include "ultrasonic_private.h"

volatile  u8  exit_count=1;
volatile  f32 distance=0;
volatile  u16 start_time=0,end_time=0,timeDiff=0;
volatile  u16 ovfCounter_start,ovfCounter_end;
extern volatile   u16 OvfCounter;

void ultrasonic_init(void)
{
	DIO_setPinDirection(ECHO_PORT,ECHO_PIN,DIO_PIN_INPUT);      // trigger 
	DIO_setPinDirection(TRIGGER_PORT,DIO_PIN0,DIO_PIN_OUTPUT);  // echo
	EXTI_setCallBack(&EXTI_action);                             // external interrupt call back 
}

void ultrasonic_sendTrigger(void)
{
	DIO_setPinValue(TRIGGER_PORT,TRIGGER_PIN,DIO_PIN_HIGH);    // high 
	_delay_us(10);                                             // 10 micro seconds delay
	DIO_setPinValue(TRIGGER_PORT,TRIGGER_PIN,DIO_PIN_LOW);     // low
}

void ultrasonic_get_Distance(f32* returned_distance)
{
	ultrasonic_sendTrigger();                                  // send trigger
	EXTI_enable(EXTI_INT0,EXTI_RISING_EDGE);                   // set external interrupt for rising edge
	_delay_ms(50);                                             // stability delay
	*returned_distance=distance;                               // get the distance
}



void EXTI_action(void)                                       // call back function
{
	
	if (exit_count<=2)          // check for counter status
	{						    
 		if (exit_count==1)      // check if it is the first entry
		{
			// store the start time value
			start_time=TCNT0;   
			
			// store number of OVFs at the start of the signal
			ovfCounter_start=OvfCounter; 
			
			// at the first entry  we change the capture edge to falling edge to capture echo signal
			EXTI_enable(EXTI_INT0,EXTI_FALLING_EDGE);
			
		}
		
		else if(exit_count==2) // check if it's the second entry
		{   
			//store end time value
			end_time=TCNT0;
			
			//store number of OVFs at the end of signal
			ovfCounter_end=OvfCounter;
			
			//calculate the time difference between start and end
			timeDiff=(end_time+(256*ovfCounter_end))-(start_time+(256*ovfCounter_start));
			
			//calculate the distance
			distance=timeDiff*0.068;// 	f32 ton=(h*(64/16000000))/2 >> 	*distance=ton*34000;
			
		    //reset the counter to calculate new signal
			exit_count=0;
			
		}
        
		//increase the counter to sync with the entry state
		exit_count++;
	}
	
}

