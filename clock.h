
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
typedef enum
{
	Domingo=1,
	Lunes=2,
	Martes=3,
	Miercoles=4,
	Jueves=5,
	Viernes=6,
	Sabado=7
	
}Dia_Semana;

typedef struct
{

    uint8_t second;
    uint8_t minut;
		uint8_t hour;
		uint8_t dayOfWeek;
		uint8_t dayOfMonth;
		uint8_t month;
		uint8_t year;
}Atributos_Ds1307;




uint8_t bcd(uint8_t carc);
uint8_t bin(uint8_t bcd_value);
void Set_Data_Write_date_time(Atributos_Ds1307 *clk);
void Get_Date_Time(uint8_t* data);
uint8_t Get_Data_clk(uint8_t addres_clk);





