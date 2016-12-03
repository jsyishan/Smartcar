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
#ifndef   _TEST_H_
#define   _TEST_H_

#include  "include.h"

//#define CAR_DEBUG
#ifdef CAR_DEBUG
void TestCircuitBoard(void);
#endif

//#define DEBUG_SHAWN
#ifdef DEBUG_SHAWN
void Test(void);
#endif

#endif

