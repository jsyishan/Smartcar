#include    "motor_control.h"

#define TABLE_DIMENSION   60

const uint8_t gl_speedDifference[3][TABLE_DIMENSION]  = {						
{100, 98, 96, 95, 93,	91, 89, 87, 86, 84,	82, 80, 79, 77, 75,	73, 72, 70, 68, 66,	65, 63, 61, 60, 58,	56, 55, 53, 51, 50,48, 47, 45, 43, 42,	40, 39, 37, 35, 34,	32, 31, 29, 28, 26,	25, 23, 22, 20, 19,	17, 16, 15, 13, 12,	10, 9, 8, 6, 5,},
{100, 98, 96, 95, 93,	91, 90, 88, 87, 85,	84, 82, 81, 79, 78,	76, 75, 74, 72, 71,	70, 69, 68, 66, 65,	64, 63, 62, 61, 60,59, 58, 57, 56, 55,	54, 53, 53, 52, 51,	50, 49, 49, 48, 47,	46, 46, 45, 44, 44,	43, 43, 42, 42, 41,	40, 40, 39, 39, 39,},
{100, 100, 100, 100, 100,	100, 100, 99, 99, 99,	99, 98, 98, 98, 97,	97, 97, 96, 96, 95,	95, 94, 94, 93, 93,	92, 92, 91, 91, 90,89, 89, 88, 88, 87,	86, 85, 85, 84, 83,	83, 82, 81, 80, 80,	79, 78, 77, 76, 75,	75, 74, 73, 72, 71,	70, 69, 68, 68, 67}};	

	
/*-------------------------------------------------------------------
  *   Notes       :    带差速的速度输出，angle 为差速角度，以外侧电机为参考，内侧电机会根据差速表中比例给定内侧的PWM
                       例：外侧输出80%， 差速查表得内侧为外侧的60%，则内侧输出为 80% * 60% = 48%
					   因此控制时，主要给出的PWM占空比为外侧基准电机的占空比，其余电机均为查表计算得出
--------------------------------------------------------------------*/

//  四驱方案以外侧前轮为基准
void PWMOut(int8_t pwmduty, int8_t angle)
{
    char InsideRDiff = 0;			// Speed differential proportion of inside rear wheel      positive PWM 
    char InsideFDiff = 0;			// Speed differential proportion of inside front wheel     positive PWM
    char OutsideRDiff = 0;			// Speed differential proportion of outside rear wheel     positive PWM
	
    int pwmdutyTemp = 0;
    int angleTemp = 0;
	
    pwmdutyTemp = pwmduty;
    angleTemp   = angle;

	if (angleTemp > 0)
	{
		if (angleTemp > (TABLE_DIMENSION - 1))               //  防止寻址溢出
		{
		    angleTemp = TABLE_DIMENSION - 1;
		}
		InsideRDiff  = gl_speedDifference[0][angleTemp];
        InsideFDiff  = gl_speedDifference[1][angleTemp];
        OutsideRDiff = gl_speedDifference[2][angleTemp];
		PWMOut4(PWM_OUTSIDE_R, pwmdutyTemp, PWM_INSIDE_R , PWM_INSIDE_F);
	}
	else
	{
		angleTemp = 0 - angleTemp;
		if (angleTemp > (TABLE_DIMENSION - 1))               //  防止寻址溢出
		{
		    angleTemp = TABLE_DIMENSION - 1;
		}
		InsideRDiff  = gl_speedDifference[0][angleTemp];
        InsideFDiff  = gl_speedDifference[1][angleTemp];
        OutsideRDiff = gl_speedDifference[2][angleTemp];
		PWMOut4(PWM_INSIDE_R , PWM_INSIDE_F, PWM_OUTSIDE_R , pwmdutyTemp);
	}
}

/************************************************************************
 * Function         SpeedOut                                              
 * Usage            Speed Output                           
 * Argument         (int)speed, (int)PWMAngle                                                
 * Return value     NONE                                                
 * Modification History:                                                
 * 01a 2012-12-11 21:03:47   
 *
 ************************************************************************/
void SpeedOut (int speed, int angle) 
{
    char motorPWM;
    motorPWM = (char)speed;

	if(gl_iPattern == 9)
	{
		gl_cMotorPWM = 0;
		PWMOut4(0,0,0,0);
	}
    else
    {
        gl_cMotorPWM = motorPWM;
        PWMOut(speed, angle);
    }
}		/* -----  end of function SpeedOut  ----- */

