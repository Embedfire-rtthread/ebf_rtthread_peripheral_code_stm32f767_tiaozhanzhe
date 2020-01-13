/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./tim/bsp_advance_tim.h"
#include "./usart/bsp_debug_usart.h"

/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>


void ADVANCE_TIM_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

  HAL_TIM_IRQHandler(&TIM_PWMINPUT_Handle);

  /* 离开中断 */
  rt_interrupt_leave();

}

