///Implementación recursiva de recorridos en profundidad de árboles binarios
template <typename T>void preordenAbin (typename Abin<T>::nodo n, const Abin<T>& A,
                   void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
// Recorrido en preorden del subárbol cuya raíz es el nodo n perteneciente al árbol binario A.
// Cada nodo visitado se procesa mediante la función procesar().
{if (n != Abin<T>::NODO_NULO)
    {   procesar(n, A);
        preordenAbin(A.hijoIzqdoB(n), A, procesar);
        preordenAbin(A.hijoDrchoB(n), A, procesar);
    }
}

/**############################################################################*/

template <typename T>void inordenAbin (typename Abin<T>::nodo n, const Abin<T>& A,
                  void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
// Recorrido en inorden del subárbol cuya raíz es el nodo n perteneciente al árbol binario A.
// Cada nodo visitado se procesa mediante la función procesar().
{if (n != Abin<T>::NODO_NULO)
    {   inordenAbin(A.hijoIzqdoB(n), A, procesar);
        procesar(n, A);
        inordenAbin(A.hijoDrchoB(n), A, procesar);
    }
}

/**############################################################################*/

template <typename T>void postordenAbin (typename Abin<T>::nodo n, const Abin<T>& A,
                    void (*procesar)(typename Abin<T>::nodo, const Abin<T>&))
// Recorrido en postorden del subárbol cuya raíz es el nodo n perteneciente al árbol binario A.
// Cada nodo visitado se procesa mediante la función procesar().
{if (n != Abin<T>::NODO_NULO)
    {   postordenAbin(A.hijoIzqdoB(n), A, procesar);
        postordenAbin(A.hijoDrchoB(n), A, procesar);
        procesar(n, A);
    }
}
template <typename T> void escribirNodo (typename Abin<T>::nodo n, const Abin<T>& A)
{    if (n != Abin<T>::NODO_NULO)
        std::cout << A.elemento(n) << ' ';
}
