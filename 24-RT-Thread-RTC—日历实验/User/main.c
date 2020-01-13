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
	/* RTC配置：选择时钟源，设置RTC_CLK的分频系数 */
	RTC_CLK_Config();

	if (HAL_RTCEx_BKUPRead(&Rtc_Handle,RTC_BKP_DRX) != 0X32F3)
	{				
		/* 设置时间和日期 */
		RTC_TimeAndDate_Set();
	}
	else
	{
		/* 检查是否电源复位 */
		if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
		{
		  printf("\r\n 发生电源复位....\r\n");
		}
		/* 检查是否外部复位 */
		else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
		{
		  printf("\r\n 发生外部复位....\r\n");
		}
		printf("\r\n 不需要重新配置RTC....\r\n");    
		/* 使能 PWR 时钟 */
		__HAL_RCC_PWR_CLK_ENABLE();
		/* PWR_CR:DBF置1，使能RTC、RTC备份寄存器和备份SRAM的访问 */
		HAL_PWR_EnableBkUpAccess();
		/* 等待 RTC APB 寄存器同步 */
		HAL_RTC_WaitForSynchro(&Rtc_Handle);
	} 
	/* 显示时间和日期 */
	RTC_TimeAndDate_Show();
  
}

/********************************END OF FILE****************************/
