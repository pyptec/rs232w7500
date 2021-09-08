#include <stdio.h>
#include "W7500x.h"
#include "W7500x_gpio.h"
/*exportar funciones*/
//void configi2c(void);
uint32_t I2C_Init(GPIO_InitTypeDef* conf);
void ackd (void);
void start(void);
