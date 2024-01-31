/*
 * TMR2_config.h
 *
 * Created: 10/6/2023 2:20:47 PM
 *  Author:  Autonomous Car Team
 */ 


#ifndef TMR2_CONFIG_H_
#define TMR2_CONFIG_H_


/* Options FOR TMR2 Mode:
1- TMR2_NORMAL_MODE
2- TMR2_CTC_MODE
3- TMR2_FAST_PWM_MODE
*/

#define TMR2_PRELOAD_VALUE      113
#define TMR2_OVER_FLOW_COUNTER  977


#define TMR2_MODE  TMR2_FAST_PWM_MODE

#define TMR2_CTC_COUNTER 4000

#endif /* TMR2_CONFIG_H_ */