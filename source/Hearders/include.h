/**********************************************************************************
 *						Includes.h ----- Header Functions
 *		(c) Copyright 2013 HUST RENESAS LAB,The Department of CSE, HUST
 *                       	 All Rights Reserved
 *Filename             :   Includes.h
 *Programmer(s)        :   Chen Xi
 *Description          :
 *Modification History :
 *01a 2013-8-1 10:31:03
**********************************************************************************/
#ifndef   _INCLUDES_H_
#define   _INCLUDES_H_

/*       SYSTEM LIBRARY        */

/*       MCU LIBRARY           */ 
#include "LPC11xx.h"			/* LPC11xx Peripheral Registers */        //  For simplifying stdio; placed first in the file.
#include <stdint.h>
#include <stdio.h>

/*       Driver Libary          */
#include "SystemInit.h"
#include "Init_motor.h"
#include "Init_GPIO.h"
#include "digital_sensor.h"
#include "Init_servo.h"
#include "motor.h"
#include "servo.h"

/*       Common Libary          */
#include "common.h"

/*       User Control         */
#include "Arithmetic.h"
#include "servo_control.h"   
#include "IRQHandler.h"
#include "motor_control.h"
#include "protect.h"

/*      Test                  */
#include "uart.h"
#include "test.h"

/*      Encoder               */
#include "Init_Encoder.h"


extern uint8_t gl_ucSensorNumber;
extern int8_t gl_cServoAngle;
extern int8_t gl_cMotorPWM;	
extern uint32_t gl_uiDigitalSensor;
extern uint8_t gl_ucSwitchValue;
extern int gl_iPattern;
extern unsigned long gl_ulTimerCnt;
extern uint32_t SystemAHBFrequency;
extern int gl_iProgramPeriod;
extern int gl_iCurSpeed;
extern unsigned long gl_ulTotalDistance;
extern int gl_iStraightSpeed;
extern int gl_iR600Speed;
extern int gl_iR450Speed;
extern int gl_iNowErr;
extern unsigned int gl_uiLastDigitalSensor;
extern int gl_iSensorDistance[11];

#endif     //  End of _INCLUDES_H_

