/************************************************************
 *              Servo.h -----
 *		(c) Copyright 2010 HUST RENESAS LAB,The Department of CSE, HUST
 *                        All Rights Reserved
 *Filename                :   
 *Programmer(s)           :   Sun Jiajaing
 *Description             :
 *Modification History	  :
 *01a 2010-11-4 16:37:11                
****************************************************************/
#ifndef _SERVO_H_
#define	_SERVO_H_
/*   Files include     */
#include "include.h"
/*   Constant Define   */
#define  SERVO_CENTER      (8560 + 14*50)			 // 舵机中心值，可以通过Test函数来测试后调整
#define  ANGLE_SCALE       50
#define  MAX_ANGLE         60

/*   Function Declaration   */
void SetServoAngle(int8_t angle);
void servo_PWMOut(void);

#endif    //  End of _SERVO_H_
