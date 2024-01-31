/*
 * Autonomous_car.c
 *
 * Created: 10/29/2023 7:09:51 PM
 * Author : Autonomous Car Team
 */
#define  F_CPU 16000000UL   
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "TMR0_interface.h"
#include "TMR1_interface.h"
#include "GI_interface.h"
#include "EXTI_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "DCM_interface.h"
#include "SRVM_interface.h"
#include "ultrasonic_interface.h"


#define  stop_distance 30 


int main(void)
{
	f32 distance;                      //measured distance
    f32 distance_Right,distance_Left;  //left and right measured distance 
  
  //initializations 
	GI_enable();
	ultrasonic_init();
    LCD_init();
    TMR0_init();
    TMR0_start();
    DCM_init(DCM_A);
    DCM_init(DCM_B);
	SRVM_init();
	
	
	SRVM_on(0);         // reset servo motor for zero position (forward position)
	_delay_ms(1000);    // delay for stability  
	
	
    
    while(1)
    {
	    
		  // sensor reads
          ultrasonic_get_Distance(&distance);
	    
		  //display the readings
	      LCD_clear();
	      LCD_sendString((u8*)"distance:");
	      LCD_sendNumber(distance);
	      LCD_sendString((u8*)" cm");
	      _delay_ms(250);
	      LCD_clear();
		
		
          // check for the measured distance
          if(distance>stop_distance)
          {
	          //safe distance ---> move forword
	          DCM_Car_Move_Forward();
	          
          }
          
          
          else if(distance<=stop_distance)
          {
            //unsafe distance ---> stop
			DCM_Car_Stop();
           
		   
		    //Sudden obstacle 
			if (distance<10)  
            {
                DCM_Car_Move_Back();//go back to safe distance
                _delay_ms(500); 
				DCM_Car_Stop();
            }
           
	
			//Look at left direction
            SRVM_on(90);
            _delay_ms(1000);
			
		
			//sensor reads
			ultrasonic_get_Distance(&distance);
			
			//store it at left distance variable
            distance_Left=distance;
			
			//display the stable reading
			LCD_sendString((u8*)"L-dist.:");
			LCD_sendNumber(distance_Left);
			LCD_sendString((u8*)" cm");
            _delay_ms(500);
          
		    // Look at Right direction
		    SRVM_on(-90);
            _delay_ms(1000);
         
			//sensor reads
			ultrasonic_get_Distance(&distance);
			
	    	//store it at right distance variable	
            distance_Right=distance;
	    	
			//display the stable reading
			LCD_clear();
	    	LCD_sendString((u8*)"R-dist.:");
	    	LCD_sendNumber(distance_Right);
	    	LCD_sendString((u8*)" cm");
            _delay_ms(500);
	    	LCD_clear();
	    	
			// reset the servo position (forward position)
			SRVM_on(0);
			
			//compare the two distances if the left obstacle is farther than right obstacle --> move left
		    if (distance_Left>distance_Right)
			{
            
			//display that the car will move to the left
			LCD_clear();
			LCD_sendString((u8*)"Moving Left");
           
		    //move the car to the left
		    DCM_Car_Move_Left_90();
			LCD_clear();
			
           }
		   
		   
           else 
           {
            
			//display that the car will move to the right 
			LCD_clear();
			LCD_sendString((u8*)"Moving Right");
			
			//move the car to the right
            DCM_Car_Move_Right_90();
			LCD_clear();
				
            }
        }
    }
}












