/**
  ******************************************************************************
  * @file    I2C/I2C_EEPROM/i2c_ee.c
  * @brief   This file provides a set of functions needed to manage the 
  *          communication between I2C peripheral and I2C M24C64 EEPROM.
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
/* Includes ------------------------------------------------------------------*/
#include "i2c_ee.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_Speed              100000
#define I2C1_SLAVE_ADDRESS7    0xA0
#define EEPROM_BASE_ADDRESS    0x0000
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t EEPROM_ADDRESS = 0xA0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief Initializes the I2C peripheral registers to communicate the EEPROM
  * @par Parameters:
  * None
  * @retval None
  */

void I2C_EEInit(void)
{
  
  /* I2C Peripheral Enable */
  I2C_Cmd(ENABLE);
  /* Apply I2C configuration after enabling it */
  I2C_Init(I2C_Speed, I2C1_SLAVE_ADDRESS7, I2C_DutyCycle_2, I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);
	
}

/**
  * @brief Writes one byte to the I2C EEPROM.
  * @param[in] pBuffer Pointer to the buffer containing the data to be 
	* written to the EEPROM.
  * @param[in] WriteAddr EEPROM's internal address to write to.
  * @retval None
  */
void I2C_EE_ByteWrite(uint8_t* pBuffer, uint16_t WriteAddr)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(ENABLE);

  /* Test on EV5 and clear it I2C_EVENT_MASTER_MODE_SELECT */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));  

  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_GetFlagStatus(I2C_FLAG_ADDR);
	(void)(I2C->SR3);
	
  /* Send Address (on 2 bytes) of first byte to be written & wait event detection */
  I2C_SendData((uint8_t)(WriteAddr >> 8)); /* MSB */
  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  I2C_SendData((uint8_t)(WriteAddr)); /* LSB */
  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
 
  /* Send the byte to be written */
  I2C_SendData(*pBuffer); 
	
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STOP condition */
  I2C_GenerateSTOP(ENABLE);
}

/**
  * @brief Writes more than one byte to the EEPROM with a single WRITE cycle. 
  *  The number of byte can't exceed the EEPROM page size.
  * @param[in] pBuffer Pointer to the buffer containing the data to be 
	* written to the EEPROM.
  * @param[in] WriteAddr EEPROM's internal address to write to.
  * @param[in] NumByteToWrite EEPROM's number of bytes to write to the EEPROM.  
  * @retval None
  */
void I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite)
{
  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2C_FLAG_BUSY));
  
  /* Send START condition */
  I2C_GenerateSTART(ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT)); 
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_ADDRESS, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_GetFlagStatus(I2C_FLAG_ADDR);
	(void)(I2C->SR3);

  /* Send Address (on 2 bytes) of first byte to be written & wait event detection */
  I2C_SendData((uint8_t)(WriteAddr >> 8)); /* MSB */
  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
  I2C_SendData((uint8_t)(WriteAddr)); /* LSB */
  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));  


  /* While there is data to be written */
  while(NumByteToWrite--)  
  {
    /* Send the current byte */
    I2C_SendData(*pBuffer); 

    /* Point to the next byte to be written */
    pBuffer++; 
  
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(ENABLE);
}

/**
  * @brief Reads a block of data from the EEPROM. 
  * @param[in] pBuffer pointer to the buffer that receives the data read
  * from the EEPROM.
  * @param[in] WriteAddr EEPROM's internal address to read from.
  * @param[in] NumByteToWrite EEPROM's number of bytes to read from the EEPROM.  
  * @retval None
  */
void I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint8_t NumByteToRead)
{  
	/* While the bus is busy */
  while(I2C_GetFlagStatus(I2C_FLAG_BUSY));
  
  /* Generate start & wait event detection */
  I2C_GenerateSTART(ENABLE);
  /* Test on EV5 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send slave Address in write direction & wait detection event */
  I2C_Send7bitAddress(EEPROM_ADDRESS, I2C_Direction_Transmitter);
  /* Test on EV6 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_GetFlagStatus(I2C_FLAG_ADDR);
	(void)(I2C->SR3);
    
  /* Send Address of first byte to be read & wait event detection */
  I2C_SendData((uint8_t)(ReadAddr >> 8)); /* MSB */
  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  I2C_SendData((uint8_t)(ReadAddr)); /* LSB */
  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(ENABLE);
  /* Test on EV5 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send slave Address in read direction & wait event */
  I2C_Send7bitAddress(EEPROM_ADDRESS, I2C_Direction_Receiver);
  /* Test on EV6 and clear it */
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  I2C_GetFlagStatus(I2C_FLAG_ADDR);
	(void)(I2C->SR3);

  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(DISABLE);			
		}

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_RECEIVED))
    {      
      /* Read a byte from the EEPROM */
      *pBuffer = I2C_ReceiveData();

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;    
    }
    if(NumByteToRead == 0)
    {
      /* Send STOP Condition */
      I2C_GenerateSTOP(ENABLE);
		}
	}

  /* Enable Acknowledgement to be ready for another reception */
	I2C_AckPositionConfig(I2C_AckPosition_Current);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
