/*2. Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando
los subárboles izquierdo y derecho en cada nodo. Implementa un subprograma que devuelva
el árbol binario reflejado de uno dado.*/

#include "01 abin.hpp"
#include <iostream>
#include "0 abin_E-S.hpp"

template <typename T> Abin<T> reflejado(const Abin<T>& A)
{
    Abin<char> A2;

    if(A.raizB() != A.NODO_NULO)
    {
        A2.insertarRaizB(A.elemento(A.raizB()));
        reflejadoRec(A.raizB(), A, A2.raizB(), A2);
    }
    return A2;
}

template <typename T> void reflejadoRec(typename Abin<T>::nodo n1,const  Abin<T>&A1,
										   typename Abin<T>::nodo n2,       Abin<T>& A2)
{
    if(A1.hijoIzqdoB(n1) != Abin<T>::NODO_NULO)
    {
        A2.insertarHijoDrchoB(n2,A1.elemento(A1.hijoIzqdoB(n1)));
        reflejadoRec(A1.hijoIzqdoB(n1), A1, A2.hijoDrchoB(n2), A2);
    }
    if(A1.hijoDrchoB(n1) != Abin<T>::NODO_NULO)
    {
        A2.insertarHijoIzqdoB(n2,A1.elemento(A1.hijoDrchoB(n1)));
        reflejadoRec(A1.hijoDrchoB(n1), A1, A2.hijoDrchoB(n2), A2);
    }
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<char> arbol;
    rellenarAbin(arbol, 'q');

    arbol = reflejado(arbol);

    cout<<"El árbol resultante es: "<<endl;
    imprimirAbin(arbol);

    return 0;

}
