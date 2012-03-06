/** @page TIM2_Input_Capture TIM2 - Signal frequency Capture
  
  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    TIM2/TIM2_Input_Capture/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Signal frequency Capture
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

  This example shows how to configure the TIM2 peripheral to capture a signal frequency.
  TIM2CLK is fixed to 16 MHz with a Prescaler of 1. The TIM2 Channel 1 is configured as Input capture.
  TIM3 Channel 2 is configured to generate a 128 kHz signal frequency. 
  The TIM2 Channel 1 is connected to the TIM3 Channel 2 pin. 
  The value of TIM2 CC1 frequency is stored in the TIM2ClockFreq variable.


  @par Directory contents

  - TIM2\TIM2_Input_Capture\main.c                       Main file containing the "main" function
  - TIM2\TIM2_Input_Capture\stm8tl5x_conf.h              Library Configuration file
  - TIM2\TIM2_Input_Capture\stm8tl5x_it.c                Interrupt routines source (not used in this example)
  - TIM2\TIM2_Input_Capture\stm8tl5x_it.h                Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.
    
  - Board Set-up
     - Connect the TIM2 Channel 1 (GPIOD.4) to the TIM3 Channel 2 pin (GPIOD.7).  


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_tim2.c
    - stm8tl5x_tim3.c
    - stm8tl5x_gpio.c
    - stm8tl5x_clk.c


  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - Connect the TIM2 Channel 1 (GPIOD.4) to the TIM3 Channel 2 pin (GPIOD.7).
  - Set a breakpoint in the code on the nop instruction and read the value of TIM3ClockFreq variable.

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
