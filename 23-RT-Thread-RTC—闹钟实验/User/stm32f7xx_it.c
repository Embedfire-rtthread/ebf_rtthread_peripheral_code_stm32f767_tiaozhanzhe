/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./RTC/bsp_rtc.h"
/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>


void RTC_Alarm_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

  HAL_RTC_AlarmIRQHandler(&Rtc_Handle);

  /* 离开中断 */
  rt_interrupt_leave();
}
