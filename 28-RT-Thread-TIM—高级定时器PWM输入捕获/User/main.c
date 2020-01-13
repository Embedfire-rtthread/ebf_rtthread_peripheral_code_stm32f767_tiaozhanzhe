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
///* 定义信号量控制块 */
//rt_sem_t test_sem = RT_NULL;

extern TIM_HandleTypeDef  TIM_PWMOUTPUT_Handle;
extern TIM_HandleTypeDef  TIM_PWMINPUT_Handle;
extern __IO uint16_t IC2Value;
extern __IO uint16_t IC1Value;
extern __IO float DutyCycle;
extern __IO float Frequency;
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
//   /* 创建一个信号量 */
//	test_sem = rt_sem_create("test_sem",/* 信号量名字 */
//                     1,     /* 信号量初始值，默认有一个信号量 */
//                     RT_IPC_FLAG_FIFO); /* 信号量模式 FIFO(0x00)*/
//  if (test_sem != RT_NULL)
//    rt_kprintf("信号量创建成功！\n\n");
  
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
//		rt_sem_take(test_sem,	/* 获取信号量 */
//                RT_WAITING_FOREVER); 	/* 等待时间：一直等 */

    rt_thread_delay ( 1000 );  					      //每1s读一次	
		printf("IC1Value = %d  IC2Value = %d ",IC1Value,IC2Value);
		printf("占空比：%0.2f%%   频率：%0.2fHz\n",DutyCycle,Frequency);
    
  }
}

/********************************END OF FILE****************************/
