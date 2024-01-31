/*
 * TMR2_interface.h
 *
 * Created: 10/6/2023 2:20:25 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef TMR2_INTERFACE_H_
#define TMR2_INTERFACE_H_

void TMR2_init  (void);
void TMR2_start (void);
void TMR2_stop  (void);
void TMR2_setCallBackOVF(void(*ptrToFun)(void));
void TMR2_setCallBackCTC(void(*ptrToFun)(void));
void TMR2_setCompareMatchValue(u8 compareValue);
void TMR2_setDelay_ms_usingCTC   (u16 delat_ms);
void TMR2_setDutyCycle           (u8 dutycylce);


#endif /* TMR2_INTERFACE_H_ */