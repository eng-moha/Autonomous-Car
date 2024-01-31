/*
 * LCD_program.c
 *
 * Created: 10/1/2023 12:12:44 PM
 *  Author: Autonomous Car Team
 */ 
 
 
 #define F_CPU 16000000UL
 #include <util/delay.h>
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

void LCD_init(void)
{
	DIO_setPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);
	
	_delay_ms(35);
	
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);   // RS=0 
   
	DIO_setPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);   //RW =0 
	
	private_writeHalfPort(0b0010);
	DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH); 
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);   
    // Function Set
	LCD_sendComand(0b00101000);
	_delay_ms(45);
	//Display ON/OFF
	LCD_sendComand(0b00001111);
	_delay_us(45);
	//Display Clear
	LCD_sendComand(0b00000001);
	_delay_ms(2);
	
	LCD_sendComand(0b00000110);
	
	
}
			
void LCD_sendComand (u8 comand) 
{
	
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);   // RS=0 

	DIO_setPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);   //RW =0 
	
	
	    private_writeHalfPort(comand>>4);
	
	
	
		DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH); 
	    _delay_ms(1);
		DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);   

	    private_writeHalfPort(comand);
	
	
	    DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH); 
	    _delay_ms(1);
		DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);   

}


void LCD_sendChar(u8 data)
{
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);   // RS=1 
   
	DIO_setPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);   //RW =0 
	
	
    private_writeHalfPort(data>>4);
	
	DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH); 
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
    private_writeHalfPort(data);
	
	DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH); 
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);	
	
	
	
}

void LCD_sendString(u8* String)
{
	u8 counter=0;
	while(String[counter]!='\0')
	{
		LCD_sendChar(String[counter]);
		++counter;
	}
}
void LCD_clear(void)
{
	LCD_sendComand(0b00000001);
	_delay_ms(2);
}



static void  private_writeHalfPort(u8 value)
{
	
	if (GET_BIT(value,0)==1)
	{
		DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_LOW);
	}
	if (GET_BIT(value,1)==1)
	{
		DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_LOW);
	}
	
	if (GET_BIT(value,2)==1)
	{
		DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_LOW);
	}
	
	if (GET_BIT(value,3)==1)
	{
		DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_HIGH);
	}
	else
	{
		DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_LOW);
	}
	
	
}



void LCD_sendNumber         (s32 number)
{
	u8 count=0;
	u8 reminder,arr[16]={0,0,0,0,0};
	if (number<0)
	{
		LCD_sendChar('-');
		number=number * -1;
	}
	else if (number==0)
	{
		LCD_sendChar('0');
		
	}
	while (number !=0)
	{
		reminder=number % 10; //2
		arr[count]=reminder; //
		number=number/10;    //5
		count++;
		
	}
	

    s8 num_count;
	for(num_count =(count-1);num_count>=0;num_count--)//54321
	{
		LCD_sendChar(arr[num_count]+'0');
		
	}
	
	
	
}