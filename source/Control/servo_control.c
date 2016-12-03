/**********************************************************************************
 *						Control.c -----
 *		(c) Copyright 2010 HUST RENESAS LAB,The Department of CSE, HUST
 *                       	 All Rights Reserved
 *Filename              :  Control.c
 *Programmer(s)         :  Sun Jiajiang
 *Description           :  
 *Modification History  :
 *01a 2010-11-4 16:35:47
**********************************************************************************/

#include "servo_control.h"

/*===================================================================
   *   Function   
===================================================================*/
/*-------------------------------------------------------------------
  *   Function    :    
  *   Description :    
  *   Return      :    none
  *   Notes       :    
  *   Modification History
  *   01a 2010-12-4 0:05:17
--------------------------------------------------------------------*/

int s_lastPositionErr = 0; //上一次舵机打角
static int s_iLastErr = 0;

int GetExpectedServoAngle(int num_lights, int sum_angle) {

    int maxDeviatedServoAngle = 5;
    if(num_lights == 0) {
        return s_iLastErr;

    } else {
        //TODO:
        int avg_angle = sum_angle / num_lights;

        if(s_lastPositionErr - avg_angle < maxDeviatedServoAngle || avg_angle - s_lastPositionErr < maxDeviatedServoAngle) {
            return s_lastPositionErr;

        }else {
            return avg_angle;

        }

    }
}

int GetErr(void) {
	int	 iPositionErr = 0;
	unsigned int sensor = 0;
	unsigned char lightCount = 0;
    int i = 0;
    int lastPositionFlag = 0; // 是否已记录上次打角
	
	sensor = gl_uiDigitalSensor;

	for (i=0; i<11; i++) {	
		if (sensor & 0x0001) {
			/* if the light is too far from last m ,do not count*/
			if (((gl_iSensorDistance[i] - gl_iNowErr) < 30) && ((gl_iSensorDistance[i] - gl_iNowErr) > -30)) {

                if(!lastPositionFlag) {
                    s_lastPositionErr = gl_iSensorDistance[i];
                }
                lastPositionFlag++;

				iPositionErr += gl_iSensorDistance[i];
				lightCount++;
			}
		}
		sensor >>= 1;
	}

    return GetExpectedServoAngle(lightCount, iPositionErr);

	// if (lightCount > 0 )
	// {
 //        s_iLastErr = iPositionErr / lightCount;
	// 	return (iPositionErr / lightCount);
	// }
	// else
	// {
 //        return s_iLastErr;
	// 	//return  1000;                  //if no light
	// } 
}
