#include "wiegand.h"
#include <stdio.h>

extern ATRIBUTOS_Wiegand wg;

void DoL_data0(void)
{
	
	
	/*DOL1 - DATA0
	  lee solo los datos del los bits de (0)*/
		wg.Codebits[wg.nex_bit] = '0';
		
		
		
			if(	++wg.nex_bit == WGND_SIZE )
			{
				wg.completo= 1 ;
				wg.Codebits[wg.nex_bit+1] = 0 ;
			}
			
}
void D1L_data1(void)
{
	/*D1L1 - DATA1 
				lee solo los datos del los bits de (1)*/

		wg.Codebits[wg.nex_bit] = '1';	
		
		
		if(	++wg.nex_bit == WGND_SIZE )
		{
			wg.completo= 1;
			wg.Codebits[wg.nex_bit+1] = 0;
		}

	
}
/*------------------------------------------------------------------------------
rutina que limpia el buffer de lectura de wiegand
------------------------------------------------------------------------------*/
void limpia_data(void)
{
unsigned char i;
  for(i=0;i<WGND_SIZE+1;i++)
	{	
		wg.Codebits[i]=0x00;	 					/*se limpia buffer de bits de wiegand*/
 	}
	 	wg.nex_bit=0;									/*contador de bits*/
		wg.completo=0;									/*indica que hay un dato de wiegand*/
		wg.Facility_code=0;
		wg.Card_Number=0;
		wg.Card_Number1=0;
		wg.Card_Number2=0;
	
}

/*------------------------------------------------------------------------------
rutina que ajusta la lectura de wiegand
------------------------------------------------------------------------------*/

void ajusta_code(void)
{
	wg.Facility_code=bits_wiegand_hex(1);
	wg.Card_Number=bits_wiegand_hex(9);
	wg.Card_Number1=bits_wiegand_hex(17);
	wg.Card_Number2=bits_wiegand_hex(25);
}

/*------------------------------------------------------------------------------
rutina que convierte los bits de lectura de wiegand a hex
bits= es un arreglo donde se realiza una or con cada bit para crear el dato hex 
starting_position= posicion de inicio de analisis del arreglo de bits, para crear el caracter hex

codebits=Lectura de bits del codigo wiegand
------------------------------------------------------------------------------*/

unsigned char  bits_wiegand_hex(unsigned char starting_position)
{
	unsigned char i,j,code_wiegand=0;
	unsigned char bits[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	i=starting_position+8;
	
  for(j=starting_position ; j < i ; j++)
	{
    	if(wg.Codebits[j]=='1')
		{
      	code_wiegand=code_wiegand | bits[j-starting_position];
		}
			
		else if((wg.Codebits[j]>'1') || (wg.Codebits[j]< '0'))
		 {
			   
			
 			printf("ERROR DE LECTURA");
			code_wiegand=  0;
			break;	
		 }

	}
	return code_wiegand;
}
void ID_Car_Proximidad(uint8_t *buffer_wiegand)
{
		ajusta_code();	
		*buffer_wiegand=wg.Card_Number;
		*(buffer_wiegand+1)=wg.Card_Number1;
		*(buffer_wiegand+2)=wg.Card_Number2;	
}


	
	
