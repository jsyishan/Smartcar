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
#ifndef   _COMMON_H_
#define   _COMMON_H_

#include  "include.h"

uint8_t ReadSwitch(uint8_t switch_select);
void WriteLEDOnDrive(uint8_t LED_select);
void BUZZER_ON(void);
void BUZZER_OFF(void);
uint8_t Remote(void);

#endif

