/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./led/bsp_led.h"
#include "./tim/bsp_advance_tim.h"

/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

/* �ⲿ�����ź������ƿ� */
extern rt_sem_t test_sem;

void  ADVANCE_TIM_IRQHandler (void)
{
  /* �����ж� */
  rt_interrupt_enter();

  HAL_TIM_IRQHandler(&TIM_TimeBaseStructure);	 

  /* �뿪�ж� */
  rt_interrupt_leave();
  
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM_TimeBaseStructure))
    {
      rt_sem_release(test_sem);   //�ͷŶ�ֵ�ź��� 
    }
}







