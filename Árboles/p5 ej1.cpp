/*Dado un árbol binario de enteros donde el valor de cada nodo es menor que el de sus
hijos, implementa un subprograma para eliminar un valor del mismo preservando la propiedad
de orden establecida. Explica razonadamente la elección de la estructura de datos.
Nota: Se supone que en el árbol no hay elementos repetidos, y que el número de
nodos del mismo no está acotado*/
//Es como nuestro apo, pero el nº de nodos no está acotado, es decir, no tiene por qué ser
// un arbol completo. La idea es sustituir el elemento a borrar por el siguiente(el inmediatamente
// mayor) de sus sucesores, e ir recontruyendo el (sub)árbol con el resto de elementos
/*
3 9 15 17 0 0 19 0 0 24 0 25 0 0 6 16 31 0 0 0 21 43 0 0 27 0 0 9
*/
#include<iostream>
#include "0 abin_E-S.hpp"
#include "01 abin.hpp"
using namespace std;

template <typename T> bool soloHijoIzqBin(typename Abin<T>::nodo n, Abin<T>& A)
{   return (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO); }
template <typename T> bool soloHijoDchBin(typename Abin<T>::nodo n, Abin<T>& A)
{   return (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO); }
template <typename T> bool esHojaBin(typename Abin<T>::nodo n, Abin<T>& A)
{   return (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO); }

void eliminarNodoAbinRec(int x, typename Abin<int>::nodo n, Abin<int>& A)
{
    if(n != Abin<int>::NODO_NULO)
    {
        if(A.elemento(n) == x)
        { //encuentra el elemento
            if(esHojaBin(n, A))
            { //es un nodo hoja, puede pasar 3 cosas
                if(n == A.raizB())                      //1. El nodo encontrado es la raiz del arbol
                    A.eliminarRaizB();                          //elimino la raiz del arbol y listo.
                else if(n == A.hijoIzqdoB(A.padreB(n))) //2. Es hijo izquierdo de su padre, entonces,..
                    A.eliminarHijoIzqdoB(A.padreB(n));          //elimino al hijo izq del padre de n, es decir, a él
                else                                    //3. Es hijo derecho de su padre, por tanto,..
                    A.eliminarHijoDrchoB(A.padreB(n));          //elimino al hijo drc del padre de n, es decir, a él.
            }
            else if(soloHijoIzqBin(n, A))
            {
                A.elemento(n) = A.elemento(A.hijoIzqdoB(n));    //intercambio hijo izq. por el elemento
                A.elemento(A.hijoIzqdoB(n)) = x;                //bajo el elemento x a si hijo izq.
                eliminarNodoAbinRec(x, A.hijoIzqdoB(n), A);     //Llamada recursiva con el izq.
            }
            else if(soloHijoDchBin(n, A))
            {
                A.elemento(n) = A.elemento(A.hijoDrchoB(n));    //intercambio hijo dcho. por el elemento
                A.elemento(A.hijoDrchoB(n)) = x;                //bajo elemento x a su hijo dcho.
                eliminarNodoAbinRec(x, A.hijoDrchoB(n), A);     //Llamada recursiva con el dch
            }
            else
            { //tiene 2 hijos. tengo que intercambiarlo por el menor de los 2
                if(A.elemento(A.hijoIzqdoB(n)) < A.elemento(A.hijoDrchoB(n))) //el izq. es el menor, hago lo mismo que cd solo tenia hijo izq.
                {
                    A.elemento(n) = A.elemento(A.hijoIzqdoB(n));    //intercambio hijo izq. por el elemento
                    A.elemento(A.hijoIzqdoB(n)) = x;                //bajo el elemento x a si hijo izq.
                    eliminarNodoAbinRec(x, A.hijoIzqdoB(n), A);     //Llamada recursiva con el izq.
                }
                else //el dcho. es el menor, hago lo mismo que cd solo tenia hijo dcho.
                {
                    A.elemento(n) = A.elemento(A.hijoDrchoB(n));    //intercambio hijo dcho. por el elemento
                    A.elemento(A.hijoDrchoB(n)) = x;                //bajo elemento x a su hijo dcho.
                    eliminarNodoAbinRec(x, A.hijoDrchoB(n), A);     //Llamada recursiva con el dch
                }
            }
        }
        else if(A.elemento(n) < x)
        { //como no lo he encontrado y el elemento del nodo actual es aun menor que el que busco, sigo buscando,...
            eliminarNodoAbinRec(x, A.hijoIzqdoB(n), A);
            eliminarNodoAbinRec(x, A.hijoDrchoB(n), A);
        } //ni el elemento de n es igual a x ni tampoco es menor, luego ya no puede estar por aqui.
    }
}

void eliminarNodoAbin(int x, Abin<int>& A){ eliminarNodoAbinRec(x, A.raizB(), A); }

int main()
{
    Abin<int> A;
    int elemento;
    rellenarAbin(A, 0);
    cout<<"Que elemento quieres borrar? "<<endl;
    cin>>elemento;
    eliminarNodoAbin(elemento,A);
    cout<<"El arbol queda de la siguiente forma:"<<endl;
    imprimirAbin(A);
    return 0;
}
