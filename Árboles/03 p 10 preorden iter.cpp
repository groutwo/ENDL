///Implementaci�n iterativa del recorrido en preorden de �rboles binarios
#include "0pilaenla.hpp"
///Implementaci�n iterativa del recorrido en preorden de �rboles binarios
template <typename T> void preordenAbin2 (typename Abin<T>::nodo n, const Abin<T>& A,
                    void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
{
    // Algoritmo b�sico
    Pila<typename Abin<T>::nodo> P; // pila de nodos de un �rbol binario
    P.push(n);
    while (!P.vacia())
    {   n = P.tope(); P.pop();
        procesar(n, A);
        if (n != Abin<T>::NODO_NULO)
        {   P.push(A.hijoDrchoB(n)); P.push(A.hijoIzqdoB(n)); }
    }
}

template <typename T> void preordenAbin2 (typename Abin<T>::nodo n, const Abin<T>& A,
                    void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
// Recorrido en preorden del sub�rbol cuya ra�z es el nodo n
// perteneciente al �rbol binario A. Cada nodo visitado se procesa
// mediante la funci�n procesar().
{
    // Algoritmo mejorado
    Pila<typename Abin<T>::nodo> P; // pila de nodos de �rbol binario
    do
    {   if (n != Abin<T>::NODO_NULO)
        {   procesar(n, A);
            if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO) P.push(A.hijoDrchoB(n));
            n = A.hijoIzqdoB(n);
        }
        else if (!P.vacia())
        {   n = P.tope(); P.pop(); }
    }
    while (!(n == Abin<T>::NODO_NULO && P.vacia()));
}
