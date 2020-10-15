#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

//PRE: Recibe un string y verifica que contenga sólo letras y/o espacios.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloLetras(char strg[]);

//PRE: char numChar debe estar inicializado y definido con el ingreso que hizo el usuario
//POST: Verifica que se haya ingresado un numero, llamando a la funcion soloNumeros()
//      Una vez verificado el numero, se retorna el valor entero del char que se ingresó
int validarNum(char numChar[]);

//PRE: o = Origen de la busqueda, desde donde empieza
//     v[] = es el string en donde se tiene que realizar la busqueda
//     c = es el caracter que tiene que encontrarse
//     t = es el tamaño del string
//POST: devuelve la posicion en donde se econtró coincidencia
int busquedaSecuencial (int o,char v[], char c, int t);

//PRE: Recibe como parametro un valor del minimo y un valor del maximo para generar el numero aleatorio
//POST: Devuelve un unico valor entero entre mini y maxi
int aleatorioEntre(int mini, int maxi);

//PRE: Se le pasa un valor (num) el cual se va a verificar que exista entre el valor min y el valor max.
//POST: Retorna 1 si num se encuentra en los parametros establecidos.
//      Retorna 0 si num no se encuentra en los parametros establecidos.
int validarNumerosEntre (int num,int min, int max);

//PRE: Recibe dos int como parametro
//POST: Devuelve 1 si son iguales, 0 si son distintos
int compararNumeros(int num1, int num2);

//PRE: Recibe un string y verifica que contenga sólo números.
//POST: Devuelve 0 si la condición se cumple, 1 en caso contrario.
int soloNumeros(char strg[]);

#endif // FUNCIONES_H_INCLUDED
