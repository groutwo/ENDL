//El grado de un arbol viene dado por el grado maximo de sus hijos o del mismo
#include "04 agen.hpp"
#include "04 agen_E-S.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T> int numeroDeHijos(typename Agen<T>::nodo n, Agen<T> A)
{
    int numHijos;
    typename Agen<T>::nodo hijo;

    if( n == Agen<T>::NODO_NULO )
        return 0;
    else
    {
        numHijos=0;
        hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            cout<<"numHijos:"<<numHijos<<endl;
            numHijos++;
            hijo = A.hermDrcho(hijo);
        }
    }
    return numHijos;
}

template<typename T> int calculaGradoRec(typename Agen<T>::nodo n, Agen<T> A)
{
    int maximo;
    typename Agen<T>::nodo hijo;

    if(n==Agen<T>::NODO_NULO)
        return 0;
    else
    {
        maximo = numeroDeHijos(n, A);
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            maximo = max(maximo,calculaGradoRec(n,A));
            hijo = A.hermDrcho(hijo);
        }
        return maximo;
    }
}

template<typename T> int calculaGrado(Agen<T> A)
{
    return calculaGradoRec(A.raiz(),A);
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Agen<char> A;
    rellenarAgen(A, 'z');

    int grado  = calculaGrado(A);
    cout<<"El grado del arbol es: "<<grado<<endl;
    return 0;
}
