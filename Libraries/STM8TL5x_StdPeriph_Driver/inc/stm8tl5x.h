/**
  ******************************************************************************
  * @file    stm8tl5x.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all HW registers definitions and memory mapping.
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
#ifndef __STM8TL5X_H
#define __STM8TL5X_H

/******************************************************************************/
/*                   Library configuration section                            */
/******************************************************************************/

/* Check the used compiler */
#if defined(__CSMC__)
 #define _COSMIC_
#elif defined(__RCST7__)
 #define _RAISONANCE_
#elif defined(__ICCSTM8__)
 #define _IAR_
#else
 #error "Unsupported Compiler!"          /* Compiler defines not found */
#endif

#if !defined  USE_STDPERIPH_DRIVER
/* Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will be
   based on direct access to peripherals registers */
#define USE_STDPERIPH_DRIVER
#endif

#if defined(_COSMIC_)
 #define FAR  @far
 #define NEAR @near
 #define TINY @tiny
 #define EEPROM @eeprom
 #define CONST  const
#elif defined(_RAISONANCE_)
 #define FAR  far
 #define NEAR data
 #define TINY page0
 #define EEPROM eeprom
 #define CONST  code
 #define MEMCPY memcpy /*!< Used with memory Models for code less than 64K */
#else /* _IAR_ */
 #define FAR  __far
 #define NEAR __near
 #define TINY __tiny
 #define EEPROM __eeprom
 #define CONST  const
#endif

/**
  * @brief Legacy definition
  */
#define __CONST  CONST

/*!< Used with memory Models for code smaller than 64K */
#define PointerAttr NEAR

/* Uncomment the line below to enable the FLASH functions execution from RAM */
#if !defined (RAM_EXECUTION)
/* #define RAM_EXECUTION  (1) */
#endif /* RAM_EXECUTION */

#ifdef RAM_EXECUTION
 #ifdef _COSMIC_
   #define IN_RAM(a) a
 #elif defined (_RAISONANCE_) /* __RCST7__ */
   #define IN_RAM(a) a inram
 #else /*_IAR_*/
  #define IN_RAM(a) __ramfunc a
 #endif /* _COSMIC_ */
#else 
  #define IN_RAM(a) a
#endif /* RAM_EXECUTION */

#ifdef _RAISONANCE_
// enable the direct call of parameters inside a structure omitting the structure name
#pragma SUE_OPT
#endif

/*!< [31:16] STM8TL5X Standard Peripheral Library main version */
#define __STM8TL5X_STDPERIPH_VERSION_MAIN   ((uint8_t)0x01) /*!< [31:24] main version */                                  
#define __STM8TL5X_STDPERIPH_VERSION_SUB1   ((uint8_t)0x00) /*!< [23:16] sub1 version */
#define __STM8TL5X_STDPERIPH_VERSION_SUB2   ((uint8_t)0x00) /*!< [15:8]  sub2 version */
#define __STM8TL5X_STDPERIPH_VERSION_RC     ((uint8_t)0x00) /*!< [7:0]  release candidate */ 
#define __STM8TL5X_STDPERIPH_VERSION       ( (__STM8TL5X_STDPERIPH_VERSION_MAIN << 24)\
                                          |(__STM8TL5X_STDPERIPH_VERSION_SUB1 << 16)\
                                          |(__STM8TL5X_STDPERIPH_VERSION_SUB2 << 8)\
                                          |(__STM8TL5X_STDPERIPH_VERSION_RC))


/******************************************************************************/

/* Includes ------------------------------------------------------------------*/

/* Exported types and constants-----------------------------------------------*/

/** @addtogroup Exported_types
  * @{
  */

/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */
#define     __I     volatile const            /*!< defines 'read only' permissions      */
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

/*!< Signed integer types  */
typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;

/*!< Unsigned integer types  */
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;

/*!< STM8TL5X Standard Peripheral Library old types (maintained for legacy purpose) */

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;


typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus, BitAction;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#define U8_MAX     (255)
#define S8_MAX     (127)
#define S8_MIN     (-128)
#define U16_MAX    (65535u)
#define S16_MAX    (32767)
#define S16_MIN    (-32768)
#define U32_MAX    (4294967295uL)
#define S32_MAX    (2147483647)
#define S32_MIN    (-2147483648uL)

/**
  * @}
  */

/** @addtogroup MAP_FILE_Exported_Types_and_Constants
  * @{
  */

/******************************************************************************/
/*                          IP registers structures                           */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/**
  * @brief General Purpose I/Os (GPIO)
  */
typedef struct GPIO_struct
{
  __IO uint8_t ODR; /*!< Output Data Register */
  __IO uint8_t IDR; /*!< Input Data Register */
  __IO uint8_t DDR; /*!< Data Direction Register */
  __IO uint8_t CR1; /*!< Configuration Register 1 */
  __IO uint8_t CR2; /*!< Configuration Register 2 */
}
GPIO_TypeDef;

/** @addtogroup GPIO_Registers_Reset_Value
  * @{
  */
#define GPIO_ODR_RESET_VALUE ((uint8_t)0x00)
#define GPIO_DDR_RESET_VALUE ((uint8_t)0x00)
#define GPIO_CR1_RESET_VALUE ((uint8_t)0x00)
#define GPIO_CR2_RESET_VALUE ((uint8_t)0x00)
/**
  * @}
  */
/*----------------------------------------------------------------------------*/

/**
  * @brief Auto Wake Up (AWU) peripheral registers.
  */
typedef struct AWU_struct
{
  __IO uint8_t CSR; /*!< AWU Control status register */
  __IO uint8_t APR; /*!< AWU Asynchronous prescalar buffer */
  __IO uint8_t TBR; /*!< AWU Time base selection register */
}
AWU_TypeDef;

/** @addtogroup AWU_Registers_Reset_Value
  * @{
  */

#define AWU_CSR_RESET_VALUE ((uint8_t)0x00)
#define AWU_APR_RESET_VALUE ((uint8_t)0x3F)
#define AWU_TBR_RESET_VALUE ((uint8_t)0x00)

/**
  * @}
  */

/** @addtogroup AWU_Registers_Bits_Definition
  * @{
  */

#define AWU_CSR_AWUF  ((uint8_t)0x20) /*!< Interrupt flag mask */
#define AWU_CSR_AWUEN ((uint8_t)0x10) /*!< Auto Wake-up enable mask */
#define AWU_CSR_MSR   ((uint8_t)0x01) /*!< Measurement enable mask */

#define AWU_APR_APR ((uint8_t)0x3F) /*!< Asynchronous Prescaler divider mask */

#define AWU_TBR_AWUTB ((uint8_t)0x0F) /*!< Timebase selection mask */

/**
  * @}
  */


/*----------------------------------------------------------------------------*/
/**
  * @brief Beeper (BEEP) peripheral registers.
  */

typedef struct BEEP_struct
{
  __IO uint8_t CSR; /*!< BEEP Control status register */
}
BEEP_TypeDef;

/** @addtogroup BEEP_Registers_Reset_Value
  * @{
  */

#define BEEP_CSR_RESET_VALUE ((uint8_t)0x1F)

/**
  * @}
  */

/** @addtogroup BEEP_Registers_Bits_Definition
  * @{
  */

#define BEEP_CSR_BEEPSEL ((uint8_t)0xC0) /*!< Beeper frequency selection mask */
#define BEEP_CSR_BEEPEN  ((uint8_t)0x20) /*!< Beeper enable mask */
#define BEEP_CSR_BEEPDIV ((uint8_t)0x1F) /*!< Beeper Divider prescalar mask */

/**
  * @}
  */

/*----------------------------------------------------------------------------ok*/

/**
  * @brief Configuration Registers (CFG)
  */

typedef struct CFG_struct
{
  __IO uint8_t GCR; /*!< Global Configuration register */
}
CFG_TypeDef;

/** @addtogroup CFG_Registers_Reset_Value
  * @{
  */

#define CFG_GCR_RESET_VALUE ((uint8_t)0x00)

/**
  * @}
  */

/** @addtogroup CFG_Registers_Bits_Definition
  * @{
  */

#define CFG_GCR_SWD ((uint8_t)0x01) /*!< Swim disable bit mask */
#define CFG_GCR_AL  ((uint8_t)0x02) /*!< Activation Level bit mask */

/**
  * @}
  */

/**
  * @}
  */

/*----------------------------------------------------------------------------ok*/

/**
  * @brief Clock Controller (CLK)
  */
typedef struct CLK_struct
{
  __IO uint8_t CKDIVR;      /*!< Clock Divider Register */
  uint8_t RESERVED1;
  uint8_t RESERVED2;
  __IO uint8_t PCKENR1;     /*!< Peripheral Clock Gating Register  */
  __IO uint8_t PCKENR2;     /*!< Peripheral Clock Gating Register  */
  __IO uint8_t CCOR;       /*!< Configurable Clock Output Register */
}
CLK_TypeDef;

/** @addtogroup CLK_Registers_Reset_Value
  * @{
  */
#define CLK_CKDIVR_RESET_VALUE      ((uint8_t)0x03)
#define CLK_PCKENR1_RESET_VALUE     ((uint8_t)0x00)
#define CLK_PCKENR2_RESET_VALUE     ((uint8_t)0x01)
#define CLK_CCOR_RESET_VALUE        ((uint8_t)0x00)
/**
  * @}
  */

/** @addtogroup CLK_Registers_Bits_Definition
  * @{
  */

#define CLK_CKDIVR_HSIDIV  ((uint8_t)0x03) /*!< clock prescaler */

#define CLK_PCKENR1_TIM2  ((uint8_t)0x01) /*!< Peripheral Clock Enable 1, TIM2 */
#define CLK_PCKENR1_TIM3  ((uint8_t)0x02) /*!< Peripheral Clock Enable 1, TIM3 */
#define CLK_PCKENR1_TIM4  ((uint8_t)0x04) /*!< Peripheral Clock Enable 1, TIM4 */
#define CLK_PCKENR1_I2C   ((uint8_t)0x08) /*!< Peripheral Clock Enable 1, I2C */
#define CLK_PCKENR1_SPI   ((uint8_t)0x10) /*!< Peripheral Clock Enable 1, SPI */
#define CLK_PCKENR1_USART ((uint8_t)0x20) /*!< Peripheral Clock Enable 1, USART */
#define CLK_PCKENR1_AWU   ((uint8_t)0x40) /*!< Peripheral Clock Enable 1, AWU */
#define CLK_PCKENR1_PXS   ((uint8_t)0x80) /*!< Peripheral Clock Enable 1, PXS */

#define CLK_PCKENR2_WWDG  ((uint8_t)0x01) /*!< Peripheral Clock Enable 1, WWDG */

#define CLK_CCOR_CCOSLP    ((uint8_t)0x30) /*!< Configurable clock output slope */
#define CLK_CCOR_CCOSEL    ((uint8_t)0x06) /*!< Configurable clock output selection */
#define CLK_CCOR_CCOEN     ((uint8_t)0x01) /*!< Configurable clock output enable */

/**
  * @}
  */
/*----------------------------------------------------------------------------ok*/


/**
  * @brief External Interrupt Controller (EXTI)
  */
typedef struct EXTI_struct
{
  __IO uint8_t CR1;  /*!<  The four LSB EXTI  pin sensitivity */
  __IO uint8_t CR2;  /*!<  The four MSB EXTI  pin sensitivity */
  __IO uint8_t CR3;  /*!<  EXTI port B & port D sensitivity */
  __IO uint8_t SR1;  /*!<  Pins Status flag register 1 */
  __IO uint8_t SR2;  /*!<  Ports Status flage register 2 */
  __IO uint8_t CONF; /*!<  Port interrupt selector */
}
EXTI_TypeDef;

/** @addtogroup EXTI_Registers_Reset_Value
  * @{
  */

#define EXTI_CR1_RESET_VALUE ((uint8_t)0x00)
#define EXTI_CR2_RESET_VALUE ((uint8_t)0x00)
#define EXTI_CR3_RESET_VALUE ((uint8_t)0x00)
#define EXTI_CONF_RESET_VALUE ((uint8_t)0x00)
#define EXTI_SR1_RESET_VALUE ((uint8_t)0x00)
#define EXTI_SR2_RESET_VALUE ((uint8_t)0x00)

/**
  * @}
  */

/** @addtogroup EXTI_Registers_Bits_Definition
  * @{
  */
/* CR1 */
#define EXTI_CR1_P3IS ((uint8_t)0xC0) /*!< EXTI Pin 3 external interrupt sensitivity bit Mask */
#define EXTI_CR1_P2IS ((uint8_t)0x30) /*!< EXTI Pin 2 external interrupt sensitivity bit Mask */
#define EXTI_CR1_P1IS ((uint8_t)0x0C) /*!< EXTI Pin 1  external interrupt sensitivity bit Mask */
#define EXTI_CR1_P0IS ((uint8_t)0x03) /*!< EXTI Pin 0 external interrupt sensitivity bit Mask */

/* CR2 */
#define EXTI_CR2_P7IS ((uint8_t)0xC0) /*!< EXTI Pin 7 external interrupt sensitivity bit Mask */
#define EXTI_CR2_P6IS ((uint8_t)0x30) /*!< EXTI Pin 6 external interrupt sensitivity bit Mask */
#define EXTI_CR2_P5IS ((uint8_t)0x0C) /*!< EXTI Pin 5  external interrupt sensitivity bit Mask */
#define EXTI_CR2_P4IS ((uint8_t)0x03) /*!< EXTI Pin 4 external interrupt sensitivity bit Mask */

/* CR3 */
#define EXTI_CR3_PBIS ((uint8_t)0x03) /*!< EXTI PORTB external interrupt sensitivity bits Mask */
#define EXTI_CR3_PDIS ((uint8_t)0x0C) /*!< EXTI PORTD external interrupt sensitivity bits Mask */

/* CONF */
#define EXTI_CONF_PBL ((uint8_t)0x01) /*!< EXTI PORTB low interrupt selector bit Mask */
#define EXTI_CONF_PBH ((uint8_t)0x02) /*!< EXTI PORTB high interrupt selector bit Mask */
#define EXTI_CONF_PDL ((uint8_t)0x04) /*!< EXTI PORTD low interrupt selector bit Mask */
#define EXTI_CONF_PDH ((uint8_t)0x08) /*!< EXTI PORTD high interrupt selector bit Mask */

/**
  * @}
  */

/*----------------------------------------------------------------------------ok*/

/**
  * @brief FLASH and Data EEPROM
  */
typedef struct FLASH_struct
{
  __IO uint8_t CR1;        /*!< Flash control register 1 */
  __IO uint8_t CR2;        /*!< Flash control register 2 */
  __IO uint8_t PUKR;       /*!< Flash program memory unprotection register */
  __IO uint8_t DUKR;       /*!< Data EEPROM unprotection register */
  __IO uint8_t IAPSR;      /*!< Flash in-application programming status register */
}
FLASH_TypeDef;

/** @addtogroup FLASH_Registers_Reset_Value
  * @{
  */
#define FLASH_CR1_RESET_VALUE   ((uint8_t)0x00)
#define FLASH_CR2_RESET_VALUE   ((uint8_t)0x00)
#define FLASH_PUKR_RESET_VALUE   ((uint8_t)0xAE)
#define FLASH_DUKR_RESET_VALUE   ((uint8_t)0x56)
#define FLASH_IAPSR_RESET_VALUE ((uint8_t)0x40)


/**
  * @}
  */

/** @addtogroup FLASH_Registers_Bits_Definition
  * @{
  */
#define FLASH_CR1_IE             ((uint8_t)0x02) /*!< Flash Interrupt enable Mask */
#define FLASH_CR1_FIX            ((uint8_t)0x01) /*!< Fix programming time Mask */

#define FLASH_CR2_WPRG           ((uint8_t)0x40) /*!< Word write once Mask */
#define FLASH_CR2_ERASE          ((uint8_t)0x20) /*!< Erase block Mask */
#define FLASH_CR2_FPRG           ((uint8_t)0x10) /*!< Fast programming mode Mask */
#define FLASH_CR2_PRG            ((uint8_t)0x01) /*!< Program block Mask */

#define FLASH_IAPSR_HVOFF        ((uint8_t)0x40) /*!< End of high voltage flag Mask */
#define FLASH_IAPSR_DUL          ((uint8_t)0x08) /*!< Data EEPROM unlocked flag Mask */
#define FLASH_IAPSR_EOP          ((uint8_t)0x04) /*!< End of operation flag Mask */
#define FLASH_IAPSR_PUL          ((uint8_t)0x02) /*!< Program memory unlocked flag Mask */
#define FLASH_IAPSR_WR_PG_DIS    ((uint8_t)0x01) /*!< Write attempted to protected page Mask */

#define FLASH_PUKR_PUK ((uint8_t)0xFF) /*!< Flash Program memory unprotection mask */

#define FLASH_DUKR_DUK ((uint8_t)0xFF) /*!< Data EEPROM unprotection mask */

/**
  * @}
  */

/*----------------------------------------------------------------------------*/

/**
  * @brief Inter-Integrated Circuit (I2C)
  */
typedef struct I2C_struct
{
  __IO uint8_t CR1;    /*!< I2C control register 1 */
  __IO uint8_t CR2;    /*!< I2C control register 2 */
  __IO uint8_t FREQR;  /*!< I2C frequency register */
  __IO uint8_t OAR1L;  /*!< I2C own address register 1 LSB */
  __IO uint8_t OAR1H;  /*!< I2C own address register 1 MSB */
  __IO uint8_t OAR2;   /*!< I2C own address register 2 */
  __IO uint8_t DR;     /*!< I2C data register */
  __IO uint8_t SR1;    /*!< I2C status register 1 */
  __IO uint8_t SR2;    /*!< I2C status register 2 */
  __IO uint8_t SR3;    /*!< I2C status register 3 */
  __IO uint8_t ITR;    /*!< I2C interrupt register */
  __IO uint8_t CCRL;   /*!< I2C clock control register low */
  __IO uint8_t CCRH;   /*!< I2C clock control register high */
  __IO uint8_t TRISER; /*!< I2C maximum rise time register */
}
I2C_TypeDef;

/** @addtogroup I2C_Registers_Reset_Value
  * @{
  */
#define I2C_CR1_RESET_VALUE    ((uint8_t)0x00)
#define I2C_CR2_RESET_VALUE    ((uint8_t)0x00)
#define I2C_FREQR_RESET_VALUE  ((uint8_t)0x00)
#define I2C_OAR1L_RESET_VALUE  ((uint8_t)0x00)
#define I2C_OAR1H_RESET_VALUE  ((uint8_t)0x00)
#define I2C_OAR2_RESET_VALUE   ((uint8_t)0x00)
#define I2C_DR_RESET_VALUE     ((uint8_t)0x00)
#define I2C_SR1_RESET_VALUE    ((uint8_t)0x00)
#define I2C_SR2_RESET_VALUE    ((uint8_t)0x00)
#define I2C_SR3_RESET_VALUE    ((uint8_t)0x00)
#define I2C_ITR_RESET_VALUE    ((uint8_t)0x00)
#define I2C_CCRL_RESET_VALUE   ((uint8_t)0x00)
#define I2C_CCRH_RESET_VALUE   ((uint8_t)0x00)
#define I2C_TRISER_RESET_VALUE ((uint8_t)0x02)

/**
  * @}
  */

/** @addtogroup I2C_Registers_Bits_Definition
  * @{
  */

#define I2C_CR1_NOSTRETCH ((uint8_t)0x80) /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_ENGC      ((uint8_t)0x40) /*!< General Call Enable */
#define I2C_CR1_PE        ((uint8_t)0x01) /*!< Peripheral Enable */

#define I2C_CR2_SWRST ((uint8_t)0x80) /*!< Software Reset */
#define I2C_CR2_POS   ((uint8_t)0x08) /*!< Acknowledge */
#define I2C_CR2_ACK   ((uint8_t)0x04) /*!< Acknowledge Enable */
#define I2C_CR2_STOP  ((uint8_t)0x02) /*!< Stop Generation */
#define I2C_CR2_START ((uint8_t)0x01) /*!< Start Generation */

#define I2C_FREQR_FREQ ((uint8_t)0x3F) /*!< Peripheral Clock Frequency */

#define I2C_OAR1L_ADD  ((uint8_t)0xFE) /*!< Interface Address 1 bits [7..1] */
#define I2C_OAR1L_ADD0 ((uint8_t)0x01) /*!< Interface Address 1 bit0 */

#define I2C_OAR1H_ADDMODE ((uint8_t)0x80) /*!< Addressing Mode (Slave mode) */
#define I2C_OAR1H_ADDCONF ((uint8_t)0x40) /*!< Address mode configuration */
#define I2C_OAR1H_ADD     ((uint8_t)0x06) /*!< Interface Address 1 bits [9..8] */

#define I2C_OAR2_ADD     ((uint8_t)0xFE) /*!< Interface Address 2 bits [7..1] */
#define I2C_OAR2_ENDUAL  ((uint8_t)0x01) /*!< Dual Addressing Enable */



#define I2C_DR_DR ((uint8_t)0xFF) /*!< Data Register */

#define I2C_SR1_TXE   ((uint8_t)0x80) /*!< Data Register Empty (transmitters) */
#define I2C_SR1_RXNE  ((uint8_t)0x40) /*!< Data Register not Empty (receivers) */
#define I2C_SR1_STOPF ((uint8_t)0x10) /*!< Stop detection (Slave mode) */
#define I2C_SR1_ADD10 ((uint8_t)0x08) /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_BTF   ((uint8_t)0x04) /*!< Byte Transfer Finished */
#define I2C_SR1_ADDR  ((uint8_t)0x02) /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_SB    ((uint8_t)0x01) /*!< Start Bit (Master mode) */

#define I2C_SR2_WUFH    ((uint8_t)0x20) /*!< Wake-up from Halt */
#define I2C_SR2_OVR     ((uint8_t)0x08) /*!< Overrun/Underrun */
#define I2C_SR2_AF      ((uint8_t)0x04) /*!< Acknowledge Failure */
#define I2C_SR2_ARLO    ((uint8_t)0x02) /*!< Arbitration Lost (master mode) */
#define I2C_SR2_BERR    ((uint8_t)0x01) /*!< Bus Error */

#define I2C_SR3_GENCALL ((uint8_t)0x10) /*!< General Call Header (Slave mode) */
#define I2C_SR3_TRA     ((uint8_t)0x04) /*!< Transmitter/Receiver */
#define I2C_SR3_BUSY    ((uint8_t)0x02) /*!< Bus Busy */
#define I2C_SR3_MSL     ((uint8_t)0x01) /*!< Master/Slave */

#define I2C_ITR_ITBUFEN ((uint8_t)0x04) /*!< Buffer Interrupt Enable */
#define I2C_ITR_ITEVTEN ((uint8_t)0x02) /*!< Event Interrupt Enable */
#define I2C_ITR_ITERREN ((uint8_t)0x01) /*!< Error Interrupt Enable */

#define I2C_CCRL_CCR ((uint8_t)0xFF) /*!< Clock Control Register (Master mode) */

#define I2C_CCRH_FS   ((uint8_t)0x80) /*!< Master Mode Selection */
#define I2C_CCRH_DUTY ((uint8_t)0x40) /*!< Fast Mode Duty Cycle */
#define I2C_CCRH_CCR  ((uint8_t)0x0F) /*!< Clock Control Register in Fast/Standard mode (Master mode) bits [11..8] */

#define I2C_TRISER_TRISE ((uint8_t)0x3F) /*!< Maximum Rise Time in Fast/Standard mode (Master mode) */

/**
  * @}
  */

/*----------------------------------------------------------------------------*/


/**
  * @brief Interrupt Controller (ITC)
  */
typedef struct ITC_struct
{
  __IO uint8_t ISPR1; /*!<  Interrupt Software Priority register 1 */
  __IO uint8_t ISPR2; /*!<  Interrupt Software Priority register 2 */
  __IO uint8_t ISPR3; /*!<  Interrupt Software Priority register 3 */
  __IO uint8_t ISPR4; /*!<  Interrupt Software Priority register 4 */
  __IO uint8_t ISPR5; /*!<  Interrupt Software Priority register 5 */
  __IO uint8_t ISPR6; /*!<  Interrupt Software Priority register 6 */
  __IO uint8_t ISPR7; /*!<  Interrupt Software Priority register 7 */
  __IO uint8_t ISPR8; /*!< Interrupt Software Priority register 8 */
}
ITC_TypeDef;

/** @addtogroup ITC_Registers_Reset_Value
  * @{
  */
#define ITC_SPR1_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 1 */
#define ITC_SPR2_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 2 */
#define ITC_SPR3_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 3 */
#define ITC_SPR4_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 4 */
#define ITC_SPR5_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 5 */
#define ITC_SPR6_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 6 */
#define ITC_SPR7_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 7 */
#define ITC_SPR8_RESET_VALUE ((uint8_t)0xFF) /*!< Reset value of Software Priority registers 8 */
/**
  * @}
  */

/*----------------------------------------------------------------------------*/

/**
  * @brief Internal Low Speed Watchdog (IWDG)
  */
typedef struct IWDG_struct
{
  __IO uint8_t KR;  /*!<  Low Speed Watchdog Key Register */
  __IO uint8_t PR;  /*!<  Low Speed Watchdog Prescaler Register */
  __IO uint8_t RLR; /*!<  Low Speed Watchdog Reload Register */
}
IWDG_TypeDef;

/** @addtogroup IWDG_Registers_Reset_Value
  * @{
  */
#define IWDG_RLR_RESET_VALUE    ((uint8_t)0xFF)  /*! <Reload Register Default Value */
#define IWDG_PR_RESET_VALUE     ((uint8_t)0x00)  /*! <Prescaler Register Default Value */
/**
  * @}
  */

/*----------------------------------------------------------------------------*/

/**
  * @brief Window Watchdog (WWDG)
  */
typedef struct WWDG_struct
{
  __IO uint8_t CR; /*!< Control Register */
  __IO uint8_t WR; /*!< Window Register */
}
WWDG_TypeDef;

/** @addtogroup WWDG_Registers_Reset_Value
  * @{
  */
#define WWDG_CR_RESET_VALUE ((uint8_t)0x7F)
#define WWDG_WR_RESET_VALUE ((uint8_t)0x7F)
/**
* @}
*/

/** @addtogroup WWDG_Registers_Bits_Definition
  * @{
  */
#define WWDG_CR_WDGA ((uint8_t)0x80) /*!< WDGA bit mask */
#define WWDG_CR_T6   ((uint8_t)0x40) /*!< T6 bit mask */
#define WWDG_CR_T    ((uint8_t)0x7F) /*!< T bits mask */

#define WWDG_WR_MSB  ((uint8_t)0x80) /*!< MSB bit mask */
#define WWDG_WR_W    ((uint8_t)0x7F) /*!< W bits mask */
/**
  * @}
  */

/*----------------------------------------------------------------------------*/

/**
  * @brief ProxSense interface (PXS)
  */

typedef struct PXS_struct
{
  __IO uint8_t CR1;   /*!< Control register1  */
  __IO uint8_t CR2;      /*!< Control register2  */
  __IO uint8_t CR3;      /*!< Control register3  */
  uint8_t RESERVED_0x03;
  __IO uint8_t ISR;      /*!< Status register  */

  uint8_t RESERVED_0x05;

  __IO uint8_t CKCR1;      /*!< Clock Control Register 1 */

  __IO uint8_t CKCR2;         /*!< Clock Control Register 1 */

  union
  {
    struct
    {
      __IO uint8_t RXENRH;  /* MSByte of the 16-bit register */
      __IO uint8_t RXENRL;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    RXEN;
#else
    };
#endif
    __IO uint16_t RXENR;          /*!< Receiver Enable Register */
#ifdef _RAISONANCE_
  }
  RXENRegister;
#else
  };
#endif

  union
  {
    struct
    {
      __IO uint8_t RXCR1H;  /* MSByte of the 16-bit register */
      __IO uint8_t RXCR1L;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    RXC1;
#else
    };
#endif
    __IO uint16_t RXCR1;          /*!< Cs / Cx Receiver Control Register 1 */
#ifdef _RAISONANCE_
  }RXC1Register;
#else
  };
#endif


  union
  {
    struct
    {
      __IO uint8_t RXCR2H;  /* MSByte of the 16-bit register */
      __IO uint8_t RXCR2L;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    RXC2;
#else
    };
#endif
    __IO uint16_t RXCR2;          /*!< Cs / Cx Receiver Control Register 2 */
#ifdef _RAISONANCE_
  }RXC2Register;
#else
  };
#endif

  union
  {
    struct
    {
      __IO uint8_t RXCR3H;  /* MSByte of the 16-bit register */
      __IO uint8_t RXCR3L;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    RXC3;
#else
    };
#endif
    __IO uint16_t RXCR3;          /*!< Cs / Cx Receiver Control Register 1 */
#ifdef _RAISONANCE_
  }RXC3Register;
#else
  };
#endif

  uint8_t RESERVED_0x10;
  uint8_t RESERVED_0x11;

  union
  {
    struct
    {
      uint8_t RXINSRH;  /* MSByte of the 16-bit register */
      uint8_t RXINSRL;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    RXINS;
#else
    };
#endif
    uint16_t RXINSR;
#ifdef _RAISONANCE_
  }RXINSRegister;
#else
  };
#endif

  uint8_t RESERVED_0x14;
  uint8_t RESERVED_0x15;

  union
  {
    struct
    {
      uint8_t TXENRH;  /* MSByte of the 16-bit register */
      uint8_t TXENRL;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    TXEN;
#else
    };
#endif
    uint16_t TXENR; /*!< Cx Transmit Enable Register */
#ifdef _RAISONANCE_
  }TXENRegister;
#else
  };
#endif

  uint8_t RESERVED_0x18;
  uint8_t RESERVED_0x19;

  union
  {
    struct
    {
      uint8_t MAXRH;  /* MSByte of the 16-bit register */
      uint8_t MAXRL;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    MAX;
#else
    };
#endif
    uint16_t MAXR; /*!< Maximum Counter Value Register */
#ifdef _RAISONANCE_
  }MAXRegister;
#else
  };
#endif

  union
  {
    struct
    {
      uint8_t MAXENRH;  /* MSByte of the 16-bit register */
      uint8_t MAXENRL;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    MAXEN;
#else
    };
#endif
    uint16_t MAXENR; /*!< Maximum Counter Enable Register */
#ifdef _RAISONANCE_
  }MAXENRegister;
#else
  };
#endif


  union
  {
    struct
    {
      __I uint8_t RXSRH;  /* MSByte of the 16-bit register */
      __I uint8_t RXSRL;  /* LSByte of the 16-bit register */
#ifdef _RAISONANCE_
    }
    RXS;
#else
    };
#endif
    __I uint16_t RXSR;          /*!< Receiver Status  Register */
#ifdef _RAISONANCE_
  }RXSRegister;
#else
  };
#endif
  __IO uint16_t RXCNTR[10];     /*!< receiver Counter Registers */

  uint8_t RESERVED_0x34_0x3F[12];

  __IO uint8_t RXCSSELR[10];     /*!< Cs Size Selection Registers */

  uint8_t RESERVED_0x4A_0x4F[6];

  __IO uint8_t RXEPCCSELR[10];     /*!< EPCC Capacitor Size Selection Registers */

  uint8_t RESERVED_0x5A_0x5F[6];
  uint8_t RESERVED_0x60_0x63[4];

  uint8_t RESERVED_0x64_0x68[5];

  uint8_t RESERVED_0x69;
  uint8_t RESERVED_0x6A_0x6B[2];
}
PXS_TypeDef;

/** @addtogroup PXS_Registers_Reset_Value
  * @{
  */

#define PXS_RX_MAX_CHANNEL_NUMBER ((uint8_t)10)

#define PXS_CR1_RESET_VALUE  ((uint8_t)0x00)
#define PXS_CR2_RESET_VALUE  ((uint8_t)0x07)
#define PXS_CR3_RESET_VALUE  ((uint8_t)0x04)

#define PXS_CRXCR1_RESET_VALUE  ((uint16_t)0x0000)
#define PXS_CRXCR2_RESET_VALUE  ((uint16_t)0x0000)
#define PXS_CRXCR3_RESET_VALUE  ((uint16_t)0x0000)

#define PXS_CKCR1_RESET_VALUE ((uint8_t)0x30) /*!< PXS Clock set to 1MHz */
#define PXS_CKCR2_RESET_VALUE ((uint8_t)0x11) /*!< Up and Pass phase length set to 1 */

#define PXS_RXINSR_RESET_VALUE ((uint16_t) 0x03FF) /*!< All PXS RX driven to VSS*/

#define PXS_RXENR_RESET_VALUE ((uint16_t) 0x0000) /*!< All PXS RX disabled*/

#define PXS_TXENR_RESET_VALUE ((uint16_t) 0x0000) /*!< All PXS TX disabled*/

#define PXS_MAXR_RESET_VALUE ((uint16_t) 0xFFFF) /*!< Maximum PXS Counter value reset value*/

#define PXS_MAXENR_RESET_VALUE ((uint16_t) 0x0000) /*!< Maximum PXS Counter Enable reset value*/

#define PXS_RXCSSELR_RESET_VALUE ((uint8_t) 0x00) /*!<  PXS CS Size reset value */

#define PXS_RXEPCCSELR_RESET_VALUE ((uint8_t) 0x00) /*!<  PXS EPCC Size reset value */


/**
  * @}
  */
/*----------------------------------------------------------------------------*/

/** @addtogroup PXS_Registers_Bits_Definition
  * @{
  */
#define PXS_CR1_PXSEN       ((uint8_t)0x80) /*!< PXS Enable bit in CR1 */
#define PXS_CR1_START       ((uint8_t)0x40) /*!< PXS Start conversion bit in CR1 */
#define PXS_CR1_LOW_POWER   ((uint8_t)0x20) /*!< PXS Low Power bit in CR1 */

#define PXS_CR2_EOCITEN     ((uint8_t)0x80) /*!< PXS End Of Conversion Interrupt Enable bit in CR2 */
#define PXS_CR2_FCCITEN     ((uint8_t)0x40) /*!< PXS First Conversion Completion Interrupt Enable bit in CR2 */
#define PXS_CR2_NOISEDETEN  ((uint8_t)0x20) /*!< PXS Noise Detection Interrupt Enable bit in CR2 */
#define PXS_CR2_RXGROUP     ((uint8_t)0x08) /*!< PXS Group selection bit in CR2 */
#define PXS_CR2_RXCOUPLING  ((uint8_t)0x04) /*!< PXS RX Coupling bit in CR2 */
#define PXS_CR2_SYNCEN      ((uint8_t)0x02) /*!< PXS Synchronization Enable bit in CR2 */
#define PXS_CR2_SYNCEDGE    ((uint8_t)0x01) /*!< PXS Synchronization Edege selection bit in CR2 */
#define PXS_CR3_STAB       ((uint8_t)0xC0) /*!< Mask the Stabilization related bits in CR3 */
#define PXS_CR3_BIAS        ((uint8_t)0x30) /*!< Mask the Bias related bits in CR3 */
#define PXS_CR3_VTHR        ((uint8_t)0x0F) /*!< Mask the Voltage Threshold related bits in CR3 */

#define PXS_ISR_EOCF         ((uint8_t)0x80) /*!< PXS End Of Conversion flag in SR */
#define PXS_ISR_FCCF         ((uint8_t)0x40) /*!< PXS First Conversion Completion flag in SR */
#define PXS_ISR_NOISEDETF    ((uint8_t)0x20) /*!< PXS Noise Detection flag in SR */
#define PXS_ISR_CIPF         ((uint8_t)0x10) /*!< PXS Conversion In Progress flag in SR */
#define PXS_ISR_SYNCPF       ((uint8_t)0x08) /*!< PXS Synchro pending flag in SR */
#define PXS_ISR_SYNCOVRF     ((uint8_t)0x04) /*!< PXS Synchronization Overflow flag in SR */


#define PXS_CKCR1_PRESC      ((uint8_t)0x70) /*!< Mask the Frequency related bits in CKCR1 */
#define PXS_CKCR1_16MHZ     ((uint8_t)0x70) /*!< PXS Clock set to 16MHz  */
#define PXS_CKCR1_8MHZ      ((uint8_t)0x60) /*!< PXS Clock set to 8MHz */
#define PXS_CKCR1_4MHZ      ((uint8_t)0x50) /*!< PXS Clock set to 4MHz */
#define PXS_CKCR1_2MHZ      ((uint8_t)0x40) /*!< PXS Clock set to 2MHz */
#define PXS_CKCR1_1MHZ      ((uint8_t)0x30) /*!< PXS Clock set to 1MHz */
#define PXS_CKCR1_500KHZ    ((uint8_t)0x20) /*!< PXS Clock set to 500 kHz */
#define PXS_CKCR1_250KHZ    ((uint8_t)0x10) /*!< PXS Clock set to 250 kHz */
#define PXS_CKCR1_125KHZ    ((uint8_t)0x00) /*!< PXS Clock set to 125 kHz */

#define PXS_CKCR2_UPLEN     ((uint8_t)0x70) /*!< Mask the Up phase Length related bits in CKCR2 */
#define PXS_CKCR2_PASSLEN   ((uint8_t)0x07) /*!< Mask the Pass phase Length related bits in CKCR2 */



typedef enum {RXGROUPA = (uint8_t)0, RXGROUPB = (uint8_t)!RXGROUPA} RxGroupSelection;
typedef enum {HIGH_BIAS = (uint8_t)0x30, MEDIUM_BIAS = (uint8_t)0x20, LOW_BIAS = (uint8_t)0x10, VERY_LOW_BIAS = (uint8_t)0} BiasSelection;
typedef enum {LONG_STAB = (uint8_t)0, MEDIUM_STAB = (uint8_t)0x40, SHORT_STAB = (uint8_t)0x80} StabSelection;

#define enablePXS()                {PXS->CR1 |= PXS_CR1_PXSEN;}            /*!< Enables the PXS cell*/
#define disablePXS()               {PXS->CR1 &= (uint8_t)~PXS_CR1_PXSEN;}  /*!< Disables the PXS cell*/
#define startPXSAcquisition()      {PXS->CR1 |= PXS_CR1_START;}            /*!< Starts a PXS conversion*/
#define setPXSLowPower()           {PXS->CR1 |= PXS_CR1_LOW_POWER;}        /*!< Enable low power mode*/
#define resetPXSLowPower()         {PXS->CR1 &= (uint8_t)~PXS_CR1_LOW_POWER;} /*!< Enable low power mode*/
#define enablePXSInterrupts(IT)    {PXS->CR2 |= IT;}                       /*!< Enable interrupts */
#define disablePXSInterrupts(IT)   {PXS->CR2 &= (uint8_t)~IT;}             /*!< Disable interrupts */
#define disablePXSAllInterrupts()  {PXS->CR2 &= (uint8_t)~(PXS_CR2_EOCITEN|PXS_CR2_FCCITEN);} /*!<disable interrupts */
#define enablePXSNoiseDetection()  {PXS->CR2 |= PXS_CR2_NOISEDETEN;}       /*!< Enable noise detection */

#define selectPXSRxGroup(RxGroup)      {if (RxGroup)PXS->CR2 |= PXS_CR2_RXGROUP; \
    else PXS->CR2 &= (uint8_t)~PXS_CR2_RXGROUP;} /*!< Select GroupA or GroupB channels */

#define getPXSRxGroup()              (RxGroupSelection)(PXS->CR2 && PXS_CR2_RXGROUP) /*!< Return 0 if Group A is selected and a not null value if GroupB is selected */

#define selectPXSRxGroupA()        {PXS->CR2 &= (uint8_t)~PXS_CR2_RXGROUP;} /*!< Select acquisition on channels A*/
#define selectPXSRxGroupB()        {PXS->CR2 |= PXS_CR2_RXGROUP;}           /*!< Select acquisition on channels B*/
#define enablePXSCoupling()        {PXS->CR2 |= PXS_CR2_RXCOUPLING;}        /*!< Enable coupling between channels i.e. activated RX continue to toggle till the last RX has reached its VTHR */
#define disablePXSCoupling()       {PXS->CR2 &= (uint8_t)~PXS_CR2_RXCOUPLING;} /*!< Disable coupling between channels i.e. activated RX stops once it has reached its VTHR */
#define enablePXSSync()            {PXS->CR2 |= PXS_CR2_SYNCEN;}           /*!< Enable the synchronization feature*/
#define disablePXSSync()           {PXS->CR2 &= (uint8_t)~PXS_CR2_SYNCEN;} /*!< Disable the synchronization feature*/
#define selectPXSSyncRisingEdge()  {PXS->CR2 |= PXS_CR2_SYNCEDGE;}         /*!< Conversion will be started on a rising edge of PXS_TRIG pin*/
#define selectPXSSyncFallingEdge() {PXS->CR2 &= (uint8_t)~PXS_CR2_SYNCEDGE;} /*!< Conversion will be started on a falling edge of PXS_TRIG pin*/
#define setPXSStab(stab)           {PXS->CR3 &= (uint8_t)~PXS_CR3_STAB;PXS->CR3 |= (uint8_t)stab;} /*!< select stabilization delay (the value must be one of the StabSelection enumeration)*/
#define setPXSBias(bias)           {PXS->CR3 &= (uint8_t)~PXS_CR3_BIAS; PXS->CR3 |= (uint8_t)bias;} /*!< select the bias (the value must be one of the BiasSelection enumeration)*/
#define setPXSVthr(nVREG)          {PXS->CR3 = (PXS->CR3 & (uint8_t)~PXS_CR3_VTHR) + (uint8_t)(nVREG-1);}  /*!< nVREG allows to set the threshold to nVREG *0.1Vreg\n NVREG must be between 1 and 9 */

//clearing of the ISR flags must not use a BRES instruction in order to not clear accidentaly another flag, so each flag has its own macro to clear it
#define clearPXS_ISR_EOCF     {PXS->ISR = (uint8_t)0x60;}      /*!< Clear only the status flags PXS_ISR_EOCF  */
#define clearPXS_ISR_FCCF     {PXS->ISR = (uint8_t)0xA0;}      /*!< Clear only the status flags PXS_SR_FCCF */
#define clearPXS_ISR_NOISEDETF     {PXS->ISR = (uint8_t)0xC0;} /*!< Clear only the status flags PXS_SR_NOISEDETF */

#define checkPXSInterruptStatusFlag(FLAG)      (PXS->ISR & FLAG) /*!< Return a null value if the flag to check is not set, else a not null value is return */
#define setPXSRXProjected(RX)      {PXS->RXCR3 |= (uint16_t)RX;PXS->RXCR2 |= (uint16_t)RX;PXS->RXCR1 |= (uint16_t)RX;}      /*!< Configures RXCR3/RXCR2/RXCR1 to set the selected RX as Receiver in projected mode */
#define setPXSTXProjected(RX)      {PXS->RXCR3 |= (uint16_t)RX;PXS->RXCR2 |= (uint16_t)RX;PXS->RXCR1 &= (uint16_t)~RX;} /*!< Configures RXCR3/RXCR2/RXCR1 to set the selected RX as Transmitter in projected mode\n Must be called after the setPXSRXProjected */
#define setPXSInactiveStateToVSS(RX)  {PXS->RXINSR &= ((uint16_t)~RX);} /*!< Configure the selected RX to be driven to VSS when not under acquisition */
#define setPXSInactiveStateToHighZ(RX){PXS->RXINSR |= ((uint16_t)RX);}  /*!< Configure the selected RX to be floating when not under acquisition */

/**
  * @}
  */


/**
  * @brief Wait For Event (WFE) peripheral registers.
  */
/** @addtogroup WFE_Registers
  * @{
  */
typedef struct WFE_struct
{
  __IO uint8_t CR1;   /*!<  Wait for event control register 1 */
  __IO uint8_t CR2;   /*!<  Wait for event control register 2 */
}
WFE_TypeDef;
/**
  * @}
  */
/** @addtogroup WFE_Registers_Reset_Value
  * @{
  */

#define WFE_CR1_RESET_VALUE ((uint8_t)0x00) /*!< Reset value wait for event control register1*/
#define WFE_CR2_RESET_VALUE ((uint8_t)0x00) /*!< Reset value wait for event control register2*/
/**
  * @}
  */

/** @addtogroup WFE_Registers_Bits_Definition
  * @{
  */

#define WFE_CR1_EXTI_EV3     ((uint8_t)0x80) /*!< External interrupt event 3*/
#define WFE_CR1_EXTI_EV2     ((uint8_t)0x40) /*!< External interrupt event 2*/
#define WFE_CR1_EXTI_EV1     ((uint8_t)0x20) /*!< External interrupt event 1*/
#define WFE_CR1_EXTI_EV0     ((uint8_t)0x10) /*!< External interrupt event 0*/
#define WFE_CR1_PXS_EV       ((uint8_t)0x08) /*!< PXS event */
#define WFE_CR1_TIM2_EV1     ((uint8_t)0x02) /*!< TIM2 event 1*/
#define WFE_CR1_TIM2_EV0     ((uint8_t)0x01) /*!< TIM2 event 0*/

#define WFE_CR2_EXTI_EVD     ((uint8_t)0x20) /*!< External interrupt event on Port D*/
#define WFE_CR2_EXTI_EVB     ((uint8_t)0x10) /*!< External interrupt event on Port B*/
#define WFE_CR2_EXTI_EV7     ((uint8_t)0x08) /*!< External interrupt event 7*/
#define WFE_CR2_EXTI_EV6     ((uint8_t)0x04) /*!< External interrupt event 6*/
#define WFE_CR2_EXTI_EV5     ((uint8_t)0x02) /*!< External interrupt event 5*/
#define WFE_CR2_EXTI_EV4     ((uint8_t)0x01) /*!< External interrupt event 4*/

/**
  * @}
  */

/*----------------------------------------------------------------------------*/
/**
  * @brief Option Bytes (OPT)
  */
typedef struct OPT_struct
{
  __IO uint8_t OPT0_LOCKBYTE;   /*!< Option byte 0 */
  __IO uint8_t OPT1_PCODESIZE;  /*!< Option byte 1 */
  __IO uint8_t OPT2_BOOTSIZE;   /*!< Option byte 2 */
  __IO uint8_t OPT3_DATASIZE;   /*!< Option byte 3 */
}
OPT_TypeDef;

/**
  * @}
  */

/*----------------------------------------------------------------------------*/

/**
  * @brief Reset Controller (RST)
  */
typedef struct RST_struct
{
  __IO uint8_t CR;  /*!< Multiplex Reset Pad */
  __IO uint8_t SR;  /*!< Reset status register */

}
RST_TypeDef;
/**
  * @}
  */

/** @addtogroup RST_Registers_Reset_Value
  * @{
  */

#define RST_CR_RESET_VALUE    ((uint8_t)0x00) /*!< Reset pin configuration register  1 reset value */
#define RST_SR_RESET_VALUE    ((uint8_t)0x01) /*!< Reset status register 2 reset value */

/**
  * @}
  */

/** @addtogroup RST_Registers_Bits_Definition
  * @{
  */

#define RST_SR_WWDGF  ((uint8_t)0x10) /*!< Window Watchdog reset flag mask */
#define RST_SR_SWIMF  ((uint8_t)0x08) /*!< SWIM reset flag mask */
#define RST_SR_ILLOPF ((uint8_t)0x04) /*!< Illegal opcode reset flag mask */
#define RST_SR_IWDGF  ((uint8_t)0x02) /*!< Independent Watchdog reset flag mask */
#define RST_SR_PORF   ((uint8_t)0x01) /*!< Power On Reset (POR) flag mask */

/**
  * @}
  */
/*----------------------------------------------------------------------------ok*/

/**
  * @brief Serial Peripheral Interface (SPI)
  */
typedef struct SPI_struct
{
  __IO uint8_t CR1;    /*!< SPI control register 1 */
  __IO uint8_t CR2;    /*!< SPI control register 2 */
  __IO uint8_t ICR;    /*!< SPI interrupt control register */
  __IO uint8_t SR;     /*!< SPI status register */
  __IO uint8_t DR;     /*!< SPI data I/O register */
}
SPI_TypeDef;

/** @addtogroup SPI_Registers_Reset_Value
  * @{
  */

#define SPI_CR1_RESET_VALUE    ((uint8_t)0x00) /*!< Control Register 1 reset value */
#define SPI_CR2_RESET_VALUE    ((uint8_t)0x00) /*!< Control Register 2 reset value */
#define SPI_ICR_RESET_VALUE    ((uint8_t)0x00) /*!< Interrupt Control Register reset value */
#define SPI_SR_RESET_VALUE     ((uint8_t)0x02) /*!< Status Register reset value */
#define SPI_DR_RESET_VALUE     ((uint8_t)0x00) /*!< Data Register reset value */

/**
  * @}
  */

/** @addtogroup SPI_Registers_Bits_Definition
  * @{
  */

#define SPI_CR1_LSBFIRST ((uint8_t)0x80) /*!< Frame format mask */
#define SPI_CR1_SPE      ((uint8_t)0x40) /*!< Enable bits mask */
#define SPI_CR1_BR       ((uint8_t)0x38) /*!< Baud rate control mask */
#define SPI_CR1_MSTR     ((uint8_t)0x04) /*!< Master Selection mask */
#define SPI_CR1_CPOL     ((uint8_t)0x02) /*!< Clock Polarity mask */
#define SPI_CR1_CPHA     ((uint8_t)0x01) /*!< Clock Phase mask */

#define SPI_CR2_BDM     ((uint8_t)0x80) /*!< Bi-directional data mode enable mask */
#define SPI_CR2_BDOE    ((uint8_t)0x40) /*!< Output enable in bi-directional mode mask */
#define SPI_CR2_RXONLY  ((uint8_t)0x04) /*!< Receive only mask */
#define SPI_CR2_SSM     ((uint8_t)0x02) /*!< Software slave management mask */
#define SPI_CR2_SSI     ((uint8_t)0x01) /*!< Internal slave select mask */

#define SPI_ICR_TXIE    ((uint8_t)0x80) /*!< Tx buffer empty interrupt enable mask */
#define SPI_ICR_RXIE    ((uint8_t)0x40) /*!< Rx buffer empty interrupt enable mask */
#define SPI_ICR_ERRIE   ((uint8_t)0x20) /*!< Error interrupt enable mask */
#define SPI_ICR_WKIE    ((uint8_t)0x10) /*!< Wake-up interrupt enable mask */

#define SPI_SR_BSY    ((uint8_t)0x80) /*!< Busy flag */
#define SPI_SR_OVR    ((uint8_t)0x40) /*!< Overrun flag */
#define SPI_SR_MODF   ((uint8_t)0x20) /*!< Mode fault */
#define SPI_SR_WKUP   ((uint8_t)0x08) /*!< Wake-Up flag */
#define SPI_SR_TXE    ((uint8_t)0x02) /*!< Transmit buffer empty */
#define SPI_SR_RXNE   ((uint8_t)0x01) /*!< Receive buffer not empty */

/**
  * @}
  */

/*----------------------------------------------------------------------------ok*/

/**
  * @brief SWIM
  */
typedef struct SWIM_struct
{
  __IO uint8_t CSR; /* Control/Status register  */
  /* uint8_t DR; */  /* Data register */
}
SWIM_TypeDef;

/*----------------------------------------------------------------------------*/

/**
  * @brief 16 bit timer with complementary PWM outputs (TIM2 & TIM3)
  */
typedef struct TIM_struct
{
  __IO uint8_t CR1;  /*!< control register 1   */
  __IO uint8_t CR2;  /*!< control register 2   */
  __IO uint8_t SMCR;  /*!< Synchro mode control register */
  __IO uint8_t ETR;  /*!< external trigger register */
  __IO uint8_t IER;  /*!< interrupt enable register*/
  __IO uint8_t SR1;  /*!< status register 1   */
  __IO uint8_t SR2;  /*!< status register 2   */
  __IO uint8_t EGR;  /*!< event generation register */
  __IO uint8_t CCMR1;  /*!< CC mode register 1      */
  __IO uint8_t CCMR2;  /*!< CC mode register 2      */
  __IO uint8_t CCER1;  /*!< CC enable register 1     */
  __IO uint8_t CNTRH;  /*!< counter high       */
  __IO uint8_t CNTRL;  /*!< counter low       */
  __IO uint8_t PSCR;  /*!< prescaler     */
  __IO uint8_t ARRH;  /*!< auto-reload register high  */
  __IO uint8_t ARRL;  /*!< auto-reload register low    */
  __IO uint8_t CCR1H;  /*!< capture/compare register 1 high   */
  __IO uint8_t CCR1L;  /*!< capture/compare register 1 low     */
  __IO uint8_t CCR2H;  /*!< capture/compare register 2 high   */
  __IO uint8_t CCR2L;  /*!< capture/compare register 2 low     */
  __IO uint8_t BKR;  /*!< Break Register */
  __IO uint8_t OISR;  /*!< Output idle register */
}
TIM_TypeDef;

/** @addtogroup TIM2_TIM3_Registers_Reset_Value
  * @{
  */
#define TIM_CR1_RESET_VALUE  ((uint8_t)0x00)
#define TIM_CR2_RESET_VALUE  ((uint8_t)0x00)
#define TIM_SMCR_RESET_VALUE ((uint8_t)0x00)
#define TIM_ETR_RESET_VALUE  ((uint8_t)0x00)
#define TIM_IER_RESET_VALUE  ((uint8_t)0x00)
#define TIM_SR1_RESET_VALUE  ((uint8_t)0x00)
#define TIM_SR2_RESET_VALUE  ((uint8_t)0x00)
#define TIM_EGR_RESET_VALUE  ((uint8_t)0x00)
#define TIM_CCMR1_RESET_VALUE  ((uint8_t)0x00)
#define TIM_CCMR2_RESET_VALUE  ((uint8_t)0x00)

#define TIM_CCER1_RESET_VALUE  ((uint8_t)0x00)

#define TIM_CNTRH_RESET_VALUE  ((uint8_t)0x00)
#define TIM_CNTRL_RESET_VALUE  ((uint8_t)0x00)

#define TIM_PSCR_RESET_VALUE  ((uint8_t)0x00)
#define TIM_ARRH_RESET_VALUE  ((uint8_t)0xFF)
#define TIM_ARRL_RESET_VALUE  ((uint8_t)0xFF)

#define TIM_CCR1H_RESET_VALUE  ((uint8_t)0x00)
#define TIM_CCR1L_RESET_VALUE  ((uint8_t)0x00)
#define TIM_CCR2H_RESET_VALUE  ((uint8_t)0x00)
#define TIM_CCR2L_RESET_VALUE  ((uint8_t)0x00)

#define TIM_BKR_RESET_VALUE  ((uint8_t)0x00)
#define TIM_OISR_RESET_VALUE  ((uint8_t)0x00)

/**
  * @}
  */

/** @addtogroup TIM2_TIM3_Registers_Bits_Definition
  * @{
  */
/* CR1*/
#define TIM_CR1_ARPE    ((uint8_t)0x80) /*!< Auto-Reload Preload Enable Mask. */
#define TIM_CR1_CMS     ((uint8_t)0x60) /*!< Center-aligned Mode Selection Mask. */
#define TIM_CR1_DIR     ((uint8_t)0x10) /*!< Direction Mask. */
#define TIM_CR1_OPM     ((uint8_t)0x08) /*!< One Pulse Mode Mask. */
#define TIM_CR1_URS     ((uint8_t)0x04) /*!< Update Request Source Mask. */
#define TIM_CR1_UDIS    ((uint8_t)0x02) /*!< Update DIsable Mask. */
#define TIM_CR1_CEN     ((uint8_t)0x01) /*!< Counter Enable Mask. */

/* CR2*/
#define TIM_CR2_TI1S    ((uint8_t)0x80) /*!< TI1S Selection Mask. */
#define TIM_CR2_MMS     ((uint8_t)0x70) /*!< MMS Selection Mask. */

/* SMCR*/
#define TIM_SMCR_MSM    ((uint8_t)0x80) /*!< Master/Slave Mode Mask. */
#define TIM_SMCR_TS     ((uint8_t)0x70) /*!< Trigger Selection Mask. */
#define TIM_SMCR_SMS    ((uint8_t)0x07) /*!< Slave Mode Selection Mask. */


/* ETR*/
#define TIM_ETR_ECE     ((uint8_t)0x40)/*!< External Clock Mask. */
#define TIM_ETR_ETP     ((uint8_t)0x80) /*!< External Trigger Polarity Mask. */
#define TIM_ETR_ETPS    ((uint8_t)0x30) /*!< External Trigger Prescaler Mask. */
#define TIM_ETR_ETF     ((uint8_t)0x0F) /*!< External Trigger Filter Mask. */


/* IER*/
#define TIM_IER_BIE     ((uint8_t)0x80) /*!< Break Interrupt Enable Mask. */
#define TIM_IER_TIE     ((uint8_t)0x40) /*!< Trigger Interrupt Enable Mask. */
#define TIM_IER_CC2IE   ((uint8_t)0x04) /*!< Capture/Compare 2 Interrupt Enable Mask. */
#define TIM_IER_CC1IE   ((uint8_t)0x02) /*!< Capture/Compare 1 Interrupt Enable Mask. */
#define TIM_IER_UIE     ((uint8_t)0x01) /*!< Update Interrupt Enable Mask. */

/* SR1*/
#define TIM_SR1_BIF     ((uint8_t)0x80) /*!< Break Interrupt Flag Mask. */
#define TIM_SR1_TIF     ((uint8_t)0x40) /*!< Trigger Interrupt Flag Mask. */
#define TIM_SR1_CC2IF   ((uint8_t)0x04) /*!< Capture/Compare 2 Interrupt Flag Mask. */
#define TIM_SR1_CC1IF   ((uint8_t)0x02) /*!< Capture/Compare 1 Interrupt Flag Mask. */
#define TIM_SR1_UIF     ((uint8_t)0x01) /*!< Update Interrupt Flag Mask. */

/* SR2*/
#define TIM_SR2_CC2OF   ((uint8_t)0x04) /*!< Capture/Compare 2 Overcapture Flag Mask. */
#define TIM_SR2_CC1OF   ((uint8_t)0x02) /*!< Capture/Compare 1 Overcapture Flag Mask. */

/*EGR*/
#define TIM_EGR_BG      ((uint8_t)0x80) /*!< Break Generation Mask. */
#define TIM_EGR_TG      ((uint8_t)0x40) /*!< Trigger Generation Mask. */
#define TIM_EGR_CC2G    ((uint8_t)0x04) /*!< Capture/Compare 2 Generation Mask. */
#define TIM_EGR_CC1G    ((uint8_t)0x02) /*!< Capture/Compare 1 Generation Mask. */
#define TIM_EGR_UG      ((uint8_t)0x01) /*!< Update Generation Mask. */

/*CCMR*/
#define TIM_CCMR_ICxPSC          ((uint8_t)0x0C) /*!< Input Capture x Prescaler Mask. */
#define TIM_CCMR_ICxF            ((uint8_t)0xF0) /*!< Input Capture x Filter Mask. */
#define TIM_CCMR_OCM             ((uint8_t)0x70) /*!< Output Compare x Mode Mask. */
#define TIM_CCMR_OCxPE         ((uint8_t)0x08) /*!< Output Compare x Preload Enable Mask. */
#define TIM_CCMR_OCxFE          ((uint8_t)0x04) /*!< Output Compare x Fast Enable Mask. */
#define TIM_CCMR_CCxS            ((uint8_t)0x03) /*!< Capture/Compare x Selection Mask. */
#define TIM_CCMR_TIxDirect_Set   ((uint8_t)0x01)

/*CCER1*/
#define TIM_CCER1_CC2P  ((uint8_t)0x20) /*!< Capture/Compare 2 output Polarity Mask. */
#define TIM_CCER1_CC2E  ((uint8_t)0x10) /*!< Capture/Compare 2 output enable Mask. */
#define TIM_CCER1_CC1P  ((uint8_t)0x02) /*!< Capture/Compare 1 output Polarity Mask. */
#define TIM_CCER1_CC1E  ((uint8_t)0x01) /*!< Capture/Compare 1 output enable Mask. */

/*CNTR*/
#define TIM_CNTRH_CNT   ((uint8_t)0xFF) /*!< Counter Value (MSB) Mask. */
#define TIM_CNTRL_CNT   ((uint8_t)0xFF) /*!< Counter Value (LSB) Mask. */

/*PSCR*/
#define TIM_PSC_PSC     ((uint8_t)0x03) /*!< Prescaler Value  Mask. */

/*ARR*/
#define TIM_ARRH_ARR    ((uint8_t)0xFF) /*!< Autoreload Value (MSB) Mask. */
#define TIM_ARRL_ARR    ((uint8_t)0xFF) /*!< Autoreload Value (LSB) Mask. */


/*CCR1*/
#define TIM_CCR1H_CCR1  ((uint8_t)0xFF) /*!< Capture/Compare 1 Value (MSB) Mask. */
#define TIM_CCR1L_CCR1  ((uint8_t)0xFF) /*!< Capture/Compare 1 Value (LSB) Mask. */

/*CCR2*/
#define TIM_CCR2H_CCR2  ((uint8_t)0xFF) /*!< Capture/Compare 2 Value (MSB) Mask. */
#define TIM_CCR2L_CCR2  ((uint8_t)0xFF) /*!< Capture/Compare 2 Value (LSB) Mask. */


/*BKR*/
#define TIM_BKR_MOE     ((uint8_t)0x80) /*!< Main Output Enable Mask. */
#define TIM_BKR_AOE     ((uint8_t)0x40) /*!< Automatic Output Enable Mask. */
#define TIM_BKR_BKP     ((uint8_t)0x20) /*!< Break Polarity Mask. */
#define TIM_BKR_BKE     ((uint8_t)0x10) /*!< Break Enable Mask. */
#define TIM_BKR_OSSI    ((uint8_t)0x04) /*!< Off-State Selection for Idle mode Mask. */
#define TIM_BKR_LOCK    ((uint8_t)0x03) /*!<Lock Configuration Mask. */

/*OISR*/
#define TIM_OISR_OIS2   ((uint8_t)0x04) /*!< Output Idle state 2 (OC2 output) Mask. */
#define TIM_OISR_OIS1   ((uint8_t)0x01) /*!< Output Idle state 1 (OC1 output) Mask. */

/**
  * @}
  */


/*----------------------------------------------------------------------------*/

/**
  * @brief 8-bit system or Low End Small Timer (TIM4)
  */
typedef struct TIM4_struct
{
  __IO uint8_t CR1;  /*!< control register 1 */
  __IO uint8_t CR2;  /*!< control register 2 */
  __IO uint8_t SMCR;  /*!< Synchro mode control register */
  __IO uint8_t IER;  /*!< interrupt enable register  */
  __IO uint8_t SR1;  /*!< status register 1    */
  __IO uint8_t EGR;  /*!< event generation register */
  __IO uint8_t CNTR;  /*!< counter register  */
  __IO uint8_t PSCR;  /*!< prescaler register */
  __IO uint8_t ARR;  /*!< auto-reload register */
}
TIM4_TypeDef;
/** @addtogroup TIM4_Registers_Reset_Value
  * @{
  */
#define TIM4_CR1_RESET_VALUE    ((uint8_t)0x00)
#define TIM4_CR2_RESET_VALUE    ((uint8_t)0x00)
#define TIM4_SMCR_RESET_VALUE   ((uint8_t)0x00)
#define TIM4_IER_RESET_VALUE    ((uint8_t)0x00)
#define TIM4_SR1_RESET_VALUE    ((uint8_t)0x00)
#define TIM4_EGR_RESET_VALUE    ((uint8_t)0x00)
#define TIM4_CNTR_RESET_VALUE   ((uint8_t)0x00)
#define TIM4_PSCR_RESET_VALUE   ((uint8_t)0x00)
#define TIM4_ARR_RESET_VALUE    ((uint8_t)0xFF)

/**
* @}
*/

/** @addtogroup TIM4_Registers_Bits_Definition
  * @{
  */
/* CR1*/
#define TIM4_CR1_ARPE     ((uint8_t)0x80) /*!< Auto-Reload Preload Enable Mask. */
#define TIM4_CR1_OPM      ((uint8_t)0x08) /*!< One Pulse Mode Mask. */
#define TIM4_CR1_URS      ((uint8_t)0x04) /*!< Update Request Source Mask. */
#define TIM4_CR1_UDIS     ((uint8_t)0x02) /*!< Update DIsable Mask. */
#define TIM4_CR1_CEN      ((uint8_t)0x01) /*!< Counter Enable Mask. */

/* CR2*/
#define TIM4_CR2_MMS   ((uint8_t)0x70) /*!< MMS Selection Mask. */

/* SMCR*/
#define TIM4_SMCR_TS       ((uint8_t)0x70) /*!< Trigger Selection Mask. */
#define TIM4_SMCR_SMS      ((uint8_t)0x07) /*!< Slave Mode Selection Mask. */
#define TIM4_SMCR_MSM      ((uint8_t)0x80) /*!< Master/Slave Mode Mask. */

/* IER*/
#define TIM4_IER_TIE       ((uint8_t)0x40) /*!< Trigger Interrupt Enable Mask. */
#define TIM4_IER_UIE       ((uint8_t)0x01) /*!< Update Interrupt Enable Mask. */

/* SR1*/
#define TIM4_SR1_TIF       ((uint8_t)0x40) /*!< Trigger Interrupt Flag Mask. */
#define TIM4_SR1_UIF       ((uint8_t)0x01) /*!< Update Interrupt Flag Mask. */

/* EGR*/
#define TIM4_EGR_TG        ((uint8_t)0x40) /*!< Trigger Generation Mask. */
#define TIM4_EGR_UG        ((uint8_t)0x01) /*!< Update Generation Mask. */

/* CNTR*/
#define TIM4_CNTR_CNT      ((uint8_t)0xFF) /*!<Counter Value (LSB) Mask. */

/* PSCR*/
#define TIM4_PSCR_PSC      ((uint8_t)0x0F) /*!<Prescaler Value  Mask. */

/* ARR*/
#define TIM4_ARR_ARR     ((uint8_t)0xFF) /*!<Autoreload Value Mask. */
/**
  * @}
  */

/*----------------------------------------------------------------------------*/

/**
  * @brief USART
  */
typedef struct USART_struct
{
  __IO uint8_t SR;  /*!<  USART status register  */
  __IO uint8_t DR;  /*!<  USART data register     */
  __IO uint8_t BRR1;  /*!<  USART baud rate register   */
  __IO uint8_t BRR2;  /*!<  USART DIV mantissa[11:8] SCIDIV fraction */
  __IO uint8_t CR1;  /*!<  USART control register 1     */
  __IO uint8_t CR2;  /*!<  USART control register 2     */
  __IO uint8_t CR3;  /*!<  USART control register 3      */
  __IO uint8_t CR4;  /*!< USART control register 4      */
  __IO uint8_t CR5;  /*!<  USART control register 5       */
  __IO uint8_t GTR;  /*!<  USART guard time register     */
  __IO uint8_t PSCR;  /*!<  USART prescaler register     */
}
USART_TypeDef;


/** @addtogroup USART_Registers_Reset_Value
  * @{
  */
#define USART_SR_RESET_VALUE ((uint8_t)0xC0)
#define USART_BRR1_RESET_VALUE ((uint8_t)0x00)
#define USART_BRR2_RESET_VALUE ((uint8_t)0x00)
#define USART_CR1_RESET_VALUE ((uint8_t)0x00)
#define USART_CR2_RESET_VALUE ((uint8_t)0x00)
#define USART_CR3_RESET_VALUE ((uint8_t)0x00)
#define USART_CR4_RESET_VALUE ((uint8_t)0x00)

/**
  * @}
  */

/** @addtogroup USART_Registers_Bits_Definition
  * @{
  */
#define USART_SR_TXE      ((uint8_t)0x80) /*!< Transmit Data Register Empty Mask         */
#define USART_SR_TC       ((uint8_t)0x40) /*!< Transmission Complete Mask                */
#define USART_SR_RXNE     ((uint8_t)0x20) /*!< Read Data Register Not Empty Mask         */
#define USART_SR_IDLE     ((uint8_t)0x10) /*!< IDLE line detected Mask                   */
#define USART_SR_OR       ((uint8_t)0x08) /*!< OverRun error Mask                        */
#define USART_SR_NF       ((uint8_t)0x04) /*!< Noise Flag Mask                           */
#define USART_SR_FE       ((uint8_t)0x02) /*!< Framing Error Mask                        */
#define USART_SR_PE       ((uint8_t)0x01) /*!< Parity Error Mask                         */
#define USART_BRR1_DIVM   ((uint8_t)0xFF) /*!< LSB mantissa of USARTDIV [7:0] Mask       */
#define USART_BRR2_DIVM   ((uint8_t)0xF0) /*!< MSB mantissa of USARTDIV [11:8] Mask      */
#define USART_BRR2_DIVF   ((uint8_t)0x0F) /*!< Fraction bits of USARTDIV [3:0] Mask      */
#define USART_CR1_R8      ((uint8_t)0x80) /*!< Receive Data bit 8                        */
#define USART_CR1_T8      ((uint8_t)0x40) /*!< Transmit data bit 8                       */
#define USART_CR1_USARTD ((uint8_t)0x20)  /*!< USART Disable (for low power consumption) */
#define USART_CR1_M       ((uint8_t)0x10) /*!< Word length Mask                          */
#define USART_CR1_WAKE    ((uint8_t)0x08) /*!< Wake-up method Mask                       */
#define USART_CR1_PCEN    ((uint8_t)0x04) /*!< Parity Control Enable Mask                */
#define USART_CR1_PS      ((uint8_t)0x02) /*!< USART Parity Selection                 */
#define USART_CR1_PIEN    ((uint8_t)0x01) /*!< USART Parity Interrupt Enable Mask        */
#define USART_CR2_TIEN    ((uint8_t)0x80) /*!< Transmitter Interrupt Enable Mask         */
#define USART_CR2_TCIEN   ((uint8_t)0x40) /*!< TransmissionComplete Interrupt Enable Mask*/
#define USART_CR2_RIEN    ((uint8_t)0x20) /*!< Receiver Interrupt Enable Mask            */
#define USART_CR2_ILIEN   ((uint8_t)0x10) /*!< IDLE Line Interrupt Enable Mask           */
#define USART_CR2_TEN     ((uint8_t)0x08) /*!< Transmitter Enable Mask                   */
#define USART_CR2_REN     ((uint8_t)0x04) /*!< Receiver Enable Mask                      */
#define USART_CR2_RWU     ((uint8_t)0x02) /*!< Receiver Wake-Up Mask                     */
#define USART_CR2_SBK     ((uint8_t)0x01) /*!< Send Break Mask                     */
#define USART_CR3_Reserved ((uint8_t)0x80) /*!< RESERVED bit Mask                        */
#define USART_CR3_STOP    ((uint8_t)0x30) /*!< STOP bits [1:0] Mask                      */
#define USART_CR3_CLKEN   ((uint8_t)0x08) /*!< Clock Enable Mask                         */
#define USART_CR3_CPOL    ((uint8_t)0x04) /*!< Clock Polarity Mask                       */
#define USART_CR3_CPHA    ((uint8_t)0x02) /*!< Clock Phase Mask                          */
#define USART_CR3_LBCL    ((uint8_t)0x01) /*!< Last Bit Clock pulse Mask                 */
#define USART_CR4_Reserved ((uint8_t)0x80) /*!< RESERVED bit Mask                        */
#define USART_CR4_ADD     ((uint8_t)0x0F) /*!< Address of the USART node Mask            */
/**
  * @}
  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                          Peripherals Base Address                          */
/******************************************************************************/


#define GPIOA_BaseAddress       0x5000
#define GPIOB_BaseAddress       0x5005
#define GPIOD_BaseAddress       0x500F

#define FLASH_BaseAddress       0x5050

#define USART_BaseAddress       0x5230

#define TIM2_BaseAddress        0x5250
#define TIM3_BaseAddress        0x5280
#define TIM4_BaseAddress        0x52E0

#define PXS_BaseAddress        0x5300

#define SWIM_BaseAddress        0x7F80

#define EXTI_BaseAddress        0x50A0

#define WFE_BaseAddress         0x50A6

#define RST_BaseAddress         0x50B0

#define CLK_BaseAddress         0x50C0

#define WWDG_BaseAddress        0x50D3

#define IWDG_BaseAddress        0x50E0

#define AWU_BaseAddress         0x50F0

#define BEEP_BaseAddress        0x50F3

#define SPI_BaseAddress         0x5200

#define I2C_BaseAddress         0x5210

#define OPT_BaseAddress         0x4800

#define CFG_BaseAddress         0x7F60

#define ITC_BaseAddress         0x7F70

#define DM_BaseAddress          0x7F90

/******************************************************************************/
/*                          Peripherals declarations                          */
/******************************************************************************/


#define GPIOA ((GPIO_TypeDef *) GPIOA_BaseAddress)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BaseAddress)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BaseAddress)
#define FLASH ((FLASH_TypeDef *) FLASH_BaseAddress)
#define EXTI ((EXTI_TypeDef *) EXTI_BaseAddress)
#define RST ((RST_TypeDef *) RST_BaseAddress)
#define CLK ((CLK_TypeDef *) CLK_BaseAddress)
#define WWDG ((WWDG_TypeDef *) WWDG_BaseAddress)
#define IWDG ((IWDG_TypeDef *) IWDG_BaseAddress)
#define WFE ((WFE_TypeDef *) WFE_BaseAddress)
#define AWU ((AWU_TypeDef *) AWU_BaseAddress)
#define BEEP ((BEEP_TypeDef *) BEEP_BaseAddress)
#define SPI ((SPI_TypeDef *) SPI_BaseAddress)
#define I2C ((I2C_TypeDef *) I2C_BaseAddress)
#define USART ((USART_TypeDef *) USART_BaseAddress)
#define TIM2 ((TIM_TypeDef *) TIM2_BaseAddress)
#define TIM3 ((TIM_TypeDef *) TIM3_BaseAddress)
#define TIM4 ((TIM4_TypeDef *) TIM4_BaseAddress)
#define ITC ((ITC_TypeDef *) ITC_BaseAddress)
#define CFG ((CFG_TypeDef *) CFG_BaseAddress)
#define SWIM ((SWIM_TypeDef *) SWIM_BaseAddress)
#define DM ((DM_TypeDef *) DM_BaseAddress)
#define PXS ((PXS_TypeDef *) PXS_BaseAddress)
#define OPT ((OPT_TypeDef *) OPT_BaseAddress)



#ifdef USE_STDPERIPH_DRIVER
#include "stm8tl5x_conf.h"
#endif

/* Exported macro --------------------------------------------------------------*/

/*============================== Interrupts ====================================*/
#if defined(_RAISONANCE_)
#include <intrins.h>
#define enableInterrupts()  _rim_()  /*!< Enable interrupts */
#define disableInterrupts() _sim_()  /*!< Disable interrupts */
#define rim()               _rim_()  /*!< Enable interrupts */
#define sim()               _sim_()  /*!< Disable interrupts */
#define nop()               _nop_()  /*!< No Operation */
#define trap()              _trap_() /*!< Trap (soft IT) */
#define wfi()               _wfi_()  /*!< Wait For Interrupt */
#define wfe()               _wfe_()  /*!< Wait For Interrupt */
#define halt()              _halt_() /*!< Halt */
#elif defined(_COSMIC_)
#define enableInterrupts()  {_asm("rim\n");}  /*!< Enable interrupts */
#define disableInterrupts() {_asm("sim\n");}  /*!< Disable interrupts */
#define rim()               {_asm("rim\n");}  /*!< Enable interrupts */
#define sim()               {_asm("sim\n");}  /*!< Disable interrupts */
#define nop()               {_asm("nop\n");}  /*!< No Operation */
#define trap()              {_asm("trap\n");} /*!< Trap (soft IT) */
#define wfi()               {_asm("wfi\n");}  /*!< Wait For Interrupt */
#define wfe()               {_asm("wfe\n");}  /*!< Wait for event */
#define halt()              {_asm("halt\n");} /*!< Halt */
#else /* _IAR */
#include <intrinsics.h>
#define enableInterrupts()  __enable_interrupt()   /*!< Enable interrupts */
#define disableInterrupts() __disable_interrupt()  /*!< Disable interrupts */
#define rim()               __enable_interrupt()   /*!< Enable interrupts */
#define sim()               __disable_interrupt()  /*!< Disable interrupts */
#define nop()               __no_operation()       /*!< No Operation */
#define trap()              __trap()               /*!< Trap (soft IT) */
#define wfi()               __wait_for_interrupt() /*!< Wait For Interrupt */
#define wfe()               __wait_for_event();    /*!< Wait for event */
#define halt()              __halt()               /*!< Halt */
#endif /* _RAISONANCE_ */

/*============================== Interrupt vector Handling ========================*/

#ifdef _COSMIC_
#define INTERRUPT_HANDLER(a,b) @far @interrupt void a(void)
#define INTERRUPT_HANDLER_TRAP(a) void @far @interrupt a(void)
#endif

#ifdef _RAISONANCE_
#define INTERRUPT_HANDLER(a,b) void a(void) interrupt b
#define INTERRUPT_HANDLER_TRAP(a) void a(void) trap
#endif

#ifdef _IAR_
#define STRINGVECTOR(x) #x
#define VECTOR_ID(x) STRINGVECTOR( vector = (x) )
#define INTERRUPT_HANDLER( a, b )  \
  _Pragma( VECTOR_ID( (b)+2 ) )        \
  __interrupt void (a)( void )
#define INTERRUPT_HANDLER_TRAP(a) \
  _Pragma( VECTOR_ID( 1 ) ) \
  __interrupt void (a) (void)
#endif

/*============================== Interrupt Handler declaration ========================*/

#ifdef _COSMIC_
#define INTERRUPT @far @interrupt
#endif

#ifdef _IAR_
#define INTERRUPT __interrupt
#endif


/*============================== Handling bits ====================================*/
/*-----------------------------------------------------------------------------
Method : I
Description : Handle the bit from the character variables.
Comments :    The different parameters of commands are
              - VAR : Name of the character variable where the bit is located.
              - Place : Bit position in the variable (7 6 5 4 3 2 1 0)
              - Value : Can be 0 (reset bit) or not 0 (set bit)
              The "MskBit" command allows to select some bits in a source
              variables and copy it in a destination var (return the value).
              The "ValBit" command returns the value of a bit in a char
              variable: the bit is reseted if it returns 0 else the bit is set.
              This method generates not an optimised code yet.
-----------------------------------------------------------------------------*/
#define SetBit(VAR,Place)         ( (VAR) |= (uint8_t)((uint8_t)1<<(uint8_t)(Place)) )
#define ClrBit(VAR,Place)         ( (VAR) &= (uint8_t)((uint8_t)((uint8_t)1<<(uint8_t)(Place))^(uint8_t)0xFF) )

#define ChgBit(VAR,Place)         ( (VAR) ^= (uint8_t)((uint8_t)1<<(uint8_t)(Place)) )
#define AffBit(VAR,Place,Value)   ((Value) ? \
                                   ((VAR) |= ((uint8_t)1<<(Place))) : \
                                   ((VAR) &= (((uint8_t)1<<(Place))^(uint8_t)0xFF)))
#define MskBit(Dest,Msk,Src)      ( (Dest) = ((Msk) & (Src)) | ((~(Msk)) & (Dest)) )

#define ValBit(VAR,Place)         ((uint8_t)(VAR) & (uint8_t)((uint8_t)1<<(uint8_t)(Place)))

#define BYTE_0(n)                 ((uint8_t)((n) & (uint8_t)0xFF))        /*!< Returns the low byte of the 32-bit value */
#define BYTE_1(n)                 ((uint8_t)(BYTE_0((n) >> (uint8_t)8)))  /*!< Returns the second byte of the 32-bit value */
#define BYTE_2(n)                 ((uint8_t)(BYTE_0((n) >> (uint8_t)16))) /*!< Returns the third byte of the 32-bit value */
#define BYTE_3(n)                 ((uint8_t)(BYTE_0((n) >> (uint8_t)24))) /*!< Returns the high byte of the 32-bit value */

/*============================== Assert Macros ====================================*/
#define IS_STATE_VALUE(STATE) \
  (((STATE) == SET) || \
   ((STATE) == RESET))

/*-----------------------------------------------------------------------------
Method : II
Description : Handle directly the bit.
Comments :    The idea is to handle directly with the bit name. For that, it is
              necessary to have RAM area descriptions (example: HW register...)
              and the following command line for each area.
              This method generates the most optimized code.
-----------------------------------------------------------------------------*/

#define AREA 0x00     /* The area of bits begins at address 0x10. */

#define BitClr(BIT)  ( *((unsigned char *) (AREA+(BIT)/8)) &= (~(1<<(7-(BIT)%8))) )
#define BitSet(BIT)  ( *((unsigned char *) (AREA+(BIT)/8)) |= (1<<(7-(BIT)%8)) )
#define BitVal(BIT)  ( *((unsigned char *) (AREA+(BIT)/8)) & (1<<(7-(BIT)%8)) )


#endif /* __STM8TL5X_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
