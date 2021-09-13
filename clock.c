
#include "clock.h"
#define SLAVE_ADDRESS	0xD0


/*------------------------------------------------------------------------------
rutinas de conversiones  de bcd a hex
------------------------------------------------------------------------------*/
uint8_t  bcd_hex (uint8_t l_data)
 {
 	uint8_t  temp,j;
	temp=l_data;
	temp>>=4;
	temp=temp & 0x0f;
	if (temp!=0x00)
	{
		l_data=l_data & 0x0f;
	 	for (j=0;j<temp;j++)
	 	{
	  	 	l_data=l_data+0x0a;
	 	}	
	}
	return l_data;
 }
 void hex_ascii(unsigned char * datos,unsigned char * fecha_asii)
{
uint8_t dato;
	
		//dato=hex_bcd (*datos);
		*fecha_asii=((dato&0xf0)>>4)| 0x30;			/*dato parte alta*/
	 	*(fecha_asii+1)=(dato&0x0f)| 0x30;						/*dato parte bajo*/
	  datos++;
}
void inicializa_reloj()
{
//	uint8_t  i, len;
//	uint8_t  dato[2]={0,0};
		I2C_Start();
	  if(I2C_WriteByte(SLAVE_ADDRESS) != 0)
    {
			UartPuts(UART0,(unsigned char *)"writee  palabra de control clk NACK !!\r\n");
     
       // return -1;
    }
		/*direccion del reloj*/
		if(I2C_WriteByte(YEAR) != 0)
    {
			UartPuts(UART0,(unsigned char *)"writee  palabra de control clk NACK !!\r\n");
     
      //  return -1;
    }
		
	//	I2C_Stop;
		
		I2C_Start();
		/*palabra de control de read*/
		if(I2C_WriteByte(SLAVE_ADDRESS | 1) != 0)
    {
			UartPuts(UART0,(unsigned char *)"writee  palabra de control clk NACK !!\r\n");
     
        //return -1;
    }
		
	//	for(i=0; i<len; i++)
   // {
       // if( i == (len - 1))
			//dato[0] = I2C_ReadByte(NACK);
//        else
			//dato[0] = I2C_ReadByte(ACK);

    //}
    I2C_Stop();
}
