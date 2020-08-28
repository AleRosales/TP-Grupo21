#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define COLUMNA 5
#define FILA 3
#define MAX 90

//Definiciones

struct Carton{
    int carton[FILA][COLUMNA];
    int fila;
    int columna;
    int bingo;

};
struct Jugador{
    int dniJugador;
    char nombreJugador[15];
    char apellidoJugador[15];
    int cantCartones;
    struct Carton cartones[3];
    int puntos;
};

//PRE: Se debe inicializar una variable del tipo int para cargarla con el dato pedido
//POST: Carga una variable verificando que sólo sea numérica.
int cargarDni();

//PRE: Requiere que las variables de char nom y ape existan previamente
//POST: Sobreescribe el valor de dichas variables con los datos ingresados verificando que solo sean letras y/o espacios.
void cargarNombreJugador(char nom[], char ape[]);

//PRE: los datos del jugador ya pasaron por el proceso de carga
//POST: Muestra los datos
void mostrarDatosJugador(double dni, char nom[], char ape[]);

//PRE:Carton tiene que estar definido.
//POST:Se generan 3 filas y 5 columnas con numeros aleatorios sin repetir.
void RellenarCarton(int carton[][COLUMNA]);

//PRE:Se tiene que recibir c/u de los números que rellenan el carton
//POST:Retorna una variable true o false. Si es true, asigna un valor sin repetir a la matriz
//Sino, vuelve a entrar en bucle hasta encontrar un número diferente al que le quiere asignar
bool NumerosDelCartonSinRepetir(int carton[][COLUMNA],int numAl);

//PRE: Cartón tiene que estar CARGADO
//POST: Muestra por pantalla el cartón (o los cartones), saltos de
//línea y varios
void MostrarCarton(int carton[][COLUMNA]);

//PRE:Se tiene que tipear un número entre 1 y 3.
//POST:Se genera una cantidad de cartones acorde a lo que pidió el usuario.
int CantidadDeCartones(struct Carton cartones[]);

//PRE: Toma el valor tipeado por el usuario y si no cumple las condiciones le hace repetir el proceso
//POST: Devuelve el valor ingresado por el usuario que sí cumple las condiciones
int chequearCartones(int num);

//PRE: bolsaNumeros y max tienen que estar definidos, bolsaNumeros tiene que ser de tamaño == max.
//POST: bolsaNumeros queda lleno por numeros unicos de 0 a < max, en orden aleatorio.
void jugarBolillas(int bolsaNumeros[], int max);

//PRE: Recibe un string y verifica que contenga sólo números.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloNumeros(char strg[]);

//PRE: Recibe un string y verifica que contenga sólo letras y/o espacios.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloLetras(char strg[]);

int main()
{
    int opcion;
    int bolsa[MAX];
    struct Jugador jugador;
    struct Jugador cpu;
    do           {
               printf("Bienvenido al Bingo! \n"
                      "Por favor, ingrese una opcion:\n"
                      "1: Ingresar datos del usuario\n"
                      "2: Seleccionar carton/es\n"
                      "3: Sacar 90 bolillas de la bolsa\n"
                      "4: Salir\n");

               scanf("%d",&opcion);

           switch (opcion)
           {
               case 1: jugador.dniJugador = cargarDni();
                       cargarNombreJugador(jugador.nombreJugador,jugador.apellidoJugador);
                       mostrarDatosJugador(jugador.dniJugador,jugador.nombreJugador,jugador.apellidoJugador);
                       system("pause");
                       system("cls");
                       break;

               case 2: jugador.cantCartones= CantidadDeCartones(jugador.cartones);
                       system("pause");
                       system("cls");
                       break;

               case 3: jugarBolillas(bolsa,MAX);
                       system("pause");
                       system("cls");
                       break;
              case 4: printf("\n>> Usted ha salido.\n");
                            break;
               default: printf("\n>> ERROR! Opcion no valida, vuelva a intentarlo.\n\n");
		system("pause");
                        system("cls");
                        break;
           }
           }while(opcion!=4);
    return 0;
}
int cargarDni(){
    int dni;
    char ChDni[25];
    printf("Ingrese su documento: ");
    fflush(stdin);
    gets(ChDni);
    while (soloNumeros(ChDni) != 1)
    {
        printf("\n>> ERROR! Solo se admiten numeros, vuelva a intentarlo.\n\n");
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
    while (soloLetras(nom) != 1)
    {
        printf("\n>> ERROR! Solo se admiten letras, vuelva a intentarlo.\n\n");
        gets(nom);
    }
    printf("Ingrese su apellido: ");
    fflush(stdin);
    gets(ape);
        while (soloLetras(ape) != 1)
    {
        printf("\n>> ERROR! Solo se admiten letras, vuelva a intentarlo.\n\n");
        gets(ape);
    }
}

void mostrarDatosJugador(double dni, char nom[], char ape[]){
    printf("-----------------\n>>> DNI: %.0f\n>>> NOMBRE: %s\n>>> APELLIDO: %s\n-----------------\n", dni, nom, ape);
}

void RellenarCarton(int carton[][COLUMNA]){
    srand(time(0));
    int numAl=0;
    for (int f=0;f<FILA;f++){
        for (int c=0;c<COLUMNA;c++){
           do {
                numAl=rand() % 91; //SELECCIONA UN ÚNICO VALOR ENTRE 0 Y 90
            }while (NumerosDelCartonSinRepetir(carton,numAl)==false); //SI EL NÚMERO SE REPITE, SE GENERARÁ OTRO NÚMERO ALEATORIO EN LA CASILLA SIGUIENTE

            carton[f][c]=numAl; //GUARDO EL NUMERO ALEATORIO EN LA MATRIZ
        }
    }
}

bool NumerosDelCartonSinRepetir(int carton[][COLUMNA],int numAl){
    for (int f=0;f<FILA;f++){
        for (int c=0;c<COLUMNA;c++){
            if (numAl==carton[f][c]){
                return false;
            }
        }
    }
    return true;
}
void MostrarCarton(int carton[][COLUMNA]){
    for (int f=0;f<FILA;f++){
        for (int c=0;c<COLUMNA;c++){
            if(carton[f][c]>-1){
                printf("%d ",carton[f][c]);
            }else{
                //El nuemro ya salio entonces es X
                printf("X ");
            }
        }
        printf("\n");
    }
}
int chequearCartones(int num){
    while((num<1) || (num>3)){
        printf("\n>> ERROR! ENTRE 1 Y 3!\n");
        printf("Vuelva a elegir la cantidad de cartones para jugar (entre 1 a 3) \n\n");
        scanf("%d",&num);
    }
    return num;
}
int CantidadDeCartones(struct Carton cartones[]){
    int cant,i=0;
    printf("Elija la cantidad de cartones para jugar (entre 1 a 3) \n");
    scanf("%d",&cant);
    cant = chequearCartones(cant); //Le asigno el valor que retorna el chequeo
    for (i=0;i<cant;i++){
        RellenarCarton(cartones[i].carton);
        MostrarCarton(cartones[i].carton);
        printf("\n");
    }
    return cant;
}




void jugarBolillas(int bolsaNumeros[], int max)
{
	for (int cont = 0; cont < max; cont++) //Lleno la matriz
{
		bolsaNumeros[cont] = cont+1;
	}
	for (int i = max-1; i > 0; i--) //Cambia aleatoriamente el orden de los elementos
    {
        int j = rand() % (i+1);
		int aux;
		aux = bolsaNumeros[i];
		bolsaNumeros[i] = bolsaNumeros[j];
		bolsaNumeros[j] = aux;
	}

	for (int i = 0; i < max; i++) //Muestro los numeros que salen de la bolsa
	{
		printf("%d ", bolsaNumeros[i]);
		if((i+1)%10 == 0)
		{
			printf("\n");
		}
	}
	printf("\n\n\n");
}

int soloNumeros(char strg[])
{
    int i=0;
    while (strg[i] != '\0')
    {
        if (strg[i] < '0' || strg[i] > '9')
        {
            return 0;
        }
        i++;
    }
            return 1;
}

int soloLetras(char strg[])
{
    int i=0;
    while (strg[i] != '\0')
    {
       if (strg[i] != ' ' && (strg[i] <'a' || strg[i] >'z') && (strg[i] < 'A' || strg[i] > 'Z'))
    {
        return 0;
    }
    i++;
    }
        return 1;
    }


