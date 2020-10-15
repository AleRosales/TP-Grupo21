#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

struct Jugadores;

typedef struct Jugadores *Jugador;

//PRE: Se debe inicializar una variable del tipo int para cargarla con el dato pedido
//POST: Carga una variable verificando que sólo sea numérica.
int cargarDni();

//PRE: Requiere que las variables de char nom y ape existan previamente
//POST: Sobreescribe el valor de dichas variables con los datos ingresados verificando que solo sean letras y/o espacios.
void cargarNombreJugador(char nom[], char ape[]);

//PRE:Se tiene que tipear un número entre 1 y 3.
//POST:Se genera una cantidad de cartones acorde a lo que pidió el usuario.
int cantidadDeCartones();

//PRE: El usuario eligio la cantidad de cartones, basado en eso llena los cartones del CPU
//POST: Genero los numeros del carton para la struct cpu
void generarCpu(Jugador jugador);

//PRE: Se pide un array del tipo struct Carton y la cantidad de cartones que el usuario eligió, que ya debe estar seleccionada.
//POST: Ejecuta una iteracion la misma cantidad de veces como cartones elegidos, llamando cada vez a rellenarCartonAleatorio().
void rellenarCartonesAleatorio(Jugador j,int cantCartones);

//PRE: Se ejecuta luego de preguntarle al usuario la cantidad de cartones a jugar.
//     cantCartones debe estar definido
//POST: Muestra un menu donde se elige si se quiere jugar aleatoriamente o manualmente.
//      Valida las entradas del usuario.
void subMenuCargarCartones(Jugador j);

//PRE: bolsaNumeros tiene que estar definida, tiene que ser de tamaño == MAX.
//POST: bolsaNumeros queda lleno por numeros unicos de 0 a < MAX, en orden aleatorio.
void jugarBolillas(int bolsaNumeros[]);

//PRE: bolsaNumeros[] ya esta definido y pasó el proceso de carga
//POST: muestra en pantalla las 90 bolillas de la bolsa
void mostrarBolsa(int bolsaNumeros[],int hasta);

//PRE: Se lo llama al comienzo del main una única vez.
//POST: Ejecuta un menu donde el usuario elije que hacer
void menu();

//PRE: Se pide un array del tipo struct Carton y la cantidad de cartones que el usuario eligió, que ya debe estar seleccionada.
//POST: Ejecuta una iteracion la misma cantidad de veces como cartones elegidos, llamando cada vez a rellenarCartonManual().
void rellenarCartonesManual(Jugador j,int cantCartones);

//PRE:El usuario selecciona jugar
//POST: Puntos y ganador de la partida
void jugar();

float multiplicarPuntos(float puntaje, int cantBolillas);

float puntajeColumna(float p);
float puntajeFila(float p);
float puntajeBingo(float p);

//PRE: se le pasa un dato de tipo struct Jugador el cual se guardará en un arhchivo
//POST: Si no existe, crea un archivo con los datos del jugador. Y si existe, agrega dichos datos al final
void guardarPuntosEnF(Jugador player);

//PRE: se le pasa un array Jugador y su repectivo tamaño
//     Abre en modo lectura un archivo (si existe) y le obtiene los datos del mismo
//     LLama a funciones para pasar los datos del texto a variables
//POST: devuelve 1 si se pudo leer, 0 si no.
int leerPuntajesDeArchivo(Jugador j[], int t);

//PRE: Se le pasa un string y su tamanio
//     Realiza busquedas secuenciales sobre el string 'c'
//POST: Devuelve un dato de tipo struct Jugador con los datos obtenidos de un archivo de texto
Jugador charAJugador(char c[], int t);

//PRE: Se le pasa un array de Jugador y su respectivo tamanio
//POST: Muestra por pantalla los puntajes y los datos de los jugadores
void mostrarPuntaje(Jugador j[], int t);

//PRE: Se le pasa un array Jugador
//     t = la cantidad máxima que almacena los puntajes
//     c = la cantidad de puntajes a mostrar
//POST: Imprime el array ordenado
void rankingPuntajes(Jugador j[], int t, int c);

//PRE: Se le pasa un array de Jugador y el tamanio del mismo
//POST: Ordena de mayor a menor la estructura
void ordenarBurbuja(Jugador p[], int t);

//PRE: se le pasa un array Jugador y su tamanio
//POST: Inicializa todos los puntajes en -1
void initPuntajes(Jugador j[], int t);

//POST:Reserva espacio memoria para jugador
Jugador newJugador();
//POST:Elimina de la memoria un Jugador
void destruirJugador(Jugador p);

#endif
