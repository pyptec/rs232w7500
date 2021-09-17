#include "W7500x.h"
#include "lintech.h"

typedef enum 
{
 EstadoActual,
 EstadoPasado,
 EstadoFuturo,
 TareadelCmd	
}Estados_Expedidor;

typedef enum 
{ 
	SEQ_INICIO,
	SEQ_CMD_ACEPTADO,
	SEQ_MOVER_CARD_RF,
	SEQ_TIPO_CARD
}SEQ_expedidor;

uint8_t Load_Secuencia_Expedidor(uint8_t *Secuencia_Expedidor,unsigned const  estadoactivo,unsigned const estadoactual,unsigned const estadofuturo);
uint8_t SecuenciaExpedidorMF( uint8_t EstadoActivo);
