//Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol,
// determine la profundidad de éste nodo en el árbol
#include "04 agen.hpp"
#include "04 agen_E-S.hpp"
#include <iostream>
template <typename T> int profundidad(typename Agen<T>::nodo n,const Agen<T>& A)
{
    int prof = -1;
    while(n!= Agen<T>::NODO_NULO)
        n = A.padre(n), prof++;
    return prof;
}

template <typename T> typename Agen<T>::nodo buscaNodo(typename Agen<T>::nodo n, const Agen<T>& A, T elementoABuscar)
{
    typename Agen<T>::nodo nodoADevolver = Agen<T>::NODO_NULO;
    typename Agen<T>::nodo hijo;

    if(n==Agen<T>::NODO_NULO || A.elemento(n) == elementoABuscar)
        return n;
    else
    {
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO && nodoADevolver == Agen<T>::NODO_NULO)
        {
            if(A.elemento(hijo) == elementoABuscar)
                nodoADevolver = hijo;
            else
            {
                typename Agen<T>::nodo nuevo = buscaNodo(hijo,A,elementoABuscar);
                if(nuevo != Agen<T>::NODO_NULO && A.elemento(nuevo) == elementoABuscar)
                    nodoADevolver = nuevo;
            }
            hijo = A.hermDrcho(hijo);
        }
    }
        return nodoADevolver;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Agen<char> A;
    rellenarAgen(A, 'z');

    char elementoABuscar;
    std::cout<<"Introduce el elemento del nodo que se quiere buscar: ";
    std::cin>>elementoABuscar;

    Agen<char>::nodo nodoABuscar = buscaNodo<char>(A.raiz(),A, elementoABuscar);

    int profundidad_ = profundidad(nodoABuscar,A);
    if(profundidad_==-1)
        std::cout<<"\nNo se ha encontrado el nodo"<<std::endl;
    std::cout<<"\nLa profundidad del nodo es de "<<profundidad_<<std::endl;
    system("pause");
    return 0;
}
