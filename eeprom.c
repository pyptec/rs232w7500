


#include "eeprom.h"


/*definicion de variables*/


/*definicion de pines*/

#define	scl_pin	GPIO_Pin_9
#define sda_pin	GPIO_Pin_10

uint32_t I2C_Init(GPIO_InitTypeDef* conf)
//uint32_t configi2c(void)
{
	/*configuramos los scl como salida*/
	  
    conf->GPIO_Pin = (GPIO_Pin_9) ; 
    conf->GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOA, &conf);
    PAD_AFConfig(PAD_PC,(scl_pin), PAD_AF1); // PAD Config - LED used 2nd 
	return 0;
}

void ackd (void)
{
	
}

void start(void)
{
	
}
