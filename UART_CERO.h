
#include "W7500x.h"
typedef enum
{

    ESPERA_RX=0,
		ESPERA_INICIO_RTA=1,
		LEN_DATA=2,
    STORE_DATA=3
	
}ESTADO_UART0;

#define 	TBUF_SIZE_LINTECH   50 
static void com_isr (void);
