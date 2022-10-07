/*5. Repite el ejercicio anterior para la representación enlazada de árboles
binarios (punteros al padre, hijo izquierdo e hijo derecho).*/

#include <iostream>
#include "01 abin.hpp"

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
    if(A.nodos[n].hizq == A.NODO_NULO && A.nodos[n].hder == A.NODO_NULO)
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
    preordenAbin(raizB(), *this, calculaAltura);
    return altura;
}

int main()
{
    return 0;
}
