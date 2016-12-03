#include "IRQHandler.h"

static uint8_t servo_counter = 0;
static uint32_t program_counter = 0;

/******************************************************************************
** Function name:		TIMER_0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER16_0_IRQHandler(void)   //1ms interrupt
{    
    if((LPC_TMR16B0->IR & 0x08) == 0x08)
    {	
        gl_ulTimerCnt ++;
        servo_counter ++;
        program_counter ++;
        gl_iProgramPeriod++;


        if(program_counter == 255)
        {
            program_counter = 0;
        }
			
        IRQ_motor_PWMOut();       // output the motor PWM per 1ms
			
        if(servo_counter >= 10)   // output the servo PWM per 10ms
        {
            servo_counter = 0;
            servo_PWMOut();
        }
    }  
    LPC_TMR16B0->IR = 0xFF;				// clear interrupt flag 			

	return;
}

