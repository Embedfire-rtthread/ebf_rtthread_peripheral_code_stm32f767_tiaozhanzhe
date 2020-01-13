#ifndef __BOARD_H__
#define __BOARD_H__

/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/
/* STM32 固件库头文件 */
#include "stm32f7xx.h"
#include "main.h"
/* 开发板硬件bsp头文件 */
#include "./led/bsp_led.h"
#include "./delay/core_delay.h"   
#include "./usart/bsp_debug_usart.h"
#include "./i2c/bsp_i2c.h"
#include "./mpu6050/mpu6050.h"
//设置是否使用LCD进行显示，不需要的话把这个宏注释掉即可
#define USE_LCD_DISPLAY

#ifdef USE_LCD_DISPLAY
 #include "./lcd/bsp_lcd.h"
#endif

/*
*************************************************************************
*                               函数声明
*************************************************************************
*/
void rt_hw_board_init(void);
void SysTick_Handler(void);
	

#endif /* __BOARD_H__ */
