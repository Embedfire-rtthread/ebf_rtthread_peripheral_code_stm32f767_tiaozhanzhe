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


typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* 获取缓冲区的长度 */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

   
/* 发送缓冲区初始化 */
uint8_t Tx_Buffer[] = "感谢您选用野火stm32开发板\r\nhttp://firestm32.taobao.com";
uint8_t Rx_Buffer[BufferSize];

//读取的ID存储位置
__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus1 = FAILED;


/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void test_thread_entry(void* parameter);

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

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
	rt_kprintf("\r\n这是一个16M串行flash(W25Q128)实验(QSPI驱动) \r\n");
  
	/* 获取 Flash Device ID */
	DeviceID = QSPI_FLASH_ReadDeviceID();
  
  rt_thread_delay(500);   /* 延时500个tick */
  
	/* 获取 SPI Flash ID */
	FlashID = QSPI_FLASH_ReadID();
  
	printf("\r\nFlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	/* 检验 SPI Flash ID */
	if (FlashID == sFLASH_ID) 
	{	
		printf("\r\n检测到QSPI FLASH W25Q128 !\r\n");
		
		/* 擦除将要写入的 QSPI FLASH 扇区，FLASH写入前要先擦除 */
		BSP_QSPI_Erase_Block(FLASH_SectorToErase);	 	 
		
		/* 将发送缓冲区的数据写到flash中 */
		BSP_QSPI_Write(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\n写入的数据为：\r\n%s", Tx_Buffer);
		
		/* 将刚刚写入的数据读出来放到接收缓冲区中 */
		BSP_QSPI_Read(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n读出的数据为：\r\n%s", Rx_Buffer);
		
		/* 检查写入的数据与读出的数据是否相等 */
		TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
		
		if( PASSED == TransferStatus1 )
		{    
			LED_GREEN;
			printf("\r\n16M串行flash(W25Q128)测试成功!\n\r");
		}
		else
		{        
			LED_RED;
			printf("\r\n16M串行flash(W25Q128)测试失败!\n\r");
		}
	}// if (FlashID == sFLASH_ID)
	else
	{    
		LED_RED;
		printf("\r\n获取不到 W25Q128 ID!\n\r");
	}
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


/*
 * 函数名：Buffercmp
 * 描述  ：比较两个缓冲区中的数据是否相等
 * 输入  ：-pBuffer1     src缓冲区指针
 *         -pBuffer2     dst缓冲区指针
 *         -BufferLength 缓冲区长度
 * 输出  ：无
 * 返回  ：-PASSED pBuffer1 等于   pBuffer2
 *         -FAILED pBuffer1 不同于 pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
}

/********************************END OF FILE****************************/
