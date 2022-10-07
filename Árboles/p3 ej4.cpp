/*Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice
la poda de A a partir de x. Se asume que no hay elementos repetidos en A.*/
#include "04 agen.hpp"
#include "04 agen_E-S.hpp"
#include <iostream>
//Nota: buscaNodo devuelve NODO_NULO si no encuentra algun nodo cuyo elemento corresponda al elementoABuscar
template <typename T> typename Agen<T>::nodo buscaNodo(typename Agen<T>::nodo n, T elementoABuscar, const Agen<T>& Arbol)
{
    typename Agen<T>::nodo nodoADevolver;
    typename Agen<T>::nodo hijo;

    if(n==Agen<T>::NODO_NULO || Arbol.elemento(n) == elementoABuscar)
        return n;
    else
    {
        hijo = Arbol.hijoIzqdo(n);
        nodoADevolver = Agen<T>::NODO_NULO;

        while (hijo != Agen<T>::NODO_NULO && nodoADevolver == Agen<T>::NODO_NULO)
        {
            if(Arbol.elemento(hijo) == elementoABuscar)
                nodoADevolver = hijo;
            else
            {
                typename Agen<T>::nodo nuevo = buscaNodo(hijo,elementoABuscar,Arbol);
                if(nuevo != Agen<T>::NODO_NULO && Arbol.elemento(nuevo) == elementoABuscar)
                    nodoADevolver = nuevo;
            }
            hijo = Arbol.hermDrcho(hijo);
        }
    }
        return nodoADevolver;
}

// podaElemento y podaNodo(que es el recursivo)
template <typename T> void podaNodo(typename Agen<T>::nodo n, Agen<T>& A)
{
    cout<<"Estamos en podaNodo con " <<A.elemento(n)<<endl;
    if(n == Agen<T>::NODO_NULO)
        cout<<"n == Agen<T>::NODO_NULO"<<endl;
    else
    {
        while(A.hijoIzqdo(n) != Agen<T>::NODO_NULO)
            podaNodo(A.hijoIzqdo(n),A);
        cout<<"En este caso, tenemos que "<<A.elemento(n)<< " no tiene hijo izquierdo"<<endl;
        typename Agen<T>::nodo hijo;
        hijo = A.hijoIzqdo(A.padre(n));
        if (hijo == n)
            A.eliminarHijoIzqdo(A.padre(n));
        else
        {
            while(A.hermDrcho(hijo)!=n)
                hijo = A.hermDrcho(hijo);
            A.eliminarHermDrcho(hijo);
        }
    }
}

template <typename T> void podaElemento(T elementoABuscar, Agen<T>& A)
{
    typename Agen<T>::nodo n;

    n = buscaNodo(A.raiz(), elementoABuscar, A );

    podaNodo(n,A);
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Agen<char> Arbol;
    rellenarAgen(Arbol, 'z');

    char elementoABuscar;
    std::cout<<"\n\nIntroduce el elemento del nodo a partir del cual se quiere hacer la poda: ";
    std::cin>>elementoABuscar;

    podaElemento(elementoABuscar,Arbol);
    std::cout<<"El arbol ha sido podado, resultado:"<<std::endl;
    imprimirAgen(Arbol);
    system("pause");
    return 0;
}
