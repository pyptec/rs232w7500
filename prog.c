#include <stdio.h>
#include <stdlib.h>
#include "prog.h"
#include <string.h>
#include "W7500x_uart.h"
#include "eeprom.h"

/*definicion de variables*/
char cursor[4] = "/"; //current working directory
char comandos[NUMCOMMAND][LONGSIZE]=
{
  "0",       		//ID_CLIENTEValor del punto cero.
	"1", 	     //COD_PARKTiempo de recolecion entre muestra
	"2",		// T_GRACIAInformacion recolectada enviada al rs232
	"3",		//SIN_COBROAjuste del cero del sensor
	"4",	//DEBUG Calibracion por la curva de la pendiente
	"5",		//USE_LPR
	"6",			//TIPO_PANTALLA
	"7",				// tarjeta automatica o boton
	"8",			//habilita apb o inhabilta
	"9",			//placa
	"10",			// direccion logico
	"11",			// prog horario
	"12",			// Validar tipo de vehiculo mensual
	"13",			// habilita apb para mensual
	"14",     // configura mensuales
	"15",     // ver comandos programados
	"16",			//AYUDA Ayuda!muestra todos los comandos
	"17",			//SALIRSalir de programacion
	"18",			//cmd escondido fecha de vencimiento password
	
};

/*------------------------------------------------------------------------------
Rutina que programa el id_cliente en eeprom
------------------------------------------------------------------------------*/
void prog_id_cliente()
{
	unsigned char buffer[10];
	unsigned int dataee;
	
	dataee=rd_eeprom(EE_ID_CLIENTE);																					/*se lee el id_cliente actual */
	sprintf((char *)buffer,"%d",dataee);																									/*se convierte  un entero a un string*/
	
	printf("\r\n\n ACTUAL ID_CLIENTE=%s\r\n\n",buffer);														/*se muestra el id_cliente actual en pantalla*/
	
	printf("\r\n\n DIGITE SU NUEVO ID_CLIENTE=");																	/*digite el nuevo id_cliente*/
	IngresaDato((unsigned char *)buffer,0);																												/*trae el dato digitado*/
	dataee=atoi((char *)buffer);																													/*lo convierto a un dato hex*/
	wr_eeprom(EE_ID_CLIENTE,dataee);																					/*grabo el dato en la eeprom*/
	
	dataee=rd_eeprom(EE_ID_CLIENTE);																					/*leo el dato grabado*/
	sprintf((char *)buffer,"%d",dataee);																									/*lo convierto a un string*/
	printf("\r\n\n DATO MODIFICADO ID_CLIENTE=%s\r\n\n",buffer);									/*lo muetro por la pantalla el dato grabado*/
}
/*------------------------------------------------------------------------------
Rutina que programa el cod_park
------------------------------------------------------------------------------*/
void prog_cod_park()
{
	unsigned char buffer[10];
	unsigned int dataee;
	
	dataee=rd_eeprom(EE_ID_PARK);																					/*se lee el id_cliente actual */
	sprintf((char *)buffer,"%d",dataee);																									/*se convierte  un entero a un string*/
	
	printf("\r\n\n ACTUAL COD_PARK=%s\r\n",buffer);														/*se muestra el id_cliente actual en pantalla*/
	
	printf("\r\n\n DIGITE SU NUEVO COD_PARK=");																	/*digite el nuevo id_cliente*/
	IngresaDato((unsigned char *)buffer,0);																												/*trae el dato digitado*/
	dataee=atoi((char *)buffer);																													/*lo convierto a un dato hex*/
	wr_eeprom(EE_ID_PARK,dataee);																					/*grabo el dato en la eeprom*/
	
	dataee=rd_eeprom(EE_ID_PARK);																					/*leo el dato grabado*/
	sprintf((char *)buffer,"%d",dataee);																									/*lo convierto a un string*/
	printf("\r\n\n DATO MODIFICADO COD_PARK=%s\r\n\n",buffer);									/*lo muetro por la pantalla el dato grabado*/
}


char ListaComandos(char *cmd)
{
   char buf[LONGSIZE];
   unsigned char i;
   
   for (i=0; i<NUMCOMMAND; i++)
   {
      strcpy(buf, &comandos[i][0]);
      if (strcmp(buf,cmd)==0)
         return(i);
   }
   
   return(0xFF);
}


char * GetOption(char *in)
{
    char tokensSpace[]=" \r\n";
    char tokensQuote[]="\"\r\n";
   
   //trim leading spaces
   while (*in==' ')
      in++;
   
   //if first char is a quote, then end token on a quote.  ELSE end token on a space
   if (*in == '\"')
      return(strtok(in,tokensQuote));
   else
      return(strtok(in,tokensSpace));
} 
/*------------------------------------------------------------------------------
Rutina que busca el \
------------------------------------------------------------------------------*/

char * GetCMD(char *in)
{
   char tokens[]=" \r\n";
   return (strtok(in,tokens));
}
/*------------------------------------------------------------------------------
Rutina que captura los datos pto serie y los muestra en el pto
------------------------------------------------------------------------------*/

void IngresaDato(unsigned char  *buffer, uint8_t modo)
{

 int i;
 
	do
	{ 
		*buffer = S_UartGetc();
	if (modo == 0) 
		{
  		 printf("%c", *buffer);
		}
		else 
		{
			S_UartPutc('*');
		}
	   i=*buffer; 
	   buffer++;
	 	*buffer='\0';	
		
	} while(i != '\r');
    
      
         
} 
void DisplayCursor(void)
{
   printf("\r\n\n%s> ", cursor);
}
void Show(void)
{
   printf("\r\n ID_CLIENTE         --- CMD 0 Identificador del cliente maximo 255");
   printf("\r\n COD_PARK           --- CMD 1 El numero del parqueadero maximo 255");
   printf("\r\n T_GRACIA           --- CMD 2 Tiempo sin cobro 00,  maximo 255");
   printf("\r\n SIN_COBRO          --- CMD 3 Inhabilitado= 0, Gratis= 1 , Gratis y salida el mismo dia= 2");
   printf("\r\n DEBUG              --- CMD 4 Habilitar = 1, Inhabilitar = 0");
	 printf("\r\n USE_LPR            --- CMD 5 Habilitar = 1, Inhabilitar = 0");
   printf("\r\n TIPO_PANTALLA      --- CMD 6 PANTALLA LCD =0 PANTALLA RASPBERRI=1");
	 printf("\r\n CARD_AUTOMATICA    --- CMD 7 BOTTON=0 AUTOMATICA=1");
	 printf("\r\n ANTIPASSBACK       --- CMD 8 Habilitar = 1, Inhabilitar = 0");
	 printf("\r\n PLACA              --- CMD 9 Habilitar = 1, Inhabilitar = 0");
	 printf("\r\n ADDRESS_HIGH_BOARD --- CMD 10 La direccion alta del board del numero 5 al 9 sino se usa debe ir en 0");
	 printf("\r\n HORARIO            --- CMD 11 Progama 10 horarios del 1 al 10");
	 printf("\r\n VALIDA_VEHI_MENSUAL--- CMD 12 Habilitar = 1, Inhabilitar = 0");
	 printf("\r\n USE_APB_MENSUAL    --- CMD 13 Habilitar = 1, Inhabilitar = 0");
	 printf("\r\n MENSUALES			     --- CMD 14 Habilitar = 1, Inhabilitar = 0");
	 printf("\r\n VER_PROGRAMACION   --- CMD 15 Muestra la programacion");
	 printf("\r\n AYUDA              --- CMD 16 Muestra los comandos");
   printf("\r\n SALIR              --- CMD 17 Salir de programacion");

}
void menu(void)
{


char  *option1;
char *cmd;
uint8_t opt_buffer[40];
unsigned char  buffer[20];



	Show();
  
  printf("\rSistema de Programacion Expedidor \n");
	
	while(1)
	{
	DisplayCursor();
		IngresaDato(buffer,0);	
		cmd = GetCMD((char *)buffer);	
		option1 = GetOption(cmd + strlen(cmd) + 1);
    //option2 = GetOption(option1 + strlen(option1) + 1);	 

 	 //si empieza con un '/', eso significa que incluye el caminoa
      //al archivo.  si el archivo no empieza con un '/', debe agregarce 
      //la ruta del archivo.
      if (option1 && (option1[0]=='/'))
      {
         //option1 is a full path
         strcpy((char *)opt_buffer, option1);
      }
      else if (option1)
      {
         // tack on the current working directory to option1
         strcpy((char *)opt_buffer, cursor);
         strcat((char *)opt_buffer, option1);
      }         
	 if (cmd)
      {
         switch(ListaComandos(cmd))
         {
            case 0:  										/*Se programa la identificacion del cliente*/
							prog_id_cliente();
						
				     break;
						 case 1:  //Tiempo de recolecion entre muestra
							prog_cod_park();
            break;
						 
					default:
               printf("\r\nComando no existe '%s'", cmd);
               break;
					}
			}	
	}
}
