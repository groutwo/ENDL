///Implementación iterativa del recorrido en preorden de árboles binarios
#include "0pilaenla.hpp"
///Implementación iterativa del recorrido en preorden de árboles binarios
template <typename T> void preordenAbin2 (typename Abin<T>::nodo n, const Abin<T>& A,
                    void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
{
    // Algoritmo básico
    Pila<typename Abin<T>::nodo> P; // pila de nodos de un árbol binario
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
// Recorrido en preorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol binario A. Cada nodo visitado se procesa
// mediante la función procesar().
{
    // Algoritmo mejorado
    Pila<typename Abin<T>::nodo> P; // pila de nodos de árbol binario
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
