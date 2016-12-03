#include    "servo.h"

static uint16_t gl_servoPWM = SERVO_CENTER;

void SetServoAngle(int8_t angle)
{
    //  限制舵机打角的最大值，保护舵机，防止舵机卡死，可以通过更改MAX_ANGLE来改变
	if(angle > MAX_ANGLE)				               
	{
	    angle = MAX_ANGLE;
	}
	else if(angle < -MAX_ANGLE)
	{
	    angle = 0 - MAX_ANGLE;
	}
	
	gl_servoPWM = SERVO_CENTER + ANGLE_SCALE * angle;	   //  给占空比变量传值会导致程序中断中占空比被频繁改变 所以使用占空比buffer来缓存传入的占空比值
}

void servo_PWMOut(void)
{
	LPC_TMR32B0->MR3 = gl_servoPWM;
}
