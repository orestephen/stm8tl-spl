/**
  @page CLK_MasterClock CLK - Master Clock Prescaler configuration example

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    CLK/CLK_MasterClock/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Master Clock Prescaler Configuration example
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

  This example demonstrates the different Master Clock Prescaler configurations.
  A press on a button allows to change the Master clock frequency. Two LEDs are blinking
  more or less quickly according to the selected clock frequency.


@par Directory contents

  - CLK\CLK_MasterClock\main.c             Main file containing the "main" function
  - CLK\CLK_MasterClock\stm8tl5x_conf.h    Library Configuration file
  - CLK\CLK_MasterClock\stm8tl5x_it.c      Interrupt routines source
  - CLK\CLK_MasterClock\stm8tl5x_it.h      Interrupt routines declaration


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
     - GPIOA.6 connected to an oscilloscope to observe the CCO signal


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_clk.c
    - stm8tl5x_exti.c
    - stm8tl5x_gpio.c
    

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - Using the button the desired Master clock:
    (HSI/4 -> HSI/2 -> HSI/1 -> HSI/8 -> HSI/4 -> etc...)
  - Observe the LEDs frequency blinking according to the selected clock. 
  - The clock output can be monitored by using an oscilloscope on PA6 (CCO).

<h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
