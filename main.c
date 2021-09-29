/*******************************************************************************************************************************************************
 * Diseñado 2021 por Ing. Jaime Pedraza> 
 * Por la presente a cualquier persona que obtenga una copia de este software y los archivos de documentación asociados a el debe tener autorizacion de uso del Ing. Jaime Pedraza
 * o aportar regalias por, los derechos de uso, copia, modificación, fusión, publicación, distribución, sublicencia,
 * y / o vender copias del Software, y permitir que las personas a quienes se les proporcione el Software lo hagan, sujeto a clausulas
 *
 
*********************************************************************************************************************************************************/
/**
  ******************************************************************************
  * @file    Sistema de parque inteligente 
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
#include "main.h"
void NVIC_Configuration(void);
/* Private variables ---------------------------------------------------------*/

uint8_t RxBuffer1[30];
uint8_t RxBuffer2[30];
extern uint8_t buffer_ready;
uint8_t buffer_ready1=0;
uint8_t buffer_ready2=0;
extern uint32_t uart0_rx_cnt;
extern uint32_t uart1_rx_cnt;
extern uint32_t uart2_rx_cnt;
extern uint8_t Buffer_Rta_Lintech[];

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */


int main()
{


	static uint8_t Estado_Comunicacion_Secuencia_MF=SEQ_INICIA_LINTECH;
	
	SystemInit();    

	/*configuramos los I/O como entradas y salidas*/
		IO_int_out();
	
	/*configuracion UART 0, 1, 2*/
		Config_Uart_X();
	/*Configuracion I2C*/
		Config_I2C();
 
 /*programo hora*/
	
	clk.second=00;
	clk.minut=5;
	clk.hour=19;
	clk.dayOfWeek=Miercoles;
	clk.dayOfMonth=22;
	clk.month=9;
	clk.year=21;
	Set_Data_Write_date_time(&clk);
	
/*------------------------------------------------------------------------------------------*/  
	/*configuro el timer*/
	//Config_timer0();
	
	/*configura wiegand*/
		Config_Wiegand();
		 /* NVIC Configuration */
    NVIC_Configuration();
		
    /* Retarget functions for GNU Tools for ARM Embedded Processors*/
		GPIO_SetBits(GPIOA, Led_out_GpioA_8); // LED(R) Off
	//	delay_ms(500);
  //	GPIO_ResetBits(GPIOA, Lock_GpioA_7);
   // GPIO_SetBits(GPIOC, GPIO_Pin_9); // LED(G) Off
	
	
		
	/*------------------------------------------------------------------------------------------*/  	
	
		ValTimeOutCom=TIME_WAIT;
		/*inicio del transporte para la configuracion del password*/
		Estado_Comunicacion_Secuencia_MF=SEQ_INICIA_LINTECH;
		
		while(Estado_Comunicacion_Secuencia_MF != 0)
		{
		Estado_Comunicacion_Secuencia_MF=SecuenciaExpedidorMF(Estado_Comunicacion_Secuencia_MF);
			
		}

		
		ValTimeOutCom=TIME_WAIT;
		
		while(1)
		{
		
			if (GPIO_ReadInputDataBit(GPIOA,  Auto_GpioA_0)== 0)
			{
				printf("Auto on ");
			}
			if (GPIO_ReadInputDataBit(GPIOA,  Sensor1_GpioA_1)== 0)
			{
				printf("Sensor_1 on ");
			}
				if (GPIO_ReadInputDataBit(GPIOA,  Sensor2_GpioA_2)== 0)
			{
				printf("Sensor_2 on ");
			}
				if (GPIO_ReadInputDataBit(GPIOA,  Pulsa_GpioA_5)== 0)
			{
				printf("Pulsa on ");
				GPIO_SetBits(GPIOA, Lock_GpioA_7);	
				delay_ms(500);	
				GPIO_ResetBits(GPIOA, Lock_GpioA_7);
				delay_ms(500);	
				GPIO_SetBits(GPIOA, Atasco_GpioA_6);	
				delay_ms(500);	
				GPIO_ResetBits(GPIOA, Atasco_GpioA_6);
				delay_ms(500);								
			}
			 
			if(wg.completo==1)
			{
				mostrar_wiegand();
				   
				
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
			
		//	Estado_Comunicacion_Secuencia_MF=SecuenciaExpedidorMF(Estado_Comunicacion_Secuencia_MF);
			
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
void Config_timer0(void)
{
	/* NVIC configuration interrupcion */
    NVIC_EnableIRQ(DUALTIMER0_IRQn);
	 /* Dualtimer 0_0 clock enable */
    DUALTIMER_ClockEnable(DUALTIMER0_0);

    /* Dualtimer 0_0 configuration */
    Dualtimer_InitStructure.TimerLoad = 0x4FFFF;
    Dualtimer_InitStructure.TimerControl_Mode = DUALTIMER_TimerControl_Periodic;
    Dualtimer_InitStructure.TimerControl_OneShot = DUALTIMER_TimerControl_Wrapping;
    Dualtimer_InitStructure.TimerControl_Pre = DUALTIMER_TimerControl_Pre_16;
    Dualtimer_InitStructure.TimerControl_Size = DUALTIMER_TimerControl_Size_32;
    
    DUALTIMER_Init(DUALTIMER0_0, &Dualtimer_InitStructure);
    
    /* Dualtimer 0_0 Interrupt enable */
    DUALTIMER_IntConfig(DUALTIMER0_0, ENABLE);
    
    /* Dualtimer 0_0 start */
    DUALTIMER_Start(DUALTIMER0_0);
}
/*------------------------------------------------------------------------------
interrupcion por timer 
ValTimeOutCom se decrementa cada overflow de la interrupcion
Timer_wait		Incrementa cada overflow de la interrrupcion
clock=22.1184mhz
ciclo de mqn= clock/12 =0.5nseg
timer= ciclo mqn* reloj = 0.5 x65535 =32
temporizado=timer* ValTimeOutCom = 32*100=320ms
------------------------------------------------------------------------------*/
void  timer0_int(void) 
{
	//uint8_t data[10]={0};		
			ValTimeOutCom--;
		//	Get_Date_Time(data);
	/*sec*/
	//data[0]=bin(data[0]) & 0x7f;
	/*min*/
//	data[1]=bin(data[1]) & 0x7f;
	/*hr*/
	//data[2]=bin(data[2]) & 0x3f;
	
	/*dow*/
	//data[3]=bin(data[3]) & 0x7f;
	/*day*/
	//data[4]=bin(data[4]) & 0x3f;
	/*mth*/
	//data[5]=bin(data[5]) & 0x1f;
	/*year*/
	//data[6]=bin(data[6]);
	//data[7]=0;
	
		//printf("sec,min,hr,dow,day,mth,year %2d %2d %2d %2d %2d %2d %2d ",data[0],data[1],data[2],data[3],data[4],data[5],data[6])	;	
			if (ValTimeOutCom == 1)
			{
				//Timer_wait++;
			}
			
			//Timer_tivo++;
		
}

void IO_int_out(void)
{
	 /* reles pa6 atasco in,pa7 lock in,pa8 led_ount*/

    GPIO_InitDef.GPIO_Pin = ( Atasco_GpioA_6 | Lock_GpioA_7 | Led_out_GpioA_8) ; 
		//GPIO_InitDef.GPIO_Pad=GPIO_PuPd_UP;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; 
    GPIO_Init(GPIOA, &GPIO_InitDef);
    PAD_AFConfig(PAD_PA,(Atasco_GpioA_6 | Lock_GpioA_7 | Led_out_GpioA_8), PAD_AF1); 
	
	/*entradas auto pa0,sensor2,pa2, pulsa pa5*/
	
		GPIO_InitDef.GPIO_Pin = ( Auto_GpioA_0  | Sensor2_GpioA_2|Pulsa_GpioA_5) ; 
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_Init(GPIOA, &GPIO_InitDef);
    PAD_AFConfig(PAD_PA,(Auto_GpioA_0 | Sensor2_GpioA_2|Pulsa_GpioA_5), PAD_AF1); 
	
	/*entrada sensor 1*/
		GPIO_InitDef.GPIO_Pin = ( Sensor1_GpioA_1) ; 
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_Init(GPIOA, &GPIO_InitDef);
    PAD_AFConfig(PAD_PA,(Sensor1_GpioA_1 ), PAD_AF0); 
}
void Config_Uart_X(void)
{
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
		/*uart2*/
		   S_UART_Init(115200);
    /* Configure Uart2 Interrupt Enable*/
    S_UART_ITConfig((S_UART_CTRL_RXI),ENABLE);
    /* NVIC configuration */
    NVIC_EnableIRQ(UART2_IRQn);
    NVIC_ClearPendingIRQ(UART2_IRQn);
}
void Config_I2C(void)
{
	uint8_t data[11]={"Bienvenido"};
	uint8_t r_data[11]={0};
		conf.scl_pin = GPIO_Pin_9;
   	conf.sda_pin = GPIO_Pin_10;
    I2C_Init(&conf);
		I2C_Write(01,data,10);
		delay_ms(1);
		I2C_Read(01,r_data ,10);
	printf("datos leidos %s \n",r_data);
}
void Config_Wiegand(void)
{
		/*wiegand*/
	
		GPIO_InitDef.GPIO_Pin = (GPIO_Pin_11 | GPIO_Pin_12) ; 
		GPIO_InitDef.GPIO_Pad=GPIO_PuPd_UP;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_Init(GPIOA, &GPIO_InitDef);
		PAD_AFConfig(PAD_PA,(GPIO_Pin_11 | GPIO_Pin_12), PAD_AF1); 
   	printf("Configuardo int DO DI\n");
	

	/* Set to GPIO_Pin_0 to External Interrupt Port */
    EXTI_InitDef.EXTI_Line = ( D0_GpioA_11 | D1_GpioA_12 ); // Connecting GPIO_Pin_0(EXTI Input)D0_GpioA_11 |
    EXTI_InitDef.EXTI_Trigger = EXTI_Trigger_Falling;//EXTI_Trigger_Falling; // Set to Trigger to Rising
    EXTI_Init(PAD_PA, &EXTI_InitDef); // Set to PAD_PA
    EXTI_Polarity_Set(PAD_PA,( D0_GpioA_11 | D1_GpioA_12),EXTI_Trigger_Falling); // Set to Polarity
		printf("Configuardo EXTI_Init\n");
	/* GPIO Interrupt Configuration */
  
		limpia_data();
}
void NVIC_Configuration(void)
{
    NVIC_ClearPendingIRQ(EXTI_IRQn); // Pending bit Clear
    NVIC_EnableIRQ(EXTI_IRQn);       // EXTI Interrupt Enable
		printf("Configuardo NVIC\n");
}

void mostrar_wiegand(void)
{
uint8_t	buffer_wiegand[4]={0};
uint16_t temp;
	ID_Car_Proximidad(buffer_wiegand);
	temp=buffer_wiegand[0];
	printf("Facility_code: %u -",temp);
	temp=(buffer_wiegand[1] <<8)| buffer_wiegand[2] ;
	printf("Code_Card: %u ",temp);
}


	


