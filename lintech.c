
#include "lintech.h"
#include <stdio.h>
#include "debuger.h"
#include "UART_CERO.h"
/*----------------------------------------------------------------------------
funcion de inicializacion del transporte

------------------------------------------------------------------------------*/

void Inicializa(TIPO_movimiento SetValue)
{
	unsigned char j, bcc;
	unsigned char	g_scArrTxComSoft[10];
	bcc=0;
	if ((SetValue==SIN_MOVIMIENTO)||(SetValue==TO_FRONT)||(SetValue==CAPTURE_BOX))
	{
		if(SetValue==SIN_MOVIMIENTO)
		{
		printf("Inicializa Dispensador SIN_MOVIMIENTO \n");
		}
	
		else if (SetValue == TO_FRONT)
		{
			printf( "Inicializa Dispensador TO_FRONT \n");
		}
		else 
		{
		printf("Inicializa Dispensador CAPTURE_BOX \n");
		}
	}
	else
	{
		printf("TIPO_movimiento no existe \n");
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
			printf("Check_Status SENSOR_NORMAL\n");
		}
		else
		{
			printf( "Check_Status SENSOR_DETAIL\n");
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
		printf("Habilita Insersion\n");
		g_scArrTxComSoft[6]=Habilita;
	}
	else
	{
		
	  printf( "Inhabilita Insersion\n");
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

		buffer_ready=0;
		g_cEstadoComSoft=ESPERA_ASK;
  	DebugBufferMF(g_scArrTxComSoft,9,DATA_ENVIADO);
  	EscribirCadenaSoft_buffer(g_scArrTxComSoft,9);
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
			printf("Moviendo Tarjeta a RF\n");
		}
		else if (Mover==MovPos_IC)
		{
			printf("Moviendo Tarjeta a IC\n");
   		}
		else if (Mover==MovPos_Front)
		{
			printf("Moviendo Tarjeta a Bezel\n");
 		}
		else if (Mover==MovPos_EjectFront)
		{
			printf("Expulsando Tarjeta\n");
		}
		else if (Mover==MovPos_Capture)
		{
			printf("Capturando Tarjeta\n");
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
	
		printf("Aut_Card_check_Status\n");
 	
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
	printf("Clave Seguridad S2\n");


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
	printf("Download MF EEprom\n");
	
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
	printf("Download MF EEprom\n");
	
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
	printf("Carga y Verifica de EEprom\n");


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

		printf("Leyendo MF > SECTOR: ");
		Debug_chr_UART2(Sector);
	
		printf( " BLOQUE: ");
		Debug_chr_UART2(Bloque);
		printf("\n");


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

		printf("Escribe MF > SECTOR: ");
		Debug_chr_UART2(Sector);
	
		printf( " BLOQUE: ");
		Debug_chr_UART2(Bloque);
		printf("\n");
																	  
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
	
		printf( "UID\n");
 	
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
	
	printf( "POWER OFF UID\n");
 	
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

