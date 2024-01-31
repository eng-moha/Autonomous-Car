/*
 * TMR0_private.h
 *
 * Created: 10/8/2023 10:29:13 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef TMR0_PRIVATE_H_
#define TMR0_PRIVATE_H_

#define TMR0_NORMAL_MODE            1
#define TMR0_CTC_MODE               2
#define TMR0_FAST_PWM_MODE          3


#define    TCCR0     (*(volatile u8*)0x53)

#define   CS00         0
#define   CS01         1
#define   CS02         2
#define   WGM01        3
#define   COM00        4
#define   COM01        5
#define   WGM00        6
#define   FOC0         7

#define    TCNT0     (*(volatile u8*)0x52)
#define    OCR0      (*(volatile u8*)0x5C)

#define    TIMSK     (*(volatile u8*)0x59)

#define    TOIE0        0
#define    OCIE0        1

#define    TIFR      (*(volatile u8*)0x58)
 
#define    TOV0         0
#define    OCF0         1



#endif /* TMR0_PRIVATE_H_ */