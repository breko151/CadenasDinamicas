#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 30

typedef char* String;
typedef struct {
    int longitudRegistro;
    String cadena;
    String binario;
    String hexadecimal;
} Registro;

void ejecutarPrograma();
int validarExistenciaArchivo();
void menu1();
void menu2();