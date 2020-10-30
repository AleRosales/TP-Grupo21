#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#define COLUMNA 5
#define FILA 3
#define MAX 90
#include "jugador.h"
#include "carton.h"
#include "funciones.h"


struct Jugadores
{
    int dniJugador;
    char nombreJugador[15];
    char apellidoJugador[15];
    int cantCartones;
    Carton cartones[3];
    float puntos;
};

int cargarDni(){
    int dni;
    char ChDni[25];
    printf("\nIngrese su documento: ");
    fflush(stdin);
    gets(ChDni);
    while (soloNumeros(ChDni) != 1){
        printf("\n>> ERROR! S%clo se admiten n%cmeros, vuelva a intentarlo.\n\n", 162, 163);
        fflush(stdin);
        gets(ChDni);
    }
    dni = atoi(ChDni);
    return dni;
}

void cargarNombreJugador(char nom[], char ape[]){
    printf("Ingrese su nombre: ");
    fflush(stdin);
    gets(nom);
    while (soloLetras(nom) != 1){
        printf("\n>> ERROR! S%clo se admiten letras, vuelva a intentarlo.\n\n", 162);
        gets(nom);
    }
    printf("Ingrese su apellido: ");
    fflush(stdin);
    gets(ape);
    while (soloLetras(ape) != 1){
        printf("\n>> ERROR! S%clo se admiten letras, vuelva a intentarlo.\n\n", 162);
        gets(ape);
    }
}
int cantidadDeCartones(){
    int cant;
    char cantChar[1];
    //Tomo el dato en char para verificar que no se inserten letras, luego se pasa a int mediante atoi()
    do{
        printf("\n>> Elija la cantidad de cartones para jugar (entre 1 a 3) \n");
        fflush(stdin);
        gets(cantChar);
        cant = validarNum(cantChar); //Le asigno el valor que retorna el chequeo
        if(validarNumerosEntre(cant, 1,3)!=1){
        printf("\n>> ERROR! Seleccion una cantidad entre 1 y 3.\n");
        }
    }while(validarNumerosEntre(cant, 1,3)!=1);
    return cant;
}

void menu(){
    char opcionChar[1]; //para la opcion en char.
    int opcion; //para la opcion en int

    //--------------PARA ARCHIVOS-----------------//
    int flagArchivo=0; //Si no hay archivo, se queda en 0
    int  tamMaxPuntaje=100;
    Jugador j[tamMaxPuntaje]; //100 seria el maximo de puntajes que almacena, se podria mejorar con una lista dinamica supongo
    for(int i=0; i<tamMaxPuntaje;i++){
          j[i]=newJugador(); //reservo memoria para los puntajes
    }
    do{
        printf("BIENVENIDO AL BINGO!\n"
               "-------------------------------\n"
               "> Por favor, ingrese una opci%cn:\n"
                "\t1 - Jugar\n"
                "\t2 - Ver historial de puntajes\n"
                "\t3 - Ver Ranking Top 3 de puntajes\n"
                "\t4 - Salir\n\n"
                "Su opci%cn: ", 162, 162);
        fflush(stdin);
        gets(opcionChar);
        opcion=validarNum(opcionChar); //devuelve el valor entero de la opcion, ya validada

    switch (opcion){
        case 1:
            system("cls");
            jugar();
            system("cls");
            break;
        case 2:
            initPuntajes(j, tamMaxPuntaje);
            flagArchivo = leerPuntajesDeArchivo(j,tamMaxPuntaje);
            if(flagArchivo==0){
                printf("\nNo hay puntajes. Todav%ca no se ha jugado ninguna partida.\n\n",161);
            } else{
                mostrarPuntaje(j, tamMaxPuntaje);
            }
            system("pause");
            system("cls");
            break;
        case 3:
            initPuntajes(j, tamMaxPuntaje);
            flagArchivo = leerPuntajesDeArchivo(j,tamMaxPuntaje);
           if(flagArchivo==0){
                printf("\nNo hay puntajes. Todav%ca no se ha jugado ninguna partida.\n\n",161);
            } else{
                rankingPuntajes(j, tamMaxPuntaje, 3); //3 porque es la cantidad de puntajes que muestro
            }
            system("pause");
            system("cls");
            break;
        case 4:
             printf("\n>> Usted ha salido.\n");
            break;
        default:
            printf("\n>> ERROR! Opci%cn no v%clida, vuelva a intentarlo.\n\n",162, 160);
            system("pause");
            system("cls");
            break;
        }
    } while(opcion!=4);
}

void subMenuCargarCartones(Jugador j){
    char opcionChar[1];
    int opInt;
    do{
        printf("\n\t%cQu%c desea hacer?\n"
               "\t\t1 - Cargar Cartones Manualmente.\n"
               "\t\t2 - Cargar Cartones Aleatoriamente\n\t> Su Opci%cn: ",168,130,162);
        fflush(stdin);
        gets(opcionChar);
        opInt=validarNum(opcionChar);
        if((validarNumerosEntre(opInt, 1,2)!=1)){
            printf("\n\t>> ERROR! Seleccione 1 o 2.\n");
        }
    } while((validarNumerosEntre(opInt, 1,2)!=1));
    switch(opInt){
        case 1:
            rellenarCartonesManual(j, j->cantCartones);
            break;
        case 2:
             rellenarCartonesAleatorio(j,j->cantCartones);
             break;
        default:
            printf("\n>> ERROR! Opci%cn no v%clida, vuelva a intentarlo.\n\n",162, 160);
            system("pause");
            system("cls");
            break;
    }
}

void jugarBolillas(int bolsaNumeros[]){
    for (int cont = 0; cont < MAX; cont++){//Lleno la matriz
        bolsaNumeros[cont] = cont+1;
    }
    for (int i = MAX-1; i > 0; i--){ //Cambia aleatoriamente el orden de los elementos
        int j = rand() % (i+1);
        int aux;
        aux = bolsaNumeros[i];
        bolsaNumeros[i] = bolsaNumeros[j];
        bolsaNumeros[j] = aux;
    }
}

void mostrarBolsa(int bolsaNumeros[],int hasta){
    printf("\n\t-----------> Bolsa <-----------\n");
    //Fines esteticos
    printf("%c", 201);
    	for(int i=0;i<49;i++){
        	printf("%c",196);
    	}
    printf("%c\n", 187);

    for (int i = 0; i < hasta; i++) {//Muestro los numeros que salen de la bolsa
        	if(i==0){ //Fin estetico
            	printf("%c",179);
        	}
        	if(bolsaNumeros[i]<10){
            	printf(" 0%d %c", bolsaNumeros[i], 179);
        	} else {
            	printf(" %d %c", bolsaNumeros[i],179);
        	}
        	if(((i+1)%10 == 0)&&(i!=hasta-1)){ //Para salto de linea cada 10 numeros
        		printf("\n%c",179);
        	} else if(i==hasta-1) { //Cambio estetico en la ultima pos.
        	printf("\n");
        	}
    }
    //Fines esteticos
    printf("%c", 200);
    	for(int i=0;i<49;i++){
        	printf("%c",196);
    	}
    printf("%c\n", 188);
}

void generarCpu(Jugador cpu){
	rellenarCartonesAleatorio(cpu, cpu->cantCartones);
}
void rellenarCartonesAleatorio(Jugador j,int cantCartones){
    for (int i=0; i<cantCartones; i++){
        j->cartones[i]=rellenarCartonAleatorio();
    }
}

void rellenarCartonesManual(Jugador j,int cantCartones){
    for (int i=0; i<cantCartones; i++){
        printf("\n-----> Rellenando Manualmente Cart%cn Nro. %d <-----\n",162,i+1);
        j->cartones[i]=rellenarCartonManual();
    }
}
void jugar(){
    int bolsa[MAX];

    //--------------CONSTRUYO EL DADO EN MEMORIA------//
    Jugador jugador=newJugador();
    Jugador cpu=newJugador();

    int cantJugadas = 0;

    //Inicializo los puntajes en 0
    jugador->puntos = 0;
    cpu->puntos = 0;

    //Inicializo los flags en 0. Estos sirven para saber si ya se ha cantado linea/columna/bingo
    int flagLinea = 0;
    int flagColumna = 0;
    int flagBingo = 0;
    int i = 0;

    int opcion = 0;

    printf("\n----A JUGAR----\n");
    //datos del jugador
    jugador->dniJugador = cargarDni();
    cargarNombreJugador(jugador->nombreJugador,jugador->apellidoJugador);
    jugador->cantCartones = cantidadDeCartones();
    //cartones
    subMenuCargarCartones(jugador);
    //mostrarCartones(jugador->cartones,jugador->cantCartones);

    cpu->cantCartones = jugador->cantCartones; //Iguala los cartones de la maquina a los del jugador.
    strcpy(cpu->nombreJugador, "CPU"); //Se guarda asi tamben en el archivo
    cpu->dniJugador=-2; //Para no mostrar el DNI de la CPU cuando se mustran los puntajes. -2 porque el '-1' es para los puntajes vacios
    strcpy(cpu->apellidoJugador, "NULL");

    rellenarCartonesAleatorio(cpu, cpu->cantCartones);
    //carga la bolsa
    jugarBolillas(bolsa);
    while(flagBingo!=1 && i<90){ //Repite mientras que cpu y usuario NO hagan bingo. Al primero que hace, corta la iteracion.
        system("cls");
        printf("Jugada nro:%d\n",i+1);
        mostrarBolsa(bolsa,i+1);
        checkAciertos(jugador->cartones, jugador->cantCartones, bolsa[i]);
        checkAciertos(cpu->cartones, cpu->cantCartones, bolsa[i]);

        printf("\n<<<< Cartones Jugador >>>>\n");
        mostrarCartones(jugador->cartones,jugador->cantCartones);

        printf("\n<<<< Cartones CPU >>>>\n");
        mostrarCartones(cpu->cartones, cpu->cantCartones);
        cpu->puntos+=puntajeParcialAutomaticoCPU(cpu->cartones, cpu->cantCartones,&flagColumna,&flagLinea,&flagBingo);

        //Para la CPU, los puntajes son automaticos
        //Para el usuario, se debe cantar linea/columna/bingo manualmente.
        if(checkBingo(cpu->cartones,cpu->cantCartones)==1){
            printf("\n>>> PARTIDA FINALIZADA. GANADOR ---> <CPU>\n");
            cantJugadas = i+1;
            cpu->puntos = multiplicarPuntos(cpu->puntos, cantJugadas);
            printf(">PUNTAJE FINAL CPU: %.2f\n", cpu->puntos);
            guardarPuntosEnF(cpu);
            flagBingo = 1;
            system("pause");
            break; //Corta la itearcion
        }

        printf("\n0 - CONTINUAR JUGADA\n"
                "1 - Cantar Linea\n"
                "2 - Cantar Columna\n"
                "3 - Cantar Bingo\n"
                "4 - Mostrar puntaje parcial\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 0:
            break;
            case 1:
                system("cls");
                if(cantarLinea(jugador->cartones, flagLinea,jugador->cantCartones)==1 &&
                   flagLinea==0){
                    jugador->puntos=puntajeFila(jugador->puntos);
                    flagLinea=1;
                }
                i--;
                system("pause");
                break;
            case 2:
                system("cls");
                if(cantarColumna(jugador->cartones, flagColumna,jugador->cantCartones)==1 &&
                   flagColumna==0){
                    jugador->puntos=puntajeColumna(jugador->puntos);
                    flagColumna=1;
                }
                i--;
                system("pause");
                break;
            case 3:
                flagBingo=cantarBingo(jugador->cartones, flagBingo,jugador->cantCartones);
                if(flagBingo==1){
                    jugador->puntos=puntajeBingo(jugador->puntos);
                    cantJugadas = i+1;
                    jugador->puntos = multiplicarPuntos(jugador->puntos, cantJugadas);
                    guardarPuntosEnF(jugador);
                    printf("\n>>> PARTIDA FINALIZADA. GANADOR ---> <%s %s>. FELICITACIONES!\n", jugador->nombreJugador, jugador->apellidoJugador);
                    printf("\n>PUNTAJE FINAL JUGADOR: %.2f\n", jugador->puntos);//Ponerlo en otro lugar??
                }
                i--;
                system("pause");
                break;
            case 4:
                system("cls");
                printf("\nPUNTAJE PARCIAL JUGADOR: %.2f"
                        "\nPUNTAJE PARCIAL CPU: %.2f\n", jugador->puntos, cpu->puntos);
                i--;
                system("pause");
                break;
            }
            i++;
    }
    //elimina de ram los datos
    for(int i=0;i<jugador->cantCartones;i++){
    	destruirCarton(jugador->cartones[i]);
    	destruirCarton(cpu->cartones[i]);
    }
    destruirJugador(jugador);
    destruirJugador(cpu);
}

float puntajeColumna(float p){
    return p+10;
}
float puntajeFila(float p){
    return p+20;
}
float puntajeBingo(float p){
    return p+70;
}


float multiplicarPuntos(float puntaje, int cantBolillas){
    if(cantBolillas<=30){
        puntaje=puntaje*2;
    } else if(cantBolillas>30&&cantBolillas<50){
        puntaje=puntaje*1.7;
    } else if(cantBolillas>=50&&cantBolillas<=70){
        puntaje=puntaje*1.5;
    }
    return puntaje;
}
void guardarPuntosEnF(Jugador player){
    FILE *archivo;
    archivo = fopen("Puntajes.txt", "a");
    fprintf(archivo,"%d+%s+%s+%.2f\n",player->dniJugador,player->nombreJugador,player->apellidoJugador,player->puntos);
    fclose(archivo);
}
int leerPuntajesDeArchivo(Jugador j[], int t){
     FILE *archivo;
    archivo = fopen("Puntajes.txt","r");
    int i=0;
    char aux[40] = " ";
    if(archivo==NULL){
        return 0;
    }
    //Mientras que el archivo exista y no llegue al final...
    while ((archivo!=NULL)&&(!feof(archivo)))
    {
        strcpy(aux, "-1+-1+-1+-1"); //esto le da el valor de '-1' a todas las variables, por lo que luego se considerará vacía la pos
                        //esto es porque siempre al leer un nuevo dato, se lee un salto de linea que hace que el while se itere una vez más al final
                        //al iterarse esa vez, genera un puntaje basura (repetido del puntaje anterior)
        fgets(aux,40,archivo);
        j[i]=charAJugador(aux, 40);
        i++;
    }
    fclose(archivo);
    return 1;
}
void mostrarPuntaje(Jugador j[], int t){
    for(int i=0; i<t; i++){
        if(j[i]->puntos!=-1){ //Mientras los puntos no sean -1
            if(j[i]->dniJugador==-2){
            printf("\tNOMBRE: [%s] - PUNTAJE: [%.2f]\n",j[i]->nombreJugador,j[i]->puntos); //Obviamente no mostramos el DNI ni Apellido de la CPU
            }else {
            printf("\tDNI: [%d] - NOMBRE: [%s] - APELLIDO: [%s] - PUNTAJE: [%.2f]\n",j[i]->dniJugador, j[i]->nombreJugador,j[i]->apellidoJugador,j[i]->puntos);
            }
        }
    }
}
Jugador charAJugador(char c[], int t){
    Jugador j = newJugador();
    int i,posMas1, posMas2, posMas3;
    char auxNombre[15]= " ", auxApellido[15]=" ",auxPuntaje[15]= " ", auxDNI[15]= " ";

    posMas1 = busquedaSecuencial(0,c, '+', t); //busqueda del '+' que empieza en 0
    posMas2 = busquedaSecuencial(posMas1+1,c,'+',t); //busqueda del '+' que empieza en posMas1+1
    posMas3 = busquedaSecuencial(posMas2+1,c,'+',t); //busqueda del '+' que empieza en posMas2+1

    for (i=0;i<posMas1;i++)
    {
       auxDNI[i] = c[i];
    }
    for (i=posMas1+1;i<posMas2;i++)
    {
        auxNombre[i-posMas1-1] = c[i];
    }
    for(i=posMas2+1;i<posMas3;i++){
        auxApellido[i-posMas2-1] = c[i];
    }
    for(i=posMas3+1; i<t;i++){
        if(c[i]=='\0'){ //si llega al final, corto la iteracion
            break;
        } else{
            auxPuntaje[i-posMas3-1] = c[i];
        }
    }
    j->dniJugador = atoi(auxDNI);
    strcpy(j->nombreJugador, auxNombre);
    strcpy(j->apellidoJugador, auxApellido);
    j->puntos = atof(auxPuntaje);
    return j;
};

void rankingPuntajes(Jugador j[], int t, int c){
    Jugador jOrdenado[t];
    for(int i=0; i<t; i++){ //Duplico el array para mantener el origina en la ejecucion del programa
        jOrdenado[i] = newJugador();
        jOrdenado[i] = j[i];
    }
    ordenarBurbuja(jOrdenado,t); //ordeno el array
    mostrarPuntaje(jOrdenado,c); //Muestro solo 5, los 5 mayores
}
void ordenarBurbuja(Jugador p[], int t){
    Jugador aux = newJugador();
    for (int j=0; j<t; j++) {
        for(int i =0 ; i<t-1; i++) {
            if(p[i]->puntos<p[i+1]->puntos) {
                aux = p[i];
                p[i]= p[i+1];
                p[i+1]= aux;
            }
        }
    }
}
void initPuntajes(Jugador j[], int t){
    for(int k=0;k<t;k++){
        j[k]->puntos=-1;
    }

}
Jugador newJugador(){
        Jugador j = malloc(sizeof(struct Jugadores)); //reservo memoria para cada jugador
        return j;
}
void destruirJugador(Jugador p){
    free(p); //libero la memoria de los jugadores
}

