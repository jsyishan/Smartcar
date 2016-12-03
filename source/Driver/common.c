#include "common.h"

uint8_t ReadSwitch(uint8_t switch_select)
{
	uint8_t switch_value[4] = {0};
	uint8_t SW_value = 0;
    uint8_t SW = 0;
	switch_value[3] = !(LPC_GPIO3->DATA & 0x0002);  // P3_1 
	switch_value[2] = !(LPC_GPIO1->DATA & 0x0800);  // P1_11 
	switch_value[1] = !(LPC_GPIO1->DATA & 0x0020);  // P1_5 
	switch_value[0] = !(LPC_GPIO2->DATA & 0x0001);  // P2_0 
	
    SW_value = switch_value[0] | (switch_value[1] << 1) | (switch_value[2] << 2) | (switch_value[3] << 3);
	
	SW = SW_value & switch_select;

	return ((uint8_t)SW);
}

void WriteLEDOnDrive(uint8_t LED_select)
{
	uint8_t loop_i = 0;
	uint8_t select_temp = LED_select;
	uint8_t LED[4] = {0};

	for(loop_i = 0; loop_i < 4; loop_i ++)	
	{
		LED[loop_i] = select_temp & 0x01;
		select_temp >>= 1;		
	}
	
	//LED
    if(LED[0])
    {
	    LPC_GPIO2->DATA &= (~0x0040);                 //  P2_6
    }
    else
    {
        LPC_GPIO2->DATA |= 0x0040;                 //  
    }

    if(LED[1])
    {
        LPC_GPIO3->DATA &= (~0x0008);                 // P3_3 
    }
    else
    {
        LPC_GPIO3->DATA |= 0x0008;                 //  
    }

    if(LED[2])
    {
		LPC_GPIO3->DATA &= (~0x0004);                 // P3_2 
    }
    else
    {
        LPC_GPIO3->DATA |= 0x0004;                 //  
    }

    if(LED[3])
    {
	    LPC_GPIO1->DATA &= (~0x0010);                 // P1_4 
    }
    else
    {
        LPC_GPIO1->DATA |= 0x0010;                 //  
    }

}

void BUZZER_ON(void)
{
		LPC_GPIO2->DATA |= 0x0008;            // P2_3 
}

void BUZZER_OFF(void)
{
		LPC_GPIO2->DATA &= (~0x0008);	
}

uint8_t Remote(void)
{
	uint8_t temp = 0;
	
	temp = !(LPC_GPIO3->DATA & 0x0001);          // P3_0 
	
	return temp;
}
