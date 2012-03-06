/**
  ******************************************************************************
  * @file    mono_lcd.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2011
  * @brief   This file contains basic functions to control the monocolor LCD.
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

/* Includes ------------------------------------------------------------------*/
#include "mono_lcd.h"

/* Private define ------------------------------------------------------------*/

/* This table contains the "S" of ST logo */
__CONST uint8_t S_CGRAM[] =
  {
    /* 0~7 */
    0x03, 0xff,
    0x02, 0x00,
    0x04, 0x00,
    0x04, 0x00,
    0x0c, 0x7f,
    0x0c, 0x7f,
    0x1c, 0x3f,
    0x1e, 0x1f,
    /* 8~15 */
    0x3f, 0x0f,
    0x3f, 0x87,
    0x7f, 0xc3,
    0x7f, 0xe3,
    0x00, 0x03,
    0x00, 0x03,
    0x00, 0x07,
    0xff, 0xfe,
  };

/* This table contains the "T" of ST logo */
__CONST uint8_t T_CGRAM[] =
  {
    /* 0~7 */
    0xff, 0xff,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0xf8, 0xf8,
    0xf0, 0xf8,
    0xf0, 0xf0,
    0xf0, 0xf0,
    /* 8~15 */
    0xe1, 0xe0,
    0xe3, 0xe0,
    0xc3, 0xc0,
    0xc7, 0xc0,
    0x87, 0xc0,
    0x8f, 0x80,
    0x0f, 0x80,
    0x1f, 0x00
  };

/** @addtogroup LCD_Private_Functions
  * @{
  */

/**
  * @brief Basic delay routine
  * @param[in] nCount Delay value
  * @retval None
  */
void LCD_Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
    nop();
  }
}

/**
  * @brief Read status from LCD
  * @param None
  * @retval None
  */
void LCD_ReadStatus(void)
{
  LCD_SendByte(STATUS_TYPE, 0x00);
  LCD_Delay(200);  
}

/**
  * @brief Send a byte to LCD through the SPI peripheral
  * @param[in] DataToSend Data to be sent
  * @retval None
  */
static void LCD_SPISendByte(uint8_t DataToSend)
{
  /* Send byte through the SPI peripheral */
  SPI->DR = DataToSend;

  while ((SPI->SR & SPI_SR_TXE) == 0)
  {
    /* Wait while the byte is transmitted */
  }
}

/**
  * @}
  */

/** @addtogroup LCD_Public_Functions
  * @{
  */

/**
  * @brief Enable or Disable the LCD through CS pin
  * @param[in] NewState CS pin state
  * @retval None
  */
void LCD_ChipSelect(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    GPIO_ResetBits(LCD_CS_PORT, LCD_CS_PIN); /* CS pin low: LCD disabled */
  }
  else
  {
    GPIO_SetBits(LCD_CS_PORT, LCD_CS_PIN); /* CS pin high: LCD enabled */
  }
}

/**
  * @brief Send a byte to LCD
  * @param[in] DataType Type of Data to be sent
  * @param[in] DataToSend Data to be sent
  * @retval None
  */
void LCD_SendByte(uint8_t DataType, uint8_t DataToSend)
{
  LCD_ChipSelect(ENABLE); /* Enable access to LCD */

  LCD_SPISendByte(DataType); /* Send Synchro/Mode byte */
  LCD_SPISendByte((uint8_t)(DataToSend & (uint8_t)0xF0)); /* Send byte high nibble */
  LCD_SPISendByte((uint8_t)((uint8_t)(DataToSend << 4) & (uint8_t)0xF0)); /* Send byte low nibble */
  
  LCD_Delay(80);
  
  LCD_ChipSelect(DISABLE); /* Disable access to LCD */
}

/**
  * @brief Send a buffer to LCD
  * @param[in] pTxBuffer Pointer to the buffer to send
  * @param[in] NumByte   Number of bytes to send and read
  * @retval None
  */
void LCD_SendBuffer(uint8_t *pTxBuffer, uint8_t NumByte)
{
  LCD_ChipSelect(ENABLE);
  
  while (NumByte--) /* while there is data to be read */
  {
    LCD_SPISendByte(*pTxBuffer);
    pTxBuffer++;
  }

  LCD_ChipSelect(DISABLE);
}

/**
  * @brief Initialize the LCD
  * @param None
  * @retval None
  */
void LCD_Init(void)
{
  /* Set LCD ChipSelect pin in Output push-pull low level (chip select disabled) */
  GPIO_Init(LCD_CS_PORT, LCD_CS_PIN, GPIO_Mode_Out_PP_Low_Fast);

  LCD_SendByte(COMMAND_TYPE, SET_TEXT_MODE); /* Set the LCD in TEXT mode */
  LCD_SendByte(COMMAND_TYPE, DISPLAY_ON); /* Enable the display */
  
  LCD_Clear();
  
  LCD_SendByte(COMMAND_TYPE, ENTRY_MODE_SET_INC); /* Select the entry mode type */
}

/**
  * @brief Clear the LCD
  * @param None
  * @retval None
  * @note The LCD must be enabled first.
  */
void LCD_Clear(void)
{
  LCD_SendByte(COMMAND_TYPE, DISPLAY_CLR); /* Clear the LCD */
  LCD_Delay(5000);
}

/**
  * @brief Set the LCD in text mode
  * @param None
  * @retval None
  */
void LCD_SetTextMode(void)
{
  LCD_SendByte(COMMAND_TYPE, SET_TEXT_MODE);
  LCD_Clear();
}

/**
  * @brief Set the LCD in graphic mode
  * @param None
  * @retval None
  */
void LCD_SetGraphicMode(void)
{
  LCD_Clear();
  LCD_SendByte(COMMAND_TYPE, SET_GRAPHIC_MODE);
}

/**
  * @brief Clear one LCD
  * @param[in] Line Line to be cleared (LCD_LINE1 or LCD_LINE2)
  * @retval None
  */
void LCD_ClearLine(uint8_t Line)
{
  uint8_t CharPos;

  /* Select the line to be cleared */
  LCD_SendByte(COMMAND_TYPE, Line);

  /* Clear the selected line */
  for (CharPos = 0; CharPos < LCD_LINE_MAX_CHAR; CharPos++)
  {
    LCD_SendByte(DATA_TYPE, ' ');
  }
}

/**
  * @brief Set the LCD cursor to the specified location
  * @param[in] Line   Line where the cursor will be set (LCD_LINE1 or LCD_LINE2)
  * @param[in] Offset is the position offset (only even position are supported)
  * @retval None
  */
void LCD_SetCursorPos(uint8_t Line, uint8_t Offset)
{
  LCD_SendByte(COMMAND_TYPE, (uint8_t)(Line + Offset));
}

/**
  * @brief Display a character at the current cursor position
  * @param[in] Ascii is the character ascii code to be displayed
  * @retval None
  * @note The cursor position must be set before calling this function
  */
void LCD_PrintChar(uint8_t Ascii)
{
  LCD_SendByte(DATA_TYPE, Ascii);
}

/**
  * @brief Display a string on the selected line of the LCD
  * @param[in] Line         Line where to display the string (LCD_LINE1 or LCD_LINE2)
  * @param[in] AutoComplete Defines if the line must be completed with spaces or not
  * @param[in] Append       Defines if the string is appended or not
  * @param[in] ptr          Pointer to the string to display
  * @retval None
  */
void LCD_PrintString(uint8_t Line, FunctionalState AutoComplete, FunctionalState Append, uint8_t *ptr)
{
  uint8_t CharPos = 0;

  /* Set cursor position at beginning of Line if Append option is enabled */
  if (Append == DISABLE)
  {
    LCD_SendByte(COMMAND_TYPE, Line);
  }

  /* Display each character of the string */
  while ((*ptr != 0) && (CharPos < LCD_LINE_MAX_CHAR))
  {
    LCD_SendByte(DATA_TYPE, *ptr);
    CharPos++;
    ptr++;
  }

  /* Complete the line with spaces if AutoFill option is enabled */
  if (AutoComplete == ENABLE)
  {
    while (CharPos < LCD_LINE_MAX_CHAR)
    {
      LCD_SendByte(DATA_TYPE, ' ');
      CharPos++;
    }
  }

}

/**
  * @brief Display a string on the LCD with automatic carriage return
  * @param[in] ptr Pointer to the string to display
  * @retval  None
  * @note
  * - The LCD is cleared prior to display the string
  * - The character % is not supported
  */
void LCD_PrintMsg(uint8_t *ptr)
{
  uint8_t Char = 0;
  uint8_t CharPos = 0;

  LCD_Clear(); /* Clear the LCD display */
  
  LCD_Delay(200);

  /* Set cursor to home position on line 1 */
  LCD_SendByte(COMMAND_TYPE, LCD_LINE1);

  /* Send String */
  while ((*ptr != 0) && (CharPos < (LCD_LINE_MAX_CHAR * 2)))
  {
    
    /* Check if string length is bigger than LINE1 */
    if (CharPos == LCD_LINE_MAX_CHAR)
    {
      LCD_SendByte(COMMAND_TYPE, LCD_LINE2); /* Select second line */
    }

    Char = *ptr;

    switch (Char)
    {
      case ('\r'):
        /* Carriage return */
        CharPos++;
        ptr++;
      break;
      case ('\n'):
        CharPos = 0;
        ptr++;
        /* Set cursor to line 2 */
        LCD_SendByte(COMMAND_TYPE, LCD_LINE2);
      break;
      default:
        /* Display characters different from (\r, \n) */
        LCD_SendByte(DATA_TYPE, Char);
        CharPos++;
        ptr++;
      break;
    }
  }

}

/**
  * @brief Display the Number in decimal format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 9 (max 1 digit)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintDec1(uint8_t Number)
{

  uint8_t NbreTmp;

  if (Number < (uint8_t)10)
  {
   
    /* Display second digit of the number : 10 */
    NbreTmp = (uint8_t)(Number / (uint8_t)10);
   
    /* Display last digit of the number : Units */
    NbreTmp = (uint8_t)(Number - (uint8_t)((uint8_t)10 * NbreTmp));
    LCD_PrintChar((uint8_t)(NbreTmp + (uint8_t)0x30));
   
  }

}

/**
  * @brief Display the Number in decimal format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 99 (max 2 digits)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintDec2(uint8_t Number)
{

  uint8_t NbreTmp;

  if (Number < (uint8_t)100)
  {
   
    /* Display second digit of the number : 10 */
    NbreTmp = (uint8_t)(Number / (uint8_t)10);
    LCD_PrintChar((uint8_t)(NbreTmp + (uint8_t)0x30));
   
    /* Display last digit of the number : Units */
    NbreTmp = (uint8_t)(Number - (uint8_t)((uint8_t)10 * NbreTmp));
    LCD_PrintChar((uint8_t)(NbreTmp + (uint8_t)0x30));
   
  }

}

/**
  * @brief Display the Number in decimal format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 999 (max 3 digits)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintDec3(uint16_t Number)
{

  uint8_t Nbre1Tmp;
  uint8_t Nbre2Tmp;

  if (Number < (uint16_t)1000)
  {
   
    /* Display first digit of the number : 100 */
    Nbre1Tmp = (uint8_t)(Number / (uint8_t)100);
    LCD_PrintChar((uint8_t)(Nbre1Tmp + (uint8_t)0x30));
   
    /* Display second digit of the number : 10 */
    Nbre1Tmp = (uint8_t)(Number - ((uint8_t)100 * Nbre1Tmp));
    Nbre2Tmp = (uint8_t)(Nbre1Tmp / (uint8_t)10);
    LCD_PrintChar((uint8_t)(Nbre2Tmp + (uint8_t)0x30));
   
    /* Display last digit of the number : Units */
    Nbre1Tmp = ((uint8_t)(Nbre1Tmp - (uint8_t)((uint8_t)10 * Nbre2Tmp)));
    LCD_PrintChar((uint8_t)(Nbre1Tmp + (uint8_t)0x30));
  }
  
}

/**
  * @brief Display the Number in decimal format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 9999 (max 4 digits)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintDec4(uint16_t Number)
{

  uint16_t Nbre1Tmp;
  uint16_t Nbre2Tmp;

  if (Number < (uint16_t)10000)
  {
   
    /* Display first digit of the number : 1000 */
    Nbre1Tmp = (uint16_t)(Number / (uint16_t)1000);
    LCD_PrintChar((uint8_t)(Nbre1Tmp + (uint8_t)0x30));
   
    /* Display second digit of the number : 100 */
    Nbre1Tmp = (uint16_t)(Number - ((uint16_t)1000 * Nbre1Tmp));
    Nbre2Tmp = (uint16_t)(Nbre1Tmp / (uint8_t)100);
    LCD_PrintChar((uint8_t)(Nbre2Tmp + (uint8_t)0x30));
   
    /* Display second digit of the number : 10 */
    Nbre1Tmp = (uint16_t)(Nbre1Tmp - ((uint16_t)100 * Nbre2Tmp));
    Nbre2Tmp = (uint16_t)(Nbre1Tmp / (uint16_t)10);
    LCD_PrintChar((uint8_t)(Nbre2Tmp + (uint8_t)0x30));
   
    /* Display last digit of the number : Units */
    Nbre1Tmp = ((uint16_t)(Nbre1Tmp - (uint16_t)((uint16_t)10 * Nbre2Tmp)));
    LCD_PrintChar((uint8_t)(Nbre1Tmp + (uint8_t)0x30));
  }

}

/**
  * @brief Display the Number in Hexadecimal format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 15 (1 digit only)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintHex1(uint8_t Number)
{
  if (Number < (uint8_t)0x0A)
  {
    LCD_PrintChar((uint8_t)(Number + (uint8_t)0x30));
  }
  else
    if (Number < (uint8_t)0x10)
    {
      LCD_PrintChar((uint8_t)(Number + (uint8_t)0x37));
    }
    else
    {
      LCD_PrintChar('-');
    }
}

/**
  * @brief Display the Number in Hexadecimal format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 255 (max 2 digits)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintHex2(uint8_t Number)
{
  LCD_PrintHex1((uint8_t)(Number >> (uint8_t)4));
  LCD_PrintHex1((uint8_t)(Number & (uint8_t)0x0F));
}

/**
  * @brief Display the Number in Hexadecimal format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 4095 (max 3 digits)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintHex3(uint16_t Number)
{
  LCD_PrintHex1((uint8_t)(Number >> (uint8_t)8)); 
  LCD_PrintHex1((uint8_t)((uint8_t)(Number) >> (uint8_t)4));
  LCD_PrintHex1((uint8_t)((uint8_t)(Number) & (uint8_t)0x0F));
}

/**
  * @brief Display the Number in binary format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 3 (max 2 digits)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintBin2(uint8_t Number)
{
  LCD_PrintHex1((uint8_t)((uint8_t)(Number & (uint8_t)0x02) >> (uint8_t)1));
  LCD_PrintHex1((uint8_t)(Number & (uint8_t)0x01));
}

/**
  * @brief Display the Number in binary format at the current cursor position
  * @param[in] Number Number to be displayed
  * @retval None
  * @note
  * - Convert only numbers between 0 and 15 (max 4 digits)
  * - The cursor position must be set before calling this function
  */
void LCD_PrintBin4(uint8_t Number)
{
  LCD_PrintHex1((uint8_t)((uint8_t)(Number & (uint8_t)0x08) >> (uint8_t)3));
  LCD_PrintHex1((uint8_t)((uint8_t)(Number & (uint8_t)0x04) >> (uint8_t)2));
  LCD_PrintHex1((uint8_t)((uint8_t)(Number & (uint8_t)0x02) >> (uint8_t)1));
  LCD_PrintHex1((uint8_t)(Number & (uint8_t)0x01));
}

/**
  * @brief Display CGRAM on even address
  * @param[in] address  Display address
  * @param[in] ptrTable Pointer a the CGRAM table to be displayed
  * @retval None
  */
void LCD_DisplayCGRAM0(uint8_t address, uint8_t *ptrTable)
{

  uint8_t u;

  /* Set CGRAM Address */
  LCD_SendByte(COMMAND_TYPE, (uint8_t)0x40);

  u = 32; /* Nb byte in the table */
  while (u)
  {
    LCD_SendByte(DATA_TYPE, ptrTable[32 - u]);
    u--;
  }

  /* Setup Display Address */
  LCD_SendByte(COMMAND_TYPE, address);
  LCD_SendByte(DATA_TYPE, (uint8_t)0x00);
  LCD_SendByte(DATA_TYPE, (uint8_t)0x00);

}

/**
  * @brief Display CGRAM on odd address
  * @param[in] address  Display address
  * @param[in] ptrTable Pointer a the CGRAM table to be displayed
  * @retval None
  */
void LCD_DisplayCGRAM1(uint8_t address, uint8_t *ptrTable)
{

  uint8_t u;

 /* Set CGRAM Address */
  LCD_SendByte(COMMAND_TYPE, (uint8_t)((uint8_t)0x40 | (uint8_t)0x10));

  u = 32; /* Nb byte in the table */
  while (u)
  {
    LCD_SendByte(DATA_TYPE, ptrTable[32 - u]);
    u--;
  }

  /* Setup Display Address */
  LCD_SendByte(COMMAND_TYPE, (uint8_t)(address + 1));
  LCD_SendByte(DATA_TYPE, (uint8_t)0x00);
  LCD_SendByte(DATA_TYPE, (uint8_t)0x02);

}

/**
  * @brief Display ST logo
  * @param[in] address Display address (LINE1:0x80-0x87 and LINE2:0x90-0x97)
  * @retval None
  */
void LCD_DisplayLogo(uint8_t address)
{
  LCD_DisplayCGRAM0(address, (uint8_t*)S_CGRAM);
  LCD_DisplayCGRAM1(address, (uint8_t*)T_CGRAM);
}

/**
  * @brief Display a string in rolling mode
  * @param[in] Line  Line used for displaying the text (LCD_LINE1 or LCD_LINE2)
  * @param[in] ptr   Pointer to the text to display
  * @param[in] speed Rolling speed
  * @retval None
  */
void LCD_RollString(uint8_t Line, uint8_t *ptr, uint16_t speed)
{

  uint8_t CharPos = 0;
  uint8_t *ptr2;
  
  /* Set cursor position at beginning of line */
  LCD_SendByte(COMMAND_TYPE, Line);
  
  ptr2 = ptr;
  
  /* Display each character of the string */
  while (*ptr2 != 0)
  {
   
    if (*ptr != 0)
    {
      LCD_SendByte(DATA_TYPE, *ptr);
      ptr++;
    }
    else
    {
      LCD_SendByte(DATA_TYPE, ' ');
    }
    
    CharPos++;
   
    if (CharPos == LCD_LINE_MAX_CHAR)
    {
      LCD_Delay(speed);
      LCD_ClearLine(Line);
      LCD_SendByte(COMMAND_TYPE, Line);
      CharPos = 0;
      ptr2++;
      ptr = ptr2;
    }
    
  }

}

/**
  * @brief Display a string from current position of the LCD cursor
  * @param[in] ptr Pointer to the string to display
  * @retval None
  */
void LCD_Print(uint8_t *ptr) {
  while (*ptr) /* Display the string */
  LCD_SendByte(DATA_TYPE, *ptr++);
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
