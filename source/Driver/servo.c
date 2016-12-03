#include    "servo.h"

static uint16_t gl_servoPWM = SERVO_CENTER;

void SetServoAngle(int8_t angle)
{
    //  ���ƶ����ǵ����ֵ�������������ֹ�������������ͨ������MAX_ANGLE���ı�
	if(angle > MAX_ANGLE)				               
	{
	    angle = MAX_ANGLE;
	}
	else if(angle < -MAX_ANGLE)
	{
	    angle = 0 - MAX_ANGLE;
	}
	
	gl_servoPWM = SERVO_CENTER + ANGLE_SCALE * angle;	   //  ��ռ�ձȱ�����ֵ�ᵼ�³����ж���ռ�ձȱ�Ƶ���ı� ����ʹ��ռ�ձ�buffer�����洫���ռ�ձ�ֵ
}

void servo_PWMOut(void)
{
	LPC_TMR32B0->MR3 = gl_servoPWM;
}
