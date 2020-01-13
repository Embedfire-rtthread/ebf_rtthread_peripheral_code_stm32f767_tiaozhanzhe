/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./led/bsp_led.h"
#include "./tim/bsp_advance_tim.h"

/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>

/* 外部定义信号量控制块 */
extern rt_sem_t test_sem;

void  ADVANCE_TIM_IRQHandler (void)
{
  /* 进入中断 */
  rt_interrupt_enter();

  HAL_TIM_IRQHandler(&TIM_TimeBaseStructure);	 

  /* 离开中断 */
  rt_interrupt_leave();
  
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM_TimeBaseStructure))
    {
      rt_sem_release(test_sem);   //释放二值信号量 
    }
}







