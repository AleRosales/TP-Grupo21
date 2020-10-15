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



struct Cartones
{
    int carton[FILA][COLUMNA];
    int fila;
    int columna;
    int bingo;

};
float puntajeParcialAutomaticoCPU(Carton cartones[],int cantCartones){
    int flagColum=0;
    int flagFil=0;
    int flagBingo=0;
    float puntaje=0;
    for(int i=0; i<cantCartones; i++){
        if((checkColumna(cartones[i]->carton)==1)&&(flagColum==0)){
            flagColum=1;
            puntaje+=10;
        }
        if((checkFila(cartones[i]->carton)==1)&&(flagFil==0)){
            flagFil=1;
            puntaje+=20;
        }
    }
    if((checkBingo(cartones,cantCartones)==1)&&(flagBingo==0)){
        flagBingo=1;
        puntaje+=70;
    }
    return puntaje;
}

Carton rellenarCartonManual(){
    int num;
    Carton cart=newCarton();
    inicializarVacio(cart->carton); //Inicializa en 0 al para comparar bien los numeros al momento de ingresar
    for(int f=0; f<FILA; f++){
        for(int c=0; c<COLUMNA; c++){
            do{
            printf("\tIngrese n%cmero [COL: %d][FIL: %d]: ",163, c+1, f+1);
            scanf("%d", &num);
                if(numerosDelCartonSinRepetir(cart->carton, num)==false){
                    printf("\n>> ERROR! No se pueden repetir los n%cmeros. Vuelva a internarlo.\n",163);
                }
                if(validarNumerosEntre(num, 1, 90)!=1){
                    printf("\n>> ERROR! El n%cmero no debe ser menor a 1 ni mayor a 90. Vuelva a internarlo.\n", 163);
                }
            }while ((numerosDelCartonSinRepetir(cart->carton, num)==false)||(validarNumerosEntre(num, 1, 90)!=1)); //Si no se cumple cualquiera de las dos, se vuelve a iterar
            cart->carton[f][c] = num; //Si pasa la validacion, se asigna el numero
        }
        printf("\n");
    }
    return cart;
}

void mostrarCartones(Carton cartones[],int cantCartones){
    for (int i=0; i<cantCartones; i++){
        printf("\n-------> Cart%cn %d <-------\n",162,i+1);
        mostrarCarton(cartones[i]->carton);
    }
}
Carton tieneFila(Carton carton){
    for (int f=0; f<FILA; f++){
        //Recorre toda la fila y chequea si salio toda
        int fila=0;
        for (int c=0; c<COLUMNA; c++){
            //si el numero ya salio de la bolsa
            if(carton->carton[f][c]<1){
                fila=fila+1;
            }
        }
        //todos los numeros ya salieron de la bolsa
        if(fila==FILA){
            carton->fila=1;
            return carton;
        }
    }
    carton->fila=0;
    return carton;
}
Carton tieneColumna(Carton carton){
    for (int c=0; c<COLUMNA; c++){
        //Recorre toda la columna y chequea si salio toda
        int col=0;
        for (int f=0; f<FILA; f++){
            //si el numero ya salio de la bolsa
            if(carton->carton[f][c]<1){
                col=col+1;
            }
        }
        //si todos los numeros ya salieron de la bolsa
        if(col==COLUMNA){
            carton->columna=1;
            return carton;
        }
    }
    carton->columna=0;
    return carton;
}
//Si alguno tiene una mejor forma o mas prolija para esto, bienvenido sea.
void checkAciertos(Carton cartones[], int cantCartones, int numeroBolsa){
    for(int cart = 0; cart < cantCartones; cart++){
        for(int fil = 0; fil < FILA; fil++){
            for(int col = 0; col < COLUMNA; col++){
                if (compararNumeros(cartones[cart]->carton[fil][col],numeroBolsa) == 1){
                    cartones[cart]->carton[fil][col] = -1;
                }
            }
        }
	}
}
int cantarColumna(Carton cartones[], int flag,int cantCartones){
    for(int i=0; i<cantCartones; i++){
        if((checkColumna(cartones[i]->carton)==1)&&(flag==0)){
            printf(">>Felicidades, ha cantado columna!!\n");
            flag = 1;
        } else if ((checkColumna(cartones[i]->carton)==1)&&(flag==1)){
            printf(">>Usted ya ha cantado columna.\n");
        } else if(checkColumna(cartones[i]->carton)!=1){
            printf(">>Usted no puede cantar columna todavia.\n");
        }
    }
    return flag;
}
int cantarLinea(Carton cartones[], int flag,int cantCartones){
    for(int i=0; i<cantCartones; i++){
        if((checkFila(cartones[i]->carton)==1)&&(flag==0)){
            printf(">>Felicidades, ha cantado linea!!\n");
            flag = 1;
        } else if ((checkFila(cartones[i]->carton)==1)&&(flag==1)){
            printf(">>Usted ya ha cantado linea.\n");
        } else if(checkFila(cartones[i]->carton)!=1){
            printf(">>Usted no puede cantar linea todavia.\n");
        }
    }
    return flag;
}
void inicializarVacio(int carton[][COLUMNA]){
    for (int f=0; f<FILA; f++){
            for (int c=0; c<COLUMNA; c++){
              carton[f][c]=0;
            }
        }
}

int checkColumna(int c[FILA][COLUMNA]){
    int contadorColum = 0;
    for(int fil=0; fil<FILA; fil++){
        for(int col=0; col<COLUMNA; col++){
            if(c[fil][col]==-1){
                contadorColum++; //Cuento la cantidad de aciertos por columna
            }
            if(contadorColum==5){
                return 1;
            }
        }
        contadorColum=0; //Reinicio el contador porque no se ha completado una columna
    }
    return 0;
}
int checkFila(int c[FILA][COLUMNA]){
    int contadorFila = 0;
    for(int col=0; col<COLUMNA; col++){
        for(int fil=0; fil<FILA; fil++){
            if(c[fil][col]==-1){
                contadorFila++; //Cuento la cantidad de aciertos por fila
            }
            if(contadorFila == 3){
                return 1;
            }
        }
        contadorFila=0; //Reinicio el contador porque no se ha completado una fila
    }
    return 0;
}
int checkBingo(Carton cartones[],int cantCartones){
    for(int i=0; i<cantCartones; i++){
        for(int fil=0; fil<FILA; fil++){
            for(int col=0; col<COLUMNA; col++){
                if(cartones[i]->carton[fil][col]!=-1){
                    return 0; //Como en el bingo todos los valores deben ser -1, al primero que no sea, corta la funcion.
                }
            }
        }
    }
    return 1;
}
int cantarBingo(Carton cartones[], int flag,int cantCartones){
    int bingo=checkBingo(cartones,cantCartones);
    if((bingo==1)&&(flag==0)){
        printf(">>Felicidades, ha cantado bingo!!\n");
        flag = 1;
    } else if ((bingo==1)&&(flag==1)){
        printf(">>Usted ya ha cantado bingo.\n");
    } else if(bingo!=1){
        printf(">>Usted no puede cantar bingo todavia.\n");
    }
    return flag;
}

Carton rellenarCartonAleatorio(){
    int numAl=0;
    Carton cart=newCarton();
    for (int f=0; f<FILA; f++){
        for (int c=0; c<COLUMNA; c++){
            do{
                numAl=aleatorioEntre(1,90); //SELECCIONA UN ÚNICO VALOR ENTRE 1 Y 90
            }
            while (numerosDelCartonSinRepetir(cart->carton,numAl)==false);  //SI EL NÚMERO SE REPITE, SE GENERARÁ OTRO NÚMERO ALEATORIO EN LA CASILLA SIGUIENTE
            cart->carton[f][c]=numAl; //GUARDO EL NUMERO ALEATORIO EN LA MATRIZ
        }
    }
    return cart;
}

bool numerosDelCartonSinRepetir(int carton[][COLUMNA],int n){
    for (int f=0; f<FILA; f++){
        for (int c=0; c<COLUMNA; c++){
            if (n==carton[f][c]){
                return false;
            }
        }
    }
    return true;
}
void mostrarCarton(int carton[][COLUMNA]){
    //Fines esteticos
    printf("%c", 201);
    for(int i=0;i<24;i++){
        printf("%c",196);
    }
    printf("%c\n", 187);

    for (int f=0; f<FILA; f++){
        for (int c=0; c<COLUMNA; c++){
            if(c==0){
                printf("%c",179);
            }
            if((carton[f][c]<10)&&(carton[f][c]>-1)){
                //Si el carton es menor a 10 Y mayor a -1, lo muestra con un 0 adelante.
                //Esto es simplemente para que el carton se muestre por pantalla de mejor manera
                printf(" 0%d %c",carton[f][c],179);
            }else if(carton[f][c]>=10) { //Si es mayor/igual a 10, se muestra sin ningun agregado
                printf(" %d %c",carton[f][c],179);
            } else{
                //El nuemro ya salio entonces es xx
                printf(" XX %c", 179);
            }

        }
        printf("\n");
    }

    //Fines esteticos
    printf("%c", 200);
    for(int i=0;i<24;i++){
    printf("%c",196);
    }
    printf("%c\n", 188);
}
int chequearCartones(char numChar[]){
    int num = 0;
    num=validarNum(numChar);
    if(num<1||num>3){
        printf("\n>> ERROR! Seleccion una cantidad entre 1 y 3.\n");
    }
    while(num<1||num>3){

    }
    return num;
}
Carton newCarton(){
        Carton c = malloc(sizeof(struct Cartones));
        return c;
}
void destruirCarton(Carton c){
    free(c);
}
