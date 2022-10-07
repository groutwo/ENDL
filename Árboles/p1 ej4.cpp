/*4. A�ade dos nuevas operaciones al TAD �rbol binario, una que calcule la
profundidad de un nodo y otra que calcule la altura de un nodo en un �rbol
dado. Implementa esta operaci�n para la representaci�n vectorial.*/

#include <iostream>
#include "01 abinVec.hpp"

template <typename T>int Abin<T>::profundidad(Abin::nodo n)
{
    assert(n >= 0 && n < numNodos); // nodo v�lido
    int profundidad = 0 ;
    while (n != NODO_NULO)
        ++profundidad, n = nodos[n].padre;
    return profundidad;
}

template <class T> void calculaAltura(typename Abin<T>::nodo n, Abin<T>& A)
{
    if(A.nodos[n].hizq > numNodos && A.nodos[n].hder > numNodos)
    {
        //Si no es nodo hoja, su hijo ser� m�s profundo
        int alturaTemporal = 0;
        while(n!= A.NODO_NULO)
            n = A.nodos[n].padre, alturaTemporal++;
        if(alturaTemporal>altura) altura = alturaTemporal;
    }
}

template <typename T> int Abin<T>::altura(Abin::nodo n)
{
    assert(n >= 0 && n < numNodos); // nodo v�lido
    int altura = calculaAltura(n,0);
    return altura;
}

int main()
{
    return 0;
}
