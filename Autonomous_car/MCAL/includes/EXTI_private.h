/*
 * EXTI_private.h
 *
 * Created: 9/25/2023 12:37:40 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


        /*----MCU Control Register----*/
#define  MCUCR          (*(volatile u8*)0x55)
#define  ISC11           3
#define  ISC10           2
#define  ISC01           1
#define  ISC00           0
         /*----MCU Control and Status----*/
#define  MCUCSR         (*(volatile u8*)0x54)
#define  ISC2            6
        /*----General Interrupt Control----*/
#define  GICR           (*(volatile u8*)0x5B)
#define  INT0            6
#define  INT1            7
#define  INT2            5
        /*----General Interrupt Flag----*/
#define  GIFR           (*(volatile u8*)0x5A)
#define  INTF1           7
#define  INTF0           6
#define  INTF2           5

#endif /* EXTI_PRIVATE_H_ */