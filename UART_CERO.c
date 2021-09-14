#include "UART_CERO.h"


extern uint32_t uart0_rx_cnt;
uint8_t Buffer_Rta_Lintech[TBUF_SIZE_LINTECH];
static void com_isr (void) 
{
//static  unsigned char cDatoRx;
uint8_t bcc;
//static  unsigned char num_datos;

/*------------------------------------------------
Received data interrupt.
------------------------------------------------*/

		
//		switch (g_cEstadoComSoft)
//		{
/*------------------------------------------------------------------------------------------------
			espera el ASK de respuesta
-------------------------------------------------------------------------------------------------*/			
//			case ESPERA_RX:
			
			
//			if(cDatoRx==ACK)  							// espera el ask
	//		{
//				aSk=1;															/*se recibe el caracter 06 y se activa*//
	//		g_cContByteRx=0;r_in=0;r_out=0;	
		//	g_cEstadoComSoft=ESPERA_INICIO_RTA;
			
	//		}
		
	//	break;
/*------------------------------------------------------------------------------------------------
			se almacena la trama 
-------------------------------------------------------------------------------------------------*/
//			case ESPERA_INICIO_RTA:
//			{	
//				Buffer_Rta_Lintech[g_cContByteRx++]=cDatoRx;
//				if(Buffer_Rta_Lintech[0]==STX_LINTECH)
//				{						
//					g_cEstadoComSoft=LEN_DATA;
//				}
//				else
//				{
//					g_cEstadoComSoft=ESPERA_RX;
//				}
//			}
//			break;
/*------------------------------------------------------------------------------------------------
			se toma la longitud de la trama a recibir y se le suman 2 caracteres ETX y BCC
-------------------------------------------------------------------------------------------------*/
//		case LEN_DATA:
			
//		if (g_cContByteRx==3)
//		{
			
	//		num_datos=cDatoRx+2;
		//	Buffer_Rta_Lintech[g_cContByteRx++]=cDatoRx;
	//		g_cEstadoComSoft=STORE_DATA;			//numero de datos a recibir
	//	}	
//		else
//		{			
//			Buffer_Rta_Lintech[g_cContByteRx++]=cDatoRx;
	//		g_cEstadoComSoft=LEN_DATA;
	//	}

	//	break;
/*------------------------------------------------------------------------------------------------
		se almacena los datos 
-------------------------------------------------------------------------------------------------*/
	//	case STORE_DATA:
			
	//			Buffer_Rta_Lintech[g_cContByteRx++]=cDatoRx;	
	//			num_datos--;
 	//			if (num_datos==0)
	//			{
	//				if(Buffer_Rta_Lintech[g_cContByteRx-2]==ETX)
	//				{
	//					bcc=0;
	//					for (k=0; k<g_cContByteRx-1; k++)
	//					{
	//						bcc=Buffer_Rta_Lintech[k]^bcc;
	//					}
	//						if (bcc==Buffer_Rta_Lintech[g_cContByteRx-1])	
	//						{
	//							aSk=0;
	//							cnt__ask_off=0;
	//							buffer_ready=1;
	//							g_cEstadoComSoft=ESPERA_RX;											/* bcc ok trama valida*/
													
	//						}
	//						else
	//						{
	//							g_cEstadoComSoft=ESPERA_RX;											/* bcc no concuerda  trama no valida*/
	//						}
	//				}	
	//				else 
	//				{
	//					g_cEstadoComSoft=ESPERA_RX;													/*  no concuerda  ETX en la trama no valida*/
	//				}	
								
	//			}
	//			else 
	//			{
	//				g_cEstadoComSoft=STORE_DATA;													/* espera datos*/
	//			}
 			 
	//	break;		
	//case STORE_PLACA:
	//	Buffer_Rta_Lintech[g_cContByteRx++]=cDatoRx;	
	//	if(Buffer_Rta_Lintech[g_cContByteRx-1]==ETX || (g_cContByteRx==8) )
	//	{
	//		aSk=0;
	//		buffer_ready=1;
	//		g_cEstadoComSoft=ESPERA_RX;
	//	}
		
	//	break;
/*------------------------------------------------------------------------------------------------
		
-------------------------------------------------------------------------------------------------*/				
	//	default:
	//		g_cEstadoComSoft=ESPERA_RX;
	//	break;
	//	}
  //}

/*------------------------------------------------
Transmitted data interrupt.
------------------------------------------------*/
//if (TI != 0)
 // {
  //TI = 0;

  //if (t_in != t_out)
  //  {
   // SBUF = tbuf [t_out & (TBUF_SIZE-1)];
	
//   t_out++;
  //  ti_restart = 0;
   //}
  //else
   // {
    //ti_restart = 1;
    //}
  //}
	
}
