/** @page IWDG_RearmReset IWDG - Watchdog Refreshing and Reset

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    IWDG/IWDG_RearmReset/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   IWDG refreshing, IWDG Reset
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

  This example provides a short description of how to use the IWDG:
  After Reset a test if performed to check if a IWDG reset occured. If yes, the
  LED1 and LED2 toggle together. If no, only the LED1 toggle.
  Pressing the button will stop the IWDG refresh and will switch the LED2 ON.
  After a short delay and as the IWDG is no more refreshed, the IWDG reset occurs.  
  The program restart and the two LEDs toggles indicating the correct operation.


  @par Directory contents

  - IWDG\IWDG_RearmReset\main.c                       Main file containing the "main" function
  - IWDG\IWDG_RearmReset\stm8tl5x_conf.h              Library Configuration file
  - IWDG\IWDG_RearmReset\stm8tl5x_it.c                Interrupt routines source 
  - IWDG\IWDG_RearmReset\stm8tl5x_it.h                Interrupt routines declaration


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
    - stm8tl5x_rst.c
    - stm8tl5x_gpio.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - After Reset a test if performed to check if a IWDG reset occured. If yes, the
    LED1 and LED2 toggle together. If no, only the LED1 toggle.
  - Pressing the button will stop the IWDG refresh and will switch the LED2 ON.
  - After a short delay and as the IWDG is no more refreshed, the IWDG reset occurs.  
  - The program restart and the two LEDs toggles indicating the correct operation.
  - You can also monitor the GPIOB.3 with an oscilloscope and measure the IWDG delay.
    The value is around 1.7 s.
    

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
