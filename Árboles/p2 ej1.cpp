/*1. Dos �rboles binarios son similares cuando tienen id�ntica estructura de
ramificaci�n, es decir, ambos son vac�os, o en caso contrario, tienen sub�rboles
izquierdo y derecho similares. Implementa un subprograma que determine si dos
�rboles binarios son similares.*/

#include <iostream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

using namespace std;

template <typename T> bool similaresRec(const Abin<T>& a1, const Abin<T>& a2,typename Abin<T>::nodo n1,typename Abin<T>::nodo n2);
template <typename T> bool similares(const Abin<T>& a1, const Abin<T>& a2);

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<char> arbol1, arbol2;
    cout<<"�rbol 1:" <<endl;
    rellenarAbin(arbol1, 'q');
    cout<<"�rbol 2:" <<endl;
    rellenarAbin(arbol2, 'q');

    if(similares(arbol1, arbol2))
        cout<<"Son �rboles similares."<<endl;
    else
        cout<<"No son �rboles similares"<<endl;

    return 0;
}

template <typename T> bool similares(const Abin<T>& a1, const Abin<T>& a2)
{
    return similaresRec( a1,a2,a1.raizB(),a2.raizB() );
}

template <typename T> bool similaresRec(const Abin<T>& a1, const Abin<T>& a2,typename Abin<T>::nodo n1,typename Abin<T>::nodo n2)
{
    if      (n1 == a1.NODO_NULO && n2 == a2.NODO_NULO)
        return true;
    else if (n1 == a1.NODO_NULO || n2 == a2.NODO_NULO)
        return false;
    else
        return ( /* a1.elemento(n1) == a2.elemento(n2) // Con esto vemos si dos arboles son exactamente iguales    && */
                   similaresRec( a1,a2,a1.hijoIzqdoB(n1),a2.hijoIzqdoB(n2)) &&
                   similaresRec( a1,a2,a1.hijoDrchoB(n1),a2.hijoDrchoB(n2))
               );
}

