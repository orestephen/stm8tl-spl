/** @page EWSTM8_template_project Template project for IAR Embedded Workbench for STM8 (EWSTM8)

  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    Templates/EWSTM8/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Template project for IAR Embedded Workbench for STM8 (EWSTM8)
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

  @par Description

  This folder contains a standard RIDE template workspace with a project 
  including all the user-modifiable files that are necessary to create a new project.
  This project template can be used by mean of minor updates in the library files
  to run the StdPeriph_Lib examples, or custom user applications.  


  @par Directories contents

  - Templates folder
     - main.c                   Main file containing the "main" function
     - stm8tl5x_conf.h          Library Configuration file
     - stm8tl5x_it.c            Interrupt routines source
     - stm8tl5x_it.h            Interrupt routines declaration
     
  - EWSTM8 folder
     - my_project.eww           Workspace file
     - my_project.ewp           IAR Embedded Workbench project


  @par How to use it ?

  - Open the EWSTM8 workspace
  - Rebuild all files: Project-> Rebuild all. 
  - Load project image: Project-> Download and Debug
  - Run program: Debug->Go (Ctrl+F5)
  
<h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>  

*/
