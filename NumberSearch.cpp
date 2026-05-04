/*

BUSQUEDA DE NUMEROS DEL 1 AL 100 USANDO UN METODO RECURSIVO

OBJETIVO:
Encontrar todos los numeros del 1 al 100 utilizando unicamente 4 numeros dados como entrada,
donde cada numero pertenece al rango [1 - 9].

------------------------------------------------------------
SOLUCION RECURSIVA:

La solucion se basa en recursividad, donde en cada paso reducimos el problema combinando elementos hasta llegar a una sola solucion.

------------------------------------------------------------
PROCESO:

1. Entrada inicial:
    Se recibe un arreglo de 4 numeros:
    [a, b, c, d], donde cada elemento pertenece a el rango [1-9].

2. Seleccion de pares:
    En cada nivel de la recursion, seleccionamos dos elementos del conjunto actual.
    Ejemplo:
    (a, b)

3. Operaciones posibles:
    Con cada par (a, b) podemos aplicar 6 operaciones basicas:
    - a + b
    - a - b
    - b - a
    - a * b
    - a / b (si b != 0)
    - b / a (si a != 0)

    Cada operacion genera un nuevo valor h.

4. Reduccion del problema:
    Cuando tenemos h, creamos un nuevo array reemplazando a y b por h:

    [a, b, c, d]
        ↓
    elegimos (a, b)
        ↓
    obtenemos h = operacion(a, b)
        ↓
    nuevo estado: [h, c, d]

5. Recursividad:
    El proceso se va a repetir con el nuevo array hasta llegar a un solo numero.

------------------------------------------------------------
CASO BASE:

Cuando el array llega a tener un solo elemento, entonces:
    - Utilizaremos ese numero como respuesta.
    - Verificamos si el numero pertenece [1-100].

------------------------------------------------------------

*/

#include <iostream>
#include <string>
#include <algorithm>
#include "functions.h"
#include <fstream>
using namespace std;


int main() {
    ofstream out("resultados.txt");
    /*
    Nums -> Guardaremos los 4 numeros que llegan por entrada.
    Expresion -> Guardaremos la forma con la que llegamos a un nuevo numero por ejemplo (a * b)
    VerificacionFactorial -> Nos permite evitar factoriales dobles.

    --- Para cada uno creamos punteros ---
    */
    for(int k = 1;k<10;k++){
        for (int l = 1; l <10;l++){
                for (int g = 1 ;g < 10;g++){
                    for (int r = 1; r <10; r++){
                        if (k != l && k != g && k != r &&l != g && l != r && g != r){
                            out<<"\n";
                            out<<"Pareja: "<<to_string(k)<<"-"<<to_string(l)<<"-"<<to_string(g)<<"-"<<to_string(r);
                        
                            int Nums[4];
                            string Expresion[4];
                            bool VerificacionFactorial[4] = {false, false, false, false};
                            int* ptrNums = Nums;
                            string* ptrExpresion = Expresion;
                            bool* ptrVerficacionFactorial = VerificacionFactorial;
                            
                            for (int i = 1; i <= 100; i++){
                                Resultados[i] = "";
                            }

                            
                            ptrNums[0] = k;
                            ptrNums[1] = l;
                            ptrNums[2] = g;
                            ptrNums[3] = r;
                            for(int i = 0; i<4;i++){
                                cout<<ptrNums[i]<<"-";
                            }
                            ptrExpresion[0] = to_string(ptrNums[0]);
                            ptrExpresion[1] = to_string(ptrNums[1]);
                            ptrExpresion[2] = to_string(ptrNums[2]);
                            ptrExpresion[3] = to_string(ptrNums[3]);
                            ElementosProcesados = 0;
                            explore(ptrNums, ptrExpresion, 4,ptrVerficacionFactorial);
                            int noposibles = 0;
                            out << "\nResultados:\n";
                            
                            for (int i = 1; i <= 100; i++) {
                                if (Resultados[i] != "")
                                    out << i << ": " << Resultados[i] << "\n";
                                else{
                                    out << i << ": No es posible\n";
                                    noposibles++;
                                }
                                    
                            }
                            NResultadosNOPosibles[NElementosNoposibles] = noposibles;
                            Combinaciones[NElementosNoposibles] = to_string(k)+"-"+to_string(l)+"-" +to_string(g)+"-" +to_string(r);
                            NElementosNoposibles++;
                            
                            }

                    }
                }
            }
        }
        out<<"\n\n\n";
        out<<"Resultados cantidad no posible por combinacion: ";
        out<<"\n\n\n";

        int maximo= 0;
        int indexmaximo = 0;
        for (int i = 0; i <NElementosNoposibles; i++){
            if (NResultadosNOPosibles[i] >= maximo){
                indexmaximo = i;
                maximo = NResultadosNOPosibles[i];
            }
            
            out<<Combinaciones[i]<<": "<<NResultadosNOPosibles[i];
            out<<"\n";
        }
        out<<"La peor combinacion es: "<<Combinaciones[indexmaximo]<<"\n";
        out<<"Errores: "<<NResultadosNOPosibles[indexmaximo]<<"\n";
        out.close();

        delete [] Procesados; 
        delete [] NResultadosNOPosibles;
        delete [] Combinaciones;

    return 0;
}
