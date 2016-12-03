/************************************************************
 *              Motor.h -----
 *		(c) Copyright 2010 HUST RENESAS LAB,The Department of CSE, HUST
 *                        All Rights Reserved
 *Filename                :   
 *Programmer(s)           :   Sun Jiajaing
 *Description             :
 *Modification History	  :
 *01a 2010-11-20 11:03:13                
****************************************************************/
#ifndef _MOTOR_H_
#define	_MOTOR_H_
/*   Files include     */
#include "include.h"
/*   Constant Define   */

/*   Function Declaration   */

#define LF 0
#define RF 1
#define LR 2
#define RR 3

void PWMout_LF(int8_t LF_pwm_value);
void PWMout_RF(int8_t RF_pwm_value);
void PWMout_LR(int8_t LR_pwm_value);
void PWMout_RR(int8_t RR_pwm_value);

//  #define SET_LF_MOTOR_BACKWARD()  (LPC_GPIO2->DATA|=0x0200)  // P2.9 
//  #define SET_LF_MOTOR_FORWARD() (LPC_GPIO2->DATA&=(~0x0200))
//  #define SET_RF_MOTOR_BACKWARD()  (LPC_GPIO2->DATA|=0x0004)  // P2.2 
//  #define SET_RF_MOTOR_FORWARD() (LPC_GPIO2->DATA&=(~0x0004))
//  #define SET_RR_MOTOR_BACKWARD()  (LPC_GPIO0->DATA|=0x0080)  // p0.7 
//  #define SET_RR_MOTOR_FORWARD() (LPC_GPIO0->DATA&=(~0x0080))
//  #define SET_LR_MOTOR_BACKWARD()  (LPC_GPIO2->DATA|=0x0400)  // p2.10 
//  #define SET_LR_MOTOR_FORWARD() (LPC_GPIO2->DATA&=(~0x0400))

#define SET_RR_MOTOR_BACKWARD()  (LPC_GPIO2->DATA|=0x0200)  // P2.9  前左电机
#define SET_RR_MOTOR_FORWARD() (LPC_GPIO2->DATA&=(~0x0200))
#define SET_LR_MOTOR_FORWARD()  (LPC_GPIO2->DATA|=0x04)  // P2.2      前右电机
#define SET_LR_MOTOR_BACKWARD() (LPC_GPIO2->DATA&=(~0x04))
#define SET_LF_MOTOR_FORWARD()  (LPC_GPIO0->DATA|=0x80)  // p0.7      后左电机
#define SET_LF_MOTOR_BACKWARD() (LPC_GPIO0->DATA&=(~0x80))
#define SET_RF_MOTOR_BACKWARD()  (LPC_GPIO2->DATA|=0x0400)  // p2.10     后右电机
#define SET_RF_MOTOR_FORWARD() (LPC_GPIO2->DATA&=(~0x0400))


void PWMOut4(int8_t LF_pwm_value, int8_t RF_pwm_value, int8_t LR_pwm_value, int8_t RR_pwm_value);

void IRQ_motor_PWMOut(void);

#endif    //  End of _MOTOR_H_
