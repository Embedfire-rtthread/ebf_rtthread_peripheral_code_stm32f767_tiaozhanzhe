/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./sdmmc/bsp_sdmmc_sd.h"

/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>


void SDMMC1_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();
  
  BSP_SD_IRQHandler();

  /* 离开中断 */
  rt_interrupt_leave();

}


void DMA2_Stream3_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

  BSP_SD_DMA_Rx_IRQHandler();

  /* 离开中断 */
  rt_interrupt_leave();
}


void DMA2_Stream6_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

	BSP_SD_DMA_Tx_IRQHandler();

  /* 离开中断 */
  rt_interrupt_leave();
}



