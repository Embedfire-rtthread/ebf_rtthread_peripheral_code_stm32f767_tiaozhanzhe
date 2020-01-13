/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

extern ADC_HandleTypeDef    ADC_Handle;

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void DMA2_Stream0_IRQHandler(void)
{
    /* �����ж� */
  rt_interrupt_enter();

  HAL_DMA_IRQHandler(ADC_Handle.DMA_Handle);

  /* �뿪�ж� */
  rt_interrupt_leave();
}

