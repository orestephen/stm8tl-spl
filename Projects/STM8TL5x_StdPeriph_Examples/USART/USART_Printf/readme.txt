/** @page USART_Printf USART - Retarget the C library printf function to the USART

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    USART/USART_Printf/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Retarget the C library printf function to the USART
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

  This example shows how to retarget the C library printf function to the USART. 
  This implementation output the printf message on the Hyperterminal using USART.

  The USART is configured as follows:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Receive and transmit enabled
 

  @par Directory contents

  - USART\USART_Printf\main.c                    Main file containing the "main" function
  - USART\USART_Printf\stm8tl5x_conf.h           Library Configuration file
  - USART\USART_Printf\stm8tl5x_it.c             Interrupt routines source (not used in this example)
  - USART\USART_Printf\stm8tl5x_it.h             Interrupt routines declaration


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


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_clk.c
    - stm8tl5x_usart.c
    - stm8tl5x_gpio.c
  
 
  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - On the PC side open an HyperTerminal window with the correct setting.
  - Each press on the Button sends a message on the Hyperterminal and toggles the LED.
  
* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
