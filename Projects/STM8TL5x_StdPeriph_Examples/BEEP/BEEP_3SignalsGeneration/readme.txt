/**
  @page BEEP_3SignalsGeneration BEEP - Generation of the 3 beep signals

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    BEEP/BEEP_3SignalsGeneration/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Generation of the 3 beep signals
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

  This example provides a short description of how to use the BEEP peripheral:
  - Initialization of the BEEP peripheral
  - Initialization of a GPIO in input mode in order to read the Key Button state
  - Initialization of GPIO in output mode to drive LEDs
  - Each action on the Key button toggles between the 3 beep frequencies


@par Directory contents

  - BEEP\BEEP_3SignalsGeneration\main.c                       Main file containing the "main" function
  - BEEP\BEEP_3SignalsGeneration\stm8tl5x_conf.h              Library Configuration file
  - BEEP\BEEP_3SignalsGeneration\stm8tl5x_it.c                Interrupt routines source
  - BEEP\BEEP_3SignalsGeneration\stm8tl5x_it.h                Interrupt routines declaration


@par Hardware and Software environment

  - This example runs on STM8TL5x devices.
  
  - This example has been tested with on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.
    
  - Board Set-up
     - LED1 connected on GPIOB.2
     - LED2 connected on GPIOB.3
     - Button connected on GPIOB.5
     - LCD screen driven with SPI_MOSI and SPI_SCK pins
     - SWIM connector
     - GPIOA.0 connected to a buzzer and/or monitored with an oscilloscope


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_beep.c
    - stm8tl5x_clk.c
    - stm8tl5x_exti.c
    - stm8tl5x_gpio.c
    - stm8tl5x_spi.c
    - stm8tl5x_tim2.c
    - mono_lcd.c (under Utilities directory)


  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Exit debugging session: Debug->Stop Debugging

  - Per default, the BEEP signal is OFF and the 2 LEDs are OFF.
  - Everytime you press the Key button on the board, you will toggle the
    buzzer frequency in this way: 1kHz -> 2kHz -> 4kHz -> OFF -> 1kHz -> etc...
  - The 2 LEDs will toggle respectively.
  - The LCD screen displays the beeper frequency selected.

<h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
