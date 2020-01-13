/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "main.h"
#include "./RTC/bsp_rtc.h"
/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>


void RTC_Alarm_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

  HAL_RTC_AlarmIRQHandler(&Rtc_Handle);

  /* �뿪�ж� */
  rt_interrupt_leave();
}
