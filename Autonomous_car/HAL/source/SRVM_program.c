/*
 * SRVM_program.c
 *
 *  
 *      Author: Autonomous Car Team 
 */


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TMR1_interface.h"
#include "DIO_interface.h"

/* HAL */

#include "SRVM_interface.h"
#include "SRVM_private.h"


void SRVM_init(void)
{
	/* OC1A pin as output pin */
	DIO_setPinDirection(DIO_PORTD,DIO_PIN5,DIO_PIN_OUTPUT);

	/* TMR1 init at pwm mode 14 */
	TMR1_init();
}


void SRVM_on(s8 angle)
{
	
	/* Set pwm fre. = 50 */
    u8 pwm_freq_HZ= 50;
	
	/* Set pwm duty cycle between 5 : 10
	 depend on desired angle(0 : 180)*/
    f32 dutyCycle;
	SRVM_mapValue(angle,-90,90,5,10,& dutyCycle);
	
	TMR1_setFastPWM_usingMode14( dutyCycle, pwm_freq_HZ);
    

	/* TMR1 start */
	TMR1_start();

}


void SRVM_off(void)
{
	/* TMR1 stop */
	TMR1_stop ();

}






// Mapping function to map values from one range to another
void SRVM_mapValue(f32 value, f32 fromMin, f32 fromMax, f32 toMin,f32 toMax,f32* returned_value) 
{
	// Ensure that the input value is within the input range
	if (value < fromMin) {
		value = fromMin;
		} else if (value > fromMax) {
		value = fromMax;
	}

	// Calculate the mapped value in the output range
	*returned_value = toMin + (value - fromMin) * (toMax - toMin) / (fromMax - fromMin);
     
}

