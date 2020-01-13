/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   SDIO sd�����������������ļ�ϵͳ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F767 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "sdmmc/sdmmc_test.h"
#include "led/bsp_led.h"
#include "sdmmc/bsp_sdmmc_sd.h"
#include "./usart/bsp_debug_usart.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
uint8_t Status;
/* Private define ------------------------------------------------------------*/
#define BLOCK_SIZE            512 /* Block Size in Bytes */

#define NUMBER_OF_BLOCKS      50  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Buffer_Block_Tx[BLOCK_SIZE/4], Buffer_Block_Rx[BLOCK_SIZE/4];
uint32_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE/4], Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE/4];
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;
//SD_Error Status = SD_OK;

/* Private function prototypes -----------------------------------------------*/
static void SD_EraseTest(void);
static void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
static void Fill_Buffer(uint32_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
static TestStatus Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint32_t BufferLength);
static TestStatus eBuffercmp(uint32_t* pBuffer, uint32_t BufferLength);

/* Private functions ---------------------------------------------------------*/



void SD_Test(void)
{

	LED_BLUE;
	/*------------------------------ SD ��ʼ�� ------------------------------ */
	/* SD��ʹ��SDIO�жϼ�DMA�жϽ������ݣ��жϷ������λ��bsp_sdio_sd.c�ļ�β*/
	if(BSP_SD_Init() != MSD_OK)
	{    
		LED_RED;
		printf("SD����ʼ��ʧ�ܣ���ȷ��SD������ȷ���뿪���壬��һ��SD�����ԣ�\n");
	}
	else
	{
		printf("SD����ʼ���ɹ���\n");		 

		LED_BLUE;
		/*��������*/
		SD_EraseTest();

		LED_BLUE;
		/*single block ��д����*/
		SD_SingleBlockTest();

		LED_BLUE;
		/*muti block ��д����*/
		SD_MultiBlockTest();
	}
 
}


/**
  * @brief  Tests the SD card erase operation.
  * @param  None
  * @retval None
  */
void SD_EraseTest(void)
{  
	/*------------------- Block Erase ------------------------------------------*/
	if (Status == SD_OK)
	{
		/* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
		Status = BSP_SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
	}

	if (Status == SD_OK)
	{
		Status = BSP_SD_ReadBlocks_DMA(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
	}

	/* Check the correctness of erased blocks */
	if (Status == SD_OK)
	{
		EraseStatus = eBuffercmp(Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE/4);
	}

	if(EraseStatus == PASSED)
	{    
		LED_GREEN;
		printf("SD���������Գɹ���\n");
	}
	else
	{
		LED_RED;
		printf("SD����������ʧ�ܣ�\n");
		printf("��ܰ��ʾ������SD����֧�ֲ������ԣ���SD����ͨ�������single��д���ԣ�����ʾSD���ܹ�����ʹ�á�\n");
	}
}

/**
  * @brief  Tests the SD card Single Blocks operations.
  * @param  None
  * @retval None
  */
void SD_SingleBlockTest(void)
{  
	/*------------------- Block Read/Write --------------------------*/
	/* Fill the buffer to send */
	Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE/4, 0);

	if (Status == SD_OK)
	{
		/* Write block of 512 bytes on address 0 */
		Status = BSP_SD_WriteBlocks_DMA(Buffer_Block_Tx, 0x00, BLOCK_SIZE,1);
	}

	if (Status == SD_OK)
	{
		/* Read block of 512 bytes from address 0 */
		Status = BSP_SD_ReadBlocks_DMA(Buffer_Block_Rx, 0x00, BLOCK_SIZE,1);
	}

	/* Check the correctness of written data */
	if (Status == SD_OK)
	{
		TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE/4);
	}

	if(TransferStatus1 == PASSED)
	{
		LED_GREEN;
		printf("Single block ���Գɹ���\n");

	}
	else
	{
		LED_RED;
		printf("Single block ����ʧ�ܣ���ȷ��SD����ȷ���뿪���壬��һ��SD�����ԣ�\n");

	}
}

/**
  * @brief  Tests the SD card Multiple Blocks operations.
  * @param  None
  * @retval None
  */
void SD_MultiBlockTest(void)
{  
  /*--------------- Multiple Block Read/Write ---------------------*/
  /* Fill the buffer to send */
  Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE/4, 0x0);

  if (Status == SD_OK)
  {
    /* Write multiple block of many bytes on address 0 */
    Status = BSP_SD_WriteBlocks_DMA(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

  }

  if (Status == SD_OK)
  {
    /* Read block of many bytes from address 0 */
    Status = BSP_SD_ReadBlocks_DMA(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

  }

  /* Check the correctness of written data */
  if (Status == SD_OK)
  {
    TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE/4);
  }
  
  if(TransferStatus2 == PASSED)
  {
	LED_GREEN;
    printf("Multi block ���Գɹ���");

  }
  else
  {
	LED_RED;
    printf("Multi block ����ʧ�ܣ���ȷ��SD����ȷ���뿪���壬��һ��SD�����ԣ�");
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None
  */
void Fill_Buffer(uint32_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
  uint32_t index = 0;
  /* Put in global buffer same values */
  for (index = 0; index < BufferLength; index++)
  {
    pBuffer[index] = index + Offset;
  }
}

/**
  * @brief  Checks if a buffer has all its values are equal to zero.
  * @param  pBuffer: buffer to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer values are zero
  *         FAILED: At least one value from pBuffer buffer is different from zero.
  */
TestStatus eBuffercmp(uint32_t* pBuffer, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    /* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
    if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))
    {
      return FAILED;
    }

    pBuffer++;
  }
  return PASSED;
}

/*********************************************END OF FILE**********************/
