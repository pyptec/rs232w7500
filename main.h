
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "W7500x_uart.h"
#include "W7500x_gpio.h"
#include "W7500x_dualtimer.h"
#include "eeprom.h"
#include "lintech.h"
#include "expedidor.h"
#include "debuger.h"
#include "clock.h"
/* Private macro struct -------------------------------------------------------------*/

UART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
I2C_ConfigStruct conf;
DUALTIMER_InitTypDef Dualtimer_InitStructure;
Atributos_Ds1307 clk;

/*salidas*/
#define Atasco_GpioA_6	GPIO_Pin_6
#define Lock_GpioA_7		GPIO_Pin_7
#define Led_out_GpioA_8	GPIO_Pin_8
/*entradas*/
#define Auto_GpioA_0		GPIO_Pin_0
#define Sensor1_GpioA_1	GPIO_Pin_1
#define Sensor2_GpioA_2	GPIO_Pin_2
#define Pulsa_GpioA_5		GPIO_Pin_5




uint8_t g_cEstadoComSoft=0;									//estados del pto serie UART0
uint8_t buffer_ready=0;
uint8_t ValTimeOutCom=0;

/* Private function prototypes -----------------------------------------------*/
void delay_ms(__IO uint32_t nCount);
void led_on(void);
void Config_timer0(void);
void IO_int_out(void);
void Config_Uart_X(void);
void Config_I2C(void);




