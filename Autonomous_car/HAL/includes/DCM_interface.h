/*
 * DCM_interface.h
 *
 * Created: 10/13/2023 6:10:43 PM
 *  Author: Autonomous Car Team
 */ 


#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_


#define DCM_A                      1
#define DCM_B                      2

#define DCM_CLOCK_WISE                   1
#define DCM_COUNTER_CLOCK_WISE           2

void DCM_init(u8 motorId);
void DCM_on(u8 motorId ,u8 motorDirection);
void DCM_onControlSpeed(u8 motorId,u8 motorDirection, u8 motorSpeed);
void DCM_off(u8 motorId);
void DCM_Car_Move_Forward(void);
void DCM_Car_Move_Left_90(void);
void DCM_Car_Move_Right_90(void);
void DCM_Car_Move_Back(void);
void DCM_Car_Stop(void);


#endif /* DCM_INTERFACE_H_ */