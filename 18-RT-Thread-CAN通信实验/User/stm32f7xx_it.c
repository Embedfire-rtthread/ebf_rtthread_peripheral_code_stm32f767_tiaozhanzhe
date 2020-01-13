/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./can/bsp_can.h"
#include "rtthread.h"

void CAN_RX_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

	HAL_CAN_IRQHandler(&Can_Handle);

  /* 离开中断 */
  rt_interrupt_leave(); 
}

void CAN1_TX_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

	HAL_CAN_IRQHandler(&Can_Handle);

  /* 离开中断 */
  rt_interrupt_leave();
}

