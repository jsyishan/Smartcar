/**********************************************************************************
 *						Init_motor.h ----- Header Functions
 *		(c) Copyright 2013 HUST RENESAS LAB,The Department of CSE, HUST
 *                       	 All Rights Reserved
 *Filename             :   Init_motor.h
 *Programmer(s)        :   Chen Xi
 *Description          :
 *Modification History :
 *01a 2013-8-1 20:40:00
**********************************************************************************/
#ifndef __INIT_MOTOR_H 
#define __INIT_MOTOR_H

#include "include.h"


/* The test is either MAT_OUT or CAP_IN. Default is MAT_OUT. */
#define TIMER_MATCH		0


#define EMC0	4
#define EMC1	6
#define EMC2	8
#define EMC3	10

#define MATCH0	(1<<0)
#define MATCH1	(1<<1)
#define MATCH2	(1<<2)
#define MATCH3	(1<<3)

///* For 16-bit timer, make sure that TIME_INTERVAL should be no
//greater than 0xFFFF. */
#ifndef TIME_INTERVAL
#define TIME_INTERVAL	(SystemAHBFrequency/1000 - 1)

#define timer16_Frequency  6  //the Frequency of the timer16, 6 ---> 6M
#define timer_period       1  //ms

#define  timer16_0_period  600 * timer_period //1ms
#define  timer16_1_period  600 * timer_period //1ms
///* depending on the SystemFrequency and SystemAHBFrequency setting, 
//if SystemFrequency = 60Mhz, SystemAHBFrequency = 1/4 SystemAHBFrequency, 
//10mSec = 150.000-1 counts */
#endif

void delayMs(uint8_t timer_num, uint32_t delayInMs);

void Init_motor(void);


#endif          //  End of __INIT_MOTOR_H

