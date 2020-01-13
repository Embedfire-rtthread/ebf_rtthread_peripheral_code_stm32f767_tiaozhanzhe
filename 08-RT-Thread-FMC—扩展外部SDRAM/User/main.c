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


uint32_t RadomBuffer[10000];

uint32_t ReadBuffer[10000];

#define SDRAM_SIZE (IS42S16400J_SIZE/4)

uint32_t *pSDRAM;

long long count=0,sdram_count=0;

RNG_HandleTypeDef hrng;

/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void test_thread_entry(void* parameter);
void SDRAM_Check(void);

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
  /*初始化RNG模块产生随机数*/
  hrng.Instance = RNG;
  HAL_RNG_Init(&hrng);

  printf("开始生成10000个SDRAM测试随机数\r\n");   
  for(count=0;count<10000;count++)

  {
      RadomBuffer[count]=HAL_RNG_GetRandomNumber(&hrng);

  }    
  printf("10000个SDRAM测试随机数生成完毕\r\n");

  SDRAM_Check();
  
  while (1)
  {
    LED1_ON;
    rt_thread_delay(500);   /* 延时500个tick */
    rt_kprintf("test_thread running,LED1_ON！\r\n");
    
    LED1_OFF;     
    rt_thread_delay(500);   /* 延时500个tick */		 		
    rt_kprintf("test_thread running,LED1_OFF！\r\n");
  }
}


void SDRAM_Check(void)
{
    pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;
	count=0;
	printf("开始写入SDRAM\r\n");
	for(sdram_count=0;sdram_count<SDRAM_SIZE;sdram_count++)
	{
		*pSDRAM=RadomBuffer[count];
		count++;
		pSDRAM++;
		if(count>=10000)

		{
			count=0;
		}
	}
	printf("写入总字节数:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	count=0;
	pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;
	printf("开始读取SDRAM并与原随机数比较\r\n");
	sdram_count=0;
	for(;sdram_count<SDRAM_SIZE;sdram_count++)
	{
		if(*pSDRAM != RadomBuffer[count])
		{
			printf("数据比较错误——退出~\r\n");
			break;
		}
		count++;
		pSDRAM++;
		if(count>=10000)
		{
			count=0;
		}
	}

	printf("比较通过总字节数:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	if(sdram_count == SDRAM_SIZE)
	{
		LED_GREEN;
		printf("SDRAM测试成功\r\n");
	}
	else
	{
		LED_RED;
		printf("SDRAM测试失败\r\n");
	}   
}


/********************************END OF FILE****************************/
