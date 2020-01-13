/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./sdmmc/bsp_sdmmc_sd.h"

/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>


void SDMMC1_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();
  
  BSP_SD_IRQHandler();

  /* �뿪�ж� */
  rt_interrupt_leave();

}


void DMA2_Stream3_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

  BSP_SD_DMA_Rx_IRQHandler();

  /* �뿪�ж� */
  rt_interrupt_leave();
}


void DMA2_Stream6_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

	BSP_SD_DMA_Tx_IRQHandler();

  /* �뿪�ж� */
  rt_interrupt_leave();
}



