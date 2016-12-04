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

static int s_lastPositionErr = 0; //上一次舵机打角
static int s_iLastErr = 0;

int GetExpectedServoAngle(unsigned char num_lights, int sum_angle) {

    int avg_angle = sum_angle / num_lights;
    
    /* 以下两个判断语句控制  小车舵机角值较小或跳动值较小时（即直线行驶）  尽量减少晃动 */
    if(num_lights == 0 || num_lights == 11) {
        return s_iLastErr;
    }

    if((sum_angle <= 4 && sum_angle >= -4) || num_lights == 1) {
        return sum_angle;
    }

    /* 以下语句对  小车舵机角跳动值较大时  跳动值与舵机补偿角成正相关 */

    //TODO:
    if(s_lastPositionErr - avg_angle < 3 || avg_angle - s_lastPositionErr < 3) {
        return s_lastPositionErr;
    } else if(s_lastPositionErr - avg_angle < 4 || avg_angle - s_lastPositionErr < 4) {
        return avg_angle;
    } else if(s_lastPositionErr - avg_angle < 5 || avg_angle - s_lastPositionErr < 5) {
        return (2 * avg_angle - s_lastPositionErr); //返回当前舵机角
    } else {
        return (2 * avg_angle - s_lastPositionErr + 7); //比当前舵机角更大的补偿角
    }

}

int GetErr(void) {
	int	 iPositionErr = 0;
	unsigned int sensor = 0;
	unsigned char lightCount = 0;
    int i = 0;

    int lastPositionFlag = 0; // 是否已记录上次打角
    s_lastPositionErr = 0;
	
	sensor = gl_uiDigitalSensor;
 
	for (i=0; i<11; i++) {	
		if (sensor & 0x0001) {
            if(!lastPositionFlag) {
                s_lastPositionErr = gl_iSensorDistance[i];
            }
            lastPositionFlag++;

			iPositionErr += gl_iSensorDistance[i];
			lightCount++;
		}
		sensor >>= 1;
	}

    return GetExpectedServoAngle(lightCount, iPositionErr);
}
