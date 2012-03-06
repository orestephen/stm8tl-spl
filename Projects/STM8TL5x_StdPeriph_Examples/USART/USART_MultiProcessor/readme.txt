/** @page USART_MultiProcessor USART - Usage of multi-processor mode

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    USART/USART_MultiProcessor/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Use the USART in multi-processor mode
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

  This example provides a description of how to use the USART in multi-processor mode.
  
  This example requires the usage of two boards:
  
  - The first board is configured as USART Master with address 0x01.
  
  - The second board is configured as USART Slave addresses with address 0x2.
   
  - The first board (USART Master) continuously
    sends the 0x33 character to the second board (USART Slave).
    The LED1 toggles for each data sent on the Master board.
    The LED2 toggles for each data received and equal to 0x33 on the Slave board.

  Mute mode

  - On the Second board When a falling edge is applied on EXTI Pin 5, an interrupt
    is generated and in the EXTI_PIN5_IRQHandler routine, the USART enters the mute
    mode and remains in this mode (no LEDs toggling) 
  - On the first board When a falling edge is applied on EXTI Pin 5, an interrupt
    is generated and in the EXTI_PIN5_IRQHandler routine, USART Master sends the
    address mark character (0x102) to wake up USART Slave. 
  - On the second board the USART slave receives the wake up and the LEDs restart toggling.


  @note If only one board is used, the data is sent and received on the same USART.
        The LED1 toggles when the data is sent and LED2 toggles when the data is received.
        The mute mode is not used. This mode is selected by uncommenting the line USART_Master_Slave 
        in the main.h file.

USART Master and Slave configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 9 Bits
  - One Stop Bit
  - No parity
  - Receive and transmit enabled

  @par Directory contents

  - USART\USART_MultiProcessor\main.c                       Main file containing the "main" function
  - USART\USART_MultiProcessor\main.h                       Main functions prototype  
  - USART\USART_MultiProcessor\stm8tl5x_conf.h              Library Configuration file
  - USART\USART_MultiProcessor\stm8tl5x_it.c                Interrupt routines source
  - USART\USART_MultiProcessor\stm8tl5x_it.h                Interrupt routines declaration

  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.
  
  - This example has been tested on generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.

  - Board Set-up    
    - To run this example it is necessary to use two boards: one to run
       the USART Master and another to run the USART Slave 
       Connect USART_Tx and USART_Rx on the first board 
       to respectively USART_Rx and USART_Tx on the second board (or connect a
       null-modem female/female RS232 cable between the two boards).
       Make sure that the two boards are connected to the same ground.
    - The Master board uses the LED1 and the Slave board the LED2.
    - One button is used on each board.
    
    If you have only one board, simply connect together the USART_Tx and USART_Rx pins. 

  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files:
    - stm8tl5x_clk.c
    - stm8tl5x_gpio.c
    - stm8tl5x_exti.c
    - stm8tl5x_usart.c

   
  - If two boards are used: select USART_Master for the first board and USART_Slave
    for the second board in the main.h
  - On the two boards:
    - Rebuild all files: Build-> Rebuild all. 
    - Load project image: Debug->Start Debugging 
    - Run program: Debug->Run (Ctrl+F5). 
    - Observe the LEDs and press the button as describe above.

<h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>

*/
