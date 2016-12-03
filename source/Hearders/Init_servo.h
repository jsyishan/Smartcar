#ifndef __INIT_SERVO_H 
#define __INIT_SERVO_H

#include "include.h"

#define timer32_Frequency  6
#define timer32_period  10
#define timer32_0_period  (5280 * timer32_period) //10ms

#define EMC0	4
#define EMC1	6
#define EMC2	8
#define EMC3	10

#define MATCH0	(1<<0)
#define MATCH1	(1<<1)
#define MATCH2	(1<<2)
#define MATCH3	(1<<3)
void Init_servo(void);

#endif
