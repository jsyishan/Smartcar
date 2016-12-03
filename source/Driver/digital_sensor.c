#include "digital_sensor.h"

uint32_t GetDigitalSensorValue(void)
{
	uint32_t DS0 = 0;	
	uint32_t DS1 = 0;	
	uint32_t DS2 = 0;
	uint32_t DS3 = 0;
	uint32_t DSensorValue = 0;
	
	DS0 = LPC_GPIO0->DATA;	
	DS1 = LPC_GPIO1->DATA;
	DS2 = LPC_GPIO2->DATA;
	DS3 = LPC_GPIO3->DATA;
	
	DSensorValue |= (!(DS3 & 0x0020));                 //P3.5  最右侧   12
	DSensorValue |= (!(DS2 & 0x0020))  << 1;           //P2.5           11
	DSensorValue |= (!(DS2 & 0x0010))  << 2;           //P2.4           10
	DSensorValue |= (!(DS3 & 0x0010))  << 3;           //P3.4           9
	DSensorValue |= (!(DS1 & 0x0100))  << 4;           //P1.8           8   
	DSensorValue |= (!(DS0 & 0x0004))  << 5;           //P0.2           6
	DSensorValue |= (!(DS0 & 0x0020))  << 6;           //P0.5           5
	DSensorValue |= (!(DS2 & 0x0080))  << 7;           //P2.7           4
	DSensorValue |= (!(DS2 & 0x0002))  << 8;           //P2.1           3
	DSensorValue |= (!(DS2 & 0x0100))  << 9;           //P2.8           2
  DSensorValue |= (!(DS0 & 0x0008))  << 10;          //P0.3           1	
	//DSensorValue |= (!(DS0 & 0x0010))  << 11;          //P0.4           7    (Start Bar)
	
	
	return DSensorValue;
}

uint8_t GET_START_BAR(void)
{
	uint8_t DSensorValue = 0;
	DSensorValue = !!(LPC_GPIO0->DATA & 0x0010);   //p0.4		11   use to check the start bar
	return DSensorValue;
}
/*-------------------------------------------------------------------
  *   Function    :    GetDigitalSensorNum
  *   Description :    count the number of sensor which on the black line
  *   Return      :    sensorCounter
  *   Notes       :    
  *   Modification History
  *   01a 2010-11-20 13:39:11
--------------------------------------------------------------------*/
void GetDigitalSensorNum(uint32_t digital_sensor)
{
    int8_t i = 0;
	unsigned char sensor_counter = 0;
	//uint32_t sensorTemp = 0;

	for(i = 0; i < 11; i ++)
	{
	   sensor_counter += (digital_sensor & 0x0001);       //  将状态变量里为“1”的位置总和统计出来
     //sensorTemp |= ((digital_sensor & 0x0001) << (10-i));
		 digital_sensor >>= 1;
	}

    //  将每一个传感器的状态左到右(即从高到低)的对应到unsigned int 中的低11位中
    //gl_digital_sensor = sensorTemp;

	  gl_ucSensorNumber = sensor_counter;
}
