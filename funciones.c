#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "funciones.h"

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

int validarNum(char numChar[]){
    while (soloNumeros(numChar) != 1){ //verifico que no se hayan ingresado letras
        printf("\n>> ERROR! S%clo se admiten n%cmeros, vuelva a intentarlo:\n\nSu opci%cn: ", 162, 163, 162);
        fflush(stdin);
        gets(numChar);
    }
     int numInt = atoi(numChar); //Paso a INT la opcion que estaba en CHAR
     return numInt;
}

int busquedaSecuencial (int o,char v[], char c, int t){
    for(int i=o; i<t; i++){
        if(v[i]==c){
            return i;
        }
    }
    return -1;
}


int aleatorioEntre(int mini, int maxi){
        int resultado = 0;
        resultado  =  mini + rand()%(maxi - mini + 1);
        return resultado;
}

int validarNumerosEntre (int num,int min, int max){
    if((num>=min)&&(num<=max)){
        return 1;
    } else{
        return 0;
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
    while (strg[i] != '\0'){ //hasta /0 porque es hasta el final del string
        if (strg[i] < '0' || strg[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}
