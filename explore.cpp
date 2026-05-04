#include "functions.h"


void explore(int* ArrayValores, string* ArrayExpresion, int Tamanio, bool* facto) {
    
    /*
    key:
        - viene de VerificadorEvitarPermutaciones
        - Guarda una combinacion unica de los elementos ordenados

    if (LinearSearch(key)):
        - Buscamos dentro de la lista Procesados si la key ya existe.
        - Si la key ya existe entonces destruimos la rama entera de la lista permutada.
        - Si la key no existe continuamos con el proceso de la rama
    
    Procesados[ElementosProcesados] = key:
        - Guardamos en Procesados la key unica. ( De esta manera recordaremos que esta combinacion ya esta hecha )

    ElementosProcesados += 1:
        - Indicamos que hemos ingresado una key mas.
    */
    string key = VerificadorEvitarPermutaciones(ArrayValores, Tamanio);
    if (LinearSearch(key)){
        return;
    }
    Procesados[ElementosProcesados] = key;
    ElementosProcesados += 1;

    
    /*
    Caso Base:
        - Cuando el tamaño del array es 1. (Solo hay un elemento)
        - Verificamos que el elemento este en el rango esperado
        Resultados[v] == "":
            - Nos permite ingresar solo una combinacion de el numero esperado.
    */
    if (Tamanio == 1) {
        int v = ArrayValores[0];

        if (v >= 1 && v <= 100 && Resultados[v] == "") {   
            Resultados[v] = ArrayExpresion[0];
        }
        return;
    }

    
    /*
    Combinamos los numeros dentro de la lista en pares
        - Nunca son iguales. (i != j)
        - i y j son indices de donde esta realmente el elemento
    */
    for (int i = 0; i < Tamanio; i++) {
        for (int j = i + 1; j < Tamanio; j++) {

            /*
            NuevoArrayValores -> Guardaremos la nueva combinacion de elementos ejem: [j, c, d].
            NuevaExpresion -> Guardaremos la nueva expresion de los elementos ejem: [(a+b), c, d]
            NuevoVerificacionFactorial -> Guardaremos la nueva posicion de los elementos a los cuales hemos aplicado factorial ejem: [false,false,false]
            
            --- Cada uno tiene su propio puntero ---
            */
            int NuevoArrayValores[10];
            string NuevaExpresion[10];
            bool NuevoVerificacionFactorial[10];

            bool* ptrNuevoVerificacionFactorial = NuevoVerificacionFactorial;
            int* ptrNuevoArrayValores = NuevoArrayValores;
            string* ptrNuevaExpresion = NuevaExpresion;

            /*
            NuevoTamanio -> La funcion se encarga de crear los nuevos arrays y retornamos el nuevo tamaño de este nuevo array.
            CrearArraysFactorial(facto,Tamanio, i,j,ptrNuevoVerificacionFactorial); -> Modificamos los indices de los elementos a los cuales hemos aplicado factorial
            */
            int NuevoTamanio = CrearArrays(ArrayValores, ArrayExpresion, Tamanio, i, j, ptrNuevoArrayValores, ptrNuevaExpresion);
            CrearArraysFactorial(facto,Tamanio, i,j,ptrNuevoVerificacionFactorial);
            /*
            OperacionesArray -> Operaciones posibles con pares de elementos.
            for -> Por cada par de elementos (a,b) evaluamos cada operacion posible de estos 2.
                ejem:
                    a+b, a-b ,a*b, a/b, a%b, a**b
            */
            char OperacionesArray[6] = {'+','-','*','/','%','^'};

            for (int k = 0; k < 6; k++) {
                
                int resultado;

                /*
                Condicionales -> Verificamos que la operacion sea posible. ( Evitamos a/0 )
                Condicionales: 
                    NuevoArrayValores[NuevoTamanio] = resultado; -> Guardamos el nuevo elemento obtenido por la combinacion.
                    NuevoVerificacionFactorial[NuevoTamanio] -> Indicamos que no hemos realizado una factorial
                    NuevaExpresion[NuevoTamanio] -> Guardamos la combinacion que hemos realizado para obtener el elemento.

                    explore(NuevoArrayValores, NuevaExpresion, NuevoTamanio + 1,NuevoVerificacionFactorial); :
                        - LLamada recursiva
                        - NuevoTamanio + 1 : Ya que eliminamos 2 elementos con la funcion CrearArrays, pero ganamos 1.
                */
                if (Operaciones(ArrayValores[i], ArrayValores[j], OperacionesArray[k], resultado)) {
                    NuevoArrayValores[NuevoTamanio] = resultado;
                    NuevoVerificacionFactorial[NuevoTamanio] = false;
                    NuevaExpresion[NuevoTamanio] = "(" + ArrayExpresion[i] + OperacionesArray[k] + ArrayExpresion[j] + ")"; 
                    explore(NuevoArrayValores, NuevaExpresion, NuevoTamanio + 1,NuevoVerificacionFactorial);  
                }

                if (Operaciones(ArrayValores[j], ArrayValores[i], OperacionesArray[k], resultado)) {
                    NuevoArrayValores[NuevoTamanio] = resultado;
                    NuevoVerificacionFactorial[NuevoTamanio] = false;
                    NuevaExpresion[NuevoTamanio] = "(" + ArrayExpresion[j] + OperacionesArray[k] + ArrayExpresion[i] + ")";
                    explore(NuevoArrayValores, NuevaExpresion, NuevoTamanio + 1,NuevoVerificacionFactorial);
                }
            }
        }
    }

    /*
    Factorial:
        - Buscamos evaluar el factorial de cada uno de los elementos en una nueva rama.
    */
    for (int i = 0; i < Tamanio; i++) {
        int resultado;
        
        /*
        Condicional:
            - Verificamos que el factorial sea posible y que sea controlado
            - resultado != ArrayValores[i] -> Evitamos factorial de 1 y 2
            -facto[i] == false -> Verificamos de que sea la primera vez que calcularemos su factorial
        */
        if (facto[i] == false && Factorial(ArrayValores[i], resultado) && resultado != ArrayValores[i] && resultado <= 1000) {
            /*
            Creamos una copia de cada uno de los arrays originales para no dañarlos
            */
            int NuevoArrayValoresFactorial[10];
            string NuevaExpresionFactorial[10];
            bool NuevoVerificacionFactorial[10];
            for (int k = 0; k < Tamanio; k++) {
                NuevoArrayValoresFactorial[k] = ArrayValores[k];
                NuevaExpresionFactorial[k] = ArrayExpresion[k];
                NuevoVerificacionFactorial[k] = facto[k];
            }

            /*
            NuevoArrayValoresFactorial[i] = resultado;  -> Remplazamos el elemento por su factorial
            NuevaExpresionFactorial[i] = "(" + ArrayExpresion[i] + "!)"; -> Guardamos el elemento
            NuevoVerificacionFactorial[i] = true; -> Indicamos de que hemos calculado el factorial del elemento
            Aplicamos la llamada recursiva para seguir explorando posibilidades.
            */
            NuevoArrayValoresFactorial[i] = resultado;   
            NuevaExpresionFactorial[i] = "(" + ArrayExpresion[i] + "!)";
            NuevoVerificacionFactorial[i] = true;
            explore(NuevoArrayValoresFactorial, NuevaExpresionFactorial, Tamanio,NuevoVerificacionFactorial);
        }
    }
}
