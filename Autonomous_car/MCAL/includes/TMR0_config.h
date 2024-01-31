/*
 * TMR0_config.h
 *
 * Created: 10/8/2023 10:29:25 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_


/* Options FOR TMR0 Mode:
1- TMR0_NORMAL_MODE
2- TMR0_CTC_MODE
3- TMR0_FAST_PWM_MODE*/

#define TMR0_MODE                      TMR0_NORMAL_MODE


#define TMR0_PRELOAD_VALUE             113
#define TMR0_OVER_FLOW_COUNTER         977

#define TMR0_CTC_COUNTER               4000


#endif /* TMR0_CONFIG_H_ */