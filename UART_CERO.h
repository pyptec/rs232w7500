
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
extern uint32_t uart0_rx_cnt;

#define 	TBUF_SIZE_LINTECH   50 
/*funciones prototipo*/
void com_isr (uint8_t cDatoRx );
void EscribirCadenaSoft_buffer(uint8_t *buffer,uint8_t tamano_cadena);

/*funciones externas*/
uint8_t UartPutc(UART_TypeDef* UARTx, uint8_t ch);


