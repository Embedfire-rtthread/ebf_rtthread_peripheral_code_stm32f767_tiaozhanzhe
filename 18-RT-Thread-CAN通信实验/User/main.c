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
static rt_thread_t test1_thread = RT_NULL;
/* �����ź������ƿ� */
rt_sem_t test_sem = RT_NULL;

__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ


/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void test_thread_entry(void* parameter);
static void test1_thread_entry(void* parameter);

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
  rt_kprintf("\r\n ��ӭʹ��Ұ��  STM32 F767 �����塣\r\n");
  rt_kprintf("\r\n Ұ��F767 CANͨѶʵ������\r\n");
	
	rt_kprintf("\r\n ʵ�鲽�裺\r\n");

	rt_kprintf("\r\n 1.ʹ�õ������Ӻ�����CANѶ�豸\r\n");
	rt_kprintf("\r\n 2.ʹ������ñ���Ӻ�:5v --- C/4-5V \r\n");
	rt_kprintf("\r\n 3.���¿������KEY1������ʹ��CAN���ⷢ��0-7�����ݰ���������չIDΪ0x1314 \r\n");
	rt_kprintf("\r\n 4.���������CAN���յ���չIDΪ0x1314�����ݰ�����������Դ�ӡ�����ڡ� \r\n");
	rt_kprintf("\r\n 5.�����е�can������Ϊ1MBps��Ϊstm32��can������ʡ� \r\n");

   /* ����һ���ź��� */
	test_sem = rt_sem_create("test_sem",/* �ź������� */
                     0,     /* �ź�����ʼֵ��Ĭ����һ���ź��� */
                     RT_IPC_FLAG_FIFO); /* �ź���ģʽ FIFO(0x00)*/
  if (test_sem != RT_NULL)
    rt_kprintf("�ź��������ɹ���\n\n");
  
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
	test1_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "test1",              /* �߳����� */
                      test1_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      4,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (test1_thread != RT_NULL)
        rt_thread_startup(test1_thread);
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
  while (1)
  {
		/*��һ�ΰ�������һ������*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
			LED_BLUE;			
			/* װ��һ֡���� */
			CAN_SetMsg();
			/* ��ʼ�������� */
			HAL_CAN_Transmit_IT(&Can_Handle);
			LED_RGBOFF;			
		}
    
    rt_thread_delay(20);   /* ��ʱ20��tick */		 		
  }
}

static void test1_thread_entry(void* parameter)
{	
  while (1)
  {
    rt_sem_take(test_sem,	/* ��ȡ�ź��� */
                RT_WAITING_FOREVER); /* �ȴ�ʱ�䣺һֱ�� */		
    {
      /*���ͳɹ�*/
			LED_GREEN;
			printf("\r\nCAN���յ����ݣ�\r\n");	
			CAN_DEBUG_ARRAY(Can_Handle.pRxMsg->Data,8); 			
			flag=0;
			LED_RGBOFF;
    }
    		
  }
}



/********************************END OF FILE****************************/
