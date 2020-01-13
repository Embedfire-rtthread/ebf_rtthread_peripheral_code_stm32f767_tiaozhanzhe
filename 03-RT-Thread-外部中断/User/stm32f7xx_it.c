/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_it.h"

#include "board.h"
#include "rtthread.h"

/* �ⲿ������Ϣ���п��ƿ� */
extern rt_mq_t test_mq;

uint32_t send_data1 = 1;
uint32_t send_data2 = 2;

/*********************************************************************************
  * @ ������  �� KEY1_IRQHandler
  * @ ����˵���� �жϷ�����
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  ********************************************************************************/
void KEY1_IRQHandler(void)
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(__HAL_GPIO_EXTI_GET_IT(KEY1_INT_GPIO_PIN) != RESET) 
	{
    /* ������д�루���ͣ��������У��ȴ�ʱ��Ϊ 0  */
    rt_mq_send(	test_mq,	/* д�루���ͣ����е�ID(���) */
                &send_data1,			/* д�루���ͣ������� */
                sizeof(send_data1));			/* ���ݵĳ��� */
    //����жϱ�־λ
		__HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);     
	}  
}
/*********************************************************************************
  * @ ������  �� KEY2_IRQHandler
  * @ ����˵���� �жϷ�����
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  ********************************************************************************/
void KEY2_IRQHandler(void)
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(__HAL_GPIO_EXTI_GET_IT(KEY2_INT_GPIO_PIN) != RESET) 
	{
    /* ������д�루���ͣ��������У��ȴ�ʱ��Ϊ 0  */
    rt_mq_send(	test_mq,	/* д�루���ͣ����е�ID(���) */
                &send_data2,			/* д�루���ͣ������� */
                sizeof(send_data2));			/* ���ݵĳ��� */
    //����жϱ�־λ
		__HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);     
	}  
}

