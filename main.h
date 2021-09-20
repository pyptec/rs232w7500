
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "W7500x_uart.h"
#include "W7500x_gpio.h"
#include "eeprom.h"
#include "lintech.h"
#include "expedidor.h"
#include "debuger.h"
/* Private macro struct -------------------------------------------------------------*/

UART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
I2C_ConfigStruct conf;

uint8_t g_cEstadoComSoft=0;									//estados del pto serie UART0
uint8_t buffer_ready=0;

/* Private function prototypes -----------------------------------------------*/
void delay_ms(__IO uint32_t nCount);
void led_on(void);
