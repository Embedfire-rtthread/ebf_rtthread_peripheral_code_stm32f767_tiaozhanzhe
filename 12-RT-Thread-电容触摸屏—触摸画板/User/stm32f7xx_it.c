/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./touch/bsp_i2c_touch.h"
#include "./led/bsp_led.h"

/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

extern void GTP_TouchProcess(void);



void GTP_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

	if(__HAL_GPIO_EXTI_GET_IT(GTP_INT_GPIO_PIN) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		LED2_TOGGLE;
        GTP_TouchProcess();    
        __HAL_GPIO_EXTI_CLEAR_IT(GTP_INT_GPIO_PIN);     //����жϱ�־λ
	}  

  /* �뿪�ж� */
  rt_interrupt_leave();
}


