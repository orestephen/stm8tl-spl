/**
  ******************************************************************************
  * @file    mono_lcd.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2011
  * @brief   This file contains LCD functions prototypes.
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

#ifndef __MONO_LCD_H
#define __MONO_LCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm8tl5x.h"

/* Exported constants --------------------------------------------------------*/

/* LCD Chip Select I/O definition */
#define LCD_CS_PORT (GPIOA)
#define LCD_CS_PIN  (GPIO_Pin_7)

/* LCD managed as 2 Lines of 15 characters (2Lines * 15Char) */
#define LCD_LINE_MAX_CHAR ((uint8_t)15)
#define LCD_LINE1         ((uint8_t)0x80)
#define LCD_LINE2         ((uint8_t)0x90)

/* LCD Commands */
#define COMMAND_TYPE       ((uint8_t)0xF8)
#define DATA_TYPE          ((uint8_t)0xFA)
#define STATUS_TYPE        ((uint8_t)0xFC)
#define SET_TEXT_MODE      ((uint8_t)0x30) /* 8-Bits Interface, Normal inst., Text mode */
#define SET_EXTENDED_INST  ((uint8_t)0x34)
#define SET_GRAPHIC_MODE   ((uint8_t)0x36) /* 8-Bits Interface, Extended inst., Graphic mode */
#define DISPLAY_ON         ((uint8_t)0x0C) /* Cursor and blink off */
#define DISPLAY_OFF        ((uint8_t)0x08)
#define DISPLAY_CLR        ((uint8_t)0x01)
#define ENTRY_MODE_SET_INC ((uint8_t)0x06)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void LCD_ReadStatus(void);
void LCD_ChipSelect(FunctionalState NewState);
void LCD_SendByte(uint8_t DataType, uint8_t DataToSend);
void LCD_SendBuffer(uint8_t *pTxBuffer, uint8_t NumByte);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetTextMode(void);
void LCD_SetGraphicMode(void);
void LCD_ClearLine(uint8_t Line);
void LCD_SetCursorPos(uint8_t Line, uint8_t Offset);
void LCD_PrintChar(uint8_t Ascii);
void LCD_PrintString(uint8_t Line, FunctionalState AutoComplete, FunctionalState Append, uint8_t *ptr);
void LCD_PrintMsg(uint8_t *ptr);
void LCD_Print(uint8_t *ptr);
void LCD_PrintDec1(uint8_t Number);
void LCD_PrintDec2(uint8_t Number);
void LCD_PrintDec3(uint16_t Number);
void LCD_PrintDec4(uint16_t Number);
void LCD_PrintHex1(uint8_t Number);
void LCD_PrintHex2(uint8_t Number);
void LCD_PrintHex3(uint16_t Number);
void LCD_PrintBin2(uint8_t Number);
void LCD_PrintBin4(uint8_t Number);
void LCD_DisplayCGRAM0(uint8_t address, uint8_t *ptrTable);
void LCD_DisplayCGRAM1(uint8_t address, uint8_t *ptrTable);
void LCD_DisplayLogo(uint8_t address);
void LCD_RollString(uint8_t Line, uint8_t *ptr, uint16_t speed);
void LCD_Delay(uint16_t nCount);

#endif /* __MONO_LCD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
