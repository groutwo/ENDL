/*Dado un árbol binario de enteros donde el valor de cada nodo es menor que el de sus
hijos, implementa un subprograma para eliminar un valor del mismo preservando la propiedad
de orden establecida. Explica razonadamente la elección de la estructura de datos.
Nota: Se supone que en el árbol no hay elementos repetidos, y que el número de
nodos del mismo no está acotado*/
//Es como nuestro apo, pero el nº de nodos no está acotado, es decir, no tiene por qué ser
// un arbol completo. La idea es sustituir el elemento a borrar por el siguiente(el inmediatamente
// mayor) de sus sucesores, e ir recontruyendo el (sub)árbol con el resto de elementos

#include<iostream>
#include <vector>
#include "0 abin_E-S.hpp"
#include "01 abin.hpp"
#include "07 Apo.hpp"
using namespace std;

template <typename T> void almacenaSucesores(Abin<T>& A, typename Abin<T>::nodo nodoAEliminar, typename std::vector<typename Abin<T>::nodo> &sucesores)
{
    if(nodoAEliminar != Abin<T>::NODO_NULO)
    {
        sucesores.push_back(nodoAEliminar);
        buscarNodo(A,A.hijoDrchoB(nodoAEliminar), A.elemento(nodoAEliminar));
        buscarNodo(A,A.hijoIzqdoB(nodoAEliminar), A.elemento(nodoAEliminar));
    }
}

template <typename T> void eliminarNodos(Abin<T>&A, typename Abin<T>::nodo nodoAEliminar)
{
    if(nodoAEliminar != Abin<T>::NODO_NULO)
    {
        eliminarNodos(A, A.hijoIzqdoB(nodoAEliminar));
        eliminarNodos(A, A.hijoDrchoB(nodoAEliminar));
        A.eliminarRaizB();
    }
}
template <typename T> void eliminamosLaRaiz(Abin<T>& A, typename Abin<T>::nodo nodoAEliminar)
{

}
template <typename T> void completarAbin(Abin<T>& A, typename Abin<T>::nodo nodoACompletar, Apo<T> apoQueOrdena)
{
    if(!apoQueOrdena.vacio()) A.insertarHijoIzqdoB(nodoACompletar,apoQueOrdena.cima()), apoQueOrdena.suprimir();
    if(!apoQueOrdena.vacio()) A.insertarHijoDrchoB(nodoACompletar,apoQueOrdena.cima()), apoQueOrdena.suprimir();

    if(!apoQueOrdena.vacio())
        completarAbin(A,A.hijoIzqdoB(nodoACompletar),apoQueOrdena),
        completarAbin(A,A.hijoDrchoB(nodoACompletar),apoQueOrdena);
}

template <typename T> void eliminarAbinOrdenado(Abin<T>& A, typename Abin<T>::nodo nodoAEliminar)
{
    typename std::vector<typename Abin<T>::nodo> sucesores;
    almacenaSucesores(A, nodoAEliminar, sucesores);
    Apo<int> apoQueOrdena(sucesores.size());

    while(!sucesores.empty())
    {
        apoQueOrdena.insertar(A.elemento(*sucesores.begin()));
        sucesores.erase(sucesores.begin());
    }

    if(A.elemento(A.raizB()) == A.elemento(nodoAEliminar))
    {
        A.~Abin();
        A.insertarRaizB(apoQueOrdena.cima());
        apoQueOrdena.suprimir();
        completarAbin(A,A.raizB(), apoQueOrdena);
    }
    else
    {
        bool estaALaIzq = (A.elemento(A.hijoIzqdoB(A.padreB(nodoAEliminar))) == A.elemento(nodoAEliminar));

        typename Abin<T>::nodo padreDelNodoAEliminar = A.padreB(nodoAEliminar);

        eliminarNodos(A,nodoAEliminar);

        if(estaALaIzq)
        {
            A.insertarHijoIzqdoB(padreDelNodoAEliminar, apoQueOrdena.cima());
            apoQueOrdena.suprimir();
            completarAbin(A,A.hijoIzqdoB(padreDelNodoAEliminar), apoQueOrdena);
        }

        else
        {
            A.insertarHijoDrchoB(padreDelNodoAEliminar, apoQueOrdena.cima());
            apoQueOrdena.suprimir();
            completarAbin(A,A.hijoDrchoB(padreDelNodoAEliminar), apoQueOrdena);
        }
    }
}

template <typename T> typename Abin<T>::nodo buscarNodo(Abin<T>& A, typename Abin<T>::nodo nodoActual, T elementoBuscado)
{
    if(nodoActual != Abin<T>::NODO_NULO)
    {
        if(A.elemento(nodoActual) == elementoBuscado)
            return nodoActual;
        buscarNodo(A, A.hijoIzqdoB(nodoActual), elementoBuscado);
        buscarNodo(A, A.hijoDrchoB(nodoActual), elementoBuscado);
    }
}

int main()
{
    Abin<int> A;
    int elemento;
    rellenarAbin(A, 0);
    cout<<"Que elemento quieres borrar? "<<endl;
    cin>>elemento;
    typename Abin<int>::nodo nodoABorrar = buscarNodo(A,A.raizB(), elemento);

    if(nodoABorrar != Abin<int>::NODO_NULO)     eliminarAbinOrdenado(A,nodoABorrar);
    else                                        cout<<"No se ha podido eliminar el nodo";

    cout<<"El arbol queda de la siguiente forma:"<<endl;
    imprimirAbin(A);
    return 0;
}
