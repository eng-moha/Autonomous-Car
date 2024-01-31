/*
 * ultrasonic_interface.h
 *
 * Created: 10/29/2023 5:50:56 PM
 *  Author: Autonomous Car Team
 */ 


#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

void ultrasonic_init(void);
void ultrasonic_sendTrigger(void);
void ultrasonic_get_Distance(f32* distance);



#endif /* ULTRASONIC_INTERFACE_H_ */