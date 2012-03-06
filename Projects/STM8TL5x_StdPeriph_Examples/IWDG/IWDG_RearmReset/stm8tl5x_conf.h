/**
  ******************************************************************************
  * @file    IWDG/IWDG_RearmReset/stm8tl5x_conf.h
  * @brief   This file is used to configure the Library.
  * @author  STMicroelectronics - MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8TL5X_CONF_H
#define __STM8TL5X_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm8tl5x.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */ 

/* Uncomment the line below to enable peripheral header file inclusion */

/*** AUTO WAKE UP *************************************************************/
/* #define _AWU (1) */

/*** BEEP *********************************************************************/
/* #define _BEEP (1) */

/*** CLOCK CONTROLLER *********************************************************/
/* #define _CLK (1) */

/*** EXTERNAL INTERRUPTS ******************************************************/
/* #define _EXTI (1) */

/*** FLASH/DATA EEPROM ********************************************************/
/* #define _FLASH (1) */

/*** GENERAL PURPOSE IOs ******************************************************/
#define _GPIO (1)

/*** INTERRUPT CONTROLLER *****************************************************/
/* #define _ITC (1) */

/*** INDEPENDANT WATCH-DOG ****************************************************/
#define _IWDG (1)

/*** I2C **********************************************************************/
/* #define _I2C (1) */

/*** OPTION BYTES *************************************************************/
/* #define _OPT (1) */

/*** RESET CONTROLLER *********************************************************/
#define _RST (1)

/*** SPI **********************************************************************/
/* #define _SPI (1) */

/*** TIMERs *******************************************************************/
/* #define _TIM2 (1) */
/* #define _TIM3 (1) */
/* #define _TIM4 (1) */

/*** USART ********************************************************************/
/* #define _USART (1) */

/*** WINDOW WATCH-DOG *********************************************************/
/* #define _WWDG (1) */

/*** WFE **********************************************************************/
/* #define _WFE (1) */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed. 
  *   If expr is true, it returns no value.
  * @retval : None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

/* Peripheral header file inclusion ******************************************/

#ifdef _AWU
#include "stm8tl5x_awu.h"
#endif /* _AWU */

#ifdef _BEEP
#include "stm8tl5x_beep.h"
#endif /* _BEEP */

#if defined(_FLASH) || defined(_OPT)
#include "stm8tl5x_flash.h"
#endif /* _FLASH/OPT */

#ifdef _EXTI
#include "stm8tl5x_exti.h"
#endif /* _EXTI */

#ifdef _GPIO
#include "stm8tl5x_gpio.h"
#endif /* _GPIOx */

#ifdef _I2C
#include "stm8tl5x_i2c.h"
#endif /* _I2C */

#ifdef _ITC
#include "stm8tl5x_itc.h"
#endif /* _ITC */

#ifdef _IWDG
#include "stm8tl5x_iwdg.h"
#endif /* _IWDG */

#ifdef _CLK
#include "stm8tl5x_clk.h"
#endif /* _CLK */

#ifdef _RST
#include "stm8tl5x_rst.h"
#endif /* _RST */

#ifdef _SPI
#include "stm8tl5x_spi.h"
#endif /* _SPI */

#ifdef _TIM2
#include "stm8tl5x_tim2.h"
#endif /* _TIM2 */

#ifdef _TIM3
#include "stm8tl5x_tim3.h"
#endif /*_TIM3 */

#ifdef _TIM4
#include "stm8tl5x_tim4.h"
#endif /* _TIM4 */

#ifdef _USART
#include "stm8tl5x_usart.h"
#endif /* _USART */

#ifdef _WFE
#include "stm8tl5x_wfe.h"
#endif /* _WFE */

#ifdef _WWDG
#include "stm8tl5x_wwdg.h"
#endif /* _WWDG */

#endif /* __STM8TL5X_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
