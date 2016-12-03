/************************************************************
 *              Control.h -----
 *		(c) Copyright 2010 HUST RENESAS LAB,The Department of CSE, HUST
 *                        All Rights Reserved
 *Filename                :   
 *Programmer(s)           :   Sun Jiajaing
 *Description             :
 *Modification History	  :
 *01a 2010-11-4 16:37:11                
****************************************************************/
#ifndef _MOTORCONTROL_H_
#define	_MOTORCONTROL_H_
/*   Files include     */
#include "include.h"
/*   Constant Define   */
#define    PWM_OUTSIDE_R       (pwmdutyTemp * OutsideRDiff / 100)
#define    PWM_INSIDE_R        (pwmdutyTemp * InsideRDiff  / 100)
#define    PWM_INSIDE_F        (pwmdutyTemp * InsideFDiff  / 100)

/*   Function Declaration   */
void PWMOut(int8_t pwmDuty, int8_t angle);
void SpeedOut(int speed, int angle);

#endif    //  End of _MOTORCONTROL_H_
