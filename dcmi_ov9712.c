/**
  ******************************************************************************
  * @file    DCMI/Camera/dcmi_ov9712.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   This file includes the driver for OV9712 Camera module mounted on 
  *          STM324xG-EVAL board RevA and RevB.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "camera_api.h"
#include "dcmi_ov9712.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup DCMI_Camera
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  TIMEOUT  2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* QQVGA 160x120 */
static unsigned char OV9712_QQVGA[][2]=
{
  0x12, 0x80,
  0x00, 0x00,
  0x01, 0x40,
  0x02, 0x40,
  0x03, 0x02,  //
  0x04, 0x00,  //REG04
  0x05, 0x00,  //GREEN
  0x06, 0x00,  //BRL
  0x07, 0x00,  //GL
  0x08, 0x00,  //REG08
  0x09, 0x00,  //COM2  
  0x0a, 0x97,
  0x0b, 0x11,
  0x0c, 0x00,
  0x0d, 0x01,
  0x0e, 0x40,
  0x0f, 0x00,
  0x11, 0x00,
  0x12, 0x40,
  0x13, 0x85,
  0x14, 0x10,
  0x15, 0x00,
  0x16, 0x01,
  0x17, 0x26,
  0x18, 0xa2,
  0x19, 0x01,
  0x1a, 0xc8,
  0x1b, 0x81,
  0x1c, 0x7f,
  0x1d, 0xa2,
  0x1e, 0x00,
  0x1f, 0x00,
  0x20, 0x00,
  0x21, 0x03,
  0x22, 0x00,
  0x23, 0x00,
  0x24, 0x60,
  0x25, 0x55,
  0x26, 0x92,
  0x27, 0x00,
  0x28, 0x00,
  0x29, 0x00,
  0x2a, 0x9b,
  0x2b, 0x06,
  0x2c, 0x50,
  0x2d, 0x00,
  0x2e, 0x00,
  0x2f, 0x00,
  0x30, 0x08,
  0x31, 0x20,
  0x32, 0x01,  //Q vs QQ 0x32, 0xa4
  0x37, 0x02,
  0x38, 0x10,
  0x3c, 0x00,
  0x3d, 0x3c,
  0x3e, 0x03,		 //Q vs QQ  0x3e, 0x0e,
  0x41, 0x82,
  0x42, 0x14,//0xd9,		//0xc0,
  0x43, 0xc0,
  0x44, 0x00,
  0x45, 0x00,
  0x46, 0x00,
  0x47, 0x00,
  0x48, 0x00,
  0x49, 0x00,
  0x4a, 0xd0,
  0x4e, 0x55,
  0x4f, 0x55,
  0x50, 0x55,
  0x51, 0x55,
  0x55, 0xff,
  0x56, 0x1f,
  0x57, 0x00,
  0x58, 0xc8,
  0x59, 0xa0,
  0x5c, 0x59,
  0x5d, 0xc4,
  0x72, 0x60,		//Q vs QQ 0x72, 0x22
  0x73, 0x49,		//Q vs QQ  0x73, 0x02
  0x74, 0xe0,
  0x75, 0xe0,
  0x76, 0xc0,
  0x77, 0xc0,
  0x78, 0xff,
  0x79, 0xff,
  0x96, 0xf9,
  0x97, 0x80,
  0x98, 0x00,
  0x99, 0x00,
  0x9a, 0x00,
  0x9b, 0x04,
  0x9c, 0x00,
  0x9d, 0xff,
  0x9e, 0x00,
  0x9f, 0x80,
  0xa0, 0xf1,
  0xa1, 0x0d,
  0xa2, 0x00, //0x9d
  0xa3, 0x80,
  0xa4, 0x90,
  0xa5, 0x12,
  0xa6, 0x22,
  0xa7, 0xc2,
  0xa8, 0x87,
  0xa9, 0x80,
  0xaa, 0x90,
  0xab, 0x12,
  0xac, 0x22,
  0xad, 0xc2,
  0xae, 0x87,
  0xaf, 0x80,
  0xb0, 0x90,
  0xb1, 0x12,
  0xb2, 0x22,
  0xb3, 0xc2,
  0xb4, 0x87,
  0xb5, 0x00,
  0xb6, 0x07,
  0xb7, 0x00,
  0xb8, 0x04,
  0xb9, 0x08,
  0xba, 0x00,
  0xbb, 0x20,
  0xbc, 0x68,
  0xbd, 0xa0,
  0xbe, 0xc8,
  0xbf, 0x00,
  0xc0, 0x00,
  0xc1, 0x00,
  0xc2, 0x80,
  0xc3, 0x20,
  0xc4, 0xab,
  0xc5, 0xb6,
  0xc6, 0x80,
  0xc7, 0x9d,
  0xc8, 0x00,		 //Q vs QQ  0xc7, 0x82,
  0xc9, 0x80,
  0xca, 0x20,
  0xcb, 0xa6,
  0xcc, 0x40,
  0xcd, 0x00,
  0xce, 0x01,
  0xcf, 0x00,
  0xd0, 0xff,
  0xd1, 0xff,
  0xd2, 0xff,
  0xd3, 0x00,
  0xd4, 0x03,
  0xd6, 0x0c,
  //0x12, 0x63,
  //0x40, 0x10,
  //0x15, 0x08,
  0xcb, 0x32,
  0xc3, 0x21,
};

/* QVGA 360x240 */
static unsigned char OV9712_QVGA[][2]=
{
  0x12, 0x80,
  0x00, 0x00,
  0x01, 0x40,
  0x02, 0x40,
  0x03, 0x02,  //
  0x04, 0x00,  //REG04
  0x05, 0x00,  //GREEN
  0x06, 0x00,  //BRL
  0x07, 0x00,  //GL
  0x08, 0x00,  //REG08
  0x09, 0x00,  //COM2  
  0x0a, 0x97,
  0x0b, 0x11,
  0x0c, 0x00,
  0x0d, 0x01,
  0x0e, 0x40,
  0x0f, 0x00,
  0x11, 0x00,
  0x12, 0x40,
  0x13, 0x85,
  0x14, 0x10,
  0x15, 0x00,
  0x16, 0x01,
  0x17, 0x26,
  0x18, 0xa2,
  0x19, 0x01,
  0x1a, 0xc8,
  0x1b, 0x81,
  0x1c, 0x7f,
  0x1d, 0xa2,
  0x1e, 0x00,
  0x1f, 0x00,
  0x20, 0x00,
  0x21, 0x03,
  0x22, 0x00,
  0x23, 0x00,
  0x24, 0x60,
  0x25, 0x55,
  0x26, 0x92,
  0x27, 0x00,
  0x28, 0x00,
  0x29, 0x00,
  0x2a, 0x9b,
  0x2b, 0x06,
  0x2c, 0x50,
  0x2d, 0x00,
  0x2e, 0x00,
  0x2f, 0x00,
  0x30, 0x08,
  0x31, 0x20,
  0x32, 0x01,  //Q vs QQ 0x32, 0xa4
  0x37, 0x02,
  0x38, 0x10,
  0x3c, 0x00,
  0x3d, 0x3c,
  0x3e, 0x03,		 //Q vs QQ  0x3e, 0x0e,
  0x41, 0x82,
  0x42, 0x14,//0xd9,		//0xc0,
  0x43, 0xc0,
  0x44, 0x00,
  0x45, 0x00,
  0x46, 0x00,
  0x47, 0x00,
  0x48, 0x00,
  0x49, 0x00,
  0x4a, 0xd0,
  0x4e, 0x55,
  0x4f, 0x55,
  0x50, 0x55,
  0x51, 0x55,
  0x55, 0xff,
  0x56, 0x1f,
  0x57, 0x00,
  0x58, 0xc8,
  0x59, 0xa0,
  0x5c, 0x59,
  0x5d, 0xc4,
  0x72, 0x60,		//Q vs QQ 0x72, 0x22
  0x73, 0x49,		//Q vs QQ  0x73, 0x02
  0x74, 0xe0,
  0x75, 0xe0,
  0x76, 0xc0,
  0x77, 0xc0,
  0x78, 0xff,
  0x79, 0xff,
  0x96, 0xf9,
  0x97, 0x80,
  0x98, 0x00,
  0x99, 0x00,
  0x9a, 0x00,
  0x9b, 0x04,
  0x9c, 0x00,
  0x9d, 0xff,
  0x9e, 0x00,
  0x9f, 0x80,
  0xa0, 0xf1,
  0xa1, 0x0d,
  0xa2, 0x00, //0x9d
  0xa3, 0x80,
  0xa4, 0x90,
  0xa5, 0x12,
  0xa6, 0x22,
  0xa7, 0xc2,
  0xa8, 0x87,
  0xa9, 0x80,
  0xaa, 0x90,
  0xab, 0x12,
  0xac, 0x22,
  0xad, 0xc2,
  0xae, 0x87,
  0xaf, 0x80,
  0xb0, 0x90,
  0xb1, 0x12,
  0xb2, 0x22,
  0xb3, 0xc2,
  0xb4, 0x87,
  0xb5, 0x00,
  0xb6, 0x07,
  0xb7, 0x00,
  0xb8, 0x04,
  0xb9, 0x08,
  0xba, 0x00,
  0xbb, 0x20,
  0xbc, 0x68,
  0xbd, 0xa0,
  0xbe, 0xc8,
  0xbf, 0x00,
  0xc0, 0x00,
  0xc1, 0x00,
  0xc2, 0x80,
  0xc3, 0x20,
  0xc4, 0xab,
  0xc5, 0xb6,
  0xc6, 0x80,
  0xc7, 0x9d,
  0xc8, 0x00,		 //Q vs QQ  0xc7, 0x82,
  0xc9, 0x80,
  0xca, 0x20,
  0xcb, 0xa6,
  0xcc, 0x40,
  0xcd, 0x00,
  0xce, 0x01,
  0xcf, 0x00,
  0xd0, 0xff,
  0xd1, 0xff,
  0xd2, 0xff,
  0xd3, 0x00,
  0xd4, 0x03,
  0xd6, 0x0c,
  //0x12, 0x63,
  //0x40, 0x10,
  //0x15, 0x08,
  0xcb, 0x32,
  0xc3, 0x21,
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the hardware resources (I2C and GPIO) used to configure 
  *         the OV9712 camera.
  * @param  None
  * @retval None
  */
void OV9712_HW_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  I2C_InitStruct;

  /*** Configures the DCMI GPIOs to interface with the OV9712 camera module ***/
  /* Enable DCMI GPIOs clocks */
  /* Enable DCMI GPIOs clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC |
                         RCC_AHB1Periph_GPIOE, ENABLE); 

  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* Connect DCMI pins to AF13 ************************************************/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);	//HSYNC
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);	//PIXCLK

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);	//DCMI_D5
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);	//VSYNC

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);	//DCMI_D0
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);	//DCMI_D1

  GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI);	//DCMI_D2
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI);	//DCMI_D3
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);	//DCMI_D4
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);	//DCMI_D6
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);	//DCMI_D7
  
  /* DCMI GPIO configuration **************************************************/
  /* HSYNC(PA4), PIXCLK(PA6) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* DCMI_D5(PB6), VSYNC(PB7) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* DCMI_D0(PC6), DCMI_D1(PC7) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;  
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* DCMI_D2(PE0), DCMI_D3(PE1), DCMI_D4(PE4), DCMI_D6(PE5), DCMI_D7(PE6),*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;  
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /****** Configures the I2C1 used for OV9712 camera module configuration *****/
 /* I2C1 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

  /* Connect I2C1 pins to AF4 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
  
  /* Configure I2C1 GPIOs */  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure I2C1 */
  /* I2C DeInit */
  I2C_DeInit(I2C1);
    
  /* Enable the I2C peripheral */
  I2C_Cmd(I2C1, ENABLE);
 
  /* Set the I2C structure parameters */
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct.I2C_OwnAddress1 = 0xFE;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStruct.I2C_ClockSpeed = 30000;
  
  /* Initialize the I2C peripheral w/ selected parameters */
  I2C_Init(I2C1, &I2C_InitStruct);
}

/**
  * @brief  Resets the OV9712 camera.
  * @param  None
  * @retval None
  */
void OV9712_Reset(void)
{
  OV9712_WriteReg(OV9712_COM7, 0x80);
}

/**
  * @brief  Reads the OV9712 Manufacturer identifier.
  * @param  OV9712ID: pointer to the OV9712 Manufacturer identifier.
  * @retval None
  */
void OV9712_ReadID(OV9712_IDTypeDef* OV9712ID)
{
  OV9712ID->Manufacturer_ID1 = OV9712_ReadReg(OV9712_MIDH);
  OV9712ID->Manufacturer_ID2 = OV9712_ReadReg(OV9712_MIDL);
  //OV9712ID->Version = OV9712_ReadReg(OV9712_VER);
  OV9712ID->PIDH = OV9712_ReadReg(OV9712_PIDH);
  OV9712ID->PIDL = OV9712_ReadReg(OV9712_PIDL);
}

/**
  * @brief  Configures the DCMI/DMA to capture image from the OV9712 camera.
  * @param  ImageFormat: Image format BMP or JPEG
  * @param  BMPImageSize: BMP Image size  
  * @retval None
  */
void OV9712_Init(ImageFormat_TypeDef ImageFormat)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /*** Configures the DCMI to interface with the OV9712 camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA2 Stream1 Configuration */
  DMA_DeInit(DMA2_Stream1);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = 0x20000000;//FSMC_LCD_ADDRESS;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = (320 * 240 * 2 / 4) / 16;//1
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   

  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   

   switch(ImageFormat)
  {
    case BMP_QQVGA:
    {
      /* DCMI configuration */
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
	  DMA_ITConfig( DMA2_Stream1, DMA_IT_TC, ENABLE);
      break;
    }
    case BMP_QVGA:
    {
      /* DCMI configuration */ 
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
	  DMA_ITConfig( DMA2_Stream1, DMA_IT_TC, ENABLE);
      break;
    }
    default:
    {
      /* DCMI configuration */ 
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      break;
    }
  }    
  DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
  DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
  DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
  DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
}

/**
  * @brief  Configures the OV9712 camera in QQVGA mode.
  * @param  None
  * @retval None
  */
void OV9712_QQVGAConfig(void)
{
  uint32_t i;

  OV9712_Reset();
  Delay(200);

  /* Initialize OV9712 */
  for(i=0; i<(sizeof(OV9712_QQVGA)/2); i++)
  {
    OV9712_WriteReg(OV9712_QQVGA[i][0], OV9712_QQVGA[i][1]);
    Delay(2);
  }
}

/**
  * @brief  SConfigures the OV9712 camera in QVGA mode.
  * @param  None
  * @retval None
  */
void OV9712_QVGAConfig(void)
{
  uint32_t i;

  OV9712_Reset();
  Delay(200);

  /* Initialize OV9712 */
  for(i=0; i<(sizeof(OV9712_QVGA)/2); i++)
  {
    OV9712_WriteReg(OV9712_QVGA[i][0], OV9712_QVGA[i][1]);
    Delay(2);
  }
}

/**
  * @brief  Configures the OV9712 camera brightness.
  * @param  Brightness: Brightness value, where Brightness can be: 
  *         positively (0x01 ~ 0x7F) and negatively (0x80 ~ 0xFF)
  * @retval None
  */
void OV9712_BrightnessConfig(uint8_t Brightness)
{
  //OV9712_WriteReg(OV9712_BRTN, Brightness);
}

/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Addr: OV9712 register address
  * @param  Data: data to be written to the specific register
  * @retval 0x00 if write operation is OK
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
uint8_t OV9712_WriteReg(uint16_t Addr, uint8_t Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  
  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on I2C1 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9712_DEVICE_WRITE_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
 
  /* Send I2C1 location address LSB */
  I2C_SendData(I2C1, (uint8_t)(Addr));

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
  
  /* Send Data */
  I2C_SendData(I2C1, Data);

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
 
  /* Send I2C1 STOP Condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
  
  /* If operation is OK, return 0 */
  return 0;
}

/**
  * @brief  Reads a byte from a specific Camera register
  * @param  Addr: OV9712 register address.
  * @retval data read from the specific register or 0xFF if timeout condition
  *         occured.
  */
uint8_t OV9712_ReadReg(uint16_t Addr)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  uint8_t Data = 0;

  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on I2C1 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
  
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9712_DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }

  /* Send I2C1 location address LSB */
  I2C_SendData(I2C1, (uint8_t)(Addr));

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  I2C1->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9712_DEVICE_READ_ADDRESS, I2C_Direction_Receiver);

  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
 
  /* Prepare an NACK for the next data received */
  I2C_AcknowledgeConfig(I2C1, DISABLE);

  /* Test on I2C1 EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }

  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(I2C1, ENABLE);

  /* Receive the Data */
  Data = I2C_ReceiveData(I2C1);

  /* return the read data */
  return Data;
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
