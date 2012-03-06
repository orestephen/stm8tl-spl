/** @page WWDG_RearmReset WWDG - Counter refresh and simulation of WWDG reset

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    WWDG/WWDG_RearmReset/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   WWDG counter refresh and simulation of WWDG reset
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

  This example shows how to refresh the WWDG counter. The WWDG timeout is set to
  251.9 ms.
  
  The AllowedRefresh variable is set to ENABLE after reset. This causes the WWDG
  counter to be refreshed and preventing a WWDG reset. The LED2 is toggling.

  When the button1 is pressed, an EXTI event is triggered and the corresponding
  ISR is served setting the AllowedRefresh variable to DISABLE. At this time the
  WWDG counter is no more refreshed. When the WWDG counter reaches 63 an MCU reset occurs.

  When the button2 is pressed, an EXTI event is triggered and the 
  corresponding ISR is served setting the NonAllowedRefresh variable to ENABLE. 
  At this time the WWDG counter is refreshed in the non-allowed window and as a result
  an MCU reset occurs.

  After reset the LED1 toggles if a WWDG reset has been detected.


  @par Directory contents

  - WWDG\WWDG_RearmReset\main.c                       Main file containing the "main" function
  - WWDG\WWDG_RearmReset\stm8tl5x_conf.h              Library Configuration file
  - WWDG\WWDG_RearmReset\stm8tl5x_it.c                Interrupt routines source 
  - WWDG\WWDG_RearmReset\stm8tl5x_it.h                Interrupt routines declaration


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
    - stm8tl5x_wwdg.c
    - stm8tl5x_rst.c
    - stm8tl5x_gpio.c
    - stm8tl5x_exti.c


  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - LED 2 is toggling, the WWDG counter is refreshed in the allowed window, so no reset.
  - When you press the button1, the WWDG counter is no more refreshed in the allowed-window
    and when it reaches 63, the LED1 toggles indicating a WWDG reset.
  - When you press the button2, the WWDG counter is refreshed in the non-allowed
    window resulting by a reset. The LED1 toggles indicating a WWDG reset.

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
