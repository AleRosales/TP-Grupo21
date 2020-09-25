#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#define COLUMNA 5
#define FILA 3
#define MAX 90

//Definiciones

struct Carton
{
    int carton[FILA][COLUMNA];
    int cartonCheck[FILA][COLUMNA];
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
void rellenarCartonAleatorio(int carton[][COLUMNA]);

//PRE:Se tiene que recibir c/u de los números que rellenan el carton
//POST:Retorna una variable true o false. Si es true, asigna un valor sin repetir a la matriz
//Sino, vuelve a entrar en bucle hasta encontrar un número diferente al que le quiere asignar
bool numerosDelCartonSinRepetir(int carton[][COLUMNA],int num);

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

//PRE: Recibe un string y verifica que contenga sólo números.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloNumeros(char strg[]);

//PRE: Recibe un string y verifica que contenga sólo letras y/o espacios.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloLetras(char strg[]);

//PRE: Recibe como parametro un valor del minimo y un valor del maximo para generar el numero aleatorio
//POST: Devuelve un unico valor entero entre mini y maxi
int aleatorioEntre(int mini, int maxi);

//PRE: Se pide un array del tipo struct Carton y la cantidad de cartones que el usuario eligió, que ya debe estar seleccionada.
//POST: Ejecuta una iteracion la misma cantidad de veces como cartones elegidos, llamando cada vez a rellenarCartonAleatorio().
void rellenarCartonesAleatorio(struct Carton cartones[],int cantCartones);

//PRE: Se pide un array del tipo struct Carton y la cantidad de cartones que el usuario eligió, que ya debe estar seleccionada.
//POST: Ejecuta una iteracion la misma cantidad de veces como cartones elegidos, llamando cada vez a mostrarCarton().
void mostrarCartones(struct Carton cartones[],int cantCartones);

struct Carton tieneColumna(struct Carton carton);

struct Carton tieneFila(struct Carton carton);

//PRE: El usuario eligio la cantidad de cartones, basado en eso llena los cartones del CPU
//POST: Genero los numeros del carton para la struct cpu
void generarCpu(struct Jugador jugador);

//PRE: bolsaNumeros tiene que estar definida, tiene que ser de tamaño == MAX.
//POST: bolsaNumeros queda lleno por numeros unicos de 0 a < MAX, en orden aleatorio.
void jugarBolillas(int bolsaNumeros[]);

//PRE: bolsaNumeros[] ya esta definido y pasó el proceso de carga
//POST: muestra en pantalla las 90 bolillas de la bolsa
void mostrarBolsa(int bolsaNumeros[],int hasta);

//PRE: Ambas struct deben estar completas (jugador/cpu cartones.carton), bolsa numeros generado
//POST: Si el numero en la coordenada carton[FILA][COLUMNA] esta en bolsaNumeros, en cartonCheck[FILA][COLUMNA] va a poner un -1.
void checkAciertos(struct Jugador *jugador, int numCartones, int numeroBolsa);

//PRE: Recibe dos int como parametro
//POST: Devuelve 1 si son iguales, 0 si son distintos
int compararNumeros(int num1, int num2);

//PRE: Se lo llama al comienzo del main una única vez.
//POST: Ejecuta un menu donde el usuario elije que hacer
void menu();

//PRE: char numChar debe estar inicializado y definido con el ingreso que hizo el usuario
//POST: Verifica que se haya ingresado un numero, llamando a la funcion soloNumeros()
//      Una vez verificado el numero, se retorna el valor entero del char que se ingresó
int validarNum(char numChar[]);

//PRE: Se lo llama dentro de la funcion rellenarCartonesManual
//     Se le pasa como parametro una matriz dentro de la struct Carton
//POST: Pide al usuario el ingreso de los numeros seleccionados para el carton
//      LLama a otras funciones para verificar que se cumplan las condiciones correspondientes
void rellenarCartonManual(int carton[][COLUMNA]);

//PRE: Se pide un array del tipo struct Carton y la cantidad de cartones que el usuario eligió, que ya debe estar seleccionada.
//POST: Ejecuta una iteracion la misma cantidad de veces como cartones elegidos, llamando cada vez a rellenarCartonManual().
void rellenarCartonesManual(struct Carton cartones[],int cantCartones);

//PRE: Se ejecuta luego de preguntarle al usuario la cantidad de cartones a jugar.
//     cantCartones debe estar definido
//POST: Muestra un menu donde se elige si se quiere jugar aleatoriamente o manualmente.
//      Valida las entradas del usuario.
void subMenuCargarCartones(struct Carton cartones[],int cantCartones);

//PRE: Se le pasa un valor (num) el cual se va a verificar que exista entre el valor min y el valor max.
//POST: Retorna 1 si num se encuentra en los parametros establecidos.
//      Retorna 0 si num no se encuentra en los parametros establecidos.
int validarNumerosEntre (int num,int min, int max);

//PRE: La matriz carton debe estar declarada
//POST: Llena la matriz con 0, para así realizar la busqueda de numeros repetidos sin analizar basura.
void inicializarVacio(int carton[][COLUMNA]);

//PRE:
//POST: Puntos y ganador de la partida
void Jugar();

int puntajes(struct Jugador j, int cantCart);
int checkColumna(int c[FILA][COLUMNA]);
int checkFila(int c[FILA][COLUMNA]);
int checkBingo(int c[FILA][COLUMNA]);

int main()
{
    menu();
    return 0;
}
void menu(){
    srand(time(0)); //Esta linea se tiene que ejecutar una sola vez al principio del programa (puede ser acá o en el main)
    /*COMENTARIO A BORRAR-->
    Acá opcionChar[] lo ideal es que sea un char solo y no un array.
    Hice una funcion que valide los numeros nueva, que reciba un char y no un string (como la que valida el DNI por ej.)
    El problema es cuando llega el atoi que lo convierte en int. atoi si o si recibe un string, y como le estariamos pasando
    un char, el programa se crashea. Solucion a medias: hacer un switch manualmente que retorne el valor entero del char. El
    tema de eso es que que si se excede el numero y se tipea "215643", va a ingresar a la opcion 2 porque solo toma el primer numero.
    Conclusion: lo dejamos asi y fue :)
    <----COMENTARIO A BORRAR*/
    char opcionChar[1]; //para la opcion en char.
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
               "4: Jugar\n"
               "5: Salir\n\n"
               "Su opci%cn: ", 162, 162);
        fflush(stdin);
        gets(opcionChar);
        opcion=validarNum(opcionChar); //devuelve el valor entero de la opcion, ya validada

    switch (opcion){
        case 1:
            jugador.dniJugador = cargarDni();
            cargarNombreJugador(jugador.nombreJugador,jugador.apellidoJugador);
            mostrarDatosJugador(jugador.dniJugador,jugador.nombreJugador,jugador.apellidoJugador);
            system("pause");
            system("cls");
            break;

        case 2:
            jugador.cantCartones = cantidadDeCartones();
            subMenuCargarCartones(jugador.cartones,jugador.cantCartones);
            mostrarCartones(jugador.cartones,jugador.cantCartones);
            system("pause");
            system("cls");
            break;

        case 3:
			cpu.cantCartones = jugador.cantCartones; //Iguala los cartones de la maquina a los del jugador.
			generarCpu(cpu); //Genera los cartones de la maquina.

			printf("Cartones del jugador: \n");
			mostrarCartones(jugador.cartones,jugador.cantCartones);

            jugarBolillas(bolsa);
            mostrarBolsa(bolsa,MAX);

            system("pause");
            system("cls");
            break;
        case 4:
            Jugar(bolsa,jugador,cpu);
            break;
        case 5:
            printf("\n>> Usted ha salido.\n");
            break;
        default:
            printf("\n>> ERROR! Opci%cn no v%clida, vuelva a intentarlo.\n\n",162, 160);
            system("pause");
            system("cls");
            break;
        }
    } while(opcion!=5);
}
int validarNum(char numChar[]){
    while (soloNumeros(numChar) != 1){ //verifico que no se hayan ingresado letras
        printf("\n>> ERROR! S%clo se admiten n%cmeros, vuelva a intentarlo:\n\nSu opci%cn: ", 162, 163, 162);
        fflush(stdin);
        gets(numChar);
    }
     int numInt = atoi(numChar); //Paso a INT la opcion que estaba en CHAR
     return numInt;
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
    printf("-----------------\n"
           ">>> DNI: %d\n"
           ">>> NOMBRE: %s\n"
           ">>> APELLIDO: %s\n"
           "-----------------\n", dni, nom, ape);
}

void rellenarCartonAleatorio(int carton[][COLUMNA]){
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
void subMenuCargarCartones(struct Carton cartones[],int cantCartones){
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
            rellenarCartonesManual(cartones, cantCartones);
            break;
        case 2:
             rellenarCartonesAleatorio(cartones,cantCartones);
             break;
        default:
            printf("\n>> ERROR! Opci%cn no v%clida, vuelva a intentarlo.\n\n",162, 160);
            system("pause");
            system("cls");
            break;
    }
}
void rellenarCartonesManual(struct Carton cartones[],int cantCartones){
    for (int i=0; i<cantCartones; i++){
        printf("\n-----> Rellenando Manualmente Cart%cn Nro. %d <-----\n",162,i+1);
        rellenarCartonManual(cartones[i].carton);
    }
}
void rellenarCartonManual(int carton[][COLUMNA]){
    int num;
    inicializarVacio(carton); //Inicializa en 0 al para comparar bien los numeros al momento de ingresar
    for(int f=0; f<FILA; f++){
        for(int c=0; c<COLUMNA; c++){
            do{
            printf("\tIngrese n%cmero [COL: %d][FIL: %d]: ",163, c+1, f+1);
            scanf("%d", &num);
                if(numerosDelCartonSinRepetir(carton, num)==false){
                    printf("\n>> ERROR! No se pueden repetir los n%cmeros. Vuelva a internarlo.\n",163);
                }
                if(validarNumerosEntre(num, 1, 90)!=1){
                    printf("\n>> ERROR! El n%cmero no debe ser menor a 1 ni mayor a 90. Vuelva a internarlo.\n", 163);
                }
            }while ((numerosDelCartonSinRepetir(carton, num)==false)||(validarNumerosEntre(num, 1, 90)!=1)); //Si no se cumple cualquiera de las dos, se vuelve a iterar
            carton[f][c] = num; //Si pasa la validacion, se asigna el numero
        }
        printf("\n");
    }
}
int aleatorioEntre(int mini, int maxi){
        int resultado = 0;
        resultado  =  mini + rand()%(maxi - mini + 1);
        return resultado;
}

void inicializarVacio(int carton[][COLUMNA]){
    for (int f=0; f<FILA; f++){
            for (int c=0; c<COLUMNA; c++){
              carton[f][c]=0;
            }
        }
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
int validarNumerosEntre (int num,int min, int max){
    if((num>=min)&&(num<=max)){
        return 1;
    } else{
        return 0;
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

void generarCpu(struct Jugador cpu){
	rellenarCartonesAleatorio(cpu.cartones, cpu.cantCartones);
}


//Si alguno tiene una mejor forma o mas prolija para esto, bienvenido sea.
void checkAciertos(struct Jugador *jugador, int cantCartones, int numeroBolsa){
	for(int cart = 0; cart <= cantCartones; cart++)
	{
		for(int fil = 0; fil <= FILA; fil++)
		{
			for(int col = 0; col <= COLUMNA; col++)
			{
                if (compararNumeros(jugador->cartones[cart].carton[fil][col],numeroBolsa) == 1)
                {
                        jugador->cartones[cart].carton[fil][col] = -1;
                }
			}
		}
	}
}

int compararNumeros(int num1, int num2)
{
	int resultado = 0;
	if (num1 == num2)
	{
		resultado = 1;
	}
	return resultado;
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
void rellenarCartonesAleatorio(struct Carton cartones[],int cantCartones){
    for (int i=0; i<cantCartones; i++){
        rellenarCartonAleatorio(cartones[i].carton);
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
void Jugar(){
        int bolsa[MAX];
        struct Jugador jugador;
        struct Jugador cpu;

        jugador.puntos = 0;
        cpu.puntos = 0;

        system("cls");
        printf("----A JUGAR----\n");
        //datos del jugador
        jugador.dniJugador = cargarDni();
        cargarNombreJugador(jugador.nombreJugador,jugador.apellidoJugador);
        jugador.cantCartones = cantidadDeCartones();
        //cartones
        subMenuCargarCartones(jugador.cartones,jugador.cantCartones);
        mostrarCartones(jugador.cartones,jugador.cantCartones);

        cpu.cantCartones = jugador.cantCartones; //Iguala los cartones de la maquina a los del jugador.

        rellenarCartonesAleatorio(cpu.cartones, cpu.cantCartones);
        //GENERAR CPU DA PROBLEMAS, MEJOR SACARLO
        //generarCpu(cpu); //Genera los cartones de la maquina.
        //carga la bolsa
        jugarBolillas(bolsa);
        for(int i=0;i<MAX;i++){
            system("cls");
            printf("Jugada nro:%d\n",i+1);
            mostrarBolsa(bolsa,i+1);
            checkAciertos(&jugador, jugador.cantCartones, bolsa[i]);
            checkAciertos(&cpu, cpu.cantCartones, bolsa[i]);

            printf("\n-------Cartones Jugador-------\n");
            mostrarCartones(jugador.cartones,jugador.cantCartones);
            jugador.puntos=puntajes(jugador, jugador.cantCartones);
            printf("\n\tPUNTAJE JUGADOR: %d\n", jugador.puntos);

            printf("\n-------Cartones CPU-------\n");
            mostrarCartones(cpu.cartones, cpu.cantCartones);
            cpu.puntos=puntajes(cpu, cpu.cantCartones);
            printf("\n\tPUNTAJE CPU: %d\n", cpu.puntos);
            /*
            Cuando trato de chequear si ya se hizo bingo, como para terminar la jugada, casi siempre me tira el error "call stack"
            o el "Segmentation fault". Segun google estos errores son casi siempre por el mal uso de punteros o porque el programa
            quiere apuntar a un lugar donde no puede acceder. Pero el codigo es bastante básico, no use punteros ni nada y solo pasa cuando
            descomento el if de abajo.
            */

//          if((checkBingo(jugador.cartones[i].carton)!=0)||(checkBingo(cpu.cartones[i].carton)!=0)){ //NO FUNCIONA
//              printf("\n>>> PARTIDA FINALIZADA.\n");
//              int cantJugadas = i+1;
//              break;
//            }

               system("pause");

            }
}
int puntajes(struct Jugador j, int cantCart){
    int flagColum=0;
    int flagFil=0;
    int flagBingo=0;
    int puntaje=0;

    for(int i=0; i<cantCart; i++){
        if((checkColumna(j.cartones[i].carton)==1)&&(flagColum==0)){
            flagColum=1;
            puntaje+=10;
        }
        if((checkFila(j.cartones[i].carton)==1)&&(flagFil==0)){
            flagFil=1;
            puntaje+=20;
        }
        if((checkBingo(j.cartones[i].carton)==1)&&(flagBingo==0)){
            flagBingo=1;
            puntaje+=70;
        }
    }
    return puntaje;
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
int checkBingo(int c[FILA][COLUMNA]){
    int contadorBingo = 0;
    for(int fil=0; fil<FILA; fil++){
        for(int col=0; col<COLUMNA; col++){
            if(c[fil][col]!=-1){ //SOLUCIONAR: A veces el debugger tira error de "call stack" acá. A veces no. Tambien tira "Segmentation fault", googlié pero no sé como solucionarlo
                return 0; //Como en el bingo todos los valores deben ser -1, al primero que no sea, corta la funcion.
            }
        }
    }
    return 1;
}
