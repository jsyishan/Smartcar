/************************************************************
 *              SmartCar6th --
 *		(c) Copyright 2013 HUST RENESAS LAB,The Department of CSE, HUST
 *                        All Rights Reserved
 *Filename                :   SmartCar6th.c
 *Programmer(s)           :   Chen xi
 *Description             :
 *Modification History	  :
 *01a 2013-8-3 20:34:57                
****************************************************************/

#include "include.h"

/*-----------------------------------------------------------------------------
 *  Global Parameters
 *-----------------------------------------------------------------------------*/
int8_t gl_cServoAngle = 0;				           //  输出舵机的角度变量(-50 - 50)
int8_t gl_cMotorPWM = 0;					           //  输出电机的PWM占空比(0-100)
uint8_t gl_ucSensorNumber = 0;
uint32_t gl_uiDigitalSensor = 0;
uint8_t gl_ucSwitchValue = 0;
int gl_iPattern = 0;
unsigned long gl_ulTimerCnt = 0;
int gl_iProgramPeriod = 0;
int gl_iCurSpeed = 0;
unsigned long gl_ulTotalDistance = 0;
int gl_iStraightSpeed = 0;
int gl_iR600Speed = 0;
int gl_iR450Speed = 0;
int gl_iNowErr = 0;
unsigned int gl_uiLastDigitalSensor = 0;
int gl_iSensorDistance[11] = {42,24,15,10,4,0,-4,-10,-15,-24,-42};


static void SetSpeed(void);

/* Main Program */
int main(void)
{
//	int a  = 0;
#ifdef CAR_DEBUG
    uint8_t string[] = {"\nTest Job End!\nIf you want to Test again,please Reset the CPU!\n"};
#endif

    Init_ALL();	
    SetServoAngle(0);
    PWMOut(0,0);
    BUZZER_OFF();


#ifdef DEBUG_SHAWN
    Test();
#endif 

#ifdef CAR_DEBUG
    TestCircuitBoard();
    UARTSend((uint8_t*) string);
#endif

    while(1)
    {
        while(gl_iProgramPeriod < 1)
        {
            ;                                    // Wait Until The Program Period End 
        }
        gl_iProgramPeriod = 0;

        gl_uiDigitalSensor = GetDigitalSensorValue();
        GetDigitalSensorNum(gl_uiDigitalSensor);

        gl_ucSwitchValue = ReadSwitch(0x0f);

        TeleControl();

        switch(gl_iPattern)
        {
            case 0: BUZZER_ON();
                    WriteLEDOnDrive(0x05);
                    SetSpeed();//根据拨码设置不同档位
                    if(!(GET_START_BAR()))
                    {
                        gl_iPattern = 11;
                    }
                    break;

            case 11:BUZZER_OFF();
                    WriteLEDOnDrive(0x0a);
                    Control();
                    if((gl_uiLastDigitalSensor== 0x0001) && (gl_uiDigitalSensor == 0x0000))
                    {
                        gl_iPattern = 21;
                    }
                    else if((gl_uiLastDigitalSensor == 0x0400) && (gl_uiDigitalSensor == 0x0000))
                    {
                        gl_iPattern = 22;
                    }
                    break;


            case 12:BUZZER_OFF();
                    WriteLEDOnDrive(0x01);
                    RightTrace();
                    break;

            case 13:BUZZER_OFF();
                    WriteLEDOnDrive(0x02);
                    LeftTrace();
                    break;

            case 21:BUZZER_ON();                 // Dangerous Mode(Right) 
                    WriteLEDOnDrive(0x04);
                    PWMOut4(0,100,0,0);
                    gl_cServoAngle = 55;
                    SetServoAngle(gl_cServoAngle);
                    if(gl_uiDigitalSensor & 0x0003)
                    {
                        gl_iPattern = 11;
                    }
                    break;

            case 22:BUZZER_ON();                 // Dangerous Mode(Left) 
                    WriteLEDOnDrive(0x08);
                    PWMOut4(0,0,0,100);
                    gl_cServoAngle = -55;
                    SetServoAngle(gl_cServoAngle);
                    if(gl_uiDigitalSensor & 0x0600)
                    {
                        gl_iPattern = 11;
                    }
                    break;

            case 9: BUZZER_ON();
                    WriteLEDOnDrive(0x0f);
                    Control();
                    gl_cMotorPWM = 0;
                    PWMOut(gl_cMotorPWM,0);
                    break;
        }
        gl_uiLastDigitalSensor = gl_uiDigitalSensor;
    }
}

/************************************************************************
 * Function         SetSpeed                                              
 * Usage            Set Speed                           
 * Argument         NONE                                                
 * Return value     NONE                                                
 * Modification History:                                                
 * 01a 2012-12-13 14:41:48   
 *
 ************************************************************************/
static void SetSpeed (void) 
{
    switch((gl_ucSwitchValue & 0x03))
    {
        case 0: gl_iStraightSpeed = 70;//3&4
                gl_iR600Speed = 65;
                gl_iR450Speed = 55;
                break;
        case 1: gl_iStraightSpeed = 50;//300;//3
                gl_iR600Speed = 45;
                gl_iR450Speed = 35;
                break;
        case 2: gl_iStraightSpeed = 60;//350;//4
                gl_iR600Speed = 55;
                gl_iR450Speed = 45;
                break;
        case 3: gl_iStraightSpeed = 40;//400;//1||2||NULL
                gl_iR600Speed = 35;
                gl_iR450Speed = 25;
                break;
        default : 
                break;
    }
}		/* -----  end of function SetSpeed  ----- */




 