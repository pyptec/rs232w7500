#include <expedidor.h>

extern uint8_t   rta_cmd_transporte(unsigned char *secuencia_Expedidor);
uint8_t Load_Secuencia_Expedidor(uint8_t *Secuencia_Expedidor,unsigned const  estadoactivo,unsigned const estadoactual,unsigned const estadofuturo)
{
	*(Secuencia_Expedidor + EstadoPasado ) = estadoactivo ;
	*(Secuencia_Expedidor + EstadoActual ) = estadoactual;
	*(Secuencia_Expedidor + EstadoFuturo ) = estadofuturo;
	return estadoactual;
}
uint8_t SecuenciaExpedidorMF( uint8_t EstadoActivo)
{
	
static uint8_t Secuencia_Expedidor[4];
	switch (EstadoActivo)
	{
		
		case SEQ_INICIO:
		Check_Status(SENSOR_NORMAL);
		EstadoActivo=Load_Secuencia_Expedidor(Secuencia_Expedidor,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_TIPO_CARD);
	
		break;
		case	SEQ_CMD_ACEPTADO:
		/*cmd comun para todos*/
			EstadoActivo=rta_cmd_transporte(Secuencia_Expedidor);
			break;
	case SEQ_MOVER_CARD_RF:
			Mov_Card(MovPos_RF);
			EstadoActivo=Load_Secuencia_Expedidor(Secuencia_Expedidor,EstadoActivo,SEQ_CMD_ACEPTADO,SEQ_TIPO_CARD);
			break;
	case SEQ_TIPO_CARD:
		printf("estoy aqui \n\r");
		break;
	}
	return EstadoActivo;
}
