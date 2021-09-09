#include <stdio.h>
#include "W7500x.h"
#include "W7500x_gpio.h"

typedef enum
{

    PORT_PA=0
    
}PORT_Type;


typedef struct
{
	PORT_Type  scl_port;
	uint32_t  scl_pin;
	PORT_Type sda_port;
	uint32_t sda_pin;

}I2C_ConfigStruct;
typedef enum
{
	NACK = 0,
	ACK = 1
}ACK_TypeDef;


/*exportar funciones*/
uint32_t I2C_Init(I2C_ConfigStruct* conf);
void I2C_WriteBitSCL(uint8_t data);
void I2C_WriteBitSDA(uint8_t data);
uint8_t I2C_ReadBitSDA(void);
void I2C_SDA_MODE(GPIOMode_TypeDef GPIO_Mode);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendACK(void);
void I2C_SendNACK(void);
uint8_t I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(ACK_TypeDef SetValue);
int I2C_Write(uint8_t addr, uint8_t* data, uint32_t len);
int I2C_Read(uint8_t addr, uint8_t* data, uint32_t len);
int I2C_WriteRepeated(uint8_t addr, uint8_t* data, uint32_t len);
int I2C_ReadRepeated(uint8_t addr, uint8_t* data, uint32_t len);
	
