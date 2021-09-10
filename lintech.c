
#include "lintech.h"
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
		
//		Debug_txt_Tibbo((unsigned char *) "Inicializa Dispensador SIN_MOVIMIENTO \r\n");
		
	//	Debug_txt_Tibbo((unsigned char *) "Inicializa Dispensador TO_FRONT \r\n");
	//	Debug_txt_Tibbo((unsigned char *) "Inicializa Dispensador CAPTURE_BOX \r\n");
		
		
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
	//	buffer_ready=0;																		/* buffer del pto serie (0) inicia a esperar la trama*/
	//	g_cEstadoComSoft=ESPERA_RX;												/* Espera el ASK en el pt o serie para empesar a almacenas*/
	//	DebugBufferMF(g_scArrTxComSoft,9,0);								/*muestra la trama enviada al pto serie a debug por tibbo*/
	//	EscribirCadenaSoft_buffer(g_scArrTxComSoft,9);		/* envio la trama por el pto serie*/
	//	ValTimeOutCom=TIME_CARD;
	}
}
