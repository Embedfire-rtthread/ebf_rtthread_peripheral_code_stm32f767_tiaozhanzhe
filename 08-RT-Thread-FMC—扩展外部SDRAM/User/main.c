/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 �̼�������
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32F767 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"


/*
*************************************************************************
*                               ����
*************************************************************************
*/
/* �����߳̿��ƿ� */
static rt_thread_t test_thread = RT_NULL;


uint32_t RadomBuffer[10000];

uint32_t ReadBuffer[10000];

#define SDRAM_SIZE (IS42S16400J_SIZE/4)

uint32_t *pSDRAM;

long long count=0,sdram_count=0;

RNG_HandleTypeDef hrng;

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void test_thread_entry(void* parameter);
void SDRAM_Check(void);

/*
*************************************************************************
*                             main ����
*************************************************************************
*/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
    /* 
	 * ������Ӳ����ʼ����RTTϵͳ��ʼ���Ѿ���main����֮ǰ��ɣ�
	 * ����component.c�ļ��е�rtthread_startup()����������ˡ�
	 * ������main�����У�ֻ��Ҫ�����̺߳������̼߳��ɡ�
	 */
	
	test_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "test",              /* �߳����� */
                      test_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      3,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             �̶߳���
*************************************************************************
*/

static void test_thread_entry(void* parameter)
{	
  /*��ʼ��RNGģ����������*/
  hrng.Instance = RNG;
  HAL_RNG_Init(&hrng);

  printf("��ʼ����10000��SDRAM���������\r\n");   
  for(count=0;count<10000;count++)

  {
      RadomBuffer[count]=HAL_RNG_GetRandomNumber(&hrng);

  }    
  printf("10000��SDRAM����������������\r\n");

  SDRAM_Check();
  
  while (1)
  {
    LED1_ON;
    rt_thread_delay(500);   /* ��ʱ500��tick */
    rt_kprintf("test_thread running,LED1_ON��\r\n");
    
    LED1_OFF;     
    rt_thread_delay(500);   /* ��ʱ500��tick */		 		
    rt_kprintf("test_thread running,LED1_OFF��\r\n");
  }
}


void SDRAM_Check(void)
{
    pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;
	count=0;
	printf("��ʼд��SDRAM\r\n");
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
	printf("д�����ֽ���:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	count=0;
	pSDRAM=(uint32_t*)SDRAM_BANK_ADDR;
	printf("��ʼ��ȡSDRAM����ԭ������Ƚ�\r\n");
	sdram_count=0;
	for(;sdram_count<SDRAM_SIZE;sdram_count++)
	{
		if(*pSDRAM != RadomBuffer[count])
		{
			printf("���ݱȽϴ��󡪡��˳�~\r\n");
			break;
		}
		count++;
		pSDRAM++;
		if(count>=10000)
		{
			count=0;
		}
	}

	printf("�Ƚ�ͨ�����ֽ���:%d\r\n",(uint32_t)pSDRAM-SDRAM_BANK_ADDR);

	if(sdram_count == SDRAM_SIZE)
	{
		LED_GREEN;
		printf("SDRAM���Գɹ�\r\n");
	}
	else
	{
		LED_RED;
		printf("SDRAM����ʧ��\r\n");
	}   
}


/********************************END OF FILE****************************/
