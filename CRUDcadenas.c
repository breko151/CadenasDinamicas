#include "CRUDcadenas.h"

void ejecutarPrograma() {
    printf("Bienvenido al Sistema...");
    if(validarExistenciaArchivo()) {
        menu2();
    } else {
        menu1();
    }   
}

int validarExistenciaArchivo() {
    FILE *file;
    file = fopen("doc.txt", "r");
    if(file == NULL) 
        return 0; 
    else 
        return 1;
}

void menu1() {
    int opc;
    printf("\nEscoge alguna de las siguientes opciones:");
    printf("\n1. Escribir registros");
    printf("\n2. Salir del programa");
    printf("\nTu opcion es: ");
    scanf("%i", &opc);
    fflush(stdin);
    if(opc == 1 || opc == 2) {
        if(opc == 1) {

        } else {
            exit(1);
        }
    } else {
        menu1();
    }
}

void menu2() {
    char res = 'S';
    int opc;

    while(res == 'S' || res == 's') {
        printf("\nEscoge una opcion: ");
        printf("\n1. Escrbir registros");
        printf("\n2. Ver registros");
        printf("\n3. Borrar registros");
        printf("\n4. Salir del programa");
        printf("\nTu opcion es: ");
        scanf("%i", &opc);
        fflush(stdin);
        printf("Deseas Continuar [s/n]: ");
        scanf("%c", &res);
        fflush(stdin);
    }
}