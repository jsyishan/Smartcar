
#include "Init_GPIO.h"

/*****************************************************************************
** Function name:		GPIOSetDir
**
** Descriptions:		Set the direction in GPIO port
**
** parameters:			None
** Returned value:	None
**
*****************************************************************************/
void set_GPIO_Dir(void)
{  
	//sensor
	LPC_GPIO0->DIR &= ~(1 << 3);
	LPC_GPIO0->DIR &= ~(1 << 4);
	LPC_GPIO0->DIR &= ~(1 << 5);
	LPC_GPIO0->DIR &= ~(1 << 6);

	LPC_GPIO1->DIR &= ~(1 << 8);

	LPC_GPIO2->DIR &= ~(1 << 1);
	LPC_GPIO2->DIR &= ~(1 << 4);
	LPC_GPIO2->DIR &= ~(1 << 5);
	LPC_GPIO2->DIR &= ~(1 << 7);
	LPC_GPIO2->DIR &= ~(1 << 8);

	
	LPC_GPIO3->DIR &= ~(1 << 4);
	LPC_GPIO3->DIR &= ~(1 << 5);
	
	//switch
	LPC_GPIO1->DIR &= ~(1 << 5);
	LPC_GPIO1->DIR &= ~(1 << 11);
	LPC_GPIO2->DIR &= ~(1 << 0);
	LPC_GPIO3->DIR &= ~(1 << 1);
	
	//LED
	LPC_GPIO2->DIR |= (1 << 6);
	LPC_GPIO3->DIR |= (1 << 3);
	LPC_GPIO3->DIR |= (1 << 2);
	LPC_GPIO1->DIR |= (1 << 4);
	
	//Beep
	LPC_GPIO2->DIR |= (1 << 3);
	
	//remote
	LPC_GPIO3->DIR &= ~(1 << 0);
	
	//Motor Direction
	  LPC_GPIO2->DIR |= (1 << 9);
    LPC_GPIO2->DIR |= (1 << 2);
    LPC_GPIO0->DIR |= (1 << 7);
    LPC_GPIO2->DIR |= (1 << 10);
		
	//Extra Setting(For Drive Board BUG)
	LPC_GPIO1->DIR &= ~(1 << 1);
	
	//Encoder
	LPC_GPIO1->DIR &= ~(1 << 0);
}

void reset_GPIO(void)
{
	//turn off led
	LPC_GPIO2->DATA = ~((1 << 6) & 0);
	LPC_GPIO3->DATA = ~((1 << 3) & 0);
	LPC_GPIO3->DATA = ~((1 << 2) & 0);
	LPC_GPIO1->DATA = ~((1 << 4) & 0);
	
	//turn off beep
	LPC_GPIO2->DATA = ~((1 << 3) & 0);
}
/*****************************************************************************
** Function name:		GPIOInit
**
** Descriptions:		Initialize GPIO, install the
**						GPIO interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the VIC table
**						is full and GPIO interrupt handler can be
**						installed.
** 
*****************************************************************************/
void Init_GPIO( void )
{
  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	set_GPIO_Dir();
	reset_GPIO();
  return;
}
