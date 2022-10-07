/*Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden
del árbol para obtener el listado ordenado de sus elementos y luego, repartir
equitativamente los elementos a izquierda y derecha colocando la mediana en la raíz
y construyendo recursivamente los subárboles izquierdo y derecho de cada nodo.
Implementa este algoritmo para equilibrar un ABB.*/
///Nota: el recorrido en inorden es: (hijoIzq) + raiz + inorden(hijoDch)

#include<iostream>
#include "06 ABB.hpp"
#include "0 abin_E-S.hpp"
#include <vector>
#include "list"
using namespace std;

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

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abb<int> ABB;
    int elemento;
    do
    {   cout<<"Introduce elemento(-1) para terminar: "; cin>>elemento;
        if(elemento!=-1)    ABB.insertar(elemento);
    }while(elemento!=-1);

    Abin<int> ABIN {ABB};
    cout<<"Mostrando el Abin que corresponde al ABB introducido: "<<endl;
    imprimirAbin(ABIN);

    equilibrarAbb(ABB);

    cout<<"Mostrando el ABB final(ordenado): "<<endl;
    Abin<int> ABB_ORDENADO {ABB};

    imprimirAbin(ABB_ORDENADO);
}
