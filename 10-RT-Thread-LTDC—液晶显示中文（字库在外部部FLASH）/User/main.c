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

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void test_thread_entry(void* parameter);

void LCD_Test(void);

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
                      1024,                 /* �߳�ջ��С */
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
  while (1)
  {
    LCD_Test(); 
  }
}


/*���ڲ��Ը���Һ���ĺ���*/
void LCD_Test(void)
{
	/*��ʾ��ʾ����*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
    /* ѡ��LCD��һ�� */
    LCD_SelectLayer(0);
	
	/* ��������ʾȫ�� */
	LCD_Clear(LCD_COLOR_BLACK);	
	/*����������ɫ������ı�����ɫ(�˴��ı�������ָLCD�ı����㣡ע������)*/
	LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	/*ѡ������*/
	LCD_SetFont(&LCD_DEFAULT_FONT);

    LCD_DisplayStringLine_EN_CH(1,(uint8_t* )"(Ұ��5.0Ӣ��Һ��������)");
    LCD_DisplayStringLine_EN_CH(2,(uint8_t* )"�ֱ���:800x480 ����");
    LCD_DisplayStringLine_EN_CH(3,(uint8_t* )"������:5����ݴ�����");
    LCD_DisplayStringLine_EN_CH(4,(uint8_t* )"ʹ��STM32-LTDCֱ������,�����ⲿҺ��������");
    LCD_DisplayStringLine_EN_CH(5,(uint8_t* )"֧��RGB888/565,24λ��������");
    LCD_DisplayStringLine_EN_CH(6,(uint8_t* )"������ʹ��IIC��������");

    /*ʹ��c��׼��ѱ���ת�����ַ���*/
    sprintf(dispBuff,"��ʾ��������: testCount = %d ",testCNT);
	LCD_ClearLine(7);
	/*����������ɫ������ı�����ɫ(�˴��ı�������ָLCD�ı����㣡ע������)*/
	LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	LCD_DisplayStringLine_EN_CH(7,(uint8_t* )dispBuff);


	/* ��ֱ�� */
	LCD_SetTextColor(LCD_COLOR_BLUE);

	LCD_ClearLine(8);
    LCD_DisplayStringLine_EN_CH(8,(uint8_t* )"����:");
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
	LCD_DrawLine(50,250,750,250);  
	LCD_DrawLine(50,300,750,300);

	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
	LCD_DrawLine(300,250,400,400);  
	LCD_DrawLine(600,250,600,400);

	rt_thread_delay(500);   /* ��ʱ500��tick */	

	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
	LCD_FillRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);


	/*������*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(8);
    LCD_DisplayStringLine_EN_CH(8,(uint8_t* )"������:");
	
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
	LCD_DrawRect(200,250,200,100);

	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
	LCD_DrawRect(350,250,200,50);

	LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
	LCD_DrawRect(200,350,50,200);

	rt_thread_delay(500);   /* ��ʱ500��tick */	


	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
	LCD_FillRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);


	/*������*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(8);
    LCD_DisplayStringLine_EN_CH(8,(uint8_t* )"������:");

	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
	LCD_FillRect(200,250,200,100);

	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
	LCD_FillRect(350,250,200,50);

	LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
	LCD_FillRect(200,350,50,200);

	rt_thread_delay(500);   /* ��ʱ500��tick */	

	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
	LCD_FillRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);

	/* ��Բ */
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(8);
    LCD_DisplayStringLine_EN_CH(8,(uint8_t* )"��Բ:");

	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_RED);
	LCD_DrawCircle(200,350,50);

	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_GREEN);
	LCD_DrawCircle(350,350,75);

	rt_thread_delay(500);   /* ��ʱ500��tick */	

	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
	LCD_FillRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);


	/*���Բ*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(8);
    LCD_DisplayStringLine_EN_CH(8,(uint8_t* )"���Բ:");

	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
	LCD_FillCircle(300,350,50);

	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
	LCD_FillCircle(450,350,75);

	rt_thread_delay(500);   /* ��ʱ500��tick */	

	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
	LCD_FillRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);

	LCD_ClearLine(8);
	
	/*͸��Ч�� ǰ�������*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(8);
	LCD_DisplayStringLine_EN_CH(8,(uint8_t* )"˫��͸��Ч����");
	
	/*����ǰ���㲻͸����*/
	LCD_SetTransparency(1, 128);

    /* ѡ��LCD��һ�� */
    LCD_SelectLayer(1);
	
	/* ��������ʾȫ�� */
	LCD_Clear(LCD_COLOR_BLACK);	
	/*��ǰ����һ����ɫԲ*/
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_TRANSPARENT);
	LCD_FillCircle(400,350,75);
	
	rt_thread_delay(500);   /* ��ʱ500��tick */	
	
	/*͸��Ч�� ���������*/

	/* ѡ��LCD������ */
	LCD_SelectLayer(0);	
	LCD_Clear(LCD_COLOR_BLACK);		
	/*���ñ����㲻͸��*/
	LCD_SetTransparency(1, 0);
	

	/*�ڱ�����һ����ɫԲ*/
	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
	LCD_FillCircle(450,350,75);
	
	/*�ڱ�����һ����ɫԲ*/
	LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
	LCD_FillCircle(350,350,75);
	
	rt_thread_delay(500);   /* ��ʱ500��tick */	
  
	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
	LCD_FillRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);

}


/********************************END OF FILE****************************/
