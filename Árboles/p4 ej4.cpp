/*Dados dos conjuntos representados mediante árboles binarios de búsqueda,
implementa la operación unión de dos conjuntos que devuelva como resultado otro
conjunto que sea la unión de ambos, representado por un ABB equilibrado */

#include<iostream>
#include "06 ABB.hpp"
#include "0 abin_E-S.hpp"
#include <vector>
#include "list"
using namespace std;
template <typename T> using conjunto =  Abb<T>;

template <typename T> void equilibrarAbbRec(Abb<T>& A,list<T> lista,
        typename std::list<T>::iterator ini, typename std::list<T>::iterator fin)
{
    if(ini==fin) return; //Si la lista está vacia, no hacemos nada

    int numElementos = 0;
    typename std::list<T>::iterator ite = ini;
    while(ite != fin)
        ++numElementos, ++ite;
    ///     cout<<"La lista en cuestion tiene "<<numElementos<<" elementos\n";
    ite = ini;
    for(int i = 0; i<numElementos/2; ite++,i++);

    ///     cout<<"insertamos un "<<*ite<<" ya que es el elemento intermedio; la mediana";
    A.insertar(*ite);
    //Hasta aqui hemos insertado la mediana


    ///     cout<<"ini: "<<*ini<<" ite: "<<*ite;
    equilibrarAbbRec(A,lista,ini,ite);


    ++ite;  //Sin esto siempre insertariamos el inicio de la lista
            //ya que tendriamos un elemento, y 1/2=0.5 -> 0
    ///     cout<<"ite: "<<*ite<<" fin: "<<*fin;
    equilibrarAbbRec(A,lista,ite,fin);
}

template <typename T> void equilibrarAbb(Abb<T>& A)
{
    list<T> lista;
    Abb<T> B;
    guardaEnLista(A, lista);

    equilibrarAbbRec(B, lista, lista.begin(), lista.end());

    A = B;
}

template <typename T> void guardaEnLista(const Abb<T>& A,std::list<T>& lista)
{
    if(!A.izqdo().vacio())  guardaEnLista(A.izqdo(),lista);
    lista.push_back(A.elemento());
    if(!A.drcho().vacio())  guardaEnLista(A.drcho(),lista);
}

template <typename T> conjunto<T> unionConjuntos(conjunto<T>& A, conjunto<T>& B)
{
    conjunto<T> C{A};
    list<T> elementosDeB;
    guardaEnLista(B, elementosDeB);

    typename std::list<T>::iterator it = elementosDeB.begin();

    while(it!=elementosDeB.end())
        C.insertar(*it),++it;
    //Aqui tenemos en el nuevo conjunto(C) los elementos de ambos conjuntos,
    //pero no está equilbrado, por lo que :
    equilibrarAbb(C);
    return C;
}

template <typename T> void inicializaArboles(Abb<T>& A, Abb<T>& B)
{   int aux;
    do
    {   cout<<"Introduce un elemento para el abb A: ";  cin>> aux;
        if(aux != -1)       A.insertar(aux);
    }
    while(aux != -1);
    do
    {   cout<<"Introduce un elemento para el abb B: ";  cin>> aux;
        if(aux != -1)       B.insertar(aux);
    }
    while(aux != -1);
}

int main()
{
    Abb<int> A, B, C;
    inicializaArboles(A,B);
    C = unionConjuntos(A,B);

    Abin<int> Abin{C};

    cout<<"Solucion:"<<endl;
    imprimirAbin(Abin);
}
