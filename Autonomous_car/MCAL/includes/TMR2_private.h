/*
 * TMR2_private.h
 *
 * Created: 10/6/2023 2:21:06 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef TMR2_PRIVATE_H_
#define TMR2_PRIVATE_H_

/* MACROS FOR TIMER MODE CONFIGURATIONS */
#define TMR2_NORMAL_MODE            1
#define TMR2_CTC_MODE               2
#define TMR2_FAST_PWM_MODE          3

#define TCCR2 (*(volatile u8*)0x45) // not done yet
#define CS20             0
#define CS21             1
#define CS22             2
#define WGM21            3
#define COM20            4
#define COM21            5
#define WGM20            6
#define FOC2             7

// Timer/Counter Register
#define TCNT2            (*(volatile u8*)0x44) //not done yet

// Output Compare Register
#define OCR2             (*(volatile u8*)0x43) //not done yet

// Timer/Counter Interrupt Mask Register
#define TIMSK            (*(volatile u8*)0x59)
#define OCIE2             7
#define TOIE2             6

// Timer/Counter Interrupt Flag Register
#define TIFR             (*(volatile u8*)0x58)
#define OCF2             7
#define TOV2             6




#endif /* TMR2_PRIVATE_H_ */