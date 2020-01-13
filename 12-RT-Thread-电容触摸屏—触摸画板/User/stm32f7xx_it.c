/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./touch/bsp_i2c_touch.h"
#include "./led/bsp_led.h"

/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>

extern void GTP_TouchProcess(void);



void GTP_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

	if(__HAL_GPIO_EXTI_GET_IT(GTP_INT_GPIO_PIN) != RESET) //确保是否产生了EXTI Line中断
	{
		LED2_TOGGLE;
        GTP_TouchProcess();    
        __HAL_GPIO_EXTI_CLEAR_IT(GTP_INT_GPIO_PIN);     //清除中断标志位
	}  

  /* 离开中断 */
  rt_interrupt_leave();
}


