#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 30

typedef struct {
    int longitudRegistro;
    char *cadena;
    char *binario;
    char *hexadecimal;
} Registro;

void ejecutarPrograma();
void menu1();
void menu2();
void registrarElementos(int);
void ordenar(Registro *, int);
void mezclar(Registro *, Registro *, Registro *, int, int);
void salir();

int generarArchivo(Registro *, int);
int validarExistenciaArchivo();