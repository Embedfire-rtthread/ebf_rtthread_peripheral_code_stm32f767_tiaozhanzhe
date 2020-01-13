/**
  ******************************************************************************
  * @file    bsp_touchpad.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ݰ���Ӧ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F767 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "./TouchPad/bsp_touchpad.h"
#include "./usart/bsp_debug_usart.h"
#include "stm32f7xx_hal.h"
//#include "./delay/core_delay.h"   
/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

//��ʱ��������ֵ
#define TPAD_ARR_MAX_VAL 	0XFFFF	

//����û����ʱ��ʱ������ֵ
__IO uint16_t tpad_default_val=0;

/***********************************
 *
 * ��ʱ�����벶������
 *
 ***********************************/	
 TIM_HandleTypeDef TIM_Handle;
static void TIMx_CHx_Cap_Init(uint32_t arr,uint16_t psc)
{
    GPIO_InitTypeDef  GPIO_InitStructure; 
    TIM_IC_InitTypeDef sConfigIC;
    //ʹ��TIMʱ��
    TPAD_TIM_CLK_ENABLE(); 	
    //ʹ��ͨ������ʱ��	
    TPAD_TIM_GPIO_CLK_ENABLE(); 	
    //�˿�����
    GPIO_InitStructure.Pin = TPAD_TIM_CH_PIN;	
    //���ù���
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Alternate = TPAD_TIM_AF;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    //���������� 
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);
    //��ʼ��TIM
    //�趨�������Զ���װֵ
    TIM_Handle.Instance = TPAD_TIMx;
    TIM_Handle.Init.Prescaler = psc;
    TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM_Handle.Init.RepetitionCounter = 0;
    TIM_Handle.Init.Period = arr;
    TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_IC_Init(&TIM_Handle);
	//�����ش���
    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	// ���벶��ѡ��
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	//���������Ƶ,����Ƶ
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	//���������˲��� ���˲�
    sConfigIC.ICFilter = 0;
	//��ʼ������ͨ��
    HAL_TIM_IC_ConfigChannel(&TIM_Handle, &sConfigIC, TPAD_TIM_Channel_X);
    //����TIM 
    HAL_TIM_IC_Start(&TIM_Handle, TPAD_TIM_Channel_X);
}

/****************************************
 *
 * Ϊ���ݰ����ŵ�
 * �����ʱ����־������
 *
 *****************************************/
static void TPAD_Reset(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure; 
    //��������Ϊ��ͨ�������
    GPIO_InitStructure.Pin = TPAD_TIM_CH_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;	
    GPIO_InitStructure.Pull = GPIO_PULLDOWN; 
    HAL_GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);

    //����͵�ƽ,�ŵ�
    HAL_GPIO_WritePin ( TPAD_TIM_CH_PORT, TPAD_TIM_CH_PIN ,GPIO_PIN_RESET);						 
    //����һС��ʱ��͵�ƽ����֤�ŵ���ȫ
    rt_thread_delay(5);

    //������±�־
    __HAL_TIM_CLEAR_FLAG(&TIM_Handle,TIM_FLAG_CC1);
    __HAL_TIM_CLEAR_FLAG(&TIM_Handle,TIM_FLAG_UPDATE);
    //��������0
    __HAL_TIM_SET_COUNTER(&TIM_Handle,0);
    //��������Ϊ���ù��ܣ����ϡ�����
    GPIO_InitStructure.Pin = TPAD_TIM_CH_PIN; 
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Alternate = TPAD_TIM_AF;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH; 
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(TPAD_TIM_CH_PORT,&GPIO_InitStructure);
}

/****************************************************
 *
 * �õ���ʱ������ֵ
 * �����ʱ,��ֱ�ӷ��ض�ʱ���ļ���ֵ.
 *
 *****************************************************/
static uint16_t TPAD_Get_Val(void)
{		
  /* �ȷŵ���ȫ������λ������ */	
	TPAD_Reset();
	//�ȴ�����������
	while(__HAL_TIM_GET_FLAG(&TIM_Handle,TIM_FLAG_CC1) == RESET )
	{
		//��ʱ��,ֱ�ӷ���CNT��ֵ
		if(__HAL_TIM_GET_COUNTER( &TIM_Handle)>TPAD_ARR_MAX_VAL-500)
			return __HAL_TIM_GET_COUNTER( &TIM_Handle);
	};
	/* ���������غ����TIMx_CCRx�Ĵ���ֵ */
	return HAL_TIM_ReadCapturedValue(&TIM_Handle, TIM_CHANNEL_1);  
} 	

/****************************************************
 *
 * ��ȡn��,ȡ���ֵ
 * n��������ȡ�Ĵ���
 * ����ֵ��n�ζ������������������ֵ
 * 
 *****************************************************/
static uint16_t TPAD_Get_MaxVal(uint8_t n)
{
	uint16_t temp=0;
	uint16_t res=0;
	while(n--)
	{
		temp=TPAD_Get_Val();//�õ�һ��ֵ
		if(temp>res)res=temp;
	};
	return res;
}  

/********************************************************
*
* ��ʼ����������
* ��ÿ��ص�ʱ����������ȡֵ.
* ����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ��
*
*********************************************************/
uint8_t TPAD_Init(void)
{
	uint16_t buf[10];
	uint32_t temp=0;
	uint8_t j,i;
	
	//�趨��ʱ��Ԥ��Ƶ��Ŀ��ʱ��Ϊ��9MHz(216Mhz/24)
	TIMx_CHx_Cap_Init(TPAD_ARR_MAX_VAL,24-1);
	for(i=0;i<10;i++)//������ȡ10��
	{				 
		buf[i]=TPAD_Get_Val();
		rt_thread_delay(10);	    
	}				    
	for(i=0;i<9;i++)//����
	{
		for(j=i+1;j<10;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	temp=0;
	//ȡ�м��6�����ݽ���ƽ��
	for(i=2;i<8;i++)
	{
	  temp+=buf[i];
	}
	
	tpad_default_val=temp/6;	
	/* printf��ӡ��������ʹ�ã�����ȷ����ֵTPAD_GATE_VAL����Ӧ�ù�����Ӧע�͵� */
	printf("tpad_default_val:%d\r\n",tpad_default_val);	
	
	//��ʼ����������TPAD_ARR_MAX_VAL/2����ֵ,������!
	if(tpad_default_val>TPAD_ARR_MAX_VAL/2)
	{
		return 1;
	}
	
	return 0;		     	    					   
}
 

/*******************************************************************************
*
* ɨ�败������
* mode:0,��֧����������(����һ�α����ɿ����ܰ���һ��);1,֧����������(����һֱ����)
* ����ֵ:0,û�а���;1,�а���;			
*
*******************************************************************************/
//��ֵ������ʱ��������(tpad_default_val + TPAD_GATE_VAL),����Ϊ����Ч����.
#define TPAD_GATE_VAL 	100	

uint8_t TPAD_Scan(uint8_t mode)
{
	//0,���Կ�ʼ���;>0,�����ܿ�ʼ���	
	static uint8_t keyen=0;
	//ɨ����
	uint8_t res=0;
	//Ĭ�ϲ�������Ϊ3��
	uint8_t sample=3;	
  //����ֵ	
	uint16_t rval;
	
	if(mode)
	{
		//֧��������ʱ�����ò�������Ϊ6��
		sample=6;	
		//֧������	
		keyen=0;	  
	}	
	/* ��ȡ��ǰ����ֵ(���� sample ��ɨ������ֵ) */
	rval=TPAD_Get_MaxVal(sample); 	
	/* printf��ӡ��������ʹ�ã�����ȷ����ֵTPAD_GATE_VAL����Ӧ�ù�����Ӧע�͵� */
//	printf("scan_rval=%d\n",rval);
	
	//����tpad_default_val+TPAD_GATE_VAL,��С��10��tpad_default_val,����Ч
	if(rval>(tpad_default_val+TPAD_GATE_VAL)&&rval<(10*tpad_default_val))
	{			
    //keyen==0,��Ч 		
		if(keyen==0)
		{
			res=1;		 
		}			
		keyen=3;				//����Ҫ�ٹ�3��֮����ܰ�����Ч   
	}
	
	if(keyen)
	{
		keyen--;		
	}		
	return res;
}	 
/*********************************************END OF FILE**********************/
