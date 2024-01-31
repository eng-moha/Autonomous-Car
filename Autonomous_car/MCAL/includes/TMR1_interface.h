/*
 * TMR1_interface.h
 *
 * Created: 10/13/2023 8:22:25 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_

void TMR1_init (void);
void TMR1_start(void);
void TMR1_stop (void);

void TMR1_setCompareMatchValueA (u16 compareValue);
void TMR1_setFastPWM_usingMode14(f32 dytyCycle, u16 frequency_hz);


#endif /* TMR1_INTERFACE_H_ */