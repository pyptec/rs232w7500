
#define 	NUMCOMMAND 19
#define 	LONGSIZE 3


extern char  *strtok  (char *str, const char *set);
void menu(void);
void Show(void);
void DisplayCursor(void);
 char * GetOption(char *in);
char * GetCMD(char *in);
void IngresaDato(unsigned char  *buffer, unsigned char modo);
char ListaComandos(char *cmd);
void prog_id_cliente(void);
void prog_cod_park(void);


