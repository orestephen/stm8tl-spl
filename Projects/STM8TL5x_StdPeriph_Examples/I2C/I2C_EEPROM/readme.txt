/** @page I2C_EEPROM I2C - Write and Read data in an I2C EEPROM memory

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    I2C/I2C_EEPROM/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Write and Read data in an I2C EEPROM memory
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

  This example provides a short description of how to: 
  - Communicate with an EEPROM
  - Perform a write data buffer in the EEPROM memory
  - Perform a random read of the previous written buffer
  - Compare the written and received data buffers.
  - The communication is configured in 7-bit addressing mode with a clock speed set to 100 KHz. 


  @par Directory contents

  - I2C\I2C_EEPROM\main.c                    Main file containing the "main" function
  - I2C\I2C_EEPROM\stm8tl5x_conf.h           Library Configuration file
  - I2C\I2C_EEPROM\stm8tl5x_it.c             Interrupt routines source (not used in this example)
  - I2C\I2C_EEPROM\stm8tl5x_it.h             Interrupt routines declaration
  - I2C\I2C_EEPROM\i2c_ee.c                  M24C64 EEPROM functions to manage communication with I2C
  - I2C\I2C_EEPROM\i2c_ee.h                  M24C64 EEPROM functions declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - This example uses an I2C EEPROM.

  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_clk.c
    - stm8tl5x_i2c.c
    - stm8tl5x_gpio.c
    - i2c_ee.c


  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - The test will compare the sent buffer & received buffer data.
  - The three LEDs (LD2, LD3 and LD4) will blink if both buffers are equals otherwise only the LED2 will blink.

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
