/************************************************************
 *              Init_motor.c -----
 *		(c) Copyright 2013 HUST RENESAS LAB,The Department of CSE, HUST
 *                        All Rights Reserved
 *Filename                :   Init_motor.c
 *Programmer(s)           :   Chen xi
 *Description             :
 *Modification History	  :
 *01a 2013-8-1 20:42:57                
****************************************************************/
#include "Init_motor.h"

uint32_t TimerInterval = 12000 - 1;
/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**									until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:	None
** 
*****************************************************************************/
void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  if (timer_num == 0)
  {
    /*
    * setup timer #0 for delay
    */
    LPC_TMR16B0->TCR = 0x02;		/* reset timer */
    LPC_TMR16B0->PR  = 0x00;		/* set prescaler to zero */
    LPC_TMR16B0->MR0 = delayInMs * (IRC_OSC / 1000);
    LPC_TMR16B0->IR  = 0xff;		/* reset all interrrupts */
    LPC_TMR16B0->MCR = 0x04;		/* stop timer on match */
    LPC_TMR16B0->TCR = 0x01;		/* start timer */
    /* wait until delay time has elapsed */
    while (LPC_TMR16B0->TCR & 0x01);
  }
  else if (timer_num == 1)
  {
    /*
    * setup timer #1 for delay
    */
    LPC_TMR16B1->TCR = 0x02;		/* reset timer */
    LPC_TMR16B1->PR  = 0x00;		/* set prescaler to zero */
    LPC_TMR16B1->MR0 = delayInMs * (IRC_OSC / 1000);
    LPC_TMR16B1->IR  = 0xff;		/* reset all interrrupts */
    LPC_TMR16B1->MCR = 0x04;		/* stop timer on match */
    LPC_TMR16B1->TCR = 0x01;		/* start timer */
    /* wait until delay time has elapsed */
    while (LPC_TMR16B1->TCR & 0x01);
  }
  return;
}


/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void enable_timer16(void)
{
  LPC_TMR16B0->TCR = 1;
  LPC_TMR16B1->TCR = 1;
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void disable_timer16(void)
{ 
    LPC_TMR16B0->TCR = 0;
    LPC_TMR16B1->TCR = 0; 
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void reset_timer16(uint8_t timer_num)
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
    regVal = LPC_TMR16B0->TCR;
    regVal |= 0x02;
    LPC_TMR16B0->TCR = regVal;
  }
  else
  {
    regVal = LPC_TMR16B1->TCR;
    regVal |= 0x02;
    LPC_TMR16B1->TCR = regVal;
  }
  return;
}

void init_timer16(void) 
{
 
    /* Some of the I/O pins need to be clearfully planned if
    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
    LPC_IOCON->PIO0_2           &= ~0x07;	/*  Timer0_16 I/O config */
    LPC_IOCON->PIO0_2           |= 0x02;		/* Timer0_16 CAP0 */
    LPC_IOCON->PIO0_8           &= ~0x07;	
    LPC_IOCON->PIO0_8           |= 0x02;		/* Timer0_16 MAT0 */
    LPC_IOCON->PIO0_9           &= ~0x07;
    LPC_IOCON->PIO0_9           |= 0x02;		/* Timer0_16 MAT1 */
		

	
    LPC_TMR16B0->MR0 = TimerInterval;

   // LPC_TMR16B0->MCR = 3;				/* Interrupt and Reset on MR0 and MR1 */
		
    /* Enable the TIMER0 Interrupt */
    NVIC_EnableIRQ(TIMER_16_0_IRQn);
 
    /* Some of the I/O pins need to be clearfully planned if
    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);
    LPC_IOCON->PIO1_8           &= ~0x07;	/*  Timer1_16 I/O config */
    LPC_IOCON->PIO1_8           |= 0x01;		/* Timer1_16 CAP0 */
    LPC_IOCON->PIO1_9           &= ~0x07;	
    LPC_IOCON->PIO1_9           |= 0x01;		/* Timer1_16 MAT0 */
    LPC_IOCON->PIO1_10          &= ~0x07;
    LPC_IOCON->PIO1_10          |= 0x02;		/* Timer1_16 MAT1 */	
		

    LPC_TMR16B1->MR0 = TimerInterval;
    LPC_TMR16B0->PR = 80;
	  LPC_TMR16B1->PR = 80;
  
    /* Enable the TIMER1 Interrupt */
    NVIC_EnableIRQ(TIMER_16_1_IRQn);
  
  return;
}

/******************************************************************************
** Function name:		init_motor_PWM
**
** Descriptions:		Initialize timer as PWM 
**									Set the period of each channel to 1ms
** parameters:			None
** Returned value:	None
** 
******************************************************************************/
void Init_motor(void)
{	
		init_timer16();
		disable_timer16();

    /* Some of the I/O pins need to be clearfully planned if
    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);  //timer16_0
	
		LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 8);  //timer16_1
    	 
    /* Setup the external match register */
    LPC_TMR16B1->EMR = (1<<EMC3)|(1<<EMC2)|(1<<EMC1)|(1<<EMC0)|(1<<3)|(MATCH1);  
	 
	  /* Setup the outputs timer16_0*/       
    LPC_IOCON->PIO0_8           &= ~0x07;	
    LPC_IOCON->PIO0_8           |= 0x02;		/* Timer0_16 MAT0 */
       
    LPC_IOCON->PIO0_9           &= ~0x07;
    LPC_IOCON->PIO0_9           |= 0x02;		/* Timer0_16 MAT1 */       
			
    /* Setup the outputs timer16_1*/
   
    LPC_IOCON->PIO1_10          &= ~0x07;
    LPC_IOCON->PIO1_10          |= 0x02;		/* Timer1_16 MAT1 */

    LPC_IOCON->PIO1_9          &= ~0x07;
    LPC_IOCON->PIO1_9          |= 0x01;		  /* Timer1_16 MAT0 */

		/* Enable the selected PWMs */
    LPC_TMR16B0->PWMC = 0x03;
	LPC_TMR16B1->PWMC = (1<<3)|0x03;//(MATCH1); 
    
				
		/* Setup the match registers */
    /* set the period value to a global variable */   
    LPC_TMR16B0->MR3  = timer16_0_period;
    LPC_TMR16B0->MR0	= timer16_0_period / 2;
    LPC_TMR16B0->MR1	= timer16_0_period / 2;
    //LPC_TMR16B0->MR2	= timer16_0_period / 2;
	      
    LPC_TMR16B1->MR3 	= timer16_1_period;  
    LPC_TMR16B1->MR1	= timer16_0_period / 2;
	LPC_TMR16B1->MR0	= timer16_0_period / 2;
   
  
		/* Set the match control register */
    LPC_TMR16B0->MCR = ((1 << 10) | (1 << 9));				  /* Interrupt and Reset on MR3*/
		    
    LPC_TMR16B1->MCR = (1 << 10);										  	/* Reset on MR3*/
		
		/* Enable the TIMER16 Interrupt */
    NVIC_EnableIRQ(TIMER_16_0_IRQn);  				    
		
		enable_timer16();
}


/******************************************************************************
**                            End Of File
******************************************************************************/


