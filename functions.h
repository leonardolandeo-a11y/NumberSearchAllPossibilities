#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
using namespace std;

extern string Resultados[101];
extern string* Procesados;
extern int ElementosProcesados;
extern int* NResultadosNOPosibles;
extern int NElementosNoposibles;
extern string* Combinaciones;
bool LinearSearch(string obj);
bool Operaciones(int a, int b, char op, int &res);
bool Factorial(int x, int &res);

int CrearArrays(int* oldVals, string* oldExpr, int size, int i, int j,int* newVals, string* newExpr);
void CrearArraysFactorial(bool* oldVals, int size, int i, int j,bool* newVals);

string VerificadorEvitarPermutaciones(int* vals, int size);
void explore(int* vals, string* expresion, int size, bool* facto);


#endif