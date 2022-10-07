template <typename T>
void preordenAgen(typename Agen<T>::nodo n, const Agen<T>& A,
                  void (*procesar)(typename Agen<T>::nodo, const Agen<T>&))
// Recorrido en preorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante
// la función procesar()
{
    if (n != Agen<T>::NODO_NULO)
    {
        procesar(n, A);
        n = A.hijoIzqdo(n);
        while (n != Agen<T>::NODO_NULO)
        {
            preordenAgen(n, A, procesar);
            n = A.hermDrcho(n);
        }
    }
}

template <typename T>
void inordenAgen(typename Agen<T>::nodo n, const Agen<T>& A,
                 void (*procesar)(typename Agen<T>::nodo, const Agen<T>&))
// Recorrido en inorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante
// la función procesar()
{
    if (n != Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        if (hijo != Agen<T>::NODO_NULO)
        {
            inordenAgen(hijo, A, procesar);
            procesar(n, A);
            while ((hijo = A.hermDrcho(hijo)) != Agen<T>::NODO_NULO)
                inordenAgen(hijo, A, procesar);
        }
        else
            procesar(n, A);
    }
}

template <typename T>
void postordenAgen(typename Agen<T>::nodo n, const Agen<T>& A,
                   void (*procesar)(typename Agen<T>::nodo, const Agen<T>&))
// Recorrido en postorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante
// la función procesar()
{
    if (n != Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            postordenAgen(hijo, A, procesar);
            hijo = A.hermDrcho(hijo);
        }
        procesar(n, A);
    }
}
template <typename T>
void escribirNodo (typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n != Agen<T>::NODO_NULO)
        std::cout << A.elemento(n) << ' ';
}
