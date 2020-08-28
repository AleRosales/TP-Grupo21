#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define COLUMNA 5
#define FILA 3
#define MAX 90

//Definiciones

struct Carton
{
    int carton[FILA][COLUMNA];
    int fila;
    int columna;
    int bingo;

};
struct Jugador
{
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
void mostrarDatosJugador(int dni, char nom[], char ape[]);

//PRE:Carton tiene que estar definido.
//POST:Se generan 3 filas y 5 columnas con numeros aleatorios sin repetir.
void rellenarCarton(int carton[][COLUMNA]);

//PRE:Se tiene que recibir c/u de los números que rellenan el carton
//POST:Retorna una variable true o false. Si es true, asigna un valor sin repetir a la matriz
//Sino, vuelve a entrar en bucle hasta encontrar un número diferente al que le quiere asignar
bool numerosDelCartonSinRepetir(int carton[][COLUMNA],int numAl);

//PRE: Cartón tiene que estar CARGADO
//POST: Muestra por pantalla el cartón (o los cartones), saltos de
//línea y varios
void mostrarCarton(int carton[][COLUMNA]);

//PRE:Se tiene que tipear un número entre 1 y 3.
//POST:Se genera una cantidad de cartones acorde a lo que pidió el usuario.
int cantidadDeCartones();

//PRE: Toma el valor tipeado por el usuario y si no cumple las condiciones le hace repetir el proceso
//POST: Devuelve el valor ingresado por el usuario que sí cumple las condiciones
int chequearCartones(char numChar[]);

//PRE: bolsaNumeros tiene que estar definida, tiene que ser de tamaño == MAX.
//POST: bolsaNumeros queda lleno por numeros unicos de 0 a < MAX, en orden aleatorio.
void jugarBolillas(int bolsaNumeros[]);

//PRE: Recibe un string y verifica que contenga sólo números.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloNumeros(char strg[]);

//PRE: Recibe un string y verifica que contenga sólo letras y/o espacios.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloLetras(char strg[]);

//PRE: Recibe como parametro un valor del minimo y un valor del maximo para generar el numero aleatorio
//POST: Devuelve un unico valor entero entre mini y maxi
int aleatorioEntre(int mini, int maxi);

void rellenarCartones(struct Carton cartones[],int cantCartones);

void mostrarCartones(struct Carton cartones[],int cantCartones);

struct Carton tieneColumna(struct Carton carton);

struct Carton tieneFila(struct Carton carton);

//PRE: bolsaNumeros[] ya esta definido y pasó el proceso de carga
//POST: muestra en pantalla las 90 bolillas de la bolsa
void mostrarBolsa(int bolsaNumeros[]); //muestra la funcion jugarBollias()

//PRE: Se le pasa por paramtero un string y dos elementos para saber si el string encuentra entre los mismos
//     Al ser strings, lo que compara son posiciones dentro de la tabla de ASCII, y como los
//     numeros en dicha tabla están todos juntos, es posible compararlos facilmente con ese método
//POST: Devuelve 0 si la condicion se cumple, 1 si no
int charMayorA(char strg[], char min, char max);

int main()
{
    srand(time(0)); //Mantener esta linea en el main, solo debe ser llamada una vez.
    char opcionChar[1]; //para la opcion en char
    int opcion; //para la opcion en int
    int bolsa[MAX];
    struct Jugador jugador;
    struct Jugador cpu;
    do{
        printf("Bienvenido al Bingo! \n"
               "Por favor, ingrese una opci%cn:\n"
               "1: Ingresar datos del usuario\n"
               "2: Seleccionar carton/es\n"
               "3: Sacar 90 bolillas de la bolsa\n"
               "4: Salir\n\n"
               "Su opci%cn: ", 162, 162);
        fflush(stdin);
        gets(opcionChar);
        while (soloNumeros(opcionChar) != 1){ //verifico que no se hayan ingresado letras
            printf("\n>> ERROR! S%clo se admiten n%cmeros, vuelva a intentarlo:\n\nSu opci%cn: ", 162, 163, 162);
            fflush(stdin);
            gets(opcionChar);
        }
        opcion = atoi(opcionChar); //Paso a INT la opcion que estaba en CHAR
        switch (opcion){
        case 1:
            jugador.dniJugador = cargarDni();
            cargarNombreJugador(jugador.nombreJugador,jugador.apellidoJugador);
            mostrarDatosJugador(jugador.dniJugador,jugador.nombreJugador,jugador.apellidoJugador);
            system("pause");
            system("cls");
            break;

        case 2:
            jugador.cantCartones= cantidadDeCartones();
            rellenarCartones(jugador.cartones,jugador.cantCartones);
            mostrarCartones(jugador.cartones,jugador.cantCartones);
            system("pause");
            system("cls");
            break;

        case 3:
            jugarBolillas(bolsa);
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
    }
    while(opcion!=4);
    return 0;
}
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

void mostrarDatosJugador(int dni, char nom[], char ape[]){
    printf("-----------------\n>>> DNI: %d\n>>> NOMBRE: %s\n>>> APELLIDO: %s\n-----------------\n", dni, nom, ape);
}

void rellenarCarton(int carton[][COLUMNA]){
    int numAl=0;
    for (int f=0; f<FILA; f++){
        for (int c=0; c<COLUMNA; c++){
            do{
                numAl=aleatorioEntre(1,90); //SELECCIONA UN ÚNICO VALOR ENTRE 1 Y 90
            }
            while (numerosDelCartonSinRepetir(carton,numAl)==false);  //SI EL NÚMERO SE REPITE, SE GENERARÁ OTRO NÚMERO ALEATORIO EN LA CASILLA SIGUIENTE
            carton[f][c]=numAl; //GUARDO EL NUMERO ALEATORIO EN LA MATRIZ
        }
    }
}
int aleatorioEntre(int mini, int maxi){
        int resultado = 0;
        resultado  =  mini + rand()%(maxi - mini + 1);
        return resultado;
}
bool numerosDelCartonSinRepetir(int carton[][COLUMNA],int numAl){
    for (int f=0; f<FILA; f++){
        for (int c=0; c<COLUMNA; c++){
            if (numAl==carton[f][c]){
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
                    //El nuemro ya salio entonces es X
                    printf(" X %c", 179);
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
    while(charMayorA(numChar, '1', '3') !=1){
        //No hace falta chequear si si ingresó una letra porque ya chequeando que no sea 1, 2 o 3 basta.
        printf("\n>> ERROR! EL N%cMERO DEBE SER ENTRE 1 Y 3. \n>> NO SE DEBEN INGRESAR LETRAS\n",233);
        printf("Vuelva a elegir la cantidad de cartones para jugar (entre 1 a 3) \n\n");
        fflush(stdin);
       gets(numChar);
    }
    num = atoi(numChar); //convierto el char a int
    return num;
}
int cantidadDeCartones(){
    int cant,i=0;
    char cantChar[1];
    //Tomo el dato en char para verificar que no se inserten letras, luego se pasa a int mediante atoi()
    printf("\n>> Elija la cantidad de cartones para jugar (entre 1 a 3) \n");
    fflush(stdin);
    gets(cantChar);
    cant = chequearCartones(cantChar); //Le asigno el valor que retorna el chequeo
    return cant;
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
    mostrarBolsa(bolsaNumeros);
}
void mostrarBolsa(int bolsaNumeros[]){
    printf("\n\t-----------> Bolsa <-----------\n");
    //Fines esteticos
    printf("%c", 201);
    for(int i=0;i<49;i++){
        printf("%c",196);
    }
    printf("%c\n", 187);

    for (int i = 0; i < MAX; i++) {//Muestro los numeros que salen de la bolsa
        if(i==0){ //Fin estetico
            printf("%c",179);
        }
        if(bolsaNumeros[i]<10){
            printf(" 0%d %c", bolsaNumeros[i], 179);
        } else {
            printf(" %d %c", bolsaNumeros[i],179);
        }
        if(((i+1)%10 == 0)&&(i!=MAX-1)){ //Para salto de linea cada 10 numeros
        printf("\n%c",179);
        } else if(i==MAX-1) { //Cambio estetico en la ultima pos.
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
int soloNumeros(char strg[]){
    int i=0;
    while (strg[i] != '\0'){
        if (strg[i] < '0' || strg[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}
int charMayorA(char strg[], char min, char max){
    int i=0;
    while (strg[i] != '\0'){
        if (strg[i] < min || strg[i] > max){
            return 0;
        }
        i++;
    }
    return 1;
}

int soloLetras(char strg[]){
    int i=0;
    while (strg[i] != '\0'){
        if (strg[i] != ' ' && (strg[i] <'a' || strg[i] >'z') && (strg[i] < 'A' || strg[i] > 'Z')){
            return 0;
        }
        i++;
    }
    return 1;
}
void rellenarCartones(struct Carton cartones[],int cantCartones){
    for (int i=0; i<cantCartones; i++){
        rellenarCarton(cartones[i].carton);
    }
}
void mostrarCartones(struct Carton cartones[],int cantCartones){
    for (int i=0; i<cantCartones; i++){
        printf("\n-------> Cart%cn %d <-------\n",162,i+1);
        mostrarCarton(cartones[i].carton);
    }
}
struct Carton tieneFila(struct Carton carton){
    for (int f=0; f<FILA; f++){
        //Recorre toda la fila y chequea si salio toda
        int fila=0;
        for (int c=0; c<COLUMNA; c++){
            //si el numero ya salio de la bolsa
            if(carton.carton[f][c]<1){
                fila=fila+1;
            }
        }
        //todos los numeros ya salieron de la bolsa
        if(fila==FILA){
            carton.fila=1;
            return carton;
        }
    }
    carton.fila=0;
    return carton;
}
struct Carton tieneColumna(struct Carton carton){
    for (int c=0; c<COLUMNA; c++){
        //Recorre toda la columna y chequea si salio toda
        int col=0;
        for (int f=0; f<FILA; f++){
            //si el numero ya salio de la bolsa
            if(carton.carton[f][c]<1){
                col=col+1;
            }
        }
        //si todos los numeros ya salieron de la bolsa
        if(col==COLUMNA){
            carton.columna=1;
            return carton;
        }
    }
    carton.columna=0;
    return carton;
}
