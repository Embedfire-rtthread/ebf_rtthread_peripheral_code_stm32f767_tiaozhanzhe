/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 固件库例程
  *********************************************************************
  * @attention
  *
  * 实验平台:野火 STM32F767 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"


/*
*************************************************************************
*                               变量
*************************************************************************
*/
/* 定义线程控制块 */
static rt_thread_t test_thread = RT_NULL;
static rt_thread_t test1_thread = RT_NULL;
/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void test_thread_entry(void* parameter);
static void test1_thread_entry(void* parameter);

/*
*************************************************************************
*                             main 函数
*************************************************************************
*/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
    /* 
	 * 开发板硬件初始化，RTT系统初始化已经在main函数之前完成，
	 * 即在component.c文件中的rtthread_startup()函数中完成了。
	 * 所以在main函数中，只需要创建线程和启动线程即可。
	 */
	
	test_thread =                          /* 线程控制块指针 */
    rt_thread_create( "test",              /* 线程名字 */
                      test_thread_entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      512,                 /* 线程栈大小 */
                      3,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
    
 	test1_thread =                          /* 线程控制块指针 */
    rt_thread_create( "test1",              /* 线程名字 */
                      test1_thread_entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      512,                 /* 线程栈大小 */
                      3,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (test1_thread != RT_NULL)
        rt_thread_startup(test1_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             线程定义
*************************************************************************
*/

static void test_thread_entry(void* parameter)
{	
  while (1)
  {
    LED3_ON;
    rt_thread_delay(500);   /* 延时500个tick */
    rt_kprintf("test_thread running,LED1_ON！\r\n");
    
    LED3_OFF;     
    rt_thread_delay(500);   /* 延时500个tick */		 		
    rt_kprintf("test_thread running,LED1_OFF！\r\n");
  }
}

static void test1_thread_entry(void* parameter)
{	
	static short Acel[3];
	static short Gyro[3];
	static float Temp;
  
  while (1)
  {
    
    MPU6050ReadAcc(Acel);
    printf("加速度：%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
    MPU6050ReadGyro(Gyro);
    printf("    陀螺仪%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
    MPU6050_ReturnTemp(&Temp);
    printf("    温度%8.2f\r\n",Temp);				
    
    #ifdef USE_LCD_DISPLAY	
      {
        char cStr [ 70 ];
        sprintf ( cStr, "Acceleration:%8d%8d%8d",Acel[0],Acel[1],Acel[2] );	//加速度原始数据


        LCD_DisplayStringLine(7,(uint8_t* )cStr);			

        sprintf ( cStr, "Gyro        :%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2] );	//角原始数据

        LCD_DisplayStringLine(8,(uint8_t* )cStr);			

        sprintf ( cStr, "Temperture  :%8.2f",Temp );	//温度值
        LCD_DisplayStringLine(9,(uint8_t* )cStr);			

      }
    #endif
    rt_thread_delay(500);   /* 延时500个tick */		 		
  }
}
/********************************END OF FILE****************************/
