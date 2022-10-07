//Implementaci�n del recorrido en anchura o por niveles de �rboles binarios
#include "0colaenla.hpp"
template <typename T> void recNivelesAbin (typename Abin<T>::nodo n, const Abin<T>& A,
        void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
{   // Algoritmo b�sico
    Cola<typename Abin<T>::nodo> C; // cola de nodos de un �rbol binario
    C.push(n);
    while (!C.vacia())
    {   n = C.frente(); C.pop();
        procesar(n, A);
        if (n != Abin<T>::NODO_NULO)
        {   C.push(A.hijoIzqdoB(n)); C.push(A.hijoDrchoB(n)); }
    }
}
template <typename T> void recNivelesAbin (typename Abin<T>::nodo n, const Abin<T>& A,
                     void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
// Recorrido por niveles del sub�rbol cuya ra�z es el nodo n
// perteneciente al �rbol binario A. Cada nodo visitado se
// procesa mediante la funci�n procesar().
{   // Algoritmo mejorado
    Cola<typename Abin<T>::nodo> C; // cola de nodos de �rbol binario
    if (n != Abin<T>::NODO_NULO)
    {   do
        {   if (!C.vacia())
            { n = C.frente(); C.pop(); }
            procesar(n, A);
            if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO) C.push(A.hijoIzqdoB(n));
            if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO) C.push(A.hijoDrchoB(n));
        }
        while (!C.vacia());
    }
}
