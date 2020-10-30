#ifndef CARTON_H_INCLUDED
#define CARTON_H_INCLUDED

struct Cartones;
typedef struct Cartones *Carton;

//PRE: Se pide un array del tipo struct Carton y la cantidad de cartones que el usuario eligió, que ya debe estar seleccionada.
//POST: Ejecuta una iteracion la misma cantidad de veces como cartones elegidos, llamando cada vez a mostrarCarton().
void mostrarCartones(Carton cartones[],int cantCartones);

//PRE: Se lo llama dentro de la funcion rellenarCartonesManual
//POST: Pide al usuario el ingreso de los numeros seleccionados para el carton
//      LLama a otras funciones para verificar que se cumplan las condiciones correspondientes
Carton rellenarCartonManual();

//PRE: El vector cartones[] corresponde a los cartones de cada jugador
//     *flagColumn corresponde a la bandera para saber si ya se ha cantado columna o no
//     *flagFil corresponde a la bandera para saber si ya se ha cantado fila o no
//     *flagBingo corresponde a la bandera para saber si ya se ha cantado bingo o no
//     cantCartones es la cantidad de cartones que el jugador ha decidido jugar
//POST: devuelve el puntaje parcial de la CPU
float puntajeParcialAutomaticoCPU(Carton cartones[],int cantCartones,int *flagColum,int *flagFil,int *flagBingo);

//PRE: Se la llama cada vez que se quiera reservar memoria para un nuevo cartón
//POST:Reserva espacio memoria para Carton
Carton newCarton();

//POST:Elimina de la memoria un Carton
void destruirCarton(Carton p);

//PRE: Ambas struct deben estar completas (jugador/cpu cartones.carton), bolsa numeros generado
//POST: Si el numero en la coordenada carton[FILA][COLUMNA] esta en bolsaNumeros, en cartonCheck[FILA][COLUMNA] va a poner un -1.
void checkAciertos(Carton cartones[], int cantCartones, int numeroBolsa);

//PRE: la matriz c[fila][columna] debe estar declarada
//POST: Deuvelve 0 si no se puede cantar columna
//      Devuelve 1 si se puede cantar columna
int checkColumna(int c[FILA][COLUMNA]);

//PRE: la matriz c[fila][columna] debe estar declarada
//POST: Deuvelve 0 si no se puede cantar fila
//      Devuelve 1 si se puede cantar fila
int checkFila(int c[FILA][COLUMNA]);

//PRE: El vector cartones[] corresponde a los cartones de cada jugador
//     cantCartones es la cantidad de cartones que el jugador ha decidido jugar
//POST: Deuvelve 0 si no se puede cantar bingo
//      Devuelve 1 si se puede cantar bingo
int checkBingo(Carton cartones[],int cantCartones);

//PRE: El vector cartones[] corresponde a los cartones de cada jugador
//     flag corresponde a la bandera para saber si ya se ha cantado linea o no
//     cantCartones es la cantidad de cartones que el jugador ha decidido jugar
//POST: devuelve  si se ha cantado linea, 0 si no
int cantarLinea(Carton cartones[], int flag,int cantCartones);

//PRE: El vector cartones[] corresponde a los cartones de cada jugador
//     flag corresponde a la bandera para saber si ya se ha cantado linea o no
//     cantCartones es la cantidad de cartones que el jugador ha decidido jugar
//POST: devuelve  si se ha cantado columna, 0 si no
int cantarColumna(Carton cartones[], int flag,int cantCartones);

//PRE: El vector cartones[] corresponde a los cartones de cada jugador
//     flag corresponde a la bandera para saber si ya se ha cantado linea o no
//     cantCartones es la cantidada de cartones que el jugador ha decidido jugar
//POST: devuelve  si se ha cantado bingo, 0 si no
int cantarBingo(Carton cartones[], int flag,int cantCartones);

//PRE: La matriz carton debe estar declarada
//POST: Llena la matriz con 0, para así realizar la busqueda de numeros repetidos sin analizar basura.
void inicializarVacio(int carton[][COLUMNA]);

//PRE: Se lo llama dentro de la funcion rellenarCartonesAleatorio
//POST: Llama a otras funciones para dar con numeros aleatorios que no se repitan
//      retorna un dato de tipo Carton cargado con numeros aleatorios
Carton rellenarCartonAleatorio();

//PRE:Se tiene que recibir c/u de los números que rellenan el carton
//POST:Retorna una variable true o false. Si es true, asigna un valor sin repetir a la matriz
//Sino, vuelve a entrar en bucle hasta encontrar un número diferente al que le quiere asignar
bool numerosDelCartonSinRepetir(int carton[][COLUMNA],int num);

//PRE: Cartón tiene que estar CARGADO
//POST: Muestra por pantalla el cartón (o los cartones), saltos de
//línea y varios
void mostrarCarton(int carton[][COLUMNA]);

//PRE: Toma el valor tipeado por el usuario y si no cumple las condiciones le hace repetir el proceso
//POST: Devuelve el valor ingresado por el usuario que sí cumple las condiciones
int chequearCartones(char numChar[]);

#endif
