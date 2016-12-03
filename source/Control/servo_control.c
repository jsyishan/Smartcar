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
int GetErr(void)
{
    static int s_iLastErr = 0;
	int	 iPositionErr = 0;
	unsigned int sensor = 0;
	unsigned char lightCount = 0 ;
    int i = 0;
	
	sensor = gl_uiDigitalSensor;    

	for (i=0; i<11; i++)
	{	
		if (sensor & 0x0001)
		{
			/* if the light is too far from last m ,do not count*/
			if (((gl_iSensorDistance[i] - gl_iNowErr) < 30) && ((gl_iSensorDistance[i] - gl_iNowErr) > -30))
			{
				iPositionErr += gl_iSensorDistance[i];
				lightCount++;
			}
		}
		sensor >>= 1;
	}	

	if (lightCount > 0 )
	{
        s_iLastErr = iPositionErr / lightCount;
		return (iPositionErr / lightCount);
	}
	else
	{
        return s_iLastErr;
		//return  1000;                  //if no light
	} 

}
