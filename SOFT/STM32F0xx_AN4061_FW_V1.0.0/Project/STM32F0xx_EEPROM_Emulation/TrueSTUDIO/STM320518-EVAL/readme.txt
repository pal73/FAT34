/**
  @page TrueSTUDIO TrueSTUDIO Project Template for STM32F0xx devices
  
  @verbatim
  ******************* (C) COPYRIGHT 2012 STMicroelectronics ********************
  * @file    readme.txt
  * @author  MCD Application Team
  * @version V1.0.0RC1
  * @date    27-January-2012
  * @brief   This sub-directory contains all the user-modifiable files needed
  *          to create a new project linked with the STM32F0xx Standard Peripheral 
  *          Library and working with TrueSTUDIO for ARM software toolchain
  *          (version 3.0.0 and later).
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
 
 @par Directory contents

 -  .cproject/.project: A pre-configured project file with the provided library
                        structure that produces an executable image with TrueSTUDIO.

 - stm32_flash.ld:             This file is the TrueSTUDIO linker script used to 
                               place program code (readonly) in internal FLASH and
                               data (readwrite, Stack and Heap)in internal SRAM. 
                               You can customize this file to your need.

 @par How to use it ?

 - Open the TrueSTUDIO toolchain.
 - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace 
   directory.
 - Click on File->Import, select General->'Existing Projects into Workspace' 
   and then click "Next". 
 - Browse to the TrueSTUDIO workspace directory and select the project: 
   - STM320518-EVAL: to configure the project for STM32F0xx devices.
     @note The needed define symbols for this config are already declared in the
           preprocessor section: USE_STDPERIPH_DRIVER, STM32F0XX, USE_STM320518_EVAL
 - Rebuild all project files: Select the project in the "Project explorer" 
   window then click on Project->build project menu.
 - Run program: Select the project in the "Project explorer" window then click 
   Run->Debug (F11)

@note
 - STM32F0xx devices are STM32F051xx microcontrollers where the Flash memory 
   density ranges between 32 and 64 Kbytes.

 * <h3><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h3>
 */
