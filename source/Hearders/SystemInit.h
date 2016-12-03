/**********************************************************************************
 *						Includes.h ----- Header Functions
 *		(c) Copyright 2013 HUST RENESAS LAB,The Department of CSE, HUST
 *                       	 All Rights Reserved
 *Filename             :   Includes.h
 *Programmer(s)        :   Chen Xi
 *Description          :
 *Modification History :
 *01a 2013-8-1 10:40:05
**********************************************************************************/
#ifndef   _SYSTEMINIT_H_
#define   _SYSTEMINIT_H_

#include "include.h"
/*--------------------- Clock Configuration ----------------------------------
//
// <e> Clock Configuration
//   <h> System Controls and Status Register (SCS)
//     <o1.4>    OSCRANGE: Main Oscillator Range Select
//                     <0=>  1 MHz to 20 MHz
//                     <1=> 15 MHz to 24 MHz
//     <e1.5>       OSCEN: Main Oscillator Enable
//     </e>
//   </h>
//
//   <h> Clock Source Select Register (CLKSRCSEL)
//     <o2.0..1>   CLKSRC: PLL Clock Source Selection
//                     <0=> Internal RC oscillator
//                     <1=> Main oscillator
//                     <2=> RTC oscillator
//   </h>
//
//   <e3> PLL0 Configuration (Main PLL)
//     <h> PLL0 Configuration Register (PLL0CFG)
//                     <i> F_cco0 = (2 * M * F_in) / N
//                     <i> F_in must be in the range of 32 kHz to 50 MHz
//                     <i> F_cco0 must be in the range of 275 MHz to 550 MHz
//       <o4.0..14>  MSEL: PLL Multiplier Selection
//                     <6-32768><#-1>
//                     <i> M Value
//       <o4.16..23> NSEL: PLL Divider Selection
//                     <1-256><#-1>
//                     <i> N Value
//     </h>
//   </e>
//
//
//   <h> CPU Clock Configuration Register (CCLKCFG)
//     <o7.0..7>  CCLKSEL: Divide Value for CPU Clock from PLL0
//                     <0-255>
//                     <i> Divide is CCLKSEL + 1. Only 0 and odd values are valid.
//   </h>
//
//
// </e>
*/
#define MAIN_CLKSRCSEL_Val    0x00000001
#define MAIN_PLL_M_Val        0x00000003
#define MAIN_PLL_P_Val        0x00000001
#define SYS_AHB_DIV_Val       1			/* 1 through 255, typical is 1 or 2 or 4 */

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL        (12000000UL)        /* Oscillator frequency               */
#define OSC_CLK     (      XTAL)        /* Main oscillator frequency          */
#define IRC_OSC     (12000000UL)        /* Internal RC oscillator frequency   */
#define WDT_OSC     (  250000UL)        /* WDT oscillator frequency           */
#define SYS_OSC     (48000000UL)

void SystemInit(void);
void Init_ALL(void);

#endif     //  End of _SYSTEMINIT_H_

