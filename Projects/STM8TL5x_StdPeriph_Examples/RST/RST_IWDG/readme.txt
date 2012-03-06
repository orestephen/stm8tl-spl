/** @page RST_IWDG RST - IWDG Reset example

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    RST/RST_IWDG/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   IWDG Reset example
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

  This example provides a short description of how to manage an IWDG reset.
  The TIM3 is used to refresh the IWDG periodically.
  Pressing the button will stop refreshing the IWDG, so a reset is generated. 
  The two LEDs blink quickly for a few moment signaling the IWDG reset. 
  When the reset flag is cleared only the LED1 blinks slowly.


  @par Directory contents

  - RST\RST_IWDG\main.c                       Main file containing the "main" function
  - RST\RST_IWDG\stm8tl5x_conf.h              Library Configuration file
  - RST\RST_IWDG\stm8tl5x_it.c                Interrupt routines source
  - RST\RST_IWDG\stm8tl5x_it.h                Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.
  
  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - LED1 connected on GPIOB.2
     - LED2 connected on GPIOB.3
     - Button1 connected on GPIOB.5
     - SWIM connector

  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_iwdg.c
    - stm8tl5x_tim3.c
    - stm8tl5x_gpio.c
    - stm8tl5x_clk.c
    - stm8tl5x_rst.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - In normal condition (the IWDG is refreshed by TIM3) the LED1 blinks slowly.
  - If you press the button, the LED1 stays ON and the IWDG is no more refreshed.
  - After a few moment a Reset occurs.
  - The two LEDs blink quickly for a few moment signaling that an IWDG reset occured.


* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
