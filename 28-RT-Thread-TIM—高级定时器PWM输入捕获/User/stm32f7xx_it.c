/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./tim/bsp_advance_tim.h"
#include "./usart/bsp_debug_usart.h"

/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>


void ADVANCE_TIM_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

  HAL_TIM_IRQHandler(&TIM_PWMINPUT_Handle);

  /* �뿪�ж� */
  rt_interrupt_leave();

}

