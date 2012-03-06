/**
  @page EXTI_InterruptPriority EXTI - Reading buttons state using external interrupts

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    EXTI/EXTI_InterruptPriority/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Reading buttons state using external interrupts
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

  This basic firwmare example shows how to use the EXTI peripheral.
  It does the following:
  - Configures one I/O in output push-pull for driving a LED
  - Configures two I/Os in input with interrupt for reading two buttons
  - Configures one button with External Interrupt on Falling edge only
  - Configures one button with External Interrupt on Falling edge + Low level


@par Directory contents

  - EXTI\EXTI_InterruptPriority\main.c            Main file containing the "main" function
  - EXTI\EXTI_InterruptPriority\main.h            Main functions prototype and I/Os definitions
  - EXTI\EXTI_InterruptPriority\stm8tl5x_conf.h   Library Configuration file
  - EXTI\EXTI_InterruptPriority\stm8tl5x_it.c     Interrupt routines source
  - EXTI\EXTI_InterruptPriority\stm8tl5x_it.h     Interrupt routines declaration


@par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - LED connected on GPIOB.2
     - Button1 connected on GPIOB.5
     - Button2 connected on GPIOB.6
     - SWIM connector


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_exti.c
    - stm8tl5x_gpio.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - The LED is OFF per default
  - The LED toggles each time the Button1 is pressed
  - The LED blinks while the Button2 is kept pressed 

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
