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
                imprimirArreglo();
            } else if(opc == 3) {
                borrarArreglo();
            } else 
                salir();
        } else 
            menu2();
        printf("Deseas Continuar [s/n]: ");
        scanf("%c", &res);
        fflush(stdin);
    }
    salir();
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
        strcpy(arregloRegistro[i].binario, convertirBinario(cadena));
        strcpy(arregloRegistro[i].hexadecimal, convertirHex(cadena));
        arregloRegistro[i].longitudRegistro = longitud;
        fflush(stdin);
        fflush(stdout);
    }
    free(cadena);
    ordenar(arregloRegistro, numeroElementos);
    if(generarArchivo(arregloRegistro, numeroElementos)) {
        printf("\nEl programa se cerrara...");
        free(arregloRegistro);
        exit(1);
    } else 
        printf("\nArchivo generado con exito...\n");
    free(arregloRegistro);
}

void ordenar(Registro *arreglo, int longitud) {
    if(longitud < 2) 
        return;
    else {
        int posicionMedia = longitud / 2;
        int posicionMedia2 = longitud - posicionMedia;
        Registro arregloIzquierdo[posicionMedia];
        Registro arregloDerecho[posicionMedia2];
        for(int i = 0; i < posicionMedia; i++) {
            arregloIzquierdo[i] = arreglo[i];
        }  
        for(int i = posicionMedia; i < longitud; i++) {
            arregloDerecho[i - posicionMedia] = arreglo[i];
        }  
        ordenar(arregloIzquierdo, posicionMedia);
        ordenar(arregloDerecho, longitud - posicionMedia);
        mezclar(arregloIzquierdo, arregloDerecho, arreglo, posicionMedia, posicionMedia2);
    }
}

void mezclar(Registro *registroIzquierdo, Registro *registroDerecho, Registro *registros, int longitudIzq, int longitudDer) {
    int indiceIzq = 0;
    int indiceDer = 0;
    int indiceFinal = 0;
    int arregloIzq[longitudIzq];
    int arregloDer[longitudDer];

    for(int i = 0; i < longitudIzq; i++)
        arregloIzq[i] = strlen(registroIzquierdo[i].cadena);
    for(int i = 0; i < longitudDer; i++)
        arregloDer[i] = strlen(registroDerecho[i].cadena);
    while(indiceIzq < longitudIzq && indiceDer < longitudDer) {
        if(arregloIzq[indiceIzq] > arregloDer[indiceDer]) {
            registros[indiceFinal] = registroIzquierdo[indiceIzq];
            indiceIzq++;
        } else {
            registros[indiceFinal] = registroDerecho[indiceDer];
            indiceDer++;
        }
        indiceFinal++;
    }
    while(indiceIzq < longitudIzq) {
        registros[indiceFinal] = registroIzquierdo[indiceIzq];
        indiceIzq++;
        indiceFinal++;
    }
    while(indiceDer < longitudDer) {
        registros[indiceFinal] = registroDerecho[indiceDer];
        indiceDer++;
        indiceFinal++;
    } 
}

void imprimirArreglo() {
    FILE *file;
    int cont = 1;
    int c;

    file = fopen("doc.txt", "r");
    if(file == NULL) {
        printf("No se ha abierto\n");
        fclose(file);
    } else {
        while(1) {
            c = fgetc(file);
            if(feof(file)) {
                break;
            } else {
                printf("%c", c);
                if(c == '\n') {
                    cont++;
                }
            }
        }
    }
}

void borrarArreglo() {
    FILE *file; 
    Registro * tabla; 
    int cont = 1, cont2=0; 
    int c,opcionUsuario; 
    char * final; 

    final = (char *) malloc(10 * sizeof(char)); 
    printf("Tus datos son: \n");
    imprimirArreglo(); 
    printf("Elija el dato a borrar: "); 
    scanf("%d", &opcionUsuario);
    fflush(stdin); 
    file = fopen("doc.txt","r");
    strcpy(final,"");  
    if(file == NULL) 
        printf("No se ha abierto\n"); 
    else {
        while(1) {
            c = fgetc(file);
            if( feof(file) ) { 
                break ;
            }
            if (cont!=opcionUsuario){
                final = (char *) realloc(final, (cont2 + 100) *sizeof(char)); 
                final[cont2]=c;
                printf("%c", c);
                cont2++; 
            }
            if (c=='\n'){
                cont++; 
            }
        }
    }
    
    fclose(file);
    file  =  fopen("doc.txt","w+");
    for(int i = 0; i < cont2; i++){
        fprintf(file,"%c",final[i]);
    }
    fclose(file);
}

void salir() {
    free(arregloRegistro);
    exit(0);
}

char *convertirBinario(char* cadena) {
    if(cadena == NULL) return 0; /* no hay cadena */
    char *binario = malloc(sizeof(char) * (MAX_CARACTERES *8));
    strcpy(binario,"");
    char *ptr = cadena;
    int i;
    for(; *ptr != 0; ++ptr) {
        for(i = 7; i >= 0; --i) {
            (*ptr & 1 << i) ? strcat(binario,"1") : strcat(binario,"0");
        }
    }
    return binario;
}

char *convertirHex(char *cadena) {
    char *hex;
    int i, j;
    if(cadena == NULL) return 0;
    hex = (char *) malloc(sizeof(char) * (MAX_CARACTERES *2));
    memset(hex ,0, sizeof(hex));
    for(i = 0, j = 0; i < strlen(cadena); i++, j += 2)
    { 
        sprintf((char*) hex + j, "%02X", cadena[i]);
    }
    hex[j]='\0';
    return hex;
}

int generarArchivo(Registro *arregloRegistro, int numeroRegistros) {
    FILE *file;

    file = fopen("doc.txt", "w");
    if(file == NULL) {
        printf("No es posible generar el archivo...");
        return 1;
    }
    for(int i = 0; i < numeroRegistros; i++) 
        fprintf(file,"%-2d%-30s%-240s%-60s%-2c%-3d\n", arregloRegistro[i].longitudRegistro, arregloRegistro[i].cadena, arregloRegistro[i].binario, arregloRegistro[i].hexadecimal, arregloRegistro[i].cadena[0], (int) arregloRegistro[i].cadena[0]);
    fclose(file);
    return 0;
}

int validarExistenciaArchivo() {
    FILE *file;

    file = fopen("doc.txt", "r");
    if(file == NULL) {
        fclose(file);
        return 0; 
    } else { 
        fclose(file);
        return 1;
    }
}