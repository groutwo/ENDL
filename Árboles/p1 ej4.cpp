/*4. Añade dos nuevas operaciones al TAD árbol binario, una que calcule la
profundidad de un nodo y otra que calcule la altura de un nodo en un árbol
dado. Implementa esta operación para la representación vectorial.*/

#include <iostream>
#include "01 abinVec.hpp"

template <typename T>int Abin<T>::profundidad(Abin::nodo n)
{
    assert(n >= 0 && n < numNodos); // nodo válido
    int profundidad = 0 ;
    while (n != NODO_NULO)
        ++profundidad, n = nodos[n].padre;
    return profundidad;
}

template <class T> void calculaAltura(typename Abin<T>::nodo n, Abin<T>& A)
{
    if(A.nodos[n].hizq > numNodos && A.nodos[n].hder > numNodos)
    {
        //Si no es nodo hoja, su hijo será más profundo
        int alturaTemporal = 0;
        while(n!= A.NODO_NULO)
            n = A.nodos[n].padre, alturaTemporal++;
        if(alturaTemporal>altura) altura = alturaTemporal;
    }
}

template <typename T> int Abin<T>::altura(Abin::nodo n)
{
    assert(n >= 0 && n < numNodos); // nodo válido
    int altura = calculaAltura(n,0);
    return altura;
}

int main()
{
    return 0;
}
