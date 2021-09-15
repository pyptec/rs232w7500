
#include "lintech.h"

/*extern variable*/

uint8_t Buffer_Rta_Lintech[TBUF_SIZE_LINTECH];


void com_isr (uint8_t cDatoRx ) 
{
//static  unsigned char cDatoRx;
uint8_t bcc, k;
static  uint8_t num_datos;

/*------------------------------------------------
Received data interrupt.
------------------------------------------------*/

		
		switch (g_cEstadoComSoft)
		{
/*------------------------------------------------------------------------------------------------
			espera el ASK de respuesta
-------------------------------------------------------------------------------------------------*/			
			case ESPERA_ASK:
			
			
			if(cDatoRx==ASK)  							// espera el ask
			{
//				aSk=1;															/*se recibe el caracter 06 y se activa*//
						uart0_rx_cnt=0;
			g_cEstadoComSoft=ESPERA_INICIO_RTA;
			
			}
		
		break;
/*------------------------------------------------------------------------------------------------
			se almacena la trama 
-------------------------------------------------------------------------------------------------*/
			case ESPERA_INICIO_RTA:
			{	
				Buffer_Rta_Lintech[uart0_rx_cnt++]=cDatoRx;
				if(Buffer_Rta_Lintech[0]==STX_LINTECH)
				{						
					g_cEstadoComSoft=LEN_DATA;
				}
				else
				{
					g_cEstadoComSoft=ESPERA_ASK;
				}
			}
			break;
/*------------------------------------------------------------------------------------------------
			se toma la longitud de la trama a recibir y se le suman 2 caracteres ETX y BCC
-------------------------------------------------------------------------------------------------*/
		case LEN_DATA:
			
		if (uart0_rx_cnt==3)
		{
			
			num_datos=cDatoRx+2;
			Buffer_Rta_Lintech[uart0_rx_cnt++]=cDatoRx;
			g_cEstadoComSoft=STORE_DATA;			//numero de datos a recibir
		}	
		else
		{			
			Buffer_Rta_Lintech[uart0_rx_cnt++]=cDatoRx;
			g_cEstadoComSoft=LEN_DATA;
		}

		break;
/*------------------------------------------------------------------------------------------------
		se almacena los datos 
-------------------------------------------------------------------------------------------------*/
		case STORE_DATA:
			
				Buffer_Rta_Lintech[uart0_rx_cnt++]=cDatoRx;	
				num_datos--;
 				if (num_datos==0)
				{
					if(Buffer_Rta_Lintech[uart0_rx_cnt-2]==ETX)
					{
						bcc=0;
						for (k=0; k<uart0_rx_cnt-1; k++)
						{
							bcc=Buffer_Rta_Lintech[k]^bcc;
						}
							if (bcc==Buffer_Rta_Lintech[uart0_rx_cnt-1])	
							{
	//							aSk=0;
	//							cnt__ask_off=0;
								buffer_ready=1;
								g_cEstadoComSoft=ESPERA_ASK;											/* bcc ok trama valida*/
													
							}
							else
							{
								g_cEstadoComSoft=ESPERA_ASK;											/* bcc no concuerda  trama no valida*/
							}
					}	
					else 
					{
						g_cEstadoComSoft=ESPERA_ASK;													/*  no concuerda  ETX en la trama no valida*/
					}	
								
				}
				else 
				{
					g_cEstadoComSoft=STORE_DATA;													/* espera datos*/
				}
 			 
		break;		
	
/*------------------------------------------------------------------------------------------------
		
-------------------------------------------------------------------------------------------------*/				
		default:
			g_cEstadoComSoft=ESPERA_ASK;
		break;
		}
 	
}



void EscribirCadenaSoft_buffer(uint8_t *buffer,uint8_t tamano_cadena)
{
	uint8_t i;
		for(i=0;i<tamano_cadena;i++)
   	{
      UartPutc(UART0,*buffer);
			buffer++;
    }
}

