
typedef enum
{
	TO_FRONT	     ='0',
	CAPTURE_BOX 	 ='1',
	SIN_MOVIMIENTO ='3'
}TIPO_movimiento;

typedef enum
{
	MovPos_Front			='0',		
	MovPos_IC					='1',
 	MovPos_RF					='2',
  MovPos_Capture		='3',
 	MovPos_EjectFront ='9'
}MOVER_card;
typedef enum
{
	Habilita					=0x30,
  Inhabilita				=0x31

}INSERCION_card;

typedef enum
{
	SENSOR_DETAIL			=0x31,
  SENSOR_NORMAL			=0x30
	
}SENSOR_detalle;
typedef enum
{
	ETX								=0x03,
 	STX_LINTECH				=0xf2
}TRAMA_lintech;



void Inicializa(TIPO_movimiento SetValue);
