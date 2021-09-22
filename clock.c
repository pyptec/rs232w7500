
#include <stdio.h>
#include "clock.h"
#include "eeprom.h"
#define SLAVE_ADDRESS	0xD0



 /*------------------------------------------------------------------------------
 convierte un binario a bcd 00 a 99
 ------------------------------------------------------------------------------*/
uint8_t bcd(uint8_t carc)
 {
uint8_t temp;
uint8_t bcd;
temp = carc;
 bcd = 0;
	while(1)
	{
    if(temp >= 10)
		{
     temp -= 10;
     bcd += 0x10;
		}
		else
		{  bcd += temp;
    break;
		}
	}  
return(bcd);
 }
 /*------------------------------------------------------------------------------
 convierte un bcd a un binario 
 ------------------------------------------------------------------------------*/
 uint8_t bin(uint8_t bcd_value)
 {
	uint8_t temp;

  temp = bcd_value;
  // Shifting upper digit right by 1 is same as multiplying by 8.
  temp >>= 1;
  // Isolate the bits for the upper digit.
  temp &= 0x78;

  // Now return: (Tens * 8) + (Tens * 2) + Ones

  return(temp + (temp >> 2) + (bcd_value & 0x0f));
 }
 
 

void Set_Data_Write_date_time(Atributos_Ds1307 *clk)
{
	//uint8_t temp_clk;
	clk->second=clk->second & 0x7f;
	clk->hour=clk->hour & 0x3f;
	I2C_Start();
	if(I2C_WriteByte(SLAVE_ADDRESS) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
       
    }
		/*addres 0*/
		if(I2C_WriteByte(SEC) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
		/*Escribe reg 0 que es second*/
			if(I2C_WriteByte(bcd(clk->second)) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
		/*escribe minutos*/
			if(I2C_WriteByte(bcd(clk->minut)) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
		/*escribe horas*/
			if(I2C_WriteByte(bcd(clk->hour)) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
		/*escribe dia de la semana*/
			if(I2C_WriteByte(bcd(clk->dayOfWeek)) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
    	/*escribe el dia del mes*/
			if(I2C_WriteByte(bcd(clk->dayOfMonth)) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
			/*escribe el  mes*/
			if(I2C_WriteByte(bcd(clk-> month)) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
		/*escribe el  año*/
			if(I2C_WriteByte(bcd(clk-> year)) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
		
		 I2C_Stop();
}
void Get_Date_Time(uint8_t* data)
{
	int i;
	uint8_t len=7;
		I2C_Start();
		if(I2C_WriteByte(SLAVE_ADDRESS) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
       
    }
		/*addres 0*/
		if(I2C_WriteByte(SEC) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
    }
		I2C_Start();
			if(I2C_WriteByte(SLAVE_ADDRESS | 1) != 0)
    {
			printf("writee  palabra de control clk NACK !!\r\n");
     
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
}
