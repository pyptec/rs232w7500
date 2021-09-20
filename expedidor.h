#include "W7500x.h"

/*funciones externas*/

typedef enum
{

    SEQ_INICIO=0,
		SEQ_CMD_ACEPTADO=1,
	  SEQ_MOVER_CARD_RF=2,
		SEQ_TIPO_CARD		=3,
		SEQ_EXPULSAR_CARD=4,
		SEQ_RESPUESTA_TRANSPORTE=5,
		SEQ_LOAD_PASSWORD=6,
		SEQ_CAPTURE_CARD=7,
		SEQ_READ_SECTOR_BLOQUE=8,
		SEQ_POWER_ON=9,
    SEQ_INICIA_LINTECH=10,
		SEQ_GRABA_EEPROM=11
}SEQ_Expedidor;
typedef enum
{
	TAREA_SENSORES_TRANSPORTE=0,
	TAREA_TIPO_TARJETA=1,
	TAREA_LECTURA_TARJETA_SECTOR_BLOQUE=2
}TAREAS_Expedidor;
typedef enum
{
	RSPT_TRP_OK	=					0,
 	NO_RSPD_TRP_PTO_COM	=	1,
 	ESPR_RSPT_TRP_TRAMA	=	2,
 	ERROR_TRP_TRAMA	=			3
}RESPUESTA_lintech;
typedef enum 
{
 EstadoActual,
 EstadoPasado,
 EstadoFuturo,
 TareadelCmd	
}Estados_Expedidor;
typedef struct
{
	uint8_t Secuencia_Expedidor[4];
	uint8_t Atributos_Expedidor[20];
	

}ATRIBUTOS_expedidor;
typedef enum 
{
 Sector,				
 Bloque,				
 Tipo_Tarjeta,
 Apb,
 Horario,
 Pico_Placa,
 Type_Vehiculo,
 Uid_0,
 Uid_1,
 Uid_2,
 Uid_3,
 Expira_ano,
 Expira_mes,
 Expira_dia,
 DateTime_year,
 DateTime_month,
 DateTime_day,
 DateTime_hour,
 DateTime_minutes	
 
}DATA_card;

typedef enum 
{
	Sector_0,
	Sector_1,
	Sector_2,
	Bloque_0 = 0,
	Bloque_1 = 1,
	Bloque_2 = 2
}MF_Sector_Bloque;

/*----------------------------------------------------------------------------
posicion de  MF  bloque 1 sector 1
(0) tipo de tarjeta 
(01) el id del cliente
(03)codigo del parqueadero	

posicion de  MF bloque 2 sector 1
(00) donde esta grabado la fecha de entrada (año,mes,dia,hora,minutos) estan en hex  
(0b) donde esta grabado la fecha de salida (año,mes,dia,hora,minutos) estan en hex 
------------------------------------------------------------------------------*/
typedef enum 
{
	/*datos de MF  bloque 1 sector 1*/
 	MF_TIPO_TARJETA	=	0X00,
 	MF_COD_PARK 		=	0x01,					//MF_ID_CLIENTE
	MF_ID_CLIENTE		=	0x03,					//MF_COD_PARK
	
	/*datos de MF  bloque 2 sector 1*/
 	MF_FECHA_INT		=	0X00,					/*año,mes,dia,hora,minutos*/
	MF_DCTO					=	0x05,					/*Tipo de descuento (00)sin descuento, (01xx xxxx) 0x40 fija fecha de salida,
																					10xx xxxx dcto por porcentaje xx xxxx= valor del porcentaje, 11xx xxxx dcto por dinero */
	MF_LSB					=	0x06,
  MF_TIPO_VEHICULO	=0x08,				/*tipo vehiculo 00 carro, 01 moto, 02 bicicleta, 04 tractomula*/
	MF_IN_PAGO			=	0x09,
 	MF_APB					=	0x0A,					/*antipassback 00 inicializado, 01 IN, 02 OUT, 03 NO USA*/
	MF_FECHA_OUT		=	0X0B,					/*año,mes,dia,hora,minutos*/
	MF_MENSUAL_ANO		=	0X05,
	MF_MENSUAL_MES		=	0X06,
	MF_MENSUAL_DIA		=	0X07,
	MF_UID_0		=	0X04,
	MF_UID_1		=	0X05,
	MF_UID_2		=	0X06,
	MF_UID_3		=	0X07,
	MF_EXPIRA_ANO		=	0X08,
  MF_EXPIRA_MES		=	0X09,
	MF_EXPIRA_DIA		=	0X0A

}DATA_MF50;
uint8_t SecuenciaExpedidorMF( uint8_t EstadoActivo);
unsigned char Load_Secuencia_Expedidor(ATRIBUTOS_expedidor* Sq,unsigned const  estadoactivo,unsigned const estadoactual,unsigned const estadofuturo);
unsigned char   rta_cmd_transporte(ATRIBUTOS_expedidor* Sq );
unsigned char Trama_Validacion_P_N(void);
unsigned char error_rx_pto(void);
unsigned char	Responde_Estado_Sensores_Transporte(void);
unsigned char Responde_Tipo_Tarjeta(void);
unsigned char  Responde_Lectura_Tarjeta_Sector1_Bloque1 (ATRIBUTOS_expedidor* Sq);







