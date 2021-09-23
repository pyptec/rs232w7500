#include "W7500x.h"

#define USING_WGND_SIZE_33

#if defined (USING_WGND_SIZE_33)
    #define WGND_SIZE  33
 
#elif defined (USING_WGND_SIZE_26)
    #define WGND_SIZE  26
#endif

/*wiegand*/
#define D0_GpioA_11			GPIO_Pin_11
#define D1_GpioA_12			GPIO_Pin_12


typedef struct
{
	uint8_t Codebits[WGND_SIZE+1];
	uint8_t Buffer_Wiegand[4];
	uint8_t Facility_code ;
	uint8_t Card_Number;
	uint8_t Card_Number1;
	uint8_t Card_Number2;
	uint8_t nex_bit;
	uint8_t completo;
}ATRIBUTOS_Wiegand;



void DoL_data0(void);
void D1L_data1(void);
void limpia_data(void);
void ajusta_code(void);
unsigned char  bits_wiegand_hex(unsigned char starting_position);
void ID_Car_Proximidad(uint8_t *buffer_wiegand);




