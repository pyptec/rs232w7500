
#include "W7500x.h"



extern void        UartPuts                (UART_TypeDef* UARTx, uint8_t *str);

typedef enum
{

    SEC=0,
		MIN=1,
		HRS=2,
		DAY=3,
		DATE=4,
		MONTH=5,
		YEAR=6
    
}Registers_Address;

//typedef enum
//{
	
//}Alarmas;
typedef struct
{

    uint8_t second;
    uint8_t minut;
		uint8_t hour;
		uint8_t dayOfWeek;
		uint8_t dayOfMonth;
		uint8_t month;
		uint8_t year;
}GetDateDs1307;

void inicializa_reloj(void);
uint8_t  bcd_hex (uint8_t l_data);

