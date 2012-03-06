/** @page TIM4_TimeBase_InterruptConfiguration TIM4 - Toggling an output with TIM4 update interrupt 

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    TIM4/TIM4_TimeBase_InterruptConfiguration/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Toggling an output with TIM4 update interrupt 
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

  This example provides a short description of how to use the TIM4 peripheral
  In this example, the GPIOA.6 pin toggles each time the Update interrupt occurs

  The TIM4CLK frequency is 2MHz, the Prescaler is 1 so the TIM4 counter clock is 2MHz. 

  The TIM4 is running at 7.8125 KHz: TIM4 Frequency = TIM4 counter clock/(ARR value + 1) 
  So the TIM4 generates an Update Interrupt each 128 us.
  
  @note The square signal frequency on GPIOA.6 is half the Update Interrupt frequency
   (signal Period = 2 x Update interrupt period).
  

  @par Directory contents

  - TIM4\TIM4_TimeBase_InterruptConfiguration\main.c                      Main file containing the "main" function
  - TIM4\TIM4_TimeBase_InterruptConfiguration\stm8tl5x_conf.h             Library Configuration file
  - TIM4\TIM4_TimeBase_InterruptConfiguration\stm8tl5x_it.c               Interrupt routines source
  - TIM4\TIM4_TimeBase_InterruptConfiguration\stm8tl5x_it.h               Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.
  
  - This example has been tested with STMicroelectronics STM8L1x-EVAL evaluation
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.
    
  - Board Set-up
    - Connect GIOA.6 pin to an oscilloscope.


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_clk.c
    - stm8tl5x_tim4.c
    - stm8tl5x_gpio.c


  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - Connect the GPIOA.6 pin to an oscilloscope 
  
* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
