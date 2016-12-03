/*****************************************************************************  
  *  Filename           :        Test.c
  *  Programmers   :     Fang Cheng.
  *  Description       : 	  Test the hardwares
  *  Modification History	:
  *                   ver1.0,2010  ,Fang Cheng
  *                   ver1.1,2010.04.11 ,Fang Huaqi add notes 
  *	 (c) Copyright 2010 HUST RENESAS LAB,The Department of CSE, HUST
  *                   All Rights Reserved
*****************************************************************************/

/******************* LIBRARY********************/
#include "include.h"
#ifdef CAR_DEBUG
extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];
#endif

/***********************Functions Prototype*************************/


/* 
 * ===  FUNCTION  ======================================================================
 *                Name:  Test
 *         Description:  The test of my own
 *           Parameter:  NONE
 *              Return:  NONE
 *                Note:  
 *Modification History:
 *    01a 2013/11/13 10:16:41 Ver1.01
 * =====================================================================================
 */
 #ifdef DEBUG_SHAWN
void Test ( void )
{
    uint8_t switch_value = 0;

    int i = 0;
    char buffer[6];
    char* str = "\n\r";

//     while(1)
//    {
//        i=gl_ulTotalDistance;
//        myitoa(i,(uint8_t *)buffer);
//        UARTSend((uint8_t*) buffer);
//        UARTSend((uint8_t*) str);
//    }

    /*while(1)
    {
        switch_value = ReadSwitch(0x0f);
        if(switch_value&0x01)
        {
            WriteLEDOnDrive(GetDigitalSensorValue()&0x000f);
        }
        else if(switch_value&0x02)
        {
            WriteLEDOnDrive((GetDigitalSensorValue()&0x00f0)>>4);
        }
        else if(switch_value&0x04)
        {
            WriteLEDOnDrive((GetDigitalSensorValue()&0x0f00)>>8);
        }
        else if(switch_value&0x08)
        {
            WriteLEDOnDrive(GET_START_BAR());
        }
    }*/
    /*while(1)
    {
        WriteLEDOnDrive(ReadSwitch((uint8_t) 0xff));
        BUZZER_ON();
    }*/
    /* while(1)
    {
        SetServoAngle(40);
    }*/
    /* while(1)
    {
        switch_value = ReadSwitch(0xff);
        WriteLEDOnDrive(switch_value);
		if(ReadSwitch(0x01))
        {
            PWMout_LR(50);
        }
        else
        {
            PWMout_LR(-50);
        }
        if(ReadSwitch(0x02))
        {
            PWMout_LF(50);
        }
        else
        {
            PWMout_LF(-50);
        }
        if(ReadSwitch(0x04))
        {
            PWMout_RR(50);
        }
        else
        {
            PWMout_RR(-50);
        }
        if(ReadSwitch(0x08))
        {
            PWMout_RF(50);
        }
        else
        {
            PWMout_RF(-50);
        }
    }*/
	
		/*while(1)
		{
			if(Remote())
            {
                WriteLEDOnDrive(0x01);
                BUZZER_ON();
            }
            else
            {
                WriteLEDOnDrive(0x00);
            }
		}*/
		
		/*while(1)
		{
			WriteLEDOnDrive(0x01);
		}*/

    /*while(1)
    {
        if(ReadSwitch(0x01))
        {
            WriteLEDOnDrive(GetDigitalSensorValue() & 0x0f);
        }
        else if(ReadSwitch(0x02))
        {
            WriteLEDOnDrive((GetDigitalSensorValue() >> 4) & 0x0f);
        }
        else if(ReadSwitch(0x04))
        {
            WriteLEDOnDrive((GetDigitalSensorValue() >> 8) & 0x0f);
        }
        else if(ReadSwitch(0x08))
        {
            WriteLEDOnDrive((GET_START_BAR()));
        }
    }*/

    /* while(1)
    {
        switch_value = ReadSwitch(0x0f);
        SetServoAngle((switch_value - 8) * 3);
    }*/

    while(1)
    {
        switch_value = ReadSwitch(0xff);
        WriteLEDOnDrive(switch_value);

        if(Remote())
        {
            BUZZER_ON();
        }
        else
        {
            BUZZER_OFF();
        }

		if(ReadSwitch(0x01))
        {
            PWMout_LR(20);
        }
        else
        {
            PWMout_LR(-20);
        }
        if(ReadSwitch(0x02))
        {
            PWMout_LF(40);
        }
        else
        {
            PWMout_LF(-40);
        }
        if(ReadSwitch(0x04))
        {
            PWMout_RR(60);
        }
        else
        {
            PWMout_RR(-60);
        }
        if(ReadSwitch(0x08))
       {
            PWMout_RF(80);
        }
        else
        {
            PWMout_RF(-80);
        }

        SetServoAngle((switch_value - 8) * 5);        
    }  
}		/* -----  end of function Test  ----- */
#endif

#ifdef CAR_DEBUG
/**********************************************************************************************************
* Function Name         :   TestServo                    
* Description           :   Test the servo and adjust the servo center
* Arguments             : 
* Modification History  : 
01a 2010-11-23 20:25:45   FangHuaqi added annotation(×¢ÊÍ) 
**********************************************************************************************************/
void TestServo(void)
 {
    uint8_t exitFlag1 = 0;		              //  servo Angle Exit Flag
    uint8_t menuSelect1 = 0;	              //  servo Debug Switch Varible  
    uint8_t selectBuff1 = 1;
    int8_t angleTemp = 0;
    /*   Print Following Information from COM   */
   // uint8_t str0[] = "\rTest Servo Angle\n";
	char* str0 = "\rTest Servo Angle\n";
    char* str1 = "\r\n";
    
    char* str2 = "\rPress 'A' to Plus Servo Angle 1       +1\n";
    char* str3 = "\rPress 'D' to Minus Servo Angle 1      -1\n";
    char* str4 = "\rPress 'W' to Plus Servo Angle 5       +5\n";
    char* str5 = "\rPress 'S' to Minus Servo Angle 5      -5\n";

    char* str6 = "\r\n";
    char* str7 = "\rPress 'E' to Exit\n";
    char* str8 = "\r\n";
    char* str9 = "Current Angle = ";
		
	char  str10[4];
	char* str11 = "\r";
    
	UARTSend((uint8_t *)str0);
	UARTSend((uint8_t *)str1);
	UARTSend((uint8_t *)str2);
	UARTSend((uint8_t *)str3);
	UARTSend((uint8_t *)str4);
	UARTSend((uint8_t *)str5);
	UARTSend((uint8_t *)str6);
	UARTSend((uint8_t *)str7);
	UARTSend((uint8_t *)str8);
    UARTSend((uint8_t *)str9);
    angleTemp =  gl_cServoAngle;
		
	myitoa(angleTemp,(uint8_t *)str10);
  
    UARTSend((uint8_t *)str10);   	        //  Display servo Center Value
    UARTSend((uint8_t *)str11);
    
	exitFlag1 = 0;													//  Clear Exit Flag
    while (!exitFlag1)											//  If not Get Exit Flag,Cycling
    {
        menuSelect1 = 0;					    			//  Clear Switch Varible
        selectBuff1 = 1;
        menuSelect1 = UART_recive();	     //  Get COM Input Value            
        switch (menuSelect1)								//  Choose Test Mode
        {
            /*  If Input 'a',Servo Angle Value Plus 1  */  
            case 'A':
            case 'a':								               
                 angleTemp ++;            						        
                 break;										//  Exit from Switch Model
                 
            /*  If Input 'd',Servo Angle Value Minus 1  */                  
       	   case 'D':
            case 'd':
                 angleTemp --;                
                 break;										//  Exit from Switch Model
                 
            /*  If Input 'w',Servo Angle Value Plus 5  */              
            case 'W':
            case 'w':
                 angleTemp += 5;                
                 break;										//  Exit from Switch Model
                 
           /*  If Input 's',Servo Angle Value Minus 5  */            
            case 'S':
            case 's':
                 angleTemp -= 5;           
                 break;										//  Exit from Switch Model
                 
            /*  If Input 'e',Servo Angle Test Finish  */                 
            case 'E':
            case 'e':
                 angleTemp = 0;
                 exitFlag1 = 1;		         //  Set Exit Flag
				 BUZZER_OFF();
				 WriteLEDOnDrive(0x00);                  
                 break;						 				 //  Exit from Switch Model 
                 
            /*  If Input other Strings,Return Cycling  */                 
            default:      
                 selectBuff1 = 0;
				 BUZZER_OFF();
				 WriteLEDOnDrive(0x00); 
                 break;								  	 //  Exit from Switch Model
        }
        //angle limit          
        if (angleTemp > MAX_ANGLE)
        {
            angleTemp = MAX_ANGLE;   
        } 
        else if (angleTemp < - MAX_ANGLE) 
        {
            angleTemp = -MAX_ANGLE;          
        }
        
        if (selectBuff1)  
        {
			myitoa(angleTemp,(uint8_t *)str10);
			UARTSend((uint8_t *)str9);
			UARTSend((uint8_t *)str10);
			UARTSend((uint8_t *)str11);            
        } 
        gl_cServoAngle = angleTemp;
			SetServoAngle(gl_cServoAngle);
    }   
 }
/**********************************************************************************************************
* Function Name         :   TestMotor                    
* Description           :   Test the motor
* Arguments             : 
* Modification History  : 
01a 2010-11-23 20:25:45   FangHuaqi added annotation(×¢ÊÍ) 
**********************************************************************************************************/
void TestMotor(void)
{
    uint8_t exitFlag = 0;		                   
    uint8_t menuSelect = 0;	                          
    uint8_t selectBuff = 1;
    int8_t motorPWMTemp = 0;                                                         
    
	  /*   Print Following Information from COM   */
//  uint8_t str0[] = {"\rTest Motor Speed\n"};    
	char* str0 = "\rTest Motor Speed\n";  
    char* str1 = "\r\n";
    char* str2 = "\rPress 'A' to Plus Motor Speed 1       +1\n";
    char* str3 = "\rPress 'D' to Minus Motor Speed 1      -1\n";
    char* str4 = "\rPress 'W' to Plus Motor Speed 5       +5\n";
    char* str5 = "\rPress 'S' to Minus Motor Speed 5      -5\n";
    char* str6 = "\r\n";
    char* str7 = "\rPress 'E' to Exit\n";
    char* str8 = "\r\n";
    
    char* str9 = "Current Motor PWM = ";
    char  str10[4];
    char* str11 = "\r";

    UARTSend((uint8_t *)str0);
    UARTSend((uint8_t *)str1);
    UARTSend((uint8_t *)str2);
    UARTSend((uint8_t *)str3);
    UARTSend((uint8_t *)str4);
    UARTSend((uint8_t *)str5);
    UARTSend((uint8_t *)str6);
	UARTSend((uint8_t *)str7);
	UARTSend((uint8_t *)str8);

    motorPWMTemp =  gl_cMotorPWM;
    
	myitoa(motorPWMTemp,(uint8_t *)str10);
	UARTSend((uint8_t *)str9);
	UARTSend((uint8_t *)str10);
	UARTSend((uint8_t *)str11);		//  Display "gl_motoSpeed" Value
    
    exitFlag = 0;									        									//  Clear Exit Flag
    while (!exitFlag)							            							//  If not set Exit Flag,Cycling
    {
        menuSelect = 0;						       	          				//  Clear Switch Varible
        selectBuff = 1;
        menuSelect = UART_recive();                       //  Get COM Input Value            
        switch (menuSelect)					                    
        {
            /*  If Input 'a',Motor Speed Value Plus 1  */  
            case 'A':
            case 'a':								                            
                 motorPWMTemp++;                
                 break;
                 
             /*  If Input 'd',Motor Speed Value Minus 1  */                  
						case 'D':
            case 'd':
                 motorPWMTemp--;                  
                 break;
                 
            /*  If Input 'w',Motor Speed Value Plus 5  */              
            case 'W':
            case 'w':
                 motorPWMTemp += 5;                 
                 break;
                 
            /*  If Input 's',Motor Speed Value Minus 5  */            
            case 'S':
            case 's':
                 motorPWMTemp -= 5;                
                 break; 
                 
            /*  If Input 'e',Motor Speed Test Finish  */                 
            case 'E':
            case 'e':
                 motorPWMTemp = 0;  
								 BUZZER_OFF();
								 WriteLEDOnDrive(0x00);                         
                 exitFlag = 1;		                             //  Set Exit Flag                 
                 break;
                 	
            /*  If Input other Strings,Return Cycling  */                 
            default:                                          //default here is must       
                 selectBuff = 0;
                 break;							              						//  If Input Other String or no Inputs,Do not Print Value
        }
        
        /*  PWM Min_Max Value Limited  */        
        if (motorPWMTemp > 100)
        {
           motorPWMTemp = 100;   
        } 
        else if (motorPWMTemp < -100) 
        {
           motorPWMTemp = -100;          
        }
        
        /*  If Input a New Effectable Available  */        
        if (selectBuff)  
        {
            myitoa(motorPWMTemp,(uint8_t *)str10);
		    UARTSend((uint8_t *)str9);
		    UARTSend((uint8_t *)str10);
		    UARTSend((uint8_t *)str11);		//  Display "gl_motoSpeed" Value
        } 
        gl_cMotorPWM = motorPWMTemp;
		PWMOut(gl_cMotorPWM,0); 
    }
 }
/**********************************************************************************************************
* Function Name         :   TestSensor                    
* Description           :   Test the sensor
* Arguments             : 
* Modification History  : 
01a 2010-11-23 20:25:45   FangHuaqi added annotation(×¢ÊÍ) 
**********************************************************************************************************/
 void TestSensor(void)
 {
    uint8_t exitFlag = 0;		                   
    uint8_t menuSelect = 0;	                          
	  int sensorInf = 0;
    uint8_t i = 0;
                                                       
    /*   Print Following Information from COM   */
    char* str0 = "\rTest Car Sensors\n";		
    char* str1 = "\r\n";
    char* str2 = "\rPress '1' Display trace sensor value\n";
    char* str3 = "\rPress '2' Display start bar sensor\n";
    char* str4 = "\r\n";
    char* str5 = "\rPress 'E' to Exit\n";
    char* str6 = "\r\n";
    char  str7[6];
		
	UARTSend((uint8_t *)str0);
	UARTSend((uint8_t *)str1);
	UARTSend((uint8_t *)str2);
	UARTSend((uint8_t *)str3);
	UARTSend((uint8_t *)str4);
	UARTSend((uint8_t *)str5);
	UARTSend((uint8_t *)str6);
		
    exitFlag = 0;									                   //  Clear Exit Flag
    while (!exitFlag)							                   //  If not set Exit Flag,Cycling
    {
        menuSelect = 0;						                   //  Clear Switch Varible
		menuSelect = UART_recive();                //  Get COM Input Value            
        switch (menuSelect)					                    
        {
            /*  If Input '1',Display trace sensor value  */  
            case '1':							                            
                    sensorInf = (int)GetDigitalSensorValue();  
                    BUZZER_OFF();
                    //myitoa(sensorInf,(uint8_t *)str7);
                    ////UARTSend((uint8_t *)str7);       
                    for(i = 0; i < 11; i++)
                    {
                        str7[0] = !!(sensorInf & 0x0400) + '0';
                        str7[1] = '\0';
                        sensorInf = sensorInf << 1;
                        UARTSend((uint8_t *)str7);
                    }
                    UARTSend((uint8_t *)str6);
                    break;
                 
             /*  If Input '2',Display start bar sensor  */                  
       	    case '2':
								 sensorInf = GET_START_BAR();				 
								 myitoa(sensorInf,(uint8_t *)str7);
							   UARTSend((uint8_t *)str7);            
						     UARTSend((uint8_t *)str6);                 
                 break;
            
            /*  If Input 'e',Car Sensors Test Finish  */                 
            case 'E':
            case 'e':                     
                 exitFlag = 1;		                                 // Set Exit Flag
								 BUZZER_OFF();
				         WriteLEDOnDrive(0x00);                 
                 break;
                 	
            /*  If Input other Strings,Return Cycling  */                 
            default:                                               //default here is must      
                 break;							                               // If Input Other String or no Inputs,Do not Print Value
        } 
    }
 }  
 /**********************************************************************************************************
* Function Name         :   TestPeriphery                    
* Description           :   Test the Periphery
* Arguments             : 
* Modification History  : 
01a 2010-11-23 20:25:45   FangHuaqi added annotation(×¢ÊÍ) 
**********************************************************************************************************/
 void TestPeriphery(void)
 {
    uint8_t exitFlag = 0;		                   
    uint8_t menuSelect = 0;	                          	
		uint8_t temp = 0;
                                                       
    /*   Print Following Information from COM   */
    char* str0 = "\rTest Periphery\n";		
    char* str1 = "\r\n";
    char* str2 = "\rPress '1' Display 4bit_Switch Value to Screen and LEDs\n";    
	char* str3 = "\rPress '2' All LEDs On\n";
	char* str4 = "\rPress '3' All LEDs off\n";
	char* str5 = "\rPress '4' Buzzer On\n";
	char* str6 = "\rPress '5' Buzzer off\n";
    char* str7 = "\r\n";
    char* str8 = "\rPress 'E' to Exit\n";
    char* str9 = "\r\n";
    char  str10[4];
		
		UARTSend((uint8_t *)str0);
		UARTSend((uint8_t *)str1);
		UARTSend((uint8_t *)str2);
		UARTSend((uint8_t *)str3);
		UARTSend((uint8_t *)str4);
		UARTSend((uint8_t *)str5);
		UARTSend((uint8_t *)str6);
		UARTSend((uint8_t *)str7);
		UARTSend((uint8_t *)str8);
		UARTSend((uint8_t *)str9);
    
		exitFlag = 0;									                 		  //  Clear Exit Flag
    while (!exitFlag)							                      //  If not set Exit Flag,Cycling
    {
        menuSelect = UART_recive(); 					                      //  Clear Switch Varible        
				
        switch (menuSelect)					                    
        {
            /*  If Input '1',Display 4bit_Switch Value to Screen and LEDs  */  
            case '1':							                            
                 temp = ReadSwitch(0x0f);
								 WriteLEDOnDrive(temp);  
								 BUZZER_OFF();
						     myitoa(temp,(uint8_t *)str10);
							   UARTSend((uint8_t *)str10);            
						     UARTSend((uint8_t *)str9);              
                 break;
                 
					  /*  If Input '2',All LEDs On\n*/                  
       	    case '2':
								 WriteLEDOnDrive(0x0f); 
								 BUZZER_OFF();              
                 break;

            /*  If Input '3',All LEDs off\n*/                  
       	    case '3':
								 WriteLEDOnDrive(0x00); 
							   BUZZER_OFF();               
                 break;

            /*  If Input '4',Buzzer On\n*/                  
       	    case '4':
								 WriteLEDOnDrive(0x00);
								 BUZZER_ON();              
                 break;

            /*  If Input '5',Buzzer Off\n*/                  
       	    case '5':
								 WriteLEDOnDrive(0x00); 
								 BUZZER_OFF();
                 break;
            
            /*  If Input 'e',Car Sensors Test Finish  */                 
            case 'E':
            case 'e':                     
                 exitFlag = 1;	
								 WriteLEDOnDrive(0x00); 
								 BUZZER_OFF();	                                        //  Set Exit Flag                 
                 break;
                 	
            /*  If Input other Strings,Return Cycling  */                 
            default:                                                    //default here is must       
                 break;							                                    //  If Input Other String or no Inputs,Do not Print Value
        } 
    }
 } 
 /**********************************************************************************************************
* Function Name         :   TestEncoder                    
* Description           :   Test the Encoder
* Arguments             : 
* Modification History  : 
01a 2010-11-23 20:25:45   FangHuaqi added annotation(×¢ÊÍ) 
**********************************************************************************************************/
 void TestEncoder(void)
 {
		uint8_t exitFlag = 0;		                   
    uint8_t menuSelect = 0;	                          	
		int speed_temp = 0;
	 unsigned long distance_temp=0;
                                                       
    /*   Print Following Information from COM   */
    char* str0 = "\rTestEncoder\n";		
    char* str1 = "\r\n";
    char* str2 = "\rPress '1' Display current speed\n";    
		char* str3 = "\rPress '2' Display current distance\n"; 
    char* str4 = "\rPress 'E' to Exit\n";
    char* str5 = "\r\n";
    char  strSpeed[5],strDistance[10];
		
		UARTSend((uint8_t *)str0);
		UARTSend((uint8_t *)str1);
		UARTSend((uint8_t *)str2);
		UARTSend((uint8_t *)str3);
    UARTSend((uint8_t *)str4);
		UARTSend((uint8_t *)str5);
		exitFlag = 0;									                 		  //  Clear Exit Flag
    while (!exitFlag)							                      //  If not set Exit Flag,Cycling
    {
        menuSelect = UART_recive(); 					                      //  Clear Switch Varible        
				
        switch (menuSelect)					                    
        {
            /*  If Input '1',Display 4bit_Switch Value to Screen and LEDs  */  
            case '1':							                            
                 speed_temp=gl_iCurSpeed;
						     myitoa(speed_temp,(uint8_t *)strSpeed);
							   UARTSend((uint8_t *)strSpeed);            
						     UARTSend((uint8_t *)str5);              
                 break;
                 
					  /*  If Input '2',All LEDs On\n*/                  
       	    case '2':
								  distance_temp=gl_ulTotalDistance;
						     myitoa(distance_temp,(uint8_t *)strDistance);
							   UARTSend((uint8_t *)strDistance);            
						     UARTSend((uint8_t *)str5);            
                 break;
            
            /*  If Input 'e',Car Sensors Test Finish  */                 
            case 'E':
            case 'e':                     
                 exitFlag = 1;	
                 break;
                 	
            /*  If Input other Strings,Return Cycling  */                 
            default:                                                    //default here is must       
                 break;							                                    //  If Input Other String or no Inputs,Do not Print Value
        } 
    }
 }
 
/**********************************************************************************************************
* Function Name         :   TestCircuitBoard                    
* Description           :   Test the CircuitBoard menu selection
* Arguments             : 
* Modification History  : 
01a 2010-11-23 20:25:45   FangHuaqi added annotation(×¢ÊÍ) 
**********************************************************************************************************/


void TestCircuitBoard(void)
{
    uint8_t menuSelect0 = 0;
    uint8_t exitFlag0 = 0;
    uint8_t printFlag0 = 1; 
	  
    char* str0 = "\r\n";
    char* str1 = "\rPeripheral Equipment,Drive Program,Circuit Board Test Menu-----\n";
    char* str2 = "\r\n";  
    char* str3 = "\rPress '1' to Test Servo\r\n";
    char* str4 = "\rPress '2' to Test Motor\r\n";
    char* str5 = "\rPress '3' to Test Sensor\r\n";
    char* str6 = "\rPress '4' to Test Periphery\r\n";
    char* str7 = "\rPress '5' to Test Encoder";
    char* str8 = "\r\n";

    while (!exitFlag0)
    {        
        if (printFlag0)
        {
		    UARTSend((uint8_t *)str0);
            UARTSend((uint8_t *)str1);
            UARTSend((uint8_t *)str2);
            UARTSend((uint8_t *)str3);
            UARTSend((uint8_t *)str4);
            UARTSend((uint8_t *)str5);
            UARTSend((uint8_t *)str6);
            UARTSend((uint8_t *)str7);
            UARTSend((uint8_t *)str8);           
            printFlag0 = 0;
        }
        menuSelect0 = UART_recive();    
        switch (menuSelect0)
        {
		
            case '1':
                TestServo(); 
                printFlag0 = 1;
                break;
                
            case '2': 
                TestMotor();
                printFlag0 = 1;
                break;
                
            case '3':
                TestSensor();      
                printFlag0 = 1;      
                break;     
                         
            case '4':
                TestPeriphery();
                printFlag0 = 1;
                break;

            case '5':
                TestEncoder();
                printFlag0 = 1;
                break;

            case '6':
                PWMOut(20,0);
                SetServoAngle(0);
                UARTSend((uint8_t *)str7);
                while(UART_recive()!='e')
                {
                    
                }
                break;
                
            case 'E':            
            case 'e':
                exitFlag0 = 1;
                break; 
                                                 
            default:
                break;  
        }
    } 
}
#endif

