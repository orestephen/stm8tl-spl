/**
  ******************************************************************************
  * @file    USART/USART_MultiProcessor/main.h
  * @brief   This file contains all the prototypes of the main functions.
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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm8tl5x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* I/Os configuration */
#define LEDS_PORT    (GPIOB)
#define LED1_PIN     (GPIO_Pin_2)
#define LED2_PIN     (GPIO_Pin_3)

#define BUTTON_PORT    (GPIOB)
#define BUTTON_PIN     (GPIO_Pin_5)


/* Exported macro ------------------------------------------------------------*/

//#define USART_Master /*Uncomment this line to run the master in multiprocesor communication*/
//#define USART_Slave   /*Uncomment this line to run the Slave in multiprocesor communication*/ 
#define USART_Master_Slave

/* Exported functions ------------------------------------------------------- */
void Delay(uint32_t nCount);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
