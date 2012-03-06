/** @page I2C_7bits_Polling_Master I2C - 7bits address transfer in Polling mode (master)

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    I2C/I2C_7bits_Polling_Master/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   7bits address transfer in Polling mode (master)
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


  @par Example description

  This example provides a short description of how to send data with 7bits addressing mode
  using I2C.

  @par Directory contents

  - I2C\I2C_7bits_Polling_Master\main.c                       Main file containing the "main" functions 
  - I2C\I2C_7bits_Polling_Master\stm8tl5x_conf.h              Library Configuration file
  - I2C\I2C_7bits_Polling_Master\stm8tl5x_it.c                Interrupt routines source (not used in this example)
  - I2C\I2C_7bits_Polling_Master\stm8tl5x_it.h                Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - LED1 connected on GPIOB.2
     - LED2 connected on GPIOB.3
     - Button connected on GPIOB.5
     - SWIM connector

    Connect the STM8TL5x I2C to a second I2C device programmed as Slave:
      - SDA pin (GPIOA.3) to SDA pin of the second I2C device.
      - SCL pin (GPIOA.4) to SCL pin of the second I2C device.
      - Add pull-up resistors (4.7k ohms) on SDA and SCL pins.
      Note: If an Aardvark module is used, configure it as slave with
        address = 0x50 (equivalent to 0xA0 shifted of one bit)


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
  - Start the second I2C device (Slave)
  - Run program: Debug->Run (Ctrl+F5).

  - The LED1 blinks continuously.
  - Each time you press on the button, some data are sent to the slave device.
  - The LED2 toggles at the end of the data transmission.

<h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>

*/
