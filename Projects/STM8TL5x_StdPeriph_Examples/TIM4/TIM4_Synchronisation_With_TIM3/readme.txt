/** @page TIM4_Synchronisation_with_TIM3 TIM4 - Synchronisation with TIM3

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    TIM4/TIM4_Synchronisation_with_TIM3/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Synchronisation between TIM4 and TIM3
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

  This example provides a short description of how to use the TIM3 peripheral
  synchronised by TIM4. TIM3 is configured as a slave of TIM4. 

  TIM3 is configurated to be enabled if it detects an edge on its input trigger (TRGI).
  TIM4 is configurated to generate an edge through its (TRGO) at the update event.
  TIM3 TRGI is configurated to be connected (internal connection) to TIM4 TRGO.

  If line "Inc1:" in main.c is commented, TIM4 is not enabled => no Edge is detected on TIM3 TRGI),
  ==> Result variable value will be equal to 0 (FAILED).
  If line "Inc1" in main.c is uncommented, TIM4 is enabled => TIM4 generate an Edge on its TRGO and 
  an Edge is detected on TIM3 TRGI. ==> Result variable value will be equal to 1 (PASS).


  @par Directory contents

  - TIM4\TIM3_Synchronisation_With_TIM4\main.c                       Main file containing the "main" function
  - TIM4\TIM3_Synchronisation_With_TIM4\stm8tl5x_conf.h              Library Configuration file
  - TIM4\TIM3_Synchronisation_With_TIM4\stm8tl5x_it.c                Interrupt routines source
  - TIM4\TIM3_Synchronisation_With_TIM4\stm8tl5x_it.h                Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.
  
  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.
    

@par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_clk.c
    - stm8tl5x_tim3.c
    - stm8tl5x_tim4.c


  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - Insert break point on main.c line "Inc2"
  - Insert break point on main.c line "Inc3"
 
* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
