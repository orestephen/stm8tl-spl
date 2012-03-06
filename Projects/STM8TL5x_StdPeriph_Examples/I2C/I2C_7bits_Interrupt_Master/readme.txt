/** @page I2C_7bits_Interrupt_Master I2C - 7bits slave address transfer in Interrupt mode

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    I2C/I2C_7bits_Interrupt_Master/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   7bits slave address transfer in Interrupt mode
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
  @endverbatim


  @par Example Description

  This example provides a short description of how to: 
  - Transfer a data byte to a second I2C using interrupts.
  - The communication is configured in 7bit addressing mode with a clock speed set to 100KHz.
  - The event and buffer interrupts are enabled for the I2C.
  - Once the start signal is generated the interrupt function detects each interrupt and sends a byte to the slave
    then generate a STOP condition.


  @par Directory contents

  - I2C\I2C_7bits_Interrupt_Master\main.c                       Main file containing the "main" function
  - I2C\I2C_7bits_Interrupt_Master\stm8tl5x_conf.h              Library Configuration file
  - I2C\I2C_7bits_Interrupt_Master\stm8tl5x_it.c                Interrupt routines source
  - I2C\I2C_7bits_Interrupt_Master\stm8tl5x_it.h                Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board setup
     - LED1 connected on GPIOB.2
     - LED2 connected on GPIOB.3
     - Button connected on GPIOB.5
     - SWIM connector

    Connect the STM8TL5x I2C to a second I2C device (Aardvark module for example): 
      - SDA pin (GPIOA.3) to SDA pin of the second I2C device.
      - SCL pin (GPIOA.4) to SCL pin of the second I2C device.
      - Add pull-up resistors (4.7k ohms) on SDA and SCL pins.
      - If an Aardvark module is used, configure it as slave with
        address = 0x50 (equivalent to 0xA0 shifted of one bit) and bitrate = 100KHz.


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_clk.c  
    - stm8tl5x_i2c.c
    - stm8tl5x_gpio.c
    - stm8tl5x_exti.c
  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Start the second I2C device or enable the Aardvark module
  - Run program: Debug->Run (Ctrl+F5).

  - The LED1 blinks continuously.
  - Each time you press on the button 5 data are sent to the slave device:
      1st time: 0x00 0x01 0x02 0x03 0x04
      2nd time: 0x05 0x06 0x07 0x08 0x09
      etc...
  - At the end of the transmission of the 5 data the LED2 toggles.

<h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>

*/
