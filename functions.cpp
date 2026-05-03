#include "functions.h"
#include <algorithm>
/*
Resultados -> Guardaremos las combinaciones que hicimos para formar un numero. ejem: (a+b)*(c! - d)
Procesados -> Guardaremos las keys de verificacion (Nos permiten evitar permutaciones que dan combinaciones iguales)
ElementosProcesados ->  Indicamos cuantas keys estamos guardando dentro de la lista.
*/
string Resultados[101];
string* Procesados = new string[10000000];
int ElementosProcesados = 0;
int* NResultadosNOPosibles = new int[10000000];
int NElementosNoposibles = 0;
string* Combinaciones = new string[10000000];

/*
Utilizamos una busqueda lineal
*/
bool LinearSearch(string obj){
    for (int i = 0; i<ElementosProcesados;i++){
        if (Procesados[i] == obj){
            return true;
        }
    }
    return false;
}

/*
Operaciones:
    - Definimos cada una de las operaciones que podemos hacer con un par de elementos.
    - Definimos restricciones para el modulo, division y potencia, 
    - Tipo bool: Nos permite saber si una operacion es posible con un par de numeros
        ejem: 5/0 -> false, 5 mod 3 -> true

*/
bool Operaciones(int a, int b, char operacion, int &resultado) {

    if (operacion == '+'){
        resultado = a + b;
    }
    else if (operacion == '-'){
        resultado = a - b;
    }
    else if (operacion == '*'){
         resultado = a * b;
    }
    else if (operacion == '/') {
        if (b == 0 || a % b != 0){
            return false;
        }
        resultado = a / b;
    }
    else if (operacion == '%') {
        if (b == 0){
            return false;
        }
        resultado = a % b;
    }
    else if (operacion == '^') {
        if ( b > 10){
            return false;
        }

        resultado = 1;
        
        for(int i = 0; i<b;i++){
            resultado *=a;
        }

        
    }
    else{
        return false;
    }

    return true;
}

/*
Factorial:
    - Definimos la funcion factorial de un numero de manera iterativa
    - Tipo bool: Nos permite saber si el factorial es aceptado.
        Ejem: 60! -> false (Muy grande)
*/
bool Factorial(int x, int &resultado) {
    if (x < 0 || x > 10){
        return false;
    }

    resultado = 1;
    for (int i = 1; i <= x; i++){
        resultado *= i;
    }

    return true;
}

/*
CrearArrays:
    - Definimos la funcion CrearArrays
    - Obj:
        Cuando tenemos una lista [a, b, c, d] y aplicamos una combinacion de dos elementos (a+b)= h. Tendremos que crear una nueva lista donde almacenar la combinacion de los 2 elementos y los otros [h c d].
        
    - Ejemplo de funcionamiento:

        Parametros:
            ArrayAntiguo = [a, b, c, d]
            ExpresionAntigua = [a, b, c, d]
            TamanioArrayAntiguo = 4
            (i,j) : Posiciones de la pareja de numeros -> i : Posicion numero 1 , j : Posicion numero 2
            NuevoArray: Aqui almacenaremos la nueva combinacion
            NuevaExpresion: Aqui almacenaremos como es posible la nueva combinacion
        
        Variables:
            idx: Representa la cantidad de elementos que pusimos dentro de NuevoArray y NuevaExpresion
        
        For ( recorremos 4 veces ):
            Condicional: 
            ejemplo de funcionamiento:
                i = 0 y j = 1 entonces k evita 0 y k evita 1 por lo que k empieza en 2
                [a b c d]  y   [expresion_1 expresion_2 expresion_3 expresion_4] 
                [0 1 2 3]  y   [     0          1            2          3     ]
                k = 2 -> ArrayAntiguo[2] y ExpresionAntigua[2] : Exactamente donde esta el siguiente elemento diferente a 0 y 1
                NuevoArray[0] = ArrayAntiguo[2]
                NuevaExpresion[0] = ExpresionAntigua[2];
                idx++


*/
int CrearArrays(int* ArrayAntiguo, string* ExpresionAntigua, int TamanioArrayAntiguo, int i, int j,int* NuevoArray, string* NuevaExpresion) {

    int idx = 0;

    for (int k = 0; k < TamanioArrayAntiguo; k++) {
        if (k != i && k != j) {  
            NuevoArray[idx] = ArrayAntiguo[k];  
            NuevaExpresion[idx] = ExpresionAntigua[k];
            idx++;
        }
    }

    return idx;
}

/*
CrearArraysFactorial:
    - Definimos la funcion CrearArraysFactorial
    - Obj:
        Conservar la posicion de los elementos a los cuales hemos aplicado factorial cuando hacemos una eliminacion una eliminacion de pares.
        
    Parametros:
            ArrayAntiguo : array booleano (true -> Se aplico factorial ) (false -> No se aplico factorial)
            TamanioArrayAntiguo : tamaño del array 
            (i,j) : Posiciones de la pareja de numeros -> i : Posicion numero 1 , j : Posicion numero 2
            NuevoArray: Aqui almacenaremos la nueva posicion de los elementos a los cuales hemos calculado el factorial.
    Ejemplo:
        si antes [a, b, c, d] y [false, false, true, false] ( Hemos aplicado factorial al tercer elemento c )
        y luego hacemos una combinacion de los pares (a,b) que nos da como resultado un numero j ( op(a,b) = j ), entonces en el nuevo array tendremos que conservar la posicion de la lista de booleanos para indicar de que el elemento c ha sido calculado su factorial:
            [j, c, d] y [false, true, false]
    
*/

void CrearArraysFactorial(bool* ArrayAntiguo, int TamanioArrayAntiguo, int i, int j,bool* NuevoArray) {

    int idx = 0;

    for (int k = 0; k < TamanioArrayAntiguo; k++) {
        if (k != i && k != j) {  
            NuevoArray[idx] = ArrayAntiguo[k];  
            idx++;
        }
    }
}

/*
VerificadorEvitarPermutaciones:
    obj:
        Cuando ejecutamos el codigo vamos a ir creando arrays nuevos por cada llamada recursiva. la funcion de VerificadorEvitarPermutaciones es evitar permutaciones innecesarias por ejemplo [a b c] y [b c a] ya que estas generan las mismas combinaciones de pares solo aumentan los pasos.
    Funcion:
        - Para no modificar el array original creamos una copia.
        - Ordenamos los elementos de la copia
        - Creamos un string que contenga todos los elementos ordenados.
            Ejem: key = "1,4,7,9,"
        - Retornamos la key esta nos servira mas adelante en el codigo.
*/


string VerificadorEvitarPermutaciones(int* Array, int tamanio) {
    int temp[tamanio];
    for (int i = 0; i< tamanio; i++){
        temp[i] = Array[i];
    }
    sort(temp, temp+tamanio);

    string key = "";
    for (int i = 0; i< tamanio; i++){
        key += to_string(temp[i]) + ",";
    }
    return key;
}