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

/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void test_thread_entry(void* parameter);


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
    LED1( ON );			 // 亮 
    rt_thread_delay(1000);
    LED1( OFF );		  // 灭
    rt_thread_delay(1000);

    LED2( ON );			// 亮 
    rt_thread_delay(1000);
    LED2( OFF );		  // 灭

    LED3( ON );			 // 亮 
    rt_thread_delay(1000);
    LED3( OFF );		  // 灭	
    
    LED4( ON );			 // 亮 
    rt_thread_delay(1000);
    LED4( OFF );		  // 灭	
    
    /*轮流显示 红绿蓝黄紫青白 颜色*/
    LED_RED;
    rt_thread_delay(1000);
    
    LED_GREEN;
    rt_thread_delay(1000);
    
    LED_BLUE;
    rt_thread_delay(1000);
    
    LED_YELLOW;
    rt_thread_delay(1000);
    
    LED_PURPLE;
    rt_thread_delay(1000);
            
    LED_CYAN;
    rt_thread_delay(1000);
    
    LED_WHITE;
    rt_thread_delay(1000);
    
    LED_RGBOFF;
    rt_thread_delay(1000);
    rt_thread_delay(500);   /* 延时500个tick */		 		
  }
}

/********************************END OF FILE****************************/
