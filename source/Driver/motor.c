/************************************************************
 *              motor.c -----
 *		(c) Copyright 2013 HUST RENESAS LAB,The Department of CSE, HUST
 *                        All Rights Reserved
 *Filename                :   motor.c
 *Programmer(s)           :   Chen xi
 *Description             :
 *Modification History	  :
 *01a 2013-8-3 20:45:50                
****************************************************************/
#include "motor.h"

static uint8_t gl_Motor_PWMBuff[4] = {0};

/******************************************************************************
** Function name:		check_pwm_limit
**
** Descriptions:		check the pwm duty percent
**
** parameters:			pwm_value
**
** Returned value:	pwm_value
** 
******************************************************************************/
int8_t check_pwm_limit(int8_t pwm_value)
{
	if(pwm_value > 95)
	{
		pwm_value = 100;	
	}
    if(pwm_value < -95)
    {
        pwm_value = -100;
    }
	if((pwm_value < 5) && (pwm_value > -5))
	{
		pwm_value = 0;
	}
	return pwm_value;
}


/*
* LF --- Left  Front
* RF --- Right Front
* LR --- Left  Rear
* RR --- Right Rear
*/
void PWMout_LF(int8_t LF_pwm_value)
{
	int8_t LF_pwm_duty_percent = 0;
	
	LF_pwm_duty_percent = check_pwm_limit(LF_pwm_value);

    if(LF_pwm_duty_percent >= 0)
    {
        SET_LF_MOTOR_FORWARD();
    }
    else
    {
        SET_LF_MOTOR_BACKWARD();
        LF_pwm_duty_percent = -LF_pwm_duty_percent;
    }
	
	gl_Motor_PWMBuff[LF] = 100 - LF_pwm_duty_percent;
}

void PWMout_RF(int8_t RF_pwm_value)
{
	int8_t RF_pwm_duty_percent = 0;
	
	RF_pwm_duty_percent = check_pwm_limit(RF_pwm_value);

    if(RF_pwm_duty_percent >= 0)
    {
        SET_RF_MOTOR_FORWARD();
    }
    else
    {
        SET_RF_MOTOR_BACKWARD();
        RF_pwm_duty_percent = -RF_pwm_duty_percent;
    }
	
	gl_Motor_PWMBuff[RF] = 100 - RF_pwm_duty_percent;
}

void PWMout_LR(int8_t LR_pwm_value)
{
	int8_t LR_pwm_duty_percent = 0;
	
	LR_pwm_duty_percent = check_pwm_limit(LR_pwm_value);

    if(LR_pwm_duty_percent >= 0)
    {
        SET_LR_MOTOR_FORWARD();
    }
    else
    {
        SET_LR_MOTOR_BACKWARD();
        LR_pwm_duty_percent = -LR_pwm_duty_percent;
    }
	
	gl_Motor_PWMBuff[LR] = 100 - LR_pwm_duty_percent;
}

void PWMout_RR(int8_t RR_pwm_value)
{
	int8_t RR_pwm_duty_percent = 0;
	
	RR_pwm_duty_percent = check_pwm_limit(RR_pwm_value);

    if(RR_pwm_duty_percent >= 0)
    {
        SET_RR_MOTOR_FORWARD();
    }
    else
    {
        SET_RR_MOTOR_BACKWARD();
        RR_pwm_duty_percent = -RR_pwm_duty_percent;
    }
	
	gl_Motor_PWMBuff[RR] = 100 - RR_pwm_duty_percent;
}
/******************************************************************************
** Function name:		PWMOut4
**
** Descriptions:		Set the pwm16 match values
**
** parameters:			timer number, match numner and the value
**
** Returned value:	None
** 
******************************************************************************/
void PWMOut4(int8_t LR_pwm_value, int8_t LF_pwm_value, int8_t RR_pwm_value, int8_t RF_pwm_value)
{  
	PWMout_LF(LF_pwm_value);
	PWMout_RF(RF_pwm_value);
	PWMout_LR(LR_pwm_value);
	PWMout_RR(RR_pwm_value);  
}



//output the MotorPWM in the interrupt
void IRQ_motor_PWMOut(void)
{
	LPC_TMR16B0->MR1 = 6 * gl_Motor_PWMBuff[LF];  //Left  Front Driver
	LPC_TMR16B1->MR1 = 6 * gl_Motor_PWMBuff[RF];  //Right Front Driver
	LPC_TMR16B1->MR0 = 6 * gl_Motor_PWMBuff[LR];  //Left  Rear  Driver 
	LPC_TMR16B0->MR0 = 6 * gl_Motor_PWMBuff[RR];  //Right Rear  Driver		
}
