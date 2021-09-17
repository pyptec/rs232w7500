#include "W7500x.h"
#include <stdio.h>
#include "debuger.h"
#include "UART_CERO.h"

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
	ASK								=06
}TRAMA_lintech;
typedef enum
{
 	RSPT_TRP_OK,						
	NO_RSPD_TRP_PTO_COM,		
 	ESPR_RSPT_TRP_TRAMA,		
 	ERROR_TRP_TRAMA				
}ERROR_transporte;	
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
	Rtype				        =0x0A,
	answerOk						=0x50,
	answerFalse					=0x4e
}Regreso_cmd_lintech;

typedef enum
{
	 REENVIA_TRAMA,			
   ESPERA_MAS_TIEMPO	
}ERROR_uart0;

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
uint8_t   rta_cmd_transporte(unsigned char *secuencia_Expedidor, Estados_Expedidor estado );
uint8_t error_rx_pto(void);
uint8_t Trama_Validacion_P_N(void);



