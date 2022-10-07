//Calcular nodos nostalgicos -> aquel que tiene mas nodos antecesores que predecesores
//mas pasado que futuro

#include <iostream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

template <typename T> int numDescendientes(const Abin<T>& arbol,typename Abin<T>::nodo n)
{
    if(arbol.elemento(n)==Abin<T>::NODO_NULO)
        return 0;
    else
        return 1 + numDescendientes(arbol,arbol.hijoIzqdoB(n)) + numDescendientes(arbol,arbol.hijoDrchoB(n));
}

template <typename T> float calculaNodosNostalgicoRec(const Abin<T>& arbol, typename Abin<T>::nodo n, int& numNodos)
{
    if(arbol.elemento(n)!= Abin<T>::NODO_NULO)
    {
        ++numNodos;
        if(numDescendientes(arbol,n) < profundidad(n))
            return 1 + esNostalgicoRec(arbol,arbol.hijoIzqdoB(n)) + esNostalgicoRec(arbol,arbol.hijoDrchoB(n));
    }
    else
        return 0;
}

template <typename T> int calculaNodosNostalgico(const Abin<T>& arbol)
{
    float numNodos=0;
    float ratio_ = calculaNodosNostalgicoRec(arbol,arbol.raizB(),numNodos)/numNodos;
    return ratio_;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<char> arbol;
    rellenarAbin(arbol, '#');

    std::cout<<"La altura del árbol en cuestion es de "<<altura<<std::endl;

    system("pause");
    return 0;
}
