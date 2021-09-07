/*******************************************************************************************************************************************************
 * Copyright ¨Ï 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ¡°Software¡±), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ¡°AS IS¡±, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
/**
  ******************************************************************************
  * @file    Uart/Printf/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "W7500x_uart.h"
#include "W7500x_gpio.h"
//#include "i2c.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define SLAVE_ADDRESS	0x78
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
//I2C_ConfigStruct conf;
uint8_t RxBuffer[30];
uint8_t RxBuffer1[30];
uint8_t RxBuffer2[30];
uint8_t buffer_ready=0;
uint8_t buffer_ready1=0;
uint8_t buffer_ready2=0;
extern uint32_t uart0_rx_cnt;
extern uint32_t uart1_rx_cnt;
extern uint32_t uart2_rx_cnt;
/* Private function prototypes -----------------------------------------------*/
void delay_ms(__IO uint32_t nCount);
void led_on(void);
//void Config_io(void);
//uint32_t I2C_Init(I2C_ConfigStruct* conf);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */


int main()
{
	
    /*System clock configuration*/
	SystemInit();    
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
	/*configuramos los led*/
	 /* GPIO LED1 & LED2 Set */
    GPIO_InitDef.GPIO_Pin = ( GPIO_Pin_8 | GPIO_Pin_9) ; // Set to Pin_1 (LED1) & Pin_2 (LED2)
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,(GPIO_Pin_8|GPIO_Pin_9), PAD_AF1); // PAD Config - LED used 2nd 
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function    
/*------------------------------------------------------------------------------------------*/  
  /* UART0  configuration*/
/*------------------------------------------------------------------------------------------*/  
    UART_StructInit(&UART_InitStructure);
    /* Configure UART0 */
    UART_Init(UART0,&UART_InitStructure);
	 /* Configure Uart0 Interrupt Enable*/
    UART_ITConfig(UART0, (UART_IT_FLAG_TXI|UART_IT_FLAG_RXI),ENABLE);
	 /* NVIC configuration */
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);

/*------------------------------------------------------------------------------------------*/  
  /* UART1  configuration*/
/*------------------------------------------------------------------------------------------*/  
   
    /* Configure UART1 */
    UART_Init(UART1,&UART_InitStructure);
	 /* Configure Uart0 Interrupt Enable*/
    UART_ITConfig(UART1, (UART_IT_FLAG_TXI|UART_IT_FLAG_RXI),ENABLE);
	 /* NVIC configuration */
    NVIC_ClearPendingIRQ(UART1_IRQn);
    NVIC_EnableIRQ(UART1_IRQn);
/*------------------------------------------------------------------------------------------*/  
		//	S_UART_Init(9600); 	//configurar serial 2
			
			 /* Configure Uart2 Interrupt Enable*/
			
		//	S_UART_ITConfig((S_UART_CTRL_TXI|S_UART_CTRL_RXI),ENABLE);
		 /* NVIC configuration */
   		
		//	NVIC_EnableIRQ(UART2_IRQn);
		//	NVIC_ClearPendingIRQ(UART2_IRQn);			
/*------------------------------------------------------------------------------------------*/  
    /* Retarget functions for GNU Tools for ARM Embedded Processors*/
		GPIO_SetBits(GPIOC, GPIO_Pin_8); // LED(R) Off
    GPIO_SetBits(GPIOC, GPIO_Pin_9); // LED(G) Off
		//S_UartPuts("hola Colombia\r\n");
		while(1)
		{
			//led_on(); 
		//	UartPuts(UART1,"UART 1 Test(#1)\r\n");
			if(buffer_ready== 1)
			{
				UartPuts(UART0,RxBuffer);
				uart0_rx_cnt=0;
				RxBuffer[0]=0;
				buffer_ready=0;
			}
			if (buffer_ready1== 1)
			
			{
				UartPuts(UART1,RxBuffer1);
				uart1_rx_cnt=0;
				RxBuffer1[0]=0;
				buffer_ready1=0;
			}
			if (buffer_ready2== 1)
			
			{
				S_UartPuts(RxBuffer2);
				uart2_rx_cnt=0;
				RxBuffer2[0]=0;
				buffer_ready2=0;
			}
		}
}
void delay_ms(__IO uint32_t nCount)
{
    volatile uint32_t delay = nCount * 2500; // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}
void led_on()
{
	// LED(RG) On/off			
		delay_ms(500);
  	GPIO_ResetBits(GPIOC, GPIO_Pin_8);				
	  GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	  delay_ms(500);
	  GPIO_SetBits(GPIOC, GPIO_Pin_8);
    GPIO_SetBits(GPIOC, GPIO_Pin_9);
}
/*void Config_io()
{
	//uint32_t data;
//GPIO setting for I2C

	conf.scl_port = PORT_PA;
	conf.scl_pin = GPIO_Pin_9;
    conf.sda_port = PORT_PA;
	conf.sda_pin = GPIO_Pin_10;
//
    //data=
	I2C_Init(&conf);
}
*/
