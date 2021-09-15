
#include "W7500x.h"
typedef enum
{

    ESPERA_ASK=0,
		ESPERA_INICIO_RTA=1,
		LEN_DATA=2,
    STORE_DATA=3
	
}ESTADO_UART0;

/* Private variables ---------------------------------------------------------*/
extern uint8_t g_cEstadoComSoft;									//estados del pto serie UART0
extern uint8_t buffer_ready;
#define 	TBUF_SIZE_LINTECH   50 
void com_isr (uint8_t cDatoRx );

