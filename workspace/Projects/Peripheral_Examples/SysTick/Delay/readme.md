/*******************************************************************************************************************************************************
 * Copyright ?? 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ??Software??), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ??AS IS??, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
#Delay example (System tick timer example)
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : SysTick/Delay/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of systic timer delay example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example shows how to use SysTick of W7500.

In this example:
  - 1) Configuration SysTick
  - 2) Run delay fucntion with 1sec
______________________________________________________________________________

### Directory contents

  - SysTick/Delay/main.c                                (Main program)
  - SysTick/Delay/W7500x_it.c                           (Interrupt Handlers)
  - SysTick/Delay/W7500x_it.h                           (Interrupt Handlers Header file)
  - SysTick/Delay/W7500x_conf.h                         (Library Configuration file)
  - SysTick/Delay/MDK/W7500x_SysTick_Delay.uvproj     (MDK Project file)
  - SysTick/Delay/GCC/Makefile                          (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up
    - No need to hardware setup
______________________________________________________________________________

### How to use it ? 

In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"
______________________________________________________________________________


<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>