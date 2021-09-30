

#include <stdio.h>
#include "eeprom.h"


/*definiciones de la rutina*/
#define SLAVE_ADDRESS	0xA0					//para leer

/*definicion de funciones*/
extern void        UartPuts                (UART_TypeDef* UARTx, uint8_t *str);
extern GPIO_InitTypeDef GPIO_InitDef;
extern void delay_ms(__IO uint32_t nCount);

/* Private variables ---------------------------------------------------------*/
uint32_t scl_port_num;
uint32_t scl_pin_index;
uint32_t sda_port_num;
uint32_t sda_pin_index;

/*definicion de pines*/


uint32_t I2C_Init(I2C_ConfigStruct* conf)
{
	/*configuramos scl y sda */
		
    scl_pin_index = conf->scl_pin;
    sda_pin_index = conf->sda_pin;
	
	/*configuracion  scl I/O*/
	
	  GPIO_InitDef.GPIO_Pin = (scl_pin_index );
	  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOA, &GPIO_InitDef);
    PAD_AFConfig(PAD_PA,(scl_pin_index ), PAD_AF1); // PAD Config - use scl
	
		/*reloj en high*/
	
		GPIO_SetBits(GPIOA,scl_pin_index);
	
	/*configuro sda */
	
		GPIO_InitDef.GPIO_Pin = (sda_pin_index );
	  GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN; // Set to Mode Output
    GPIO_Init(GPIOA, &GPIO_InitDef);
    PAD_AFConfig(PAD_PA,(sda_pin_index ), PAD_AF1); // PAD Config - use scl
		
	/*sda en low*/
		GPIO_ResetBits(GPIOA, sda_pin_index);	
	
	return 0;
}
void I2C_WriteBitSCL(uint8_t data)
{
	if(data == 1)
		GPIO_SetBits(GPIOA, scl_pin_index);
  else
		GPIO_ResetBits(GPIOA, scl_pin_index);
}
void I2C_WriteBitSDA(uint8_t data)
{
	if(data == 1)
		GPIO_SetBits(GPIOA, sda_pin_index);
    else
		GPIO_ResetBits(GPIOA, sda_pin_index);
}
uint8_t I2C_ReadBitSDA(void)
{
	
	if(GPIOA->DATA & sda_pin_index)
     return 1;
   else
		 return 0;
}
void I2C_SDA_MODE(GPIOMode_TypeDef GPIO_Mode)
{
	if(GPIO_Mode == 0)

			GPIOA->OUTENCLR = sda_pin_index; //(GPIO INPUT)
        else
			GPIOA->OUTENSET = sda_pin_index; //(GPIO OUTPUT)
}
void I2C_Start(void)
{
		I2C_SDA_MODE(GPIO_Mode_OUT);
	  I2C_WriteBitSCL(1);
    I2C_WriteBitSDA(1);
		__NOP();
    I2C_WriteBitSDA(0);
    I2C_WriteBitSCL(0);
}

void I2C_Stop(void)
{
	I2C_SDA_MODE(GPIO_Mode_OUT);

		I2C_WriteBitSCL(0);
    I2C_WriteBitSDA(0);
		__NOP();
    I2C_WriteBitSCL(1);
    I2C_WriteBitSDA(1);
	I2C_SDA_MODE(GPIO_Mode_IN);
}

void I2C_SendACK(void)
{
    I2C_WriteBitSDA(0);
    I2C_WriteBitSCL(1);
    I2C_WriteBitSCL(0);
}
void I2C_SendNACK(void)
{
    I2C_WriteBitSDA(1);
    I2C_WriteBitSCL(1);
    I2C_WriteBitSCL(0);
}

uint8_t I2C_WriteByte(uint8_t data)
{
int i;
uint8_t ret;
uint8_t sda;


    //Write byte
	I2C_SDA_MODE(GPIO_Mode_OUT);
    for(i=0; i<8; i++)
    {

        sda = ((data<<i) & 0x80) ;
		if(sda == 0x80)
			I2C_WriteBitSDA(1);
		else
			I2C_WriteBitSDA(0);

        I2C_WriteBitSCL(1);
        I2C_WriteBitSCL(0);
    }
    //Make clk for receiving ack
    I2C_SDA_MODE(GPIO_Mode_IN);
	I2C_WriteBitSCL(1);


    //Read Ack/Nack
    ret = I2C_ReadBitSDA();

    I2C_WriteBitSCL(0);

    return ret;
}
uint8_t I2C_ReadByte(ACK_TypeDef SetValue)
{
    int i;
    uint8_t ret = 0;

	I2C_SDA_MODE(GPIO_Mode_IN);

    //Read byte
    for(i=0; i<8; i++)
    {
        I2C_WriteBitSCL(1);
        ret = (ret << 1) | (I2C_ReadBitSDA());
        I2C_WriteBitSCL(0);
    }
	I2C_SDA_MODE(GPIO_Mode_OUT);


	if(SetValue == NACK )
		I2C_SendNACK();
	else
		I2C_SendACK();

    I2C_SDA_MODE(GPIO_Mode_IN);

    return ret;
}

int I2C_Write(uint16_t addr, uint8_t* data, uint32_t len)
{
   int i;
	uint8_t Dir_high,Dir_low;
	Dir_low=addr;
	Dir_high =addr >>8;

/*inicio i2c*/
    I2C_Start();

    //Write palabra de control 0xa0
    if(I2C_WriteByte(SLAVE_ADDRESS) != 0)
    {
		    printf("Received NACK at address phase!!\r\n");
        return -1;
    }
		
		//write addres high
		 if(I2C_WriteByte(Dir_high) != 0)
    {
		    printf("Received NACK at address phase!!\n");
        return -1;
    }
			//write addres low
		 if(I2C_WriteByte(Dir_low) != 0)
    {
		    printf("Received NACK at address phase!!\n");
        return -1;
    }
		
    //Write data
    for(i=0; i<len; i++)
    {
        if(I2C_WriteByte(data[i]))  return -1;
    }
    I2C_Stop();
		delay_ms(1);
    return 0;
}

int I2C_Read(uint16_t addr, uint8_t* data, uint32_t len)
{
 int i;
uint8_t Dir_high,Dir_low;
	 Dir_low=addr;
	 Dir_high =addr >>8;
	
	
    I2C_Start();

 //Write palabra de control 0xa0
    if(I2C_WriteByte(SLAVE_ADDRESS) != 0)
    {
				printf("Received NACK at palabra a0 control!!\r\n");
		    
    }
    //Write addr high
    if(I2C_WriteByte(Dir_high) != 0)
    {
      printf("Received NACK at address high phase!!\r\n");               
			
      //  return -1;
    }
		//Write addrlow
		   if(I2C_WriteByte(Dir_low) != 0)
    {
      printf("Received NACK at address low phase!!\r\n");               
			 return -1;
    }
		/*inicia*/
		I2C_Start();
		
		//Write palabra de control 0xa1
    if(I2C_WriteByte(SLAVE_ADDRESS | 1) != 0)
    {
			printf("Received NACK at palabra a1 control!!\r\n");
      
      //  return -1;
    }
    /*Read data*/
    for(i=0; i<len; i++)
    {
        if( i == (len - 1))
			data[i] = I2C_ReadByte(NACK);
        else
			data[i] = I2C_ReadByte(ACK);

    }
    I2C_Stop();

    return 0;//success
}
int I2C_WriteRepeated(uint8_t addr, uint8_t* data, uint32_t len)
{
    int i;

    I2C_Start();


    //Write addr
    if(I2C_WriteByte(addr) != 0)
    {
			UartPuts(UART0,"Received NACK at address phase!!\r\n");
       // printf("Received NACK at address phase!!\r\n");
        return -1;
    }

    //Write data
    for(i=0; i<len; i++)
    {
        if(I2C_WriteByte(data[i]))    return -1;
    }
    return 0;//success
}
int I2C_ReadRepeated(uint8_t addr, uint8_t* data, uint32_t len)
{
    int i;
    I2C_Start();
    //Write addr | read command
    if(I2C_WriteByte((addr | 1)) != 0)
    {
			UartPuts(UART0,"Received NACK at address phase!!\r\n");
      //  printf("Received NACK at address phase!!\r\n");
        return -1;
    }
    //Read data
    for(i=0; i<len; i++)
    {
        if( i == (len - 1))
			data[i] = I2C_ReadByte(NACK);
        else
			data[i] = I2C_ReadByte(ACK);


		I2C_SendACK();
    }
    return 0;//success
}

int rd_eeprom(uint16_t addr)
{
 int i;
uint8_t Dir_high,Dir_low,len,data;
	 Dir_low=addr;
	 Dir_high =addr >>8;
	
	
    I2C_Start();

 //Write palabra de control 0xa0
    if(I2C_WriteByte(SLAVE_ADDRESS) != 0)
    {
				printf("Received NACK at palabra a0 control!!\r\n");
		    
    }
    //Write addr high
    if(I2C_WriteByte(Dir_high) != 0)
    {
      printf("Received NACK at address high phase!!\r\n");               
			
      //  return -1;
    }
		//Write addrlow
		   if(I2C_WriteByte(Dir_low) != 0)
    {
      printf("Received NACK at address low phase!!\r\n");               
		//	 return -1;
    }
		/*inicia*/
		I2C_Start();
		
		//Write palabra de control 0xa1
    if(I2C_WriteByte(SLAVE_ADDRESS | 1) != 0)
    {
			printf("Received NACK at palabra a1 control!!\r\n");
      
      //  return -1;
    }
    /*Read data*/
		len=1;
    for(i=0; i<len; i++)
    {
        if( i == (len - 1))
			data = I2C_ReadByte(NACK);
        else
			data = I2C_ReadByte(ACK);

    }
    I2C_Stop();

    return data;//success
}

int wr_eeprom(uint16_t addr, uint8_t data)
{
   int i;
	uint8_t Dir_high,Dir_low,len;
	Dir_low=addr;
	Dir_high =addr >>8;

/*inicio i2c*/
    I2C_Start();

    //Write palabra de control 0xa0
    if(I2C_WriteByte(SLAVE_ADDRESS) != 0)
    {
		    printf("Received NACK at address phase!!\r\n");
        return -1;
    }
		
		//write addres high
		 if(I2C_WriteByte(Dir_high) != 0)
    {
		    printf("Received NACK at address phase!!\n");
        return -1;
    }
			//write addres low
		 if(I2C_WriteByte(Dir_low) != 0)
    {
		    printf("Received NACK at address phase!!\n");
        return -1;
    }
		len=1;
    //Write data
    for(i=0; i<len; i++)
    {
        if(I2C_WriteByte(data))  return -1;
    }
    I2C_Stop();
		delay_ms(1);
    return 0;
}
