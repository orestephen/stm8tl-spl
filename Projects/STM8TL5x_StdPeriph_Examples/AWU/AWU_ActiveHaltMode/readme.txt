/**
  @page AWU_ActiveHaltMode AWU - Using the AWU to wake-up the CPU from Active Halt mode

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    AWU/AWU_ActiveHaltMode/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Using the AWU to wake-up the CPU from Active Halt mode
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

  This example provides a short description of how to use the AWU peripheral:
  - Initialization of the AWU peripheral
  - Initialization of GPIO pin in output mode in order to drive LEDs
  - Initialization of a GPIO in input mode in order to read the Key Button state


  @par Directory contents

  - AWU\AWU_ActiveHaltMode\main.c                       Main file containing the "main" function
  - AWU\AWU_ActiveHaltMode\stm8tl5x_conf.h              Library Configuration file
  - AWU\AWU_ActiveHaltMode\stm8tl5x_it.c                Interrupt routines source
  - AWU\AWU_ActiveHaltMode\stm8tl5x_it.h                Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - LED1 connected on GPIOB.2
     - LED2 connected on GPIOB.3
     - Button connected on GPIOB.5
     - LCD display driven with SPI_MOSI and SPI_SCK pins (optional)
     - SWIM connector


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_awu.c
    - stm8tl5x_clk.c
    - stm8tl5x_exti.c
    - stm8tl5x_gpio.c
    - stm8tl5x_spi.c
    - stm8tl5x_tim2.c
    - mono_lcd.c (under Utilities directory)


  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)

  - The LED1 blinks continuously and slowly
  - If you press the button on the board, the LED1 will blink faster for
    a few seconds and then will be switched off.
  - At this stage, the CPU is in Active Halt mode. The LED2 is switched ON.
  - After few seconds (12s), the MCU will exit from halt mode thanks to the AWU.
  - The LED2 is switched OFF and the LED1 will continue to blink slowly.
  - Messages are displayed on the LCD screen (optional, activated in the code).


 <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
