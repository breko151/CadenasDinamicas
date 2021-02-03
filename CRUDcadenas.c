#include "CRUDcadenas.h"

Registro *arregloRegistro;

void ejecutarPrograma() {
    printf("Bienvenido al Sistema...");
    if(validarExistenciaArchivo()) {
        menu2();
    } else {
        menu1();
    }   
}

void menu1() {
    int opc;
    char res;
    int numeroElementos;

    printf("\nEscoge alguna de las siguientes opciones:");
    printf("\n1. Escribir registros");
    printf("\n2. Salir del programa");
    printf("\nTu opcion es: ");
    scanf("%i", &opc);
    fflush(stdin);
    if(opc == 1 || opc == 2) {
        if(opc == 1) {
            printf("Numero de elementos que desea registrar: ");
            scanf("%i", &numeroElementos);
            fflush(stdin);
            registrarElementos(numeroElementos);
        } else {
            salir();
        }
    } else {
        menu1();
    }
    printf("Desea continuar? [s/n]: ");
    scanf("%c", &res);
    fflush(stdin);
    if(res == 's' || res == 'S') {
        if(validarExistenciaArchivo()) {
            menu2();
        } else {
            printf("No es posible realizar esa accion...");
            printf("\nNo se genero archivo...");
            printf("\nTrate ingresar nuevamente...");
            free(arregloRegistro);
            exit(1);
        }
    } else {
        salir();  
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
        if (opc == 1 || opc == 2 || opc == 3 || opc ==4) {
            if(opc == 1) {

            } else if(opc == 2) {

            } else if(opc == 3) {

            } else 
                salir();
        } else 
            menu2();
        printf("Deseas Continuar [s/n]: ");
        scanf("%c", &res);
        fflush(stdin);
    }
}

void registrarElementos(int numeroElementos) {
    int longitud = 0;
    char *cadena;
    arregloRegistro = (Registro *) malloc(sizeof(Registro) * numeroElementos);
    if(arregloRegistro == NULL) {
        printf("No es posible reservar memoria...");
        printf("\nSaldrá del programa...");
        exit(1);
    }
    cadena = (char *) malloc(sizeof(char) * MAX_CARACTERES);
    if(cadena == NULL) {
        printf("No es posible reservar memoria...");
        printf("\nSaldrá del programa...");
        free(arregloRegistro);
        exit(1);
    }
    cadena[29] = '\0';
    for (int i = 0; i < numeroElementos; i++) {
        printf("Escriba: ");
        gets(cadena);
        fflush(stdin);
        longitud = strlen(cadena);
        printf("%s\n", cadena);
        arregloRegistro[i].cadena = (char *) malloc(sizeof(char) * longitud);
        if(arregloRegistro[i].cadena == NULL) {
            printf("No es posible reservar Memoria para la cadena");
            printf("\nSaldrá del programa...");
            free(arregloRegistro);
            free(cadena);
            exit(1);
        }
        arregloRegistro[i].binario = (char *) malloc(sizeof(char) * longitud * 8);
        if(arregloRegistro[i].binario == NULL) {
            printf("No es posible reservar Memoria para el binario");
            printf("\nSaldrá del programa...");
            free(arregloRegistro);
            free(cadena);
            exit(1);
        }
        arregloRegistro[i].hexadecimal = (char *) malloc(sizeof(char) * longitud * 2);
        if(arregloRegistro[i].hexadecimal == NULL) {
            printf("No es posible reservar Memoria para el hexadecimal");
            printf("\nSaldrá del programa...");
            free(arregloRegistro);
            free(cadena);
            exit(1);
        }
        strcpy(arregloRegistro[i].cadena, cadena);
        strcpy(arregloRegistro[i].binario, cadena);
        strcpy(arregloRegistro[i].hexadecimal, cadena);
        arregloRegistro[i].longitudRegistro = longitud;
        fflush(stdin);
        fflush(stdout);
    }
    free(cadena);
    if(generarArchivo(arregloRegistro, numeroElementos)) {
        printf("\nEl programa se cerrara...");
        exit(1);
    } else 
        printf("\nArchivo generado con exito...\n");
}

void salir() {
    free(arregloRegistro);
    exit(0);
}

int generarArchivo(Registro *arregloRegistro, int numeroRegistros) {
    FILE *file;
    file = fopen("doc.txt", "w");
    if(file == NULL) {
        printf("No es posible generar el archivo...");
        return 1;
    }
    for(int i = 0; i < numeroRegistros; i++) 
        fprintf(file,"%-2d%-30s%-240s%-60s%c%-3d\n", arregloRegistro[i].longitudRegistro, arregloRegistro[i].cadena, arregloRegistro[i].binario, arregloRegistro[i].hexadecimal, arregloRegistro[i].cadena[0], (int) arregloRegistro[i].cadena[0]);
    fclose(file);
    return 0;
}

int validarExistenciaArchivo() {
    FILE *file;
    file = fopen("doc.txt", "r");
    if(file == NULL) {
        return 0; 
    } else { 
        return 1;
    }
}