#ifndef __BOARD_H__
#define __BOARD_H__

/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/
/* STM32 �̼���ͷ�ļ� */
#include "stm32f7xx.h"
#include "main.h"
/* ������Ӳ��bspͷ�ļ� */
#include "./led/bsp_led.h"
#include "./delay/core_delay.h"   
#include "./usart/bsp_debug_usart.h"
#include "./i2c/bsp_i2c.h"
#include "./mpu6050/mpu6050.h"
//�����Ƿ�ʹ��LCD������ʾ������Ҫ�Ļ��������ע�͵�����
#define USE_LCD_DISPLAY

#ifdef USE_LCD_DISPLAY
 #include "./lcd/bsp_lcd.h"
#endif

/*
*************************************************************************
*                               ��������
*************************************************************************
*/
void rt_hw_board_init(void);
void SysTick_Handler(void);
	

#endif /* __BOARD_H__ */
