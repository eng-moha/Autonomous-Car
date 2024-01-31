/*
 * DIO_private.h
 *
 * Created: 8/25/2023 11:05:03 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


                              /* DIO REGISTERS*/
								 
/* DATA DIRCTION REGISTERS */
#define DDRA           (*(volatile u8*)0x3A)
#define DDRB           (*(volatile u8*)0x37)
#define DDRC           (*(volatile u8*)0x34)
#define DDRD           (*(volatile u8*)0x31)

/* OUTPUT REGISTERS */
#define PORTA          (*(volatile u8*)0x3B)
#define PORTB          (*(volatile u8*)0x38)
#define PORTC          (*(volatile u8*)0x35)
#define PORTD          (*(volatile u8*)0x32)

/* INPUT REGISTERS */
#define PINA           (*(volatile u8*)0x39)
#define PINB           (*(volatile u8*)0x36)
#define PINC           (*(volatile u8*)0x33)
#define PIND           (*(volatile u8*)0x30)


#endif /* DIO_PRIVATE_H_ */