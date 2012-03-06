/** @page USART_HyperTerminal_Interrupt USART - Communication between USART and hyperterminal using interrupts

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    USART/USART_HyperTerminal_Interrupt/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Communication between USART and hyperterminal using interrupts
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

  This example provides a description of how to use the USART interrupts to 
  communicate with the hyperterminal.
  The USART sends a predefined buffer to the hyperterminal and still waiting 
  for a string from the hyperterminal which length is defined by RxBufferSize. 
  The communication is managed by Transmit and Receive interrupts.
  The communication is re-started each time a button is pressed. 

  The USART is configured as follow:
    - BaudRate = 9600 baud  
    - Word Length = 8 Bits (Word Length = 7 data bit + 1 parity bit)
    - One Stop Bit
    - Odd parity
    - Receive and transmit enabled
    - USART Clock disabled
  
    
  @par Directory contents

    - USART\USART_HyperTerminal_Interrupt\main.c                  Main file containing the "main" function
    - USART\USART_HyperTerminal_Interrupt\stm8tl5x_conf.h         Library Configuration file
    - USART\USART_HyperTerminal_Interrupt\stm8tl5x_it.c           Interrupt routines source
    - USART\USART_HyperTerminal_Interrupt\stm8tl5x_it.h           Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up
     - 1 LED
     - 1 BUTTON
     - USART TX and RX pins connected to a ST3232 device for example.
     - Output pins of the ST3232 device connected to PC serial port through RS232 cable.

    Configure the HyperTerminal on the PC with: 9600 bits/s, 7 data bits, Odd parity and 1 stop bit


  @par How to use it ?

  In order to make the program work, you must do the following:
  - Create a project and setup all project configuration        
  - Compile the directory content files and required Library files
    - stm8tl5x_clk.c
    - stm8tl5x_usart.c
    - stm8tl5x_gpio.c
    - stm8tl5x_exti.c

  - Rebuild all files: Build-> Rebuild all.
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - After setting the Hyperterminal on the PC, a message appears on the Hyperterminal windows.
  - Each press on the Button sends a message on the Hyperterminal and toggles the LED.

* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
