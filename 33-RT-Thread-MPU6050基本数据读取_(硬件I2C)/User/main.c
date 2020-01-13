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
                      3,                   /* �̵߳����ȼ� */
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
    LED3_ON;
    rt_thread_delay(500);   /* ��ʱ500��tick */
    rt_kprintf("test_thread running,LED1_ON��\r\n");
    
    LED3_OFF;     
    rt_thread_delay(500);   /* ��ʱ500��tick */		 		
    rt_kprintf("test_thread running,LED1_OFF��\r\n");
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
    printf("���ٶȣ�%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
    MPU6050ReadGyro(Gyro);
    printf("    ������%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
    MPU6050_ReturnTemp(&Temp);
    printf("    �¶�%8.2f\r\n",Temp);				
    
    #ifdef USE_LCD_DISPLAY	
      {
        char cStr [ 70 ];
        sprintf ( cStr, "Acceleration:%8d%8d%8d",Acel[0],Acel[1],Acel[2] );	//���ٶ�ԭʼ����


        LCD_DisplayStringLine(7,(uint8_t* )cStr);			

        sprintf ( cStr, "Gyro        :%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2] );	//��ԭʼ����

        LCD_DisplayStringLine(8,(uint8_t* )cStr);			

        sprintf ( cStr, "Temperture  :%8.2f",Temp );	//�¶�ֵ
        LCD_DisplayStringLine(9,(uint8_t* )cStr);			

      }
    #endif
    rt_thread_delay(500);   /* ��ʱ500��tick */		 		
  }
}
/********************************END OF FILE****************************/
