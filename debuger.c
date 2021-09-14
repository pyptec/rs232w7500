#include "debuger.h"

extern uint8_t S_UartPutc(uint8_t ch);


void Debug_chr_UART2(uint8_t Dat)
{
uint8_t temp;
	temp=(Dat&0xf0)>>4;
	(temp>0x09)?(temp=temp+0x37):(temp=temp+0x30);
	S_UartPutc(temp);
	temp=(Dat&0x0f);
	(temp>0x09)?(temp=temp+0x37):(temp=temp+0x30);
	S_UartPutc(temp);
	S_UartPutc(' ');
}
void Debug_Buffer_UART2(uint8_t *str,uint8_t num_char)
{
uint8_t j;
	
	for (j=0; j<num_char; j++)
		{
		Debug_chr_UART2(*str);
		str++;
		}
		S_UartPutc('\n');
	
}
void Debug_txt_UART2(uint8_t * str)
{
	uint8_t i;
	i=0;
	
	
		for (i=0; str[i] != '\0'; i++)
		{
 	  		S_UartPutc(str[i]);
		}
		
}
void DebugBufferMF(uint8_t *str,uint8_t num_char,MSG_DEBUG_Estado Estado)
{
uint8_t j;
 
  	if(Estado == DATA_RECIBIDO)
		{
			printf("Datos Recibidos del Transporte: ");
		}
		else if  (Estado == DATA_ENVIADO)
		{
			printf("Datos Enviados al Transporte: ");
		}
			
		for (j=0; j<num_char; j++)
		{
		Debug_chr_UART2(*str);
		str++;
		}
		S_UartPutc('\r');
		S_UartPutc('\n');
}



