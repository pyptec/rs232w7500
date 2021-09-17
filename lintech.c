
#include "lintech.h"
/*----------------------------------------------------------------------------
funcion de inicializacion del transporte

------------------------------------------------------------------------------*/

extern uint8_t Buffer_Rta_Lintech[];
extern uint8_t g_cEstadoComSoft;	
uint8_t cnt__ask_off=0;

void Inicializa(TIPO_movimiento SetValue)
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[10];
	bcc=0;
	if ((SetValue==SIN_MOVIMIENTO)||(SetValue==TO_FRONT)||(SetValue==CAPTURE_BOX))
	{
		if(SetValue==SIN_MOVIMIENTO)
		{
		printf("Inicializa Dispensador SIN_MOVIMIENTO \r\n");
		}
	
		else if (SetValue == TO_FRONT)
		{
			printf( "Inicializa Dispensador TO_FRONT \r\n");
		}
		else 
		{
		printf("Inicializa Dispensador CAPTURE_BOX \r\n");
		}
	}
	else
	{
		printf("TIPO_movimiento no existe \r\n");
	}
	
		g_scArrTxComSoft[0]=STX_LINTECH;
		g_scArrTxComSoft[1]=0X00;
		g_scArrTxComSoft[2]=0X00;
		g_scArrTxComSoft[3]=0X03;
		g_scArrTxComSoft[4]='C';
		g_scArrTxComSoft[5]='0';
		g_scArrTxComSoft[6]=SetValue;
		g_scArrTxComSoft[7]=ETX;
		for (j=0; j<8; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[8]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,9,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,9);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
	
}
void Check_Status(SENSOR_detalle Detalle)
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[10];

	if (Detalle == SENSOR_NORMAL)
		{
			printf("Check_Status SENSOR_NORMAL\r\n");
		}
		else
		{
			printf( "Check_Status SENSOR_DETAIL\r\n");
		}
	bcc=0;

	g_scArrTxComSoft[0]=STX_LINTECH;
	g_scArrTxComSoft[1]=0X00;
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=0X03;
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]='1';
	g_scArrTxComSoft[6]=Detalle;
	g_scArrTxComSoft[7]=ETX;
	for (j=0; j<8; j++)
	{
		bcc=g_scArrTxComSoft[j]^bcc;
	}
	g_scArrTxComSoft[8]=bcc;
	buffer_ready=0;
	g_cEstadoComSoft=ESPERA_ASK;
	DebugBufferMF(g_scArrTxComSoft,9,DATA_ENVIADO);
	EscribirCadenaSoft_buffer(g_scArrTxComSoft,9);
//	ValTimeOutCom=TIME_CARD;
}
void Card_Insercion(INSERCION_card Insercion)
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[10];
	if (Insercion==Habilita)
	{
		printf("Habilita Insersion\r\n");
		g_scArrTxComSoft[6]=Habilita;
	}
	else
	{
		
	  printf( "Inhabilita Insersion\r\n");
		g_scArrTxComSoft[6]=Inhabilita;
	
	}

	bcc=0;

	g_scArrTxComSoft[0]=0xF2;
	g_scArrTxComSoft[1]=0X00;
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=0X03;
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]='3';

	g_scArrTxComSoft[7]=ETX;
	for (j=0; j<8; j++)
	{
		bcc=g_scArrTxComSoft[j]^bcc;
	}

	g_scArrTxComSoft[8]=bcc;

	//buffer_ready=0;
//	g_cEstadoComSoft=ESPERA_RX;
  	DebugBufferMF(g_scArrTxComSoft,9,DATA_ENVIADO);
  //	EscribirCadenaSoft_buffer(g_scArrTxComSoft,DATA_ENVIADO);
//	ValTimeOutCom=TIME_CARD;
}
void Mov_Card(MOVER_card Mover)
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[10];
	bcc=0;

 	if ((Mover==MovPos_RF)||(Mover==MovPos_IC)||(Mover==MovPos_Front)||(Mover==MovPos_EjectFront)||(Mover==MovPos_Capture))
	{
	 	if (Mover==MovPos_RF)
		{
			printf("Moviendo Tarjeta a RF\r\n");
		}
		else if (Mover==MovPos_IC)
		{
			printf("Moviendo Tarjeta a IC\\r\n");
   		}
		else if (Mover==MovPos_Front)
		{
			printf("Moviendo Tarjeta a Bezel\r\n");
 		}
		else if (Mover==MovPos_EjectFront)
		{
			printf("Expulsando Tarjeta\r\n");
		}
		else if (Mover==MovPos_Capture)
		{
			printf("Capturando Tarjeta\r\n");
 		}

		g_scArrTxComSoft[0]=STX_LINTECH;
		g_scArrTxComSoft[1]=0X00;
		g_scArrTxComSoft[2]=0X00;
		g_scArrTxComSoft[3]=0X03;
		g_scArrTxComSoft[4]='C';
		g_scArrTxComSoft[5]='2';
		g_scArrTxComSoft[6]=Mover;
		g_scArrTxComSoft[7]=ETX;
		for (j=0; j<8; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[8]=bcc;
		buffer_ready=0;
		g_cEstadoComSoft=ESPERA_ASK;
		DebugBufferMF(g_scArrTxComSoft,9,DATA_ENVIADO);
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,9);
	//	ValTimeOutCom=TIME_CARD;
	}

}

void Aut_Card_check_Status(void)
{
unsigned char j, bcc;
unsigned char	g_scArrTxComSoft[10];
		  bcc=0;
	
		printf("Aut_Card_check_Status\r\n");
 	
		g_scArrTxComSoft[0]=STX_LINTECH;
		g_scArrTxComSoft[1]=0X00;
		g_scArrTxComSoft[2]=0X00;
		g_scArrTxComSoft[3]=0X03;
		g_scArrTxComSoft[4]='C';
		g_scArrTxComSoft[5]=0x50;
		g_scArrTxComSoft[6]=0x31;
		g_scArrTxComSoft[7]=ETX;
	   	for (j=0; j<8; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[8]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,9,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,9);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
	}	
void Clave_Seguridad_S2(void)
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[21];
		  bcc=0;
	printf("Clave Seguridad S2\r\n");


	g_scArrTxComSoft[0]=STX_LINTECH;
	g_scArrTxComSoft[1]=0X00;
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=0X0e;	// Numero Datos
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]=0x60;
	g_scArrTxComSoft[6]='3';
	g_scArrTxComSoft[7]=0x00;
	g_scArrTxComSoft[8]=0x20;
   	g_scArrTxComSoft[9]=0x00;
	g_scArrTxComSoft[10]=0x02;

	g_scArrTxComSoft[11]=0x06;

	g_scArrTxComSoft[12]=0x41;
	g_scArrTxComSoft[13]=0x63;
	g_scArrTxComSoft[14]=0x53;
   	g_scArrTxComSoft[15]=0x45;
	g_scArrTxComSoft[16]=0x76;
	g_scArrTxComSoft[17]=0x50;


	g_scArrTxComSoft[18]=ETX;
	
	 	for (j=0; j<19; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[19]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,20,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,20);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
	

}
/*------------------------------------------------------------------------------
CMD q programa la clave en el verificador o transporte
------------------------------------------------------------------------------*/

void Dwload_EEprom (void)
{
 	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[21];
	bcc=0;
	printf("Download MF EEprom\r\n");
	
	g_scArrTxComSoft[0]=0xF2;
	g_scArrTxComSoft[1]=0X00;
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=0X0E;
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]=0x60;
	g_scArrTxComSoft[6]='3';
	g_scArrTxComSoft[7]=0x00;
	g_scArrTxComSoft[8]=0Xd0;
	g_scArrTxComSoft[9]=0X00;
	g_scArrTxComSoft[10]=0X01;
	g_scArrTxComSoft[11]=0x06;
	g_scArrTxComSoft[12]='3'; //33
	g_scArrTxComSoft[13]='V';//56
 	g_scArrTxComSoft[14]='0';//30
	g_scArrTxComSoft[15]='p';//70
	g_scArrTxComSoft[16]='4';//34
	g_scArrTxComSoft[17]='r';//72
	g_scArrTxComSoft[18]=ETX;
	
 	for (j=0; j<19; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[19]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,20,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,20);		/* envio la trama por el pto serie*/
		//ValTimeOutCom=TIME_CARD;
}

void Dwload_EEprom_prog(unsigned char *password)
{
		unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[21];
	bcc=0;
	printf("Download MF EEprom\r\n");
	
	g_scArrTxComSoft[0]=0xF2;
	g_scArrTxComSoft[1]=0X00;
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=0X0E;
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]=0x60;
	g_scArrTxComSoft[6]='3';
	g_scArrTxComSoft[7]=0x00;
	g_scArrTxComSoft[8]=0Xd0;
	g_scArrTxComSoft[9]=0X00;
	g_scArrTxComSoft[10]=0X01;
	g_scArrTxComSoft[11]=0x06;
	g_scArrTxComSoft[12]=*password; //33
	g_scArrTxComSoft[13]=*(password+1);//56
 	g_scArrTxComSoft[14]=*(password+2);//30
	g_scArrTxComSoft[15]=*(password+3);//70
	g_scArrTxComSoft[16]=*(password+4);//34
	g_scArrTxComSoft[17]=*(password+5);//72
	g_scArrTxComSoft[18]=ETX;
	
 	for (j=0; j<19; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[19]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,20,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,20);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
}

/*------------------------------------------------------------------------------
Funcion q verifica si la clave y la carga en el transporte
------------------------------------------------------------------------------*/

void LoadVerify_EEprom(void)
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[15];
	bcc=0;
	printf("Carga y Verifica de EEprom\r\n");


	g_scArrTxComSoft[0]=0xF2;
	g_scArrTxComSoft[1]=0X00;
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=0X07;
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]=0x60;
	g_scArrTxComSoft[6]='3';
	g_scArrTxComSoft[7]=0x00;
	g_scArrTxComSoft[8]=0x21;
  g_scArrTxComSoft[9]=0x00;
	g_scArrTxComSoft[10]=0x01;
	g_scArrTxComSoft[11]=ETX;
	

	

	for (j=0; j<12; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[12]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,13,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,13);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
		
}

/*------------------------------------------------------------------------------
Funcion q lee la MF dandole el sector y el bloque
------------------------------------------------------------------------------*/

void RD_MF(unsigned char Sector, unsigned char Bloque)
{

	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[15];
	bcc=0;

		printf("Leyendo MF > Sector: ");
		Debug_chr_UART2(Sector);
	
		printf( " Bloque: ");
		Debug_chr_UART2(Bloque);
		printf("\r\n");


	g_scArrTxComSoft[0]=0xF2;
	g_scArrTxComSoft[1]=0X00;									  
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=0X08;
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]=0X60;
	g_scArrTxComSoft[6]='3';
	g_scArrTxComSoft[7]=0x00;
	g_scArrTxComSoft[8]=0xb0;
	g_scArrTxComSoft[9]=Sector;
	g_scArrTxComSoft[10]=Bloque;
	g_scArrTxComSoft[11]=0x01;
	g_scArrTxComSoft[12]=ETX;

	for (j=0; j<13; j++)
	{
		bcc=g_scArrTxComSoft[j]^bcc;
	}
	g_scArrTxComSoft[13]=bcc;


		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,14,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,14);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;

}

/*------------------------------------------------------------------------------
Funcion q lescribe la MF dandole el sector y el bloque y los datos
------------------------------------------------------------------------------*/


void WR_MF(unsigned char Sector, unsigned char Bloque,unsigned char *buffer)	   
	 
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[31];
	bcc=0;

		printf("Escribe MF > Sector: ");
		Debug_chr_UART2(Sector);
	
		printf( " Bloque: ");
		Debug_chr_UART2(Bloque);
		printf("\r\n");
																	  
	g_scArrTxComSoft[0]=0xF2;
	g_scArrTxComSoft[1]=0X00;									  
	g_scArrTxComSoft[2]=0X00;
	g_scArrTxComSoft[3]=24;																	/* Numero Datos a programar */ 
	
	g_scArrTxComSoft[4]='C';
	g_scArrTxComSoft[5]=0X60;
	g_scArrTxComSoft[6]='3';
	g_scArrTxComSoft[7]=0x00;
	g_scArrTxComSoft[8]=0xd1;
	g_scArrTxComSoft[9]=Sector;															//Sector;
	g_scArrTxComSoft[10]=Bloque;														//Bloque;
	g_scArrTxComSoft[11]=0x01;

		for (j=0; j<=16; ++j)
			{
				g_scArrTxComSoft[j+12]=*(buffer + j);	
			}
	
	g_scArrTxComSoft[28]=ETX;
	
	for (j=0; j<=28; j++)
	{
		bcc=bcc^g_scArrTxComSoft[j];
	}
	g_scArrTxComSoft[29]=bcc;

	
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,30,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,30);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
	
}
//*******************************************************************************************
// rutina q mira el tipo de tarjeta si es valido para el uso 	
//*******************************************************************************************

void Unique_Identifier_UID(void)
{
unsigned char j, bcc;
unsigned char	g_scArrTxComSoft[11];
		  bcc=0;
	
		printf( "UID\r\n");
 	
	  g_scArrTxComSoft[0]=STX_LINTECH;
		g_scArrTxComSoft[1]=0X00;
		g_scArrTxComSoft[2]=0X00;
		g_scArrTxComSoft[3]=0X05;
		g_scArrTxComSoft[4]='C';
		g_scArrTxComSoft[5]=0x60;
		g_scArrTxComSoft[6]=0x30;
		g_scArrTxComSoft[7]=0x41;
		g_scArrTxComSoft[8]=0x30;
		g_scArrTxComSoft[9]=ETX;
	   	for (j=0; j<10; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[10]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,11,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,11);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
	}	
void Power_off(void)
{
uint8_t  j, bcc;
unsigned char	g_scArrTxComSoft[10];
		  bcc=0;
	
	printf( "POWER OFF UID\r\n");
 	
	g_scArrTxComSoft[0]=STX_LINTECH;
		g_scArrTxComSoft[1]=0X00;
		g_scArrTxComSoft[2]=0X00;
		g_scArrTxComSoft[3]=0X03;
		g_scArrTxComSoft[4]='C';
		g_scArrTxComSoft[5]=0x60;
		g_scArrTxComSoft[6]=0x31;
		g_scArrTxComSoft[7]=ETX;
	   	for (j=0; j<8; j++)
		{
			bcc=g_scArrTxComSoft[j]^bcc;
		}
		g_scArrTxComSoft[8]=bcc;
		buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
		g_cEstadoComSoft=ESPERA_ASK;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
		DebugBufferMF(g_scArrTxComSoft,9,DATA_ENVIADO);								/*muestra la trama enviada al pto serie a debug por tibbo*/
		EscribirCadenaSoft_buffer(g_scArrTxComSoft,9);		/* envio la trama por el pto serie*/
//		ValTimeOutCom=TIME_CARD;


}
/*------------------------------------------------------------------------------
funcion que valida la trama del verificador o transporte lintech
RSPT_TRP_OK						(0) significa que la trama es valida y sigue en el proceso
NO_RSPD_TRP_PTO_COM		(1)	falla en la respuesta por pto serie o trama invalida	
ESPR_RSPT_TRP_TRAMA		(2)	no ha recibido la trama del verificador o transporte	
ERROR_TRP_TRAMA				(3) ERROR DE TRAMA CMD (N)


------------------------------------------------------------------------------*/

uint8_t Trama_Validacion_P_N(void)
{
	uint8_t Trama_Validacion_P_N=ESPR_RSPT_TRP_TRAMA;																/*espera respuesta del transporte*/
			
			//if 																									//((ValTimeOutCom==1)||(buffer_ready==1)|| (ValTimeOutCom > TIME_CARD) )
			//{
				if (buffer_ready==1)
				{
					buffer_ready=0;
						
				
					if (Buffer_Rta_Lintech[Pos_TipoResp]==answerOk)
					{
										
						Trama_Validacion_P_N=RSPT_TRP_OK;																				/*trama ok*/
							
					}
					else if (Buffer_Rta_Lintech[Pos_TipoResp]==answerFalse)
					{
 						
						Trama_Validacion_P_N=ERROR_TRP_TRAMA	;																	/*error de trama*/
						
					}
					else
					{
					 	printf( "Respuesta  DESCONOCIDA \r\n");				/*la respuesta es desconocida*/
						Trama_Validacion_P_N=ERROR_TRP_TRAMA	;		
						
					}
				}
				//else
				//{
			 							
					//Trama_Validacion_P_N=NO_RSPD_TRP_PTO_COM;																	/*pto serie no responde */
																						
 			//	}

		//	}
			
	return Trama_Validacion_P_N;
}

/*funcion de error de respuesta pto serie

variable en uart. cnt__ask_off=cuenta los numeros de error pto serie y reset de transporte 
se limpia cuando llega la respuesta del transporte. 
Rele_Atasco = es un I/O del Mc que activa / inhabilita el rele
ON		(1) esta activo 
OFF		(0) inhactivo 
REENVIA_TRAMA		1
ESPERA_MAS_TIEMPO	0
cnt_espera_ask_on= cuenta el tiempo de ASK que esta activo,sin que le llegue
									 la trama completa, al  5 tiempos borra el ask y retrasmite el cmd

error_rx_pto= (0)= ESPERA_MAS_TIEMPO nos da mas tiempo para esperar la trama,
						= (1)= REENVIA_TRAMA reenvia la trama al transporte

cnt__ask_off= varible global esta definida en pto serie y es un contador , que 
se limpia cada vez que la trama a llegado completa y validada

aSk= significa que llego al pto serie el 06 = ask donde el transporte dice que a recibido el cmd
esta ejecutando y nos enviara la respuesta,necesita tiempo esta bit esta definino en el modulo uart es global

------------------------------------------------------------------------------*/
uint8_t error_rx_pto(void)
{

static uint8_t cnt_espera_ask_on=0;
uint8_t error_rx_pto=ESPERA_MAS_TIEMPO;

		
					
			printf( "Dispensador No Responde PTO SERIE ...");
			Debug_chr_UART2	(cnt__ask_off);	
			Debug_chr_UART2	(cnt_espera_ask_on);
			Debug_chr_UART2	(error_rx_pto);
			printf("\r\n");
//			if (aSk==OFF)
			
	//		{	
			//		cnt__ask_off++;																																		/*cuento el error*/																																
			//	if(cnt__ask_off>=10)
		//		{	
		//			printf( "ATASCADO RESET\r\n");																																			/*no contesta debe reset el transporte*/
	//				Atascado_GP0_PIN_3 = ON;																																		/*off el rele de reset del verificador*/		
//					Delay_10ms(110);
		//			cnt__ask_off=0;																																		/*limpio ls errores*/
		//			cnt_espera_ask_on=0;
			//		error_rx_pto=ESPERA_MAS_TIEMPO;																										/**/
				//	Atascado_GP0_PIN_3 = OFF;	
			//		Delay_10ms(110);																																	/*On el rele de reset del verificador*/		
				//	ValTimeOutCom=TIME_CARD;
		//		}
	//			else
	//			{
	//				error_rx_pto=REENVIA_TRAMA;																												/*1 reenvia trama*/
//					ValTimeOutCom=TIME_CARD;
//				}
			//}																																											/*aSk esta activo */
		//	else
			//{
		//			cnt_espera_ask_on++;																															/*cuento n tiempos de ask para recibir el total de la trama*/
			//	if(cnt_espera_ask_on>=1)
		//		{
		//			cnt__ask_off=0;																																		/*paso tiempo de espera y no se completo la trama 
//																																														limpio los reg y reenvio la trama y ask=off*/
		//			cnt_espera_ask_on=0;
			//		error_rx_pto=REENVIA_TRAMA;
				//	aSk=OFF;
			//		ValTimeOutCom=TIME_CARD;
			//	}
			//	else
			//	{
			//		cnt__ask_off=0;																																		/*damos tiempo de espera de la trama del transporte*/
			//		error_rx_pto=ESPERA_MAS_TIEMPO;;
				//	ValTimeOutCom=TIME_CARD;
//				}
//			}
				//return (error_rx_pto);
				return 0;
}
/*------------------------------------------------------------------------------
Funcion de respuesta a los cmd del transporte
Retorna rta_cmd_transporte el estado en que queda
Recibe tres datos unos es el 
Estado_futuro= significa que la respuesta fue ok
Estado_Error= en caso de que aya un error a que estado envia el codigo
Estado_Actua= No ha llegado la respuesta y sigue en el mismo estado
RSPT_TRP_OK						(0) significa que la trama es valida y sigue en el proceso
NO_RSPD_TRP_PTO_COM		(1)	falla en la respuesta por pto serie o trama invalida	
ESPR_RSPT_TRP_TRAMA		(2)	no ha recibido la trama del verificador o transporte	
ERROR_TRP_TRAMA				(3) ERROR DE TRAMA CMD (N)

(0)= ESPERA_MAS_TIEMPO nos da mas tiempo para esperar la trama,
(1)= REENVIA_TRAMA reenvia la trama al transporte
------------------------------------------------------------------------------*/
uint8_t   rta_cmd_transporte(unsigned char *secuencia_Expedidor,enum Estados_Expedidor estado )
{
	uint8_t temp;
	uint8_t EstadoComSeqMF;
	
	estado=EstadoPasado;
			
if((temp=Trama_Validacion_P_N())!=RSPT_TRP_OK	)
		{
			if(temp==ESPR_RSPT_TRP_TRAMA)																													/*no he recibido respuesta espero*/
			{
			EstadoComSeqMF= *(secuencia_Expedidor + EstadoActual);									       			/*SEQ_RTA_CARD_POSno ha respondido*/
			}	
			else if (temp==ERROR_TRP_TRAMA)
			{
			printf( "RTA_CMD_ERROR\r\n");															/* trama no valida respuesta incorrecta falla en la escritura */
			DebugBufferMF(Buffer_Rta_Lintech,uart0_rx_cnt,DATA_RECIBIDO);														/*imprimo la trama recibida*/	
			if(Buffer_Rta_Lintech[ERROR_COLLECT_CARD]==0x33)
				{
					printf( "RTA_CMD_ERROR COLECTOR LLENO\r\n");	
				}

			EstadoComSeqMF=*(secuencia_Expedidor + EstadoPasado);	
			//EstadoComSeqMF=SEQ_INICIO	;																														/// (3) Trama invalida cmd (N)reenvio cmd*/	
			}			
			else
			{
			/*Dispensador No Responde PTO SERIE ...*/
		
				if(temp=error_rx_pto()==ESPERA_MAS_TIEMPO)
				{
					EstadoComSeqMF=*(secuencia_Expedidor + EstadoActual);	
				}																										 																	/*SEQ_RTA_CARD_POS;*/
				else 																																									//(temp=error_rx_pto()==REENVIA_TRAMA)
				{
					EstadoComSeqMF=*(secuencia_Expedidor + EstadoPasado);																											/*SEQ_INICIO*/
				}																									
			}				
		}
		else
	  {
			
			DebugBufferMF(Buffer_Rta_Lintech,uart0_rx_cnt,DATA_RECIBIDO);
			EstadoComSeqMF=*(secuencia_Expedidor + EstadoFuturo);	
		}
	return EstadoComSeqMF;
}


