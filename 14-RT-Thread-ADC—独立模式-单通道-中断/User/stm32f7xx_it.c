/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"

#include "rtthread.h"


extern ADC_HandleTypeDef    ADC_Handle;

void ADC_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();
  
  HAL_ADC_IRQHandler(&ADC_Handle);
  
  /* 离开中断 */
  rt_interrupt_leave();
  
}


