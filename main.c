/*******************************************************************************************************************************************************
 * Diseñado 2021 por Ing. Jaime Pedraza> 
 * Por la presente a cualquier persona que obtenga una copia de este software y los archivos de documentación asociados a el debe tener autorizacion de uso del Ing. Jaime Pedraza
 * o aportar regalias por, los derechos de uso, copia, modificación, fusión, publicación, distribución, sublicencia,
 * y / o vender copias del Software, y permitir que las personas a quienes se les proporcione el Software lo hagan, sujeto a clausulas
 *
 
*********************************************************************************************************************************************************/
/**
  ******************************************************************************
  * @file    Uart/Printf/main.c 
  * @author  Jaime Pedraza
  * @version V1.0.0
  * @date    01-Junio-2021
  * @brief   Cuerpo del programa
  ******************************************************************************
  * @attention
  *
  * 
  *
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "W7500x_uart.h"
#include "W7500x_gpio.h"
#include "eeprom.h"
//#include "i2c.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SLAVE_ADDRESS	0xA0
/* Private macro struct -------------------------------------------------------------*/

UART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
I2C_ConfigStruct conf;

/* Private variables ---------------------------------------------------------*/
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

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */


int main()
{
	uint8_t data[1] = {0xAA};
  uint8_t r_data[1] ={0,};
	
    /*System clock configuration*/
	SystemInit();    
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
	/*configuramos los led*/
	 /* GPIO LED1 & LED2 Set */
    GPIO_InitDef.GPIO_Pin = ( GPIO_Pin_8 | GPIO_Pin_9) ; // Set to Pin_1 (LED1) & Pin_2 (LED2)
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,(GPIO_Pin_8|GPIO_Pin_9), PAD_AF1); // PAD Config - LED used 2nd 
	
/*------------------------------------------------------------------------------------------*/  
/*configuro I2C pines */
/*------------------------------------------------------------------------------------------*/  
		conf.scl_pin = GPIO_Pin_9;
   	conf.sda_pin = GPIO_Pin_10;
    
 
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
		I2C_Init(&conf);
		I2C_Write(SLAVE_ADDRESS,data,1);
		I2C_Read(SLAVE_ADDRESS,r_data ,1);
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

