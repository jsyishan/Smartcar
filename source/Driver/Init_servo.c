/************************************************************
 *              Init_servo.c --
 *		(c) Copyright 2013 HUST RENESAS LAB,The Department of CSE, HUST
 *                        All Rights Reserved
 *Filename                :   Init_servo.c
 *Programmer(s)           :   Chen xi
 *Description             :
 *Modification History	  :
 *01a 2013-8-3 20:34:57                
****************************************************************/

#include  "Init_servo.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:		  None
** Returned value:	None
** 
******************************************************************************/
void enable_timer32(void)
{
    LPC_TMR32B0->TCR = 1; 
		return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:		  None
** Returned value:	None
** 
******************************************************************************/
void disable_timer32(void)
{
  LPC_TMR32B0->TCR = 0;
  
  return;
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**				install timer interrupt handler
**
** parameters:		  None
** Returned value:	None
** 
******************************************************************************/
void init_timer32(void) 
{  
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);

		LPC_IOCON->PIO1_5 &= ~0x07;	/*  Timer0_32 I/O config */
    LPC_IOCON->PIO1_5 |= 0x02;	/* Timer0_32 CAP0 */
        	
		LPC_TMR32B0->PR = 8;
		LPC_TMR32B0->MCR = 3;			/* Interrupt and Reset on MR0 */
    
		enable_timer32();
		return;
}


/******************************************************************************
** Function name:		init_timer32PWM
**
** Descriptions:		Initialize timer as PWM, MAT0 control the period 
** 									The MAT3 control the duty percent
** parameters:		  None
**                  
** Returned value:	None
** 
******************************************************************************/
void Init_servo(void)
{
	  init_timer32();
    disable_timer32();
  
    /* Some of the I/O pins need to be clearfully planned if
    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);       
   
	  /* Setup the external match register */
    LPC_TMR32B0->EMR = (1<<EMC3)|(2<<EMC2)|(1<<EMC1)|(1<<EMC0)|(1<<3)|(MATCH0);
    
	  /* Setup the outputs */
		LPC_IOCON->PIO1_6         &= ~0x07;
	  LPC_IOCON->PIO1_6         |= 0x02;		/* Timer0_32 MAT0 */    
           
    LPC_IOCON->R_PIO0_11      &= ~0x07;	
    LPC_IOCON->R_PIO0_11      |= 0x03;		/* Timer0_32 MAT3 */
    
  
    /* Enable the selected PWMs and enable Match3 */
    LPC_TMR32B0->PWMC = (1<<3)|(MATCH0);
    
		/* Setup the match registers */
    /* set the period value to a global variable */
    
    LPC_TMR32B0->MR0 = timer32_0_period;
		LPC_TMR32B0->MR3 = SERVO_CENTER;
    
    LPC_TMR32B0->MCR = 0x0002;						/*Reset on MR0 */  
		  		
		enable_timer32();
}

