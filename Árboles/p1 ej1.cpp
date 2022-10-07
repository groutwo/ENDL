/*1. Implementa un subprograma que calcule el número de nodos de un árbol binario.*/
#include <iostream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

template <typename T> int calculaNumNodosRec(const Abin<T>& arbol, typename Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
        return 1 + calculaNumNodosRec(arbol, arbol.hijoIzqdoB(n)) + calculaNumNodosRec(arbol, arbol.hijoDrchoB(n));
    return 0;
}

template <typename T> int calculaNumNodos(const Abin<T>& arbol)
{
    int numero_de_nodos = calculaNumNodosRec(arbol,arbol.raizB());
    return numero_de_nodos;
}

int main()
{
    setlocale(LC_CTYPE, "spanish");
    Abin<char> arbol;
    rellenarAbin(arbol, 'q');
    int numNodos = calculaNumNodos(arbol);
    std::cout<<"El árbol en cuestion tiene "<<numNodos<< " nodos\n";

    system("pause");
    return 0;
}
