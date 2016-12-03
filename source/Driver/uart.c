
/****************************************************************************
 *   $Id:: uart.c 3648 2010-06-02 21:41:06Z usb00423                        $
 *   Project: NXP LPC11xx UART example
 *
 *   Description:
 *     This file contains UART code example which include UART 
 *     initialization, UART interrupt handler, and related APIs for 
 *     UART access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "LPC11xx.h"
//#include "uart.h"
#include "include.h"

volatile uint32_t UARTStatus;
volatile uint8_t  UARTTxEmpty = 1;
volatile uint8_t  UARTBuffer[BUFSIZE];
volatile uint32_t UARTCount = 0;
//extern uint32_t SystemAHBFrequency;
/*****************************************************************************
** Function name:		UART_IRQHandler
**
** Descriptions:		UART interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART_IRQHandler(void)
{
  uint8_t IIRValue, LSRValue;
  uint8_t Dummy = Dummy;

  IIRValue = LPC_UART->IIR;
    
  IIRValue >>= 1;			/* skip pending bit in IIR */
  IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
  if (IIRValue == IIR_RLS)		/* Receive Line Status */
  {
    LSRValue = LPC_UART->LSR;
    /* Receive Line Status */
    if (LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI))
    {
      /* There are errors or break interrupt */
      /* Read LSR will clear the interrupt */
      UARTStatus = LSRValue;
      Dummy = LPC_UART->RBR;	/* Dummy read on RX to clear 
								interrupt, then bail out */
      return;
    }
    if (LSRValue & LSR_RDR)	/* Receive Data Ready */			
    {
      /* If no error on RLS, normal ready, save into the data buffer. */
      /* Note: read RBR will clear the interrupt */
      UARTBuffer[UARTCount++] = LPC_UART->RBR;
      if (UARTCount == BUFSIZE)
      {
        UARTCount = 0;		/* buffer overflow */
      }	
    }
  }
  else if (IIRValue == IIR_RDA)	/* Receive Data Available */
  {
    /* Receive Data Available */
    UARTBuffer[UARTCount++] = LPC_UART->RBR;
    if (UARTCount == BUFSIZE)
    {
      UARTCount = 0;		/* buffer overflow */
    }
  }
  else if (IIRValue == IIR_CTI)	/* Character timeout indicator */
  {
    /* Character Time-out indicator */
    UARTStatus |= 0x100;		/* Bit 9 as the CTI error */
  }
  else if (IIRValue == IIR_THRE)	/* THRE, transmit holding register empty */
  {
    /* THRE interrupt */
    LSRValue = LPC_UART->LSR;		/* Check status in the LSR to see if
								valid data in U0THR or not */
    if (LSRValue & LSR_THRE)
    {
      UARTTxEmpty = 1;
    }
    else
    {
      UARTTxEmpty = 0;
    }
  }
  return;
}


/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART0 port, setup pin select,
**				clock, parity, stop bits, FIFO, etc.
**
** parameters:			UART baudrate
** Returned value:		None
** 
*****************************************************************************/
void Init_UART(uint32_t baudrate)
{
  uint32_t Fdiv;
  uint32_t regVal;

  UARTTxEmpty = 1;
  UARTCount = 0;
  
  //NVIC_DisableIRQ(UART_IRQn);

  LPC_IOCON->PIO1_6 &= ~0x07;    /* UART I/O config */
  LPC_IOCON->PIO1_6 |= 0x01;     /* UART RXD */
  LPC_IOCON->PIO1_7 &= ~0x07;	
  LPC_IOCON->PIO1_7 |= 0x01;     /* UART TXD */

  /* Enable UART clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
  LPC_SYSCON->UARTCLKDIV = 0x1;     /* divided by 1 */

  LPC_UART->LCR = 0x83;             /* 8 bits, no Parity, 1 Stop bit */
  regVal = LPC_SYSCON->UARTCLKDIV;
  Fdiv = ((SystemAHBFrequency/regVal)/16)/baudrate ;	/*baud rate */

  LPC_UART->DLM = Fdiv / 256;							
  LPC_UART->DLL = Fdiv % 256;
  LPC_UART->LCR = 0x03;		/* DLAB = 0 */
  LPC_UART->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

  /* Read to clear the line status. */
  regVal = LPC_UART->LSR;

  /* Ensure a clean start, no dasta in either TX or RX FIFO. */
  while (( LPC_UART->LSR & (LSR_THRE|LSR_TEMT)) != (LSR_THRE|LSR_TEMT) );
  while ( LPC_UART->LSR & LSR_RDR )
  {
   	regVal = LPC_UART->RBR;	/* Dump data from RX FIFO */
  }
 
  /* Enable the UART Interrupt */
 // NVIC_EnableIRQ(UART_IRQn);


  LPC_UART->IER = IER_RBR | IER_RLS;	/* Enable UART interrupt */

  return;
}

/*****************************************************************************
** Function name:		UARTSend
**
** Descriptions:		Send a block of data to the UART 0 port based
**				on the data length
**
** parameters:		buffer pointer, and data length
** Returned value:	None
** 
*****************************************************************************/
void UARTSend(uint8_t *BufferPtr)
{  
		LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
  while (1)
  {
	  /* THRE status, contain valid data */

	  /* Below flag is set inside the interrupt handler when THRE occurs. */
      
	    if(*BufferPtr == 0)
				break;
		  while(!(LPC_UART->LSR & (1 << 5)));
	    LPC_UART->THR = *BufferPtr;
      UARTTxEmpty = 0;	/* not empty in the THR until it shifts out */

      BufferPtr++;      
  }
	LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
  return;
}


uint8_t UART_recive(void)
{
    while(!(LPC_UART->LSR & (1 << 0)));	
	  return(LPC_UART->RBR);
}


void myitoa(int8_t num, uint8_t *str)
{
	int s[6] = {0};
	
	int i = 0;
  int j = 0;
  uint8_t flag = 0;
  
  if(num >= 0)
	{ 
		flag = 0;
  }
	else
	{
		flag = 1;
		num = 0 - num;
  }
	
	if(num == 0)
	{
		*str = '+';
		*(str + 1) = 0 + '0';
		*(str + 2) = 0 + '0';
		*(str + 3) = '\0';
	}
	else
	{
		while(num)	 
		{
			s[i] = num % 10 ;
		
			num = (int)(num / 10);
			++ i;
		}
	 
		if(flag == 0)
		{
			*str = '+';
    }
		else
		{
			*str = '-';
    }
		for(j = 1; j <= i; j ++)
		{			
 			*(str + j)= s[i - j] + '0';
		}
		*(str + i + 1) = '\0';		
		if(i == 1)
		{
			*(str + 3) = '\0';
			*(str + 2) = s[0] + '0';
			*(str + 1) = 0 + '0';
    }
	}


}
/******************************************************************************
**                            End Of File
******************************************************************************/
