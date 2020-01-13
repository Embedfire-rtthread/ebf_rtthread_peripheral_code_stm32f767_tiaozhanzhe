/* 该文件统一用于存放中断服务函数 */
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_it.h"

#include "board.h"
#include "rtthread.h"


// 串口中断服务函数
/* USER CODE BEGIN 1 */
void DEBUG_USART_IRQHandler(void)
{
  if((READ_REG(UartHandle.Instance->ISR)& USART_ISR_IDLE) != RESET)
  {
			UART_IdelCallback();
      __HAL_UART_CLEAR_IT(&UartHandle, UART_CLEAR_IDLEF);
  }
}

