/****************************************************************************** 
 *       Init_Encoder.c ----- Init Encoder          *
 *       (c) Copyright 2012 HUST RENESAS LAB,The Department of CSE, HUST       *
 *                        All Rights Reserved                                  *
 *Filename             :  Init_Encoder.c                                           *
 *Programmer(s)        :  Yang Xiang                                           *
 *Description          :                                                       *
 *Modification History :                                                       *
 *01a 2013/12/10 15:50:17                                                       *
 ******************************************************************************/
#include "Init_Encoder.h"
/************************************************************************
 * Function         Init_Encoder                                              
 * Usage            Init Encoder                           
 * Argument         NONE                                                
 * Return value     NONE                                                
 * Modification History:                                                
 * 01a 2013/12/10 16:02:02   
 *
 ************************************************************************/
void Init_Encoder (void) 
{
	
		//decoder 0
    /* Some of the I/O pins need to be clearfully planned if
    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);        /* enable CT32B1 */
	  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);        /* enable IOCON */ 
    LPC_IOCON->R_PIO1_0           &= ~0x07;	     /* Timer1_32 I/O config */
    LPC_IOCON->R_PIO1_0           |= 0x03;		   /* Timer1_32 CAP0 */  
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);	     /*disable iocon */
  	LPC_TMR32B1->CTCR = 0x01; //选择外来信号的上升沿作为TC递增
	  LPC_TMR32B1->CCR = 0X01;  //每次上升沿时CR0装载TC中的值
    LPC_TMR32B1->TC = 0x00; //TC 清零
    LPC_TMR32B1->TCR = 0x01; //启动定时器	
	
	
/*    uint32_t temp_register = 0;

    //Set the IO P1_0 as the Encoder CAP Port
    temp_register = LPC_IOCON->R_PIO1_0;
    temp_register = temp_register & (~0x0007);
    temp_register = temp_register | (0x0003);
    LPC_IOCON->R_PIO1_0 = temp_register;

    //Set the Counting Mode of Timer32 B1 as the CAP Counting Mode
    temp_register = LPC_TMR32B1->CTCR;
    temp_register = temp_register & (~0x000F);
    temp_register = temp_register | (0x0001);
    LPC_TMR32B1->CTCR = temp_register;
	*/
}		/* -----  end of function Init_Encoder  ----- */
