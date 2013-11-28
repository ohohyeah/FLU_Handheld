/**
  ******************************************************************************
  * @file    DCMI/Camera/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f4xx_it.h"
#include "stm324xg_eval.h"
#include "main.h"
#include "stm32f4xx_dma.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup DCMI_Camera
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t PressedKey;

extern ImageFormat_TypeDef ImageFormat;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/**
  * @brief  This function handles External line 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
}

void DCMI_IRQHandler(void)
{
	if (DCMI->RISR & DCMI_IT_ERR)
	{
		//STM_EVAL_LEDOn(LED1);
		DMA_Cmd(DMA2_Stream1, DISABLE); 
		DCMI_Cmd(DISABLE); 
		Camera_Config();
		DMA_Cmd(DMA2_Stream1, ENABLE); 
		DCMI_Cmd(ENABLE); 
		DCMI->ICR = DCMI_IT_ERR;
	}
	if (DCMI->RISR & DCMI_IT_OVF)
	{
		//STM_EVAL_LEDOn(LED2);
		//DMA_Cmd(DMA2_Stream1, DISABLE); 
		//DCMI_Cmd(DISABLE); 
		//Camera_Config();
		//DMA_Cmd(DMA2_Stream1, ENABLE); 
		//DCMI_Cmd(ENABLE); 
		//DCMI->ICR = DCMI_IT_OVF;
	}
	if (DCMI->RISR & DCMI_IT_VSYNC)
	{
		DCMI->ICR = DCMI_IT_VSYNC;
	}
	if (DCMI->RISR & DCMI_IT_FRAME)
	{
		DCMI->ICR = DCMI_IT_FRAME;
		//DMA_Cmd(DMA2_Stream1, DISABLE); 
		//DCMI_Cmd(DISABLE); 
	}
}

void DMA2_Stream1_IRQHandler(void)
{
	int bStop = 0;
	if (DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1) != RESET)
	{
		DMA_Cmd(DMA2_Stream1, DISABLE);
		DMA_ClearFlag(DMA2_Stream1, 0x2F7D0F7D);
		DMA_ClearFlag(DMA2_Stream1, 0x0F7D0F7D);
		if ((datablock % 16) == 15) 
		{
			DCMI_Cmd(DISABLE);
			//STM_EVAL_LEDOn(LED2);
			if (bShot)
			{
				STM_EVAL_LEDOn(LED1);
				bStop = 1;
			}
			else
			{
				DCMI_Cmd(ENABLE);
			}
		}
		//else displayblock++;
		if (datablock == 47) 
		{
			datablock = 0;
		}
		else datablock++;
		DMA2_Stream1->M0AR = 0x20000000 + 9600 * (datablock % 12);
		DMA_SetCurrDataCounter(DMA2_Stream1, (320 * 240 * 2 / 4) / 16);
		DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);
		if (bStop)
		{
			DMA_Cmd(DMA2_Stream1, DISABLE);
		}
		else
		{
			DMA_Cmd(DMA2_Stream1, ENABLE);
		}
	}
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/



/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
