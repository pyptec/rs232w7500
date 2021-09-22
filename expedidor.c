#include "expedidor.h"
#include "lintech.h"
#include "debuger.h"
#include <stdio.h>

/*variables externas*/
extern uint8_t Buffer_Rta_Lintech[];
extern int32_t uart0_rx_cnt;
extern uint8_t buffer_ready;
extern uint8_t ValTimeOutCom;


unsigned char error_rx_pto(void)
{

static unsigned cnt_espera_ask_on=0;
unsigned char error_rx_pto=ESPERA_MAS_TIEMPO;

		
					
			printf( "Dispensador No Responde PTO SERIE ...");
		//	Debug_chr_UART2	(cnt__ask_off);	
			Debug_chr_UART2(cnt_espera_ask_on);
			Debug_chr_UART2	(error_rx_pto);
			printf( "\n");
		cnt_espera_ask_on++;
		if(cnt_espera_ask_on>=70)
		{
			cnt_espera_ask_on=0;
			error_rx_pto=REENVIA_TRAMA;		
		}
		else
		{
			error_rx_pto=ESPERA_MAS_TIEMPO;
		}
		//	if (aSk==OFF)
			
		//	{	
			//		cnt__ask_off++;																																		/*cuento el error*/																																
			//	if(cnt__ask_off>=10)
				//{	
					//printf( "ATASCADO RESET\r\n");																																			/*no contesta debe reset el transporte*/
					//Atascado_GP0_PIN_3 = ON;																																		/*off el rele de reset del verificador*/		
					//Delay_10ms(110);
					//cnt__ask_off=0;																																		/*limpio ls errores*/
					//cnt_espera_ask_on=0;
					//error_rx_pto=ESPERA_MAS_TIEMPO;																										/**/
					//Atascado_GP0_PIN_3 = OFF;	
					//Delay_10ms(110);																																	/*On el rele de reset del verificador*/		
					//ValTimeOutCom=TIME_CARD;
				//}
				//else;
			//	{
				//	error_rx_pto=REENVIA_TRAMA;																												/*1 reenvia trama*/
				//	ValTimeOutCom=TIME_CARD;
				//}
			//}																																											/*aSk esta activo */
			//else
			//{
				//	cnt_espera_ask_on++;																															/*cuento n tiempos de ask para recibir el total de la trama*/
				//if(cnt_espera_ask_on>=1)
				//{
					//cnt__ask_off=0;																																		/*paso tiempo de espera y no se completo la trama 
//																																														limpio los reg y reenvio la trama y ask=off*/
					//cnt_espera_ask_on=0;
					//error_rx_pto=REENVIA_TRAMA;
					//aSk=OFF;
					//ValTimeOutCom=TIME_CARD;
				//}
				//else
			//	{
				//	cnt__ask_off=0;																																		/*damos tiempo de espera de la trama del transporte*/
					//error_rx_pto=ESPERA_MAS_TIEMPO;;
					//ValTimeOutCom=TIME_CARD;
				//}
			//}
				return error_rx_pto;
}
/*------------------------------------------------------------------------------
funcion que valida la trama del verificador o transporte lintech
RSPT_TRP_OK						(0) significa que la trama es valida y sigue en el proceso
NO_RSPD_TRP_PTO_COM		(1)	falla en la respuesta por pto serie o trama invalida	
ESPR_RSPT_TRP_TRAMA		(2)	no ha recibido la trama del verificador o transporte	
ERROR_TRP_TRAMA				(3) ERROR DE TRAMA CMD (N)


------------------------------------------------------------------------------*/

unsigned char Trama_Validacion_P_N(void)
{
	uint8_t Trama_Validacion_P_N=ESPR_RSPT_TRP_TRAMA;																/*espera respuesta del transporte*/
			
			if ((ValTimeOutCom==1)||(buffer_ready==1)|| (ValTimeOutCom > TIME_CARD) )
			{
				if (buffer_ready==1)
				{
					buffer_ready=0;
						
				
					if (Buffer_Rta_Lintech[Pos_TipoResp]==TRUE_return)
					{
										
						Trama_Validacion_P_N=RSPT_TRP_OK;																				/*trama ok*/
							
					}
					else if (Buffer_Rta_Lintech[Pos_TipoResp] == FAIL_return)
					{
 						
						Trama_Validacion_P_N=ERROR_TRP_TRAMA	;																	/*error de trama*/
						
					}
					else
					{
					 	printf( "Respuesta  DESCONOCIDA \n");				/*la respuesta es desconocida*/
						Trama_Validacion_P_N=ERROR_TRP_TRAMA	;		
						
					}
				}
				else
				{
			 							
					Trama_Validacion_P_N=NO_RSPD_TRP_PTO_COM;																	/*pto serie no responde */
																						
 				}

			}
			
	return Trama_Validacion_P_N;
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
unsigned char   rta_cmd_transporte(ATRIBUTOS_expedidor* Sq )
{
	uint8_t temp;
	uint8_t EstadoComSeqMF;
	
	
			
if((temp=Trama_Validacion_P_N())!=RSPT_TRP_OK	)
		{
			if(temp==ESPR_RSPT_TRP_TRAMA)																													/*no he recibido respuesta espero*/
			{
			EstadoComSeqMF = Sq->Secuencia_Expedidor[EstadoActual];									       			/*SEQ_RTA_CARD_POSno ha respondido*/
			}	
			else if (temp==ERROR_TRP_TRAMA)
			{
			printf( "RTA_CMD_ERROR (N)\n");																		/* trama no valida respuesta incorrecta falla en la escritura */
			DebugBufferMF(Buffer_Rta_Lintech,uart0_rx_cnt,DATA_RECIBIDO);														/*imprimo la trama recibida*/	
			if(Buffer_Rta_Lintech[ERROR_COLLECT_CARD] == FULL_colector_card)
				{
					printf( "RTA_CMD_ERROR COLECTOR LLENO\n");	
				}

			EstadoComSeqMF= Sq->Secuencia_Expedidor[EstadoPasado];	
																																								/// (3) Trama invalida cmd (N)reenvio cmd*/	
			}			
			else
			{
			/*Dispensador No Responde PTO SERIE ...*/
		
				if(error_rx_pto()==ESPERA_MAS_TIEMPO)
				{
					EstadoComSeqMF=Sq->Secuencia_Expedidor[EstadoActual];	
				}																										 																	/*SEQ_RTA_CARD_POS;*/
				else 																																									//(temp=error_rx_pto()==REENVIA_TRAMA)
				{
					EstadoComSeqMF=Sq->Secuencia_Expedidor[EstadoPasado];																											/*SEQ_INICIO*/
				}																									
			}				
		}
		else
	  {
			
			DebugBufferMF(Buffer_Rta_Lintech,uart0_rx_cnt,DATA_RECIBIDO);
			EstadoComSeqMF=Sq->Secuencia_Expedidor[EstadoFuturo];	
		}
	
	return EstadoComSeqMF;
}

/*------------------------------------------------------------------------------
Se pregunta por el estado del expedidor si hay tarjetas para precargarla

------------------------------------------------------------------------------*/

unsigned char	Responde_Estado_Sensores_Transporte(void)
{
	unsigned char Estado_expedidor;
		
			printf( "TAREA_SENSORES_TRANSPORTE\n");																	// trama valida Habilitado 
		
			if (Buffer_Rta_Lintech[Pos_St0]==NO_CARDS_IN_MCNSM)																	 								// CANAL LIBRE	  no tiene tarjetas en el mecanismo
			{
					
				if	((Buffer_Rta_Lintech[Pos_St1]==LOW_NIVEL_CARDS)||(Buffer_Rta_Lintech[Pos_St1]==FULL_CARD	)) 	//  se detecta la tarjeta en la boca TARJETA EN BEZZEL
				{
					if (Buffer_Rta_Lintech[Pos_St1]==LOW_NIVEL_CARDS	) 																						// nivel de tarjetas
						{
							printf("Nivel bajo de tarjetas\n");														// nivel bajo de tarjetas 
						//	send_portERR(LOW_CARD);																																			//envio msj al primario
						
								Estado_expedidor=SEQ_MOVER_CARD_RF;
										
						 }
						 else
								{
									/*respuesta ok*/
							
										Estado_expedidor=SEQ_MOVER_CARD_RF;
						
							 }
				}	
				else 
						{
							/*dispensador no posee tarjetas*/
							printf( "Dispensador SIN TARJETAS...\n");	
							
						//	send_portERR(NO_CARD);	
																																		// se envia msj al uC principal, visualiza en el lcd que no hay tarjetas
								
							Estado_expedidor=SEQ_INICIO;																																//inicio el loop
						 }
			}
			else if (Buffer_Rta_Lintech[Pos_St0]==CARD_IN_MOUTH)	 																						  //  se detecta la tarjeta en la boca TARJETA EN BEZZEL
				{
							/*hay una tarjeta en la boca del verificador */
							printf( "Tarjeta en la boca\n");																//se envia msj al debuger q hay tarjeta en la boca
																																																				  //se habilita recepcion de tarjetas por boca
							Estado_expedidor=SEQ_TIPO_CARD;																			//SEQ_CARD_INSERCION_ON;																										  //se trabaja mensual				
				}
			else if (Buffer_Rta_Lintech[Pos_St0]==CARD_OK_READ_RF	)	 
						
				{
							printf( "Tarjeta en RF\n");
							Estado_expedidor=SEQ_TIPO_CARD;																			//SEQ_CARD_INSERCION_ON;
				}
			
	return Estado_expedidor;	
}





unsigned char Responde_Tipo_Tarjeta(void)
	{
		unsigned char Estado_expedidor;
		
			printf( "TAREA_TIPO DE TARJETA\n");																				// trama valida Habilitado 
			
	if (Buffer_Rta_Lintech[Card_type_H]==MF50_HIGH)																														/* pregunto si la tarjeta en el transporte es MF 50 */
		{
		if ((Buffer_Rta_Lintech[Card_type_L] == MF50_LOW) || (Buffer_Rta_Lintech[Card_type_L] == MF70))	
			{
				printf( "Tarjeta valida MF50\n");																				/* trama valida son MF50*/
			//	if(MenSual ==  True)
			//	{
			//	Estado_expedidor =SEQ_CAPTURE_CARD; 							//SEQ_UID;																																					//SEQ_LOAD_PASSWORD;												
			//	}
			//	else	
			//	{
					Estado_expedidor = SEQ_LOAD_PASSWORD;			//SEQ_LPR;		//SEQ_LOAD_PASSWORD;
			//	}					
			}
		else
			{
					 if (Buffer_Rta_Lintech[Pos_St0]==CARD_OK_READ_RF)	 																						  //  se detecta la tarjeta en la boca TARJETA EN BEZZEL
					{
					
					printf( "Tarjeta invalida_1 no es MF50\n");														/* trama no valida */
								
					//send_portERR(PRMR_TARJETA_INVALIDA);																															/*envio msj principal tarjeta invalidad*/
					//PantallaLCD(TARJETA_INVALIDA);
							
						Estado_expedidor =SEQ_CAPTURE_CARD;							// Captura_Expulsa();	
					
					}	
					else	
					{
						/*NO HAY TARJETA EN RF*/
					//	MenSual = False;
						Estado_expedidor = SEQ_INICIO;		
					}						
			}
		}
		else 
			{
				 if (Buffer_Rta_Lintech[Pos_St0]==CARD_OK_READ_RF)	 																						  //  se detecta la tarjeta en la boca TARJETA EN BEZZEL
					{
						/*patina el transporte */
					
				printf("Tarjeta invalida no es MF50\n");															/* trama no valida */
								
			//	send_portERR(PRMR_TARJETA_INVALIDA);	   																													//la tarjeta no es valida 
			//	PantallaLCD(TARJETA_INVALIDA);																																		/*envio el msj por la pantalla lcd o la raspberry*/
									
				Estado_expedidor = SEQ_CAPTURE_CARD;      //Captura_Expulsa();	
										
						
					}
					else	
					{
						/*NO HAY TARJETA EN RF*/
					//	MenSual = False;
						Estado_expedidor = SEQ_INICIO;		
					}											
			}
							
		return Estado_expedidor;																																																	
	}	

unsigned char  Responde_Lectura_Tarjeta_Sector1_Bloque1 (ATRIBUTOS_expedidor* Sq)
{
	unsigned char temp;
	unsigned char Estado_expedidor;
	unsigned char buffer_S1_B1[17];
	unsigned char ID_CLIENTE;
	unsigned char COD_PARK;		
	static unsigned char falla=0;
			printf( "TAREA_LECTURA_TARJETA_SECTOR1_BLOQUE1\n");		
																	
																
			
			if (Buffer_Rta_Lintech[Pos_Length] >=0x18)
			{
				
					for (temp=0; temp<16; ++temp)
					{
						buffer_S1_B1 [temp]=Buffer_Rta_Lintech[Pos_IniDatMF+temp];														/*almaceno la informacion de MF en un arreglo*/
					 
					}
					
					
					printf( "Buffer_s1_b1\n");
					DebugBufferMF(buffer_S1_B1,16,DATA_RECIBIDO);
	//				ID_CLIENTE=rd_eeprom(0xa8,EE_ID_CLIENTE);	
	//				COD_PARK=rd_eeprom(0xa8,EE_ID_PARK);
					/*Compara  MF_ID_CLIENTE y MF_COD_PARK con el codigo del parqueadero ID_CLIENTE  COD_PARK*/
					
					if (((buffer_S1_B1 [ MF_ID_CLIENTE])==ID_CLIENTE) && ((buffer_S1_B1 [ MF_COD_PARK] ) == COD_PARK)||((ID_CLIENTE==0)&&(COD_PARK==0)))		
					{
							
						printf( "CARD ID_CLIENTE: ");								
						printf("%d",buffer_S1_B1 [ MF_ID_CLIENTE]);
						printf( "\n");
						
						printf( "ID_CLIENTE: ");								
						printf("%d",ID_CLIENTE);
						printf("\n");
						
						printf("CARD COD_PARK:");										
						printf("%d",buffer_S1_B1 [ MF_COD_PARK]);
						printf("\n"); 
						
						printf("COD_PARK:");										
						printf("%d",buffer_S1_B1 [ MF_COD_PARK]);
						printf( "\n"); 

						printf("TIPO DE TARJETA: ");
						Debug_chr_UART2(buffer_S1_B1 [MF_TIPO_TARJETA]);
						printf( "\n");
						
						Sq->Atributos_Expedidor [ Tipo_Tarjeta] = buffer_S1_B1 [MF_TIPO_TARJETA];
						/*fecha de vencimiento de mensual o prepago*/
						Sq->Atributos_Expedidor [ Expira_ano] = buffer_S1_B1 [MF_EXPIRA_ANO];
						Sq->Atributos_Expedidor [ Expira_mes] = buffer_S1_B1 [MF_EXPIRA_MES];
						Sq->Atributos_Expedidor [ Expira_dia] = buffer_S1_B1 [MF_EXPIRA_DIA];
						
						Sq->Atributos_Expedidor [ Sector] = Sector_1;
						Sq->Atributos_Expedidor [ Bloque] = Bloque_2;
						falla=0;
						Estado_expedidor = SEQ_READ_SECTOR_BLOQUE;
				
					}
					else
					{
						falla=0;
						printf("ERROR COD PARK\r\n");
					//	send_portERR(PRMR_ERROR_COD_PARK);
					//	PantallaLCD(ERROR_COD_PARK);																												//envio el msj por la pantalla lcd o la raspberry
						Estado_expedidor =SEQ_CAPTURE_CARD; 						//Captura_Expulsa();																									//	 codigo de parqueo erro expulso la tarjeta 		
					}
			}
			else
			{
					
				if ((Buffer_Rta_Lintech[Rtype]) == OPERATE_FAIL)
				{
					falla++;
				}
				 if (falla <= 2)
					
				{
					printf("ERROR OPERATE FAIL\r\n");
					Estado_expedidor = SEQ_POWER_ON;
															
				}
				else
				{
					falla=0;
					printf( "TARJETA SIN FORMATO\n");
					//send_portERR(PRMR_TARJETA_SIN_FORMATO);
					//PantallaLCD(TARJETA_SIN_FORMATO);																												/*envio el msj por la pantalla lcd o la raspberry*/
				 Estado_expedidor =SEQ_CAPTURE_CARD;																	//Captura_Expulsa();		
				}
			}
			
	return Estado_expedidor;
}	
unsigned char Load_Secuencia_Expedidor(ATRIBUTOS_expedidor* Sq,unsigned const  estadoactivo,unsigned const estadoactual,unsigned const estadofuturo)
{
	Sq->Secuencia_Expedidor[EstadoPasado ] =estadoactivo ;
	Sq->Secuencia_Expedidor[EstadoActual ] = estadoactual;
	Sq->Secuencia_Expedidor[EstadoFuturo ] = estadofuturo;
	return estadoactual;
}
uint8_t SecuenciaExpedidorMF( uint8_t EstadoActivo)
{
	ATRIBUTOS_expedidor sq;
	switch (EstadoActivo)
	{
		case SEQ_INICIO:
		Check_Status(SENSOR_NORMAL);	
		EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_RESPUESTA_TRANSPORTE);
		sq.Secuencia_Expedidor[TareadelCmd]=TAREA_SENSORES_TRANSPORTE;
		break;
		case	SEQ_CMD_ACEPTADO:
			EstadoActivo=rta_cmd_transporte(&sq);
		break;
		case SEQ_MOVER_CARD_RF:
			Mov_Card(MovPos_RF);
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_TIPO_CARD);
			break;
		case SEQ_TIPO_CARD:
			Aut_Card_check_Status();
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_RESPUESTA_TRANSPORTE);
			sq.Secuencia_Expedidor[TareadelCmd ] = TAREA_TIPO_TARJETA;
			break;
		case SEQ_EXPULSAR_CARD:
			Mov_Card(MovPos_EjectFront);
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_INICIO);
		break;
		case SEQ_CAPTURE_CARD:
			Mov_Card(MovPos_Capture);
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_INICIO);		 //SEQ_INICIOSEQ_MOVER_CARD_RF
				
		break;
		case SEQ_LOAD_PASSWORD:
			LoadVerify_EEprom();
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_READ_SECTOR_BLOQUE);
			printf("llegamos aSEQ_LOAD_PASSWORD\n");	
			sq.Atributos_Expedidor[Sector]=Sector_1;
			sq.Atributos_Expedidor[Bloque]=Bloque_1;
				break;
		case SEQ_READ_SECTOR_BLOQUE:
			RD_MF(sq.Atributos_Expedidor [ Sector ],sq.Atributos_Expedidor [ Bloque ]);
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_RESPUESTA_TRANSPORTE);
			sq.Secuencia_Expedidor[TareadelCmd ] = TAREA_LECTURA_TARJETA_SECTOR_BLOQUE;
			break;
		case SEQ_POWER_ON:
			Power_off();
			EstadoActivo = Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_LOAD_PASSWORD);
			break;
	/*casos de inicio*/
		case SEQ_INICIA_LINTECH:
			Inicializa(SIN_MOVIMIENTO);	 
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_GRABA_EEPROM);		
		break;
			
		case SEQ_GRABA_EEPROM:
			Dwload_EEprom();
			EstadoActivo=Load_Secuencia_Expedidor(&sq,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_INICIO);
			break;
		case SEQ_RESPUESTA_TRANSPORTE:
			if (sq.Secuencia_Expedidor[TareadelCmd] == TAREA_SENSORES_TRANSPORTE)
			{
			EstadoActivo=Responde_Estado_Sensores_Transporte();	
			}
			else if (sq.Secuencia_Expedidor [TareadelCmd]==TAREA_TIPO_TARJETA)
				{
						
						EstadoActivo=Responde_Tipo_Tarjeta();
				}
		 else if (sq.Secuencia_Expedidor [TareadelCmd]==TAREA_LECTURA_TARJETA_SECTOR_BLOQUE)
			{
				if ((sq.Atributos_Expedidor [ Sector ]== Sector_1)&& (sq.Atributos_Expedidor [ Bloque ]==Bloque_1))
						{
							EstadoActivo=Responde_Lectura_Tarjeta_Sector1_Bloque1 (&sq);
						}
			}
			break;
	}
	return EstadoActivo;
}
