/**********************************************************************************
 *						Arithmetic.c -----
 *		(c) Copyright 2010 HUST RENESAS LAB,The Department of CSE, HUST
 *                       	 All Rights Reserved
 *Filename              :  Arithmetic.c
 *Programmer(s)         :  Sun Jiajiang
 *Description           :  
 *Modification History  :
 *01a 2010-12-4 0:07:51
**********************************************************************************/

#include "Arithmetic.h"

/*===================================================================
   *   Function   
===================================================================*/
/*-------------------------------------------------------------------
  *   Function    :    Control
  *   Description :    
  *   Return      :    none
  *   Notes       :    
  *   Modification History
  *   01a 2010-12-4 0:05:17
--------------------------------------------------------------------*/

// int lastAngle = 0;//¼ÇÂ¼ÉÏÒ»´Î¶æ»úµÄ´ò½Ç
// int counter = 0;
// static int angleRecord[4]={0,0,0,0};
// int average(int a[]){
// 	int i = 0;
// 	int sum = 0;
// 	for(;i<=3;i++){
// 		sum += a[i];
// 	}
// 	//sum += a[counter];
// 	return (int)sum/4;
// }

void Control(void)
{
// 	int j;
// 	int lastAngle = 0;
// 	int servoAngleTemp = 0;
// 	gl_iNowErr = GetErr();
// 	servoAngleTemp = gl_iNowErr;
// 	if(servoAngleTemp>10||servoAngleTemp<-10){
// 		angleRecord[counter] = servoAngleTemp;
// 	}
// 	else{
// 		angleRecord[counter] = 0;
// 	}
// 	lastAngle = counter>0?angleRecord[3]:angleRecord[counter-1];
// 	counter++;
// 	if(counter == 3){
// 		counter = 0;
// 	}
// 	if(lastAngle - servoAngleTemp > 7 || lastAngle - servoAngleTemp < -7){
// 		for(j=0;j<4;j++){
// 			angleRecord[j] = servoAngleTemp;
// 		}
// 	}
// 	gl_cServoAngle = average(angleRecord);


// 	if(gl_cServoAngle < 6){
// 		SpeedOut(gl_iStraightSpeed,gl_cServoAngle);
// 	}
// 	else if(gl_cServoAngle < 18){
// 		SpeedOut(gl_iR600Speed,gl_cServoAngle);
// 	}
// 	else{
// 		SpeedOut(gl_iR450Speed,gl_cServoAngle);
// 	}
// 	SetServoAngle(gl_cServoAngle);
// 
    int servoAngleTemp = 0;
    gl_iNowErr = GetErr();
    servoAngleTemp = gl_iNowErr;
    gl_cServoAngle = servoAngleTemp;
    if(servoAngleTemp<0){
        servoAngleTemp = 0 - servoAngleTemp;
    }
    if(servoAngleTemp>0&&servoAngleTemp < 6){
        SpeedOut(gl_iStraightSpeed,0);
    }
    else if(servoAngleTemp < 15){
        SpeedOut(gl_iR600Speed + 12,gl_cServoAngle);
    }
    else if(servoAngleTemp < 24) {
        SpeedOut(gl_iR600Speed + 7,gl_cServoAngle);
    }
    else if(servoAngleTemp < 37) {
        SpeedOut(gl_iR600Speed + 3,gl_cServoAngle);
    }
    else if(servoAngleTemp < 50){
        SpeedOut(gl_iR600Speed - 2,gl_cServoAngle);
    }
    else{
        SpeedOut(gl_iR450Speed,gl_cServoAngle);
    }
    SetServoAngle(gl_cServoAngle);

}


/************************************************************************
 * Function         RightTrace                                              
 * Usage            Right Trace                           
 * Argument         NONE                                                
 * Return value     NONE                                                
 * Modification History:                                                
 * 01a 2012-12-13 22:54:33   
 *
 ************************************************************************/
void RightTrace (void) 
{
    gl_iNowErr = GetErr();

    if(gl_iNowErr > 0)
    {
        gl_cServoAngle = gl_iNowErr;
    }
    else if(gl_iNowErr < 0)
    {
        gl_cServoAngle = gl_iNowErr / 2;
    }
    SpeedOut(gl_iR600Speed, gl_cServoAngle);
    SetServoAngle(gl_cServoAngle);

    if(gl_iNowErr > 35)
    {
        gl_iPattern = 21;
        gl_cServoAngle = 45;
        SetServoAngle(gl_cServoAngle);
        PWMOut4(0,100,0,0);
    }
    else if(gl_uiDigitalSensor & 0x0100)
    {
        gl_iPattern = 11;
        gl_cServoAngle = -8;
        SetServoAngle(gl_cServoAngle);
        PWMOut4(20,0,0,50);
        gl_ulTimerCnt = 0;
        while(gl_ulTimerCnt < 5);
    }
}		/* -----  end of function RightTrace  ----- */

/************************************************************************
 * Function         LeftTrace                                              
 * Usage            Left Trace                           
 * Argument         NONE                                                
 * Return value     NONE                                                
 * Modification History:                                                
 * 01a 2012-12-14 00:07:14   
 *
 ************************************************************************/
void LeftTrace (void) 
{
    gl_iNowErr = GetErr();

    if(gl_iNowErr < 0)
    {
        gl_cServoAngle = gl_iNowErr;
    }
    else if(gl_iNowErr > 0)
    {
        gl_cServoAngle = gl_iNowErr / 2;
    }
    SpeedOut(gl_iR600Speed, gl_cServoAngle);
    SetServoAngle(gl_cServoAngle); 

    if(gl_iNowErr < -35)
    {
        gl_iPattern = 22;
        gl_cServoAngle = -45;
        SetServoAngle(gl_cServoAngle);
        PWMOut4(0,0,0,100);
    }
    else if(gl_uiDigitalSensor & 0x0004)
    {
        gl_iPattern = 11;
        gl_cServoAngle = 8;
        SetServoAngle(gl_cServoAngle);
        PWMOut4(0,50,20,0);
        gl_ulTimerCnt = 0;
        while(gl_ulTimerCnt < 5);
    }
}		/* -----  end of function LeftTrace  ----- */
/******************************************************************************
**                            End Of File
******************************************************************************/
