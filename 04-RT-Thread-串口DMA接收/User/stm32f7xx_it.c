/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_it.h"

#include "board.h"
#include "rtthread.h"


// �����жϷ�����
/* USER CODE BEGIN 1 */
void DEBUG_USART_IRQHandler(void)
{
  if((READ_REG(UartHandle.Instance->ISR)& USART_ISR_IDLE) != RESET)
  {
			UART_IdelCallback();
      __HAL_UART_CLEAR_IT(&UartHandle, UART_CLEAR_IDLEF);
  }
}

