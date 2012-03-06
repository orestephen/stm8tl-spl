/**
  @page GPIO_IOToggle_InterruptMode GPIO - LEDs toggling, Button reading in interrupt mode

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    GPIO/GPIO_IOToggle_InterruptMode/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   LEDs toggling, Button reading in interrupt mode
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

  This example provides a short description of how to use the GPIO peripheral:
  - Initialization of the GPIO in output and input modes with interrupt
  - LED toggling
  - Button state reading in interrupt mode


  @par Directory contents

  - GPIO\GPIO_IOToggle_InterruptMode\main.c                   Main file containing the "main" function
  - GPIO\GPIO_IOToggle_InterruptMode\stm8tl5x_conf.h             Library Configuration file
  - GPIO\GPIO_IOToggle_InterruptMode\stm8tl5x_it.c               Interrupt routines source
  - GPIO\GPIO_IOToggle_InterruptMode\stm8tl5x_it.h               Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - LED1 connected on GPIOB.2
     - Button connected on GPIOB.5
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

  - The LED toggles each time the button is pressed

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
