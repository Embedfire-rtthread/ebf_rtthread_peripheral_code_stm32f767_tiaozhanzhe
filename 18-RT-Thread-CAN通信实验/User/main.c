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
/* 定义信号量控制块 */
rt_sem_t test_sem = RT_NULL;

__IO uint32_t flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值


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
  rt_kprintf("\r\n 欢迎使用野火  STM32 F767 开发板。\r\n");
  rt_kprintf("\r\n 野火F767 CAN通讯实验例程\r\n");
	
	rt_kprintf("\r\n 实验步骤：\r\n");

	rt_kprintf("\r\n 1.使用导线连接好两个CAN讯设备\r\n");
	rt_kprintf("\r\n 2.使用跳线帽连接好:5v --- C/4-5V \r\n");
	rt_kprintf("\r\n 3.按下开发板的KEY1键，会使用CAN向外发送0-7的数据包，包的扩展ID为0x1314 \r\n");
	rt_kprintf("\r\n 4.若开发板的CAN接收到扩展ID为0x1314的数据包，会把数据以打印到串口。 \r\n");
	rt_kprintf("\r\n 5.本例中的can波特率为1MBps，为stm32的can最高速率。 \r\n");

   /* 创建一个信号量 */
	test_sem = rt_sem_create("test_sem",/* 信号量名字 */
                     0,     /* 信号量初始值，默认有一个信号量 */
                     RT_IPC_FLAG_FIFO); /* 信号量模式 FIFO(0x00)*/
  if (test_sem != RT_NULL)
    rt_kprintf("信号量创建成功！\n\n");
  
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
                      4,                   /* 线程的优先级 */
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
		/*按一次按键发送一次数据*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
			LED_BLUE;			
			/* 装载一帧数据 */
			CAN_SetMsg();
			/* 开始发送数据 */
			HAL_CAN_Transmit_IT(&Can_Handle);
			LED_RGBOFF;			
		}
    
    rt_thread_delay(20);   /* 延时20个tick */		 		
  }
}

static void test1_thread_entry(void* parameter)
{	
  while (1)
  {
    rt_sem_take(test_sem,	/* 获取信号量 */
                RT_WAITING_FOREVER); /* 等待时间：一直等 */		
    {
      /*发送成功*/
			LED_GREEN;
			printf("\r\nCAN接收到数据：\r\n");	
			CAN_DEBUG_ARRAY(Can_Handle.pRxMsg->Data,8); 			
			flag=0;
			LED_RGBOFF;
    }
    		
  }
}



/********************************END OF FILE****************************/
