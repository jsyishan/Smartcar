/******************************************************************************
 *       Init_Encoder.h ----- The header of Init_Encoder.c                           *
 *       (c) Copyright 2012 HUST RENESAS LAB, The Department of CSE, HUST      *
 *                        ALL Rights Reserved                                  *
 *Filename             :  Init_Encoder.h                                         * 
 *Programmer(s)        :  Yang Xiang                                             *
 *Descriptions         :                                                       *
 *Modification History :                                                       *
 *01a 2013/12/10 15:59:37                                                       *
 ******************************************************************************/
#ifndef _INIT_ENCODER_H_
#define _INIT_ENCODER_H_

#include "include.h"

//#define ENCODER_USE       //�����ʹ�ñ������Ļ����뽫��仰ע�͵�
void Init_Encoder(void);

#define ENCODER_PULSES (200)//������һȦ����������������100��256��512��1024
#define ENCODER_WHEEL_D (6.32)//�������ϵ��ֵ�ֱ������λcm
#define ENCODER_WHEEL_L (ENCODER_WHEEL_D*3.1416)//�������ϵ��ֵ��ܳ�
#endif


