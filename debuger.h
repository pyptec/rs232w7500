#include <stdio.h>
#include "W7500x.h"


typedef enum
{

    DATA_ENVIADO=0,
		DATA_RECIBIDO=1,
		DATA_SIN_MSJ =2
    
}MSG_DEBUG_Estado;
void Debug_chr_UART2(uint8_t Dat);
void Debug_Buffer_UART2(uint8_t *str,uint8_t num_char);
void Debug_txt_UART2(uint8_t * str);
void DebugBufferMF(uint8_t *str,uint8_t num_char,MSG_DEBUG_Estado Estado);
