/** @page TIM2_OC_ActiveMode TIM2 - Generate two different signals with two different delays with Active Mode
  
  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    TIM2/TIM2_OC_ActiveMode/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Generate two different signals with two different delays with Active Mode
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

  This example shows how to configure the TIM2 peripheral to generate two different 
  signals with two different delays.

  The TIM2CLK frequency is set to 2 MHz, the Prescaler is set to 128 and used in 
  Output Compare Active Mode.
 
  TIM2 counter clock = TIM2CLK / (Prescaler) = 15625 Hz 

  The TIM2 CCR1 register value is equal to 15625:
  TIM2_CH1 delay = CCR1_Val/TIM2 counter clock  = 1000 ms
  so the TIM2 Channel 1 generates a signal with a delay equal to 1000 ms.

  The TIM2 CCR2 register value is equal to 7812:
  TIM2_CH2 delay = CCR2_Val/TIM2 counter clock = 500 ms
  so the TIM2 Channel 2 generates a signal with a delay equal to 500 ms.
  
  The delay correspond to the time difference between GPIOA.6 rising edge and TIM2_CHx signal rising edges.


  @par Directory contents

  - TIM2\TIM2_OC_ActiveMode\main.c                      Main file containing the "main" function
  - TIM2\TIM2_OC_ActiveMode\stm8tl5x_conf.h             Library Configuration file
  - TIM2\TIM2_OC_ActiveMode\stm8tl5x_it.c               Interrupt routines source (not used in this example)
  - TIM2\TIM2_OC_ActiveMode\stm8tl5x_it.h               Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.
    
  - Board Set-up
    - Connect the following pins to an oscilloscope:
	    - GPIOA.6
	    - TIM2_CH1 pin (GPIOD.4)  
	    - TIM2_CH2 pin (GPIOD.5)  


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_tim2.c
    - stm8tl5x_gpio.c
    - stm8tl5x_clk.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - Connect GPIOA.6, TIM2_CH1 and TIM2_CH2 pins to an oscilloscope. Observe the
    delay between the rising edge of GPIOA.6 and TIM2_CHx signals.  
  
* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
