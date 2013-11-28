/**
  ******************************************************************************
  * @file    DCMI/OV9712_Camera/dcmi_ov9712.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Header for dcmi_ov9712.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DCMI_OV9712_H
#define __DCMI_OV9712_H

/* Includes ------------------------------------------------------------------*/
#include "camera_api.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8_t Manufacturer_ID1;
  uint8_t Manufacturer_ID2;
  //uint8_t Version;
  uint8_t PIDH;
  uint8_t PIDL;
}OV9712_IDTypeDef;

/* Exported constants --------------------------------------------------------*/

/* Use this define to set the maximum delay timeout for the I2C DCMI_OV9712_SingleRandomWrite()
   and DCMI_OV9712_SingleRandomRead() operations. Exeeding this timeout delay,
   the read/write functions will be aborted and return error code (0xFF).
   The period of the delay will depend on the system operating frequency. The following
   value has been set for system running at 168 MHz. */
#define DCMI_TIMEOUT_MAX  10000

#define OV9712_DEVICE_WRITE_ADDRESS    0x60
#define OV9712_DEVICE_READ_ADDRESS     0x61
//#define OV9712_DEVICE_WRITE_ADDRESS    0x42
//#define OV9712_DEVICE_READ_ADDRESS     0x43

/* OV9712 Registers definition */
#define OV9712_GAIN       0x00
#define OV9712_BLUE       0x01
#define OV9712_RED        0x02
#define OV9712_REG03      0x03
#define OV9712_REG04      0x04
#define OV9712_GREEN      0x05
#define OV9712_BRL        0x06
#define OV9712_GL         0x07
#define OV9712_REG08      0x08
#define OV9712_COM2       0x09
#define OV9712_PIDH       0x0A
#define OV9712_PIDL       0x0B
#define OV9712_COM3       0x0C
#define OV9712_COM4       0x0D
#define OV9712_COM5       0x0E
#define OV9712_COM6       0x0F
#define OV9712_AEC        0x10
#define OV9712_CLK        0x11
#define OV9712_COM7       0x12
#define OV9712_COM8       0x13
#define OV9712_COM9       0x14
#define OV9712_COM10      0x15
#define OV9712_AECH       0x16
#define OV9712_HSTART     0x17
#define OV9712_AHsize     0x18
#define OV9712_VSTART     0x19
#define OV9712_AVsize     0x1A
#define OV9712_PSHFT      0x1B
#define OV9712_MIDH       0x1C
#define OV9712_MIDL       0x1D
#define OV9712_COM11      0x1E
#define OV9712_REG1F      0x1F
#define OV9712_COM12      0x20
#define OV9712_COM13      0x21
#define OV9712_COM14      0x22
#define OV9712_COM15      0x23
#define OV9712_WPT        0x24
#define OV9712_BPT        0x25
#define OV9712_VPT        0x26
#define OV9712_COM16      0x27
#define OV9712_COM17      0x28
#define OV9712_COM18      0x29
#define OV9712_REG2A      0x2A
#define OV9712_REG2B      0x2B
#define OV9712_COM19      0x2C
#define OV9712_REG2D      0x2D
#define OV9712_YAVG       0x2E
#define OV9712_REG30      0x2F
#define OV9712_REG32      0x30
#define OV9712_HSYEN      0x31
#define OV9712_HREF       0x32
#define OV9712_COM24      0x37
#define OV9712_COM25      0x38
#define OV9712_COM28      0x3C
#define OV9712_RENDL      0x3D
#define OV9712_RENDH      0x3E
#define OV9712_REG41      0x41
#define OV9712_REG42      0x42
#define OV9712_REG43      0x43
#define OV9712_ROFFS      0x44
#define OV9712_BOFFS      0x45
#define OV9712_GrOFFS     0x46
#define OV9712_GbOFFS     0x47
#define OV9712_HOFFS      0x48
#define OV9712_REG49      0x49
#define OV9712_REG4A      0x4A
#define OV9712_REG4E      0x4E
#define OV9712_REG4F      0x4F
#define OV9712_REG50      0x50
#define OV9712_REG51      0x51
#define OV9712_REG55      0x55
#define OV9712_REG56      0x56
#define OV9712_REG57      0x57
#define OV9712_REG58      0x58
#define OV9712_REG59      0x59
#define OV9712_REG5C      0x5C
#define OV9712_REG5D      0x5D
#define OV9712_REG72      0x72
#define OV9712_REG73      0x73
#define OV9712_REG74      0x74
#define OV9712_REG75      0x75
#define OV9712_REG76      0x76
#define OV9712_REG77      0x77
#define OV9712_REG78      0x78
#define OV9712_REG79      0x79

#define OV9712_DSP_CTRL_0       0x96
#define OV9712_DSP_CTRL_1       0x97
#define OV9712_DSP_CTRL_2       0x98
#define OV9712_DSP_CTRL_3       0x99
#define OV9712_DSP_CTRL_4       0x9A
#define OV9712_DSP_CTRL_5       0x9B
#define OV9712_DSP_CTRL_6       0x9C
#define OV9712_DSP_CTRL_7       0x9D

#define OV9712_LENC_CTRL_0      0x9E
#define OV9712_LENC_CTRL_1      0x9F
#define OV9712_LENC_CTRL_02  0xA0
#define OV9712_LENC_CTRL_03  0xA1
#define OV9712_LENC_CTRL_04  0xA2
#define OV9712_LENC_CTRL_05  0xA3
#define OV9712_LENC_CTRL_06  0xA4
#define OV9712_LENC_CTRL_07  0xA5
#define OV9712_LENC_CTRL_08  0xA6
#define OV9712_LENC_CTRL_09  0xA7
#define OV9712_LENC_CTRL_10  0xA8
#define OV9712_LENC_CTRL_11  0xA9
#define OV9712_LENC_CTRL_12  0xAA
#define OV9712_LENC_CTRL_13  0xAB
#define OV9712_LENC_CTRL_14  0xAC
#define OV9712_LENC_CTRL_15  0xAD
#define OV9712_LENC_CTRL_16  0xAE


#define OV9712_LENC_CTRL_17  0xAF
#define OV9712_LENC_CTRL_18  0xB0
#define OV9712_LENC_CTRL_19  0xB1
#define OV9712_LENC_CTRL_20  0xB2
#define OV9712_LENC_CTRL_21  0xB3
#define OV9712_LENC_CTRL_22  0xB4
#define OV9712_LENC_CTRL_23  0xB5


#define OV9712_AWB_CTRL_0  0xB6
#define OV9712_AWB_CTRL_1  0xB7
#define OV9712_AWB_CTRL_2  0xB8
#define OV9712_AWB_CTRL_3  0xB9
#define OV9712_AWB_CTRL_4  0xBA
#define OV9712_AWB_CTRL_5  0xBB

#define OV9712_WBC_CTRL_0  0xBC

#define OV9712_YAVG_CTRL_0  0xBD
#define OV9712_YAVG_CTRL_1  0xBE
#define OV9712_YAVG_CTRL_2  0xBF
#define OV9712_YAVG_CTRL_3  0xC0
#define OV9712_YAVG_CTRL_4  0xC1


#define OV9712_DVP_CTRL_00  0xC2
#define OV9712_DVP_CTRL_01  0xC3
#define OV9712_DVP_CTRL_02  0xC4
#define OV9712_DVP_CTRL_03  0xC5
#define OV9712_DVP_CTRL_04  0xC6
#define OV9712_DVP_CTRL_05  0xC7
#define OV9712_DVP_CTRL_06  0xC8
#define OV9712_DVP_CTRL_07  0xC9
#define OV9712_DVP_CTRL_08  0xCA
#define OV9712_DVP_CTRL_09  0xCB
#define OV9712_DVP_CTRL_0A  0xCC
#define OV9712_DVP_CTRL_0B  0xCD
#define OV9712_DVP_CTRL_0C  0xCE
#define OV9712_DVP_CTRL_0D  0xCF


#define OV9712_DVP_CTRL_0E  0xD0   
#define OV9712_DVP_CTRL_0F  0xD1   
#define OV9712_DVP_CTRL_10  0xD2   
#define OV9712_DVP_CTRL_11  0xD3      
#define OV9712_DVP_CTRL_12  0xD4      
#define OV9712_SC_CTRL_0  0xD6       

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void OV9712_HW_Init(void);
void OV9712_Reset(void);
void OV9712_ReadID(OV9712_IDTypeDef* OV9712ID);
void OV9712_Init(ImageFormat_TypeDef ImageFormat);
void OV9712_QQVGAConfig(void);
void OV9712_QVGAConfig(void);
void OV9712_BrightnessConfig(uint8_t Brightness);
uint8_t OV9712_WriteReg(uint16_t Addr, uint8_t Data);
uint8_t OV9712_ReadReg(uint16_t Addr);

#endif /* __DCMI_OV9712_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

