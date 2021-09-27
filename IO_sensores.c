#include <stdio.h>
#include "IO_sensores.h"
#include "W7500x_gpio.h"
#include "expedidor.h"

extern ATRIBUTOS_expedidor sq;

unsigned char ValidaSensor(void)
{
	
char	Valido=0;
int	Tmin=500;
	while ((GPIO_ReadInputDataBit(GPIOA,  Sensor2_GpioA_2)== 1)&&(Valido==0))
	{
		Tmin--;
		if (Tmin==0)
		{
			 Valido=1;
		}
	}
	return Valido;
}
/*------------------------------------------------------------------------------
Funcion q debuelve que sensor esta activo
------------------------------------------------------------------------------*/
unsigned char Valida_Sensor1_Auto(void)
{
	unsigned char sensor; 
		
	if (GPIO_ReadInputDataBit(GPIOA,  Sensor1_GpioA_1)== 0)
			{
				/* sensor1  se encuentra activo */					
				if (GPIO_ReadInputDataBit(GPIOA,  Auto_GpioA_0)== 0)
					{				  														
				/* sensor Auto activo es un carro*/ 
					   printf( "Sensores Auto y sensor1 activos.\n");
					   sq.Atributos_Expedidor[Type_Vehiculo]=AUTOMOVIL;
					
					}
					else
					{
							printf( "Sensor activo sensor1.\n");
							sensor=  0xff ;
							sq.Atributos_Expedidor[Type_Vehiculo]=MOTO;
					}
			}
			else
			{ 	
					if (GPIO_ReadInputDataBit(GPIOA,  Auto_GpioA_0)== 0)
					{
						printf( "Detectado. Sensor Auto.\n");
						sensor=  0xff ;	
						sq.Atributos_Expedidor[Type_Vehiculo]=MOTO;
					}
					else
					{
						printf( "Sensores no detectados.\n");
						sensor=  0x00;	
					}
						

			}
				
				return sensor;
}
/*------------------------------------------------------------------------------
Detecto la activacion de los sensores de salida
------------------------------------------------------------------------------*/

unsigned char  ValidaSensoresPaso(void)
{
 unsigned char sensor;
			/*sensor_2 inactivo*/
		if(GPIO_ReadInputDataBit(GPIOA,  Sensor2_GpioA_2)== 1)
		{
			if (ValidaSensor()==1)
			{
				/*confirma que el Sensor_2 esta inactivo*/
				sensor=Valida_Sensor1_Auto();
	
			}
			else 
			{
				printf( "Vehiculo Esperando Salir.\n");
				return 0x00;
			}
		}
		else 
		{
				printf( "Vehiculo Saliendo. Un momento.\n");
				return 0x00;
		}
	return sensor;
}
