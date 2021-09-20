#include "W7500x.h"

typedef enum
{
	TO_FRONT	     ='0',
	CAPTURE_BOX 	 ='1',
	SIN_MOVIMIENTO ='3'
}TIPO_movimiento;

typedef enum
{
	MovPos_Front			='0',		
	MovPos_IC					='1',
 	MovPos_RF					='2',
  MovPos_Capture		='3',
 	MovPos_EjectFront ='9'
}MOVER_card;
typedef enum
{
	Habilita					=0x30,
  Inhabilita				=0x31

}INSERCION_card;

typedef enum
{
	SENSOR_DETAIL			=0x31,
  SENSOR_NORMAL			=0x30
	
}SENSOR_detalle;
typedef enum
{
	ETX								=0x03,
 	STX_LINTECH				=0xf2,
	ASK								=06,
	NAK								=0X15
}TRAMA_lintech;

/*------------------------------------------------------------------------------
Definicion de la trama Lintech de las respuestas de los cmd
------------------------------------------------------------------------------*/
typedef enum
{
 Pos_Length					=3,
 Pos_TipoResp				=4,
 ERROR_COLLECT_CARD	=6,
 Pos_St0							=7,
 Pos_St1							=8,
 Pos_St2							=9,
 Pos_IniDatMF				=0x0a,
 Card_type_H					=0x0a,
 Card_type_L					=0x0b,
 Rtype				        =0x0A
}OPERATE_lintech;
typedef enum
{
	e0=7,
	e1=8
}OPERATE_fail;
typedef enum
{
	FAIL_return =0x4E,
	TRUE_return=0x50,
	FULL_colector_card=0x33
}CODIGOS_error;
typedef enum
{
	REENVIA_TRAMA		=	0,
	ESPERA_MAS_TIEMPO=1
}ERROR_ptoserie;


/*------------------------------------------------------------------------------
Definicion del estado de st0,st1,st2 de la trama Lintech 
NO_CARDS_IN_MCNSM	-> No tiene tarjetas en el mecanismo 			sto=0
CARD_IN_MOUTH			-> hay una tarjeta dentro del bessel 			st0=1
CARD_OK_READ_RF		-> Tarjeta en posicion para leer/escribir dentro del mecanismo st0=2
NO_HAVE_CARDS			-> no tiene tarjetas en el deposito st1=0
LOW_NIVEL_CARDS		-> nivel bajo de tarjetas en el deposito	st1=1
FULL_CARD					-> Deposito de tarjetas esta lleno				st1=2
------------------------------------------------------------------------------*/


typedef enum
{
	NO_CARDS_IN_MCNSM=		'0',
  CARD_IN_MOUTH	=			'1',
  CARD_OK_READ_RF=			'2',
	NO_HAVE_CARDS		=		'0',
	LOW_NIVEL_CARDS		=	'1',
	FULL_CARD						='2'
}ESTADO_st0_1_2;

/*Comprobacion automatica del tipo de tarjeta 
checking RF card type
Card_type_H		Card_type_L	 explicacion
    0							0						tarjeta desconocida
		1							0						MF50
		1							1						MF70
		1							2						MF_UL
		2							0						TYPE_A_CPU
------------------------------------------------------------------------------*/
typedef enum
{
	MF50_HIGH	=						'1',
	MF50_LOW	=						'0',
	MF70			=						'1',
	OPERATE_FAIL=				0X6F
}CARD_tipo;
/* Private variables externas ---------------------------------------------------------*/


void Inicializa(TIPO_movimiento SetValue);
void Check_Status(SENSOR_detalle Detalle);
void Card_Insercion(INSERCION_card Insercion);
void Mov_Card(MOVER_card Mover);
void Aut_Card_check_Status(void);
void Clave_Seguridad_S2(void);
void Dwload_EEprom (void);
void Dwload_EEprom_prog(unsigned char *password);
void LoadVerify_EEprom(void);
void RD_MF(unsigned char Sector, unsigned char Bloque);
void WR_MF(unsigned char Sector, unsigned char Bloque,unsigned char *buffer);
void Unique_Identifier_UID(void);
void Power_off(void);
