##Freescale SmartCat Project
* 关于对差速表的优化
	* ```motor_control.c```
	* 测量误差
* 关于对舵机打角的优化
	* ```SmartCar6th.c```
	* 对应打角值的数组参数调整
	* 算法优化
* 关于对传感器采集数据的优化
	* ```servo_control.c```
	* 算法优化
* 待做事项
	* 测量传感器打角，将车子放在赛道上，用电脑连接进入debug模式（注意烧进去的一定要是debug版本），调试舵机偏角，记录每个传感器亮时舵机的打角
	* 重新测量差速表，差速表在机械部分的文件夹内，可以先画到纸上再测
