/** @page TIM2_Sinewave_Generation TIM2 - Generate a sinewave in the range of 45Hz to 65Hz with the resolution of 0.1Hz

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    TIM2/TIM2_Sinewave_Generation/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Generate a sinewave in the range of 45Hz to 65Hz with the resolution of 0.1Hz
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

  This example shows how user can generate a sinewave with a frequency between
  45Hz to 65Hz using TIM2. 
    
  TIM2 CLK is fixed to 4 MHz, the TIM2 Prescaler is equal to 1 so the TIM2 counter
  clock used is 4 MHz. 
  
  The TIM2 Channel 1 is configured as PWM Output Mode 1.
  
  To generate a sine wave of frequency 65.3595Hz, you have to uncomment "#define FREQ_65_3595"
  (User can define only specific frequencies, which are commented out in "main.h"). 
  According to frequency selected by define directive, five parameters will be defined. 
  These parameters will make the corresponding sine wave frequency.
  
  The TIM2_CC1 must be connected to a "Low Pass" filter (Rfilter =1.8Kohm, Cfilter= 0.47uF)

 @code  
  TIM2_CC1 |-><-----[Rfilter=1.8Kohm]----+-------------> to the oscilloscope
                                         |
                                 [Cfilter=0.47uF]
                                         |
                                       ///// GND
 @endcode 

  @par Directory contents

  - TIM2\TIM2_Sinewave_Generation\main.h                      Defines macroes for all
                                                              the frequencies in the range
                                                              of 45Hz to 65Hz with the resolution of 0.1Hz. 
  - TIM2\TIM2_Sinewave_Generation\main.c                      Main file containing the "main" function
  - TIM2\TIM2_Sinewave_Generation\stm8tl5x_conf.h             Library Configuration file
  - TIM2\TIM2_Sinewave_Generation\stm8tl5x_it.c               Interrupt routines source
  - TIM2\TIM2_Sinewave_Generation\stm8tl5x_it.h               Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.
    
  - Board Set-up
     - Connect  TIM2_CC1 pin (GPIOD.4) to a "Low Pass" filter (Rfilter =1.8Kohm, Cfilter= 0.47uF).
     - Connect the "Low Pass" filter output to an oscilloscope.


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
  - Connect TIM2_CC1 to a "Low Pass" Filter (Rfilter =1.8Kohm, Cfilter= 0.47uF)
  - Connect the "Low Pass" filter output to an oscilloscope.

 
* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
