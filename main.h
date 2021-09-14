
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "W7500x_uart.h"
#include "W7500x_gpio.h"
#include "eeprom.h"
/* Private macro struct -------------------------------------------------------------*/

UART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
I2C_ConfigStruct conf;

/* Private function prototypes -----------------------------------------------*/
void delay_ms(__IO uint32_t nCount);
void led_on(void);
