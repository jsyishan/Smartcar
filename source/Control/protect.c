/*
 * =====================================================================================
 *
 *            Filename :  protect.c
 *
 *         Description :  The Program To Protect Your Car
 *
 *             Version :  1.01
 *             Created :  2013/11/17 10:38:57
 *            Compiler :  Keil C51
 *
 *              Author :  Yang Xiang (YX), 398908756@qq.com
 *             Company :  HUST RENESAS LAB,The Department of CSE, HUST
 *
 *Modification History :
 *    01a 2013/11/17 10:38:57 OE 1.01
 *
 * =====================================================================================
 */

/*-----------------------------------------------------------------------------
 *  Include Files
 *-----------------------------------------------------------------------------*/
#include "protect.h"

/*-----------------------------------------------------------------------------
 *  Functions
 *-----------------------------------------------------------------------------*/
/* 
 * ===  FUNCTION  ======================================================================
 *                Name:  TeleControl
 *         Description:  Detect the Infraed Ray signal
 *           Parameter:  NONE
 *              Return:  NONE
 *                Note:  
 *Modification History:
 *    01a 2013/11/17 10:42:24 Ver1.01
 * =====================================================================================
 */
void TeleControl ( void )
{
    static char teleControlCounter = 0;
    static char Counter = 0;
    uint8_t switchTeleCtrl = 0;
    uint8_t infraedRayValue = 0;

    switchTeleCtrl = !!(gl_ucSwitchValue & 0x08);

    if(switchTeleCtrl)
    {
        infraedRayValue = Remote();

        if(infraedRayValue)
        {
            teleControlCounter ++;
        }

        Counter ++;

        if(teleControlCounter > 6)
        {
            gl_iPattern = 9;
        }
        else
        {
            if(Counter > 50)
            {
                teleControlCounter = 0;
                Counter = 0;
            }
        }
    }



}		/* -----  end of function TeleControl  ----- */
