/** @page ITC_SoftwarePriority ITC - Changing software priority on two external interrupt lines

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    ITC/ITC_SoftwarePriority/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Changing software priority on two external interrupt lines
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

  This basic firwmare example shows how to use the ITC peripheral.
  It does the following:
  - Configures two I/Os in output push-pull for driving two LEDs
  - Configures two I/Os in input with interrupt for reading two buttons
  - Configures the two External Interrupt lines in Falling edge + Low level
  - Changes software priority between the two interrupt lines


  @par Directory contents

  - ITC\ITC_SoftwarePriority\main.c                       Main file containing the "main" function
  - ITC\ITC_SoftwarePriority\main.h                       Main functions prototype
  - ITC\ITC_SoftwarePriority\stm8tl5x_conf.h              Library Configuration file
  - ITC\ITC_SoftwarePriority\stm8tl5x_it.c                Interrupt routines source
  - ITC\ITC_SoftwarePriority\stm8tl5x_it.h                Interrupt routines declaration


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
    - stm8tl5x_exti.c
    - stm8tl5x_gpio.c
    - stm8tl5x_itc.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - The LED1 and LED2 are ON per default
  - When the Button1 is pressed, the LED1 toggles and LED2 is OFF
  - When the Button2 is pressed, the LED2 toggles and LED1 is OFF
  - Without changing the software priority the Button1 has the priority over the Button2.  
  - Play with the two buttons in order to see which one has the highest priority:
     - press and maintain the Button1 -> LED1 toggles, LED2 OFF
     - Continue pressing the Button1 and press the Button2 -> LED2 toggles instead, LED1 OFF (Button2 has the priority)
  - If you do the opposite, you can see that the Button2 is not interrupted by the Button1 as configured by hardware.

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
