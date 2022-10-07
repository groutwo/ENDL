#ifndef E_S_ATER_H
#define E_S_ATER_H

#include <iostream>
//Ejercicio5.5

/* ENTRADA */
template <typename T>
Ater<T> leerAter(const T& fin)
{
    Ater<T> arbol;
    T ele;
    std::cout << "Introduce RAIZ: ";
    std::cin >> ele;
    if (ele != fin)
    {
        arbol.crearRaizT(ele);
        leerDescendientes(arbol.raizT(), arbol, fin);
    }
    return arbol;
}

template <typename T>
void leerDescendientes(typename Ater<T>::nodo n, Ater<T>& A, const T& fin)
{
    T ele;
    std::cout << "Elemento IZQ de " <<  A.elemento(n) << ": ";
    std::cin >> ele;
    if(ele != fin)
    {
        A.insertarHijoIzqdoT(n, ele);
        leerDescendientes(A.hijoIzqdoT(n), A, fin);
    }
    std::cout << "Elemento MED de " <<  A.elemento(n) << ": ";
    std::cin >> ele;
    if(ele != fin)
    {
        A.insertarHijoMedioT(n, ele);
        leerDescendientes(A.hijoMedioT(n), A, fin);
    }

    std::cout << "Elemento DCH de " <<  A.elemento(n) << ": ";
    std::cin >> ele;
    if(ele != fin)
    {
        A.insertarHijoDrchoT(n, ele);
        leerDescendientes(A.hijoDrchoT(n), A, fin);
    }
}

/* SALIDA */
template <typename T>
void imprimirAter(const Ater<T>& A)
{
    if (!A.arbolVacioT())
    {
        std::cout << "\nRaiz del arbol: " << A.elemento(A.raizT()) << std::endl;
        imprimirDescendientes(A.raizT(), A);
    }
    else
        std::cout << "Arbol vacio\n";
}

template <typename T>
void imprimirDescendientes(typename Ater<T>::nodo r, const Ater<T>& A)
{
    if (A.hijoIzqdoT(r) != Ater<T>::NODO_NULO)
    {
        std::cout << "Hijo IZQ de " << A.elemento(r) << ": " << A.elemento(A.hijoIzqdoT(r)) << std::endl;
        imprimirDescendientes(A.hijoIzqdoT(r), A);
    }

    if (A.hijoMedioT(r) != Ater<T>::NODO_NULO)
    {
        std::cout << "Hijo MED de " << A.elemento(r) << ": " << A.elemento(A.hijoMedioT(r)) << std::endl;
        imprimirDescendientes(A.hijoMedioT(r), A);
    }

    if (A.hijoDrchoT(r) != Ater<T>::NODO_NULO)
    {
        std::cout << "Hijo DCH de " << A.elemento(r) << ": " << A.elemento(A.hijoDrchoT(r)) << std::endl;
        imprimirDescendientes(A.hijoDrchoT(r), A);
    }
}

#endif // E_S_ATER_H
