/*3. Implementa un subprograma que, dados un árbol binario y un nodo del mismo,
    determine la profundidad de este nodo en dicho árbol.*/
#include <iostream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

template <typename T> int calculaProfundidad(typename Abin<T>::nodo n,const Abin<T>& A)
{
    int altura = 0;
    while(n!= Abin<T>::NODO_NULO)
        n = A.padreB(n), altura++;
    return altura;
}

template <typename T> typename Abin<T>::nodo buscaNodo(typename Abin<T>::nodo n, const Abin<T>& arbol, T elementoABuscar)
{
    if(n!= Abin<T>::NODO_NULO)
    {
        if( arbol.elemento(n) == elementoABuscar)
            return n;
        buscaNodo(arbol.hijoIzqdoB(arbol.raizB()),arbol, elementoABuscar);
        buscaNodo(arbol.hijoDrchoB(arbol.raizB()),arbol,elementoABuscar);
    }
    //return Abin<T>::NODO_NULO;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<char> arbol;
    rellenarAbin(arbol, 'q');

    char elementoABuscar;
    cout<<"Introduce el elemento del nodo que se quiere buscar ";
    cin>>elementoABuscar;

    Abin<char>::nodo nodoABuscar = buscaNodo<char>(arbol.raizB(),arbol, elementoABuscar);

    int profundidad = calculaProfundidad(nodoABuscar,arbol);
    std::cout<<"La profundidad del nodo es de "<<profundidad<<std::endl;
    system("pause");
    return 0;
}
