/** @page WFE_WakeUp WFE - Wake up from wait for event mode

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    WFE/WFE_WakeUp/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Wake up from wait for event mode
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

  This example provides a short description of how the CPU operates when entering 
  in wait for event mode.
  The device enters in WFE mode. When the button2 is pressed, an interrupt is 
  generated. The CPU wakes up from WFE mode, serves the interrupt and goes 
  back to WFE mode. When the button1 is pressed, a WFE event occurs, the CPU wakes up 
  and resumes processing without serving the interrupt routine associated to the button1.
  

  @par Directory contents

  - WFE\WFE_WakeUp\main.c                       Main file containing the "main" function
  - WFE\WFE_WakeUp\main.h                       Main functions prototype
  - WFE\WFE_WakeUp\stm8tl5x_conf.h              Library Configuration file
  - WFE\WFE_WakeUp\stm8tl5x_it.c                Interrupt routines source
  - WFE\WFE_WakeUp\stm8tl5x_it.h                Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.
  
  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - LED1 connected on GPIOB.2
     - LED2 connected on GPIOB.3
     - Button1 connected on GPIOB.5
     - Button2 connected on GPIOB.6
     - SWIM connector


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_wfe.c
    - stm8tl5x_exti.c
    - stm8tl5x_gpio.c
 

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - The LED1 and LED2 are ON
  - Press the button2. The CPU wakes up from WFE mode, an interrupt is generated
    which toggles the LED2. You can press the button2 as many time as you want.
  - Then press the button1. The CPU wakes up from WFE mode, but you can see that the
    interrupt routine associated to the button1 is not served.
  - The CPU exits from the WFE mode and the LED1 and LED2 blink continuously.


* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
