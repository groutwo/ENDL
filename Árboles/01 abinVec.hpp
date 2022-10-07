#ifndef ABIN_VEC0_H
#define ABIN_VEC0_H
#include <cassert>
#include <cstring>
#include <algorithm>    // std::max

template <typename T> class Abin
{
public:
    typedef int nodo; // índice de la matriz entre 0 y maxNodos-1
    static const nodo NODO_NULO;
    explicit Abin(size_t maxNodos); // constructor
    void insertarRaizB(const T& e);
    void insertarHijoIzqdoB(nodo n, const T& e);
    void insertarHijoDrchoB(nodo n, const T& e);
    void eliminarHijoIzqdoB(nodo n);
    void eliminarHijoDrchoB(nodo n);
    void eliminarHijo(nodo n);
    void eliminarRaizB();
    ~Abin(); // destructor
    bool arbolVacioB() const;
    const T& elemento(nodo n) const; // acceso a elto, lectura
    T& elemento(nodo n); // acceso a elto, lectura/escritura
    nodo raizB() const;
    nodo padreB(nodo n) const;
    nodo hijoIzqdoB(nodo n) const;
    nodo hijoDrchoB(nodo n) const;
    Abin(const Abin<T>& a); // ctor. de copia
    Abin<T>& operator =(const Abin<T>& a); // asignación

    //ejercicio4:
    int profundidadB(nodo n);
    int alturaB(nodo n);
private:
    struct celda
    {   T elto;
        nodo padre, hizq, hder;
        celda(T elto_,nodo padre_=NODO_NULO, nodo hizq_=NODO_NULO, nodo hder_=NODO_NULO):
             elto(elto_),padre(padre_),hizq(hizq_),hder(hder_){numNodos++;}
    };
    celda *nodos; // vector de nodos
    int maxNodos; // tamaño del vector
    int numNodos; // número de nodos del árbol
};

//Inicio métodos del ejercicio 5
template <typename T>
inline int Abin<T>::alturaB(typename Abin<T>::nodo n ) const
{
    if(n >= 0 && n < numNodos )
        return 1 + std::max( alturaB(hijoIzqdoB(n)), alturaB(hijoDrchoB(n)) );
    else
        return -1;
}

template <typename T>
inline int Abin<T>::profundidadB(typename Abin<T>::nodo n) const
{
    if( n == raizB() ) return 0;
    else return 1 + profundidadB(padreB(n));
}

//Fin métodos del ejercicio 5

/* Definición del nodo nulo */
template <typename T> const typename Abin<T>::nodo Abin<T>::NODO_NULO(-1);

template <typename T> inline Abin<T>::Abin(size_t maxNodos) :
    nodos(new celda[maxNodos]), maxNodos(maxNodos), numNodos(0) {}

template <typename T> void Abin<T>::insertarRaizB(const T& e)
{   assert(numNodos == 0); // árbol vacío
    numNodos = 1;
    nodos[0] = new celda(e);
}

template<typename T>void Abin<T>::insertarHijoIzqdoB(Abin<T>::nodo n, const T& e)
{   assert(n >= 0 && n < numNodos); // nodo válido
    assert(nodos[n].hizq == NODO_NULO); // n no tiene hijo izqdo.
    assert(numNodos < maxNodos); // árbol no lleno
    // añadir el nuevo nodo al final de la secuencia
    nodos[n].hizq = numNodos;
    nodos[numNodos] = new celda(e,n);
}

template<typename T>void Abin<T>::insertarHijoDrchoB(Abin<T>::nodo n, const T& e)
{   assert(n >= 0 && n < numNodos); // nodo válido
    assert(nodos[n].hder == NODO_NULO); // n no tiene hijo drcho.
    assert(numNodos < maxNodos); // árbol no lleno
    // añadir el nuevo nodo al final de la secuencia
    nodos[n].hder = numNodos;
    nodos[numNodos] = new celda(e,n);
}

template <typename T> void Abin<T>::eliminarHijoIzqdoB(Abin<T>::nodo n)
{   assert(n >= 0 && n < numNodos); // nodo válido
    eliminarHijo(nodos[n].hizq);
    nodos[n].hizq = NODO_NULO;
}

template <typename T> void Abin<T>::eliminarHijoDrchoB(Abin<T>::nodo n)
{   assert(n >= 0 && n < numNodos); // nodo válido
    eliminarHijo(nodos[n].hder);
    nodos[n].hder = NODO_NULO;
}

template <typename T> void Abin<T>::eliminarHijo(Abin<T>::nodo nodo_a_eliminar)
{   assert(nodo_a_eliminar != NODO_NULO); // existe hijo que se quiere eliminar
    assert(nodos[nodo_a_eliminar].hizq == NODO_NULO);
    assert(nodos[nodo_a_eliminar].hder == NODO_NULO);
    if (nodo_a_eliminar != numNodos-1)
    {// Mover el último nodo a la posición del hijo drcho.
        nodos[nodo_a_eliminar] = nodos[numNodos-1];
    // Actualizar la posición del hijo (izq o der) en el padre del nodo movido
        if   (nodos[nodos[nodo_a_eliminar].padre].hizq == numNodos-1)
             nodos[nodos[nodo_a_eliminar].padre].hizq = nodo_a_eliminar;
        else nodos[nodos[nodo_a_eliminar].padre].hder = nodo_a_eliminar;
        // Si el nodo movido tiene hijos, actualizar la posición del padre
if (nodos[nodo_a_eliminar].hizq!=NODO_NULO) nodos[nodos[nodo_a_eliminar].hizq].padre = nodo_a_eliminar;
if (nodos[nodo_a_eliminar].hder!=NODO_NULO) nodos[nodos[nodo_a_eliminar].hder].padre = nodo_a_eliminar;
    }
    numNodos--;
}

template <typename T> inline void Abin<T>::eliminarRaizB()
{ assert(numNodos == 1); numNodos = 0; }

template <typename T> inline Abin<T>::~Abin() { delete[] nodos; }

template <typename T> inline bool Abin<T>::arbolVacioB() const { return (numNodos == 0); }

template <typename T> inline const T& Abin<T>::elemento(Abin<T>::nodo n) const
{ assert(n >= 0 && n < numNodos); return nodos[n].elto; }

template <typename T> inline T& Abin<T>::elemento(Abin<T>::nodo n)
{ assert(n >= 0 && n < numNodos); return nodos[n].elto; }

template <typename T> inline typename Abin<T>::nodo Abin<T>::raizB() const
{ return (numNodos > 0) ? 0 : NODO_NULO; }

template <typename T> inline typename Abin<T>::nodo Abin<T>::padreB(Abin<T>::nodo n)const
{assert(n>=0&&n<numNodos);  return nodos[n].padre;}

template <typename T> inline typename Abin<T>::nodo Abin<T>::hijoIzqdoB(Abin<T>::nodo n)const
{assert(n>=0&&n<numNodos);  return nodos[n].hizq;}

template <typename T> inline typename Abin<T>::nodo Abin<T>::hijoDrchoB(Abin<T>::nodo n)const
{assert(n>=0&&n<numNodos);  return nodos[n].hder;}

template <typename T> Abin<T>::Abin(const Abin<T>& a):
    nodos(new celda[a.maxNodos]), maxNodos(a.maxNodos), numNodos(a.numNodos)
{ for(nodo n = 0; n <= numNodos-1; n++) nodos[n] = a.nodos[n]; }

template <typename T> Abin<T>& Abin<T>::operator =(const Abin<T>& a)
{   if (this != &a)
    {   // Evitar autoasignación.
        // Destruir el vector y crear uno nuevo si es necesario
        if (maxNodos != a.maxNodos)
            delete[] nodos, maxNodos = a.maxNodos, nodos = new celda[maxNodos];
        // Copiar el vector
        numNodos = a.numNodos;
        for (nodo n = 0; n <= numNodos-1; n++) nodos[n] = a.nodos[n];
    }
    return *this;
}
#endif // ABIN_VEC0_H
