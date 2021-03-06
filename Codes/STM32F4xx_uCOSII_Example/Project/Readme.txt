/**
  @page uC/OS-II-v2.91 example Readme file
 
  @verbatim
  ************************* COPYRIGHT 2012 Embest Tech. Co., Ltd.***************
  * @file    readme.txt 
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-December-2012
  * @brief   Description of the STM32F4xx uC/OS-II-v2.91 example.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
  * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
  * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
  */
@par Example Description 

This example provides a description of how to use the uC/OS-II-v2.91 on the STM32F4xx devices.

Two tasks work in this example:
   - App_TaskStar  Control the LED blinking
   - App_TaskKbd   Control the LED blinking frequency by User button pressing

if the Demon run ok
   - LEDs will be blink as follow : LED4 -> LED6 -> LED5 -> LED3
   - press the User button, change blinking speed of the LEDs

@par Directory contents 

  - "inc": contains the project firmware header files    
    - inc/stm32f4xx_conf.h              Library Configuration file
    - inc/system_stm32f4xx.h            STM32F4xx system clock configuration header file
    - inc/app_cfg.h                     Main program Configuration file
    - inc/bsp.h                         Board support package header file
    - inc/includes.h                    includes header file
    - inc/os_cfg.h                      uC/OS-II system Configuration file

  - "src": contains the project firmware source files
    - src/app.c                         Main program
    - src/system_stm32f4xx.c            STM32F4xx system clock configuration file
    - src/bsp.c                         Board support package 
    - src/bsp_int.c                     Interrupt controller related file
    - src/bsp_periph.c                  Peripheral Configuration file

@note The "system_stm32f4xx.c" is generated by an automatic clock configuration 
      tool and can be easily customized to your own configuration. 
      To select different clock setup, use the "STM32F4xx_Clock_Configuration_V1.0.0.xls" 
      provided with the AN3988 package available on <a href="http://www.st.com/internet/mcu/family/141.jsp">  ST Microcontrollers </a>

@par Hardware and Software environment 

  + This example has been tested with the following environment: 
     - STM32F4DISCOVERY board
  
  + Software development tools
    - EWARM V6.40
    - MDK-ARM V4.60

  + Hardware Set-up 
    - Connect the STM32F4DISCOVERY board to a PC with a 'USB type A to Mini-B' cable 
      through USB connector CN1 to power the board.
    - Use the Key user-button

         
@par How to use it ?    

  1. Download uC/OS-II-v2.91 source code.
     You can get it on the Micrium website.As below:
     http://micrium.com/page/downloads/source_code
     Copy uC/OS-II-v2.91 source from the Micrium folder(Micrium\Software\uCOS-II\Source) to Project folder(STM32F4xx_uCOSII_Example\uCOS-II\Source).
     
  2. Load the demonstration code in the STM32F4x7 Flash memory (see below)

  In order to load the Project code, you have do the following:
   - EWARM
      - Open the Project.eww workspace
      - Rebuild all files: Project->Rebuild all
      - Load project image: Project->Debug
      - Run program: Debug->Go(F5)


   - MDK-ARM
      - Open the Project.uvproj project
      - Rebuild all files: Project->Rebuild all target files
      - Load project image: Debug->Start/Stop Debug Session
      - Run program: Debug->Run (F5)     

/******************** COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE****/
