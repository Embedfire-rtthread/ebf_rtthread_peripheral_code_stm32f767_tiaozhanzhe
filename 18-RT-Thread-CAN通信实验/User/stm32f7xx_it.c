/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./can/bsp_can.h"
#include "rtthread.h"

void CAN_RX_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

	HAL_CAN_IRQHandler(&Can_Handle);

  /* �뿪�ж� */
  rt_interrupt_leave(); 
}

void CAN1_TX_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

	HAL_CAN_IRQHandler(&Can_Handle);

  /* �뿪�ж� */
  rt_interrupt_leave();
}

