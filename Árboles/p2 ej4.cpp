/*4. Una posible representación del TAD Árbol Binario consiste en almacenar los
elementos del árbol en un vector cuyo tamaño depende de la altura máxima que pueda
llegar a alcanzar el árbol. Cada nodo del árbol se corresponde con una única posición
del vector, la cual viene determinada por el recorrido en inorden del árbol.


Los hijos izquierdo y derecho de un nodo n corresponden, respectivamente, a las
posiciones n-(N+1)/2^(p+2) y n+(N+1)/2^(p+2), donde p es la profundidad de n y N es el
número máximo de nodos del árbol, es decir, el tamaño del vector.

Un nodo n es hijo izquierdo de su padre si n mod((N+1)/2^(p-1)) = ((N+1)/2^(p-1))-1*/

#ifndef ABIN_VEC1_H
#define ABIN_VEC1_H
#include <cassert>
#include <cstring>
#include <algorithm>
#include <cmath>

template <typename T> class Abin
{
public:
    typedef int nodo; // índice del vector entre 0 y maxNodos-1
    static const nodo NODO_NULO;
    explicit Abin(size_t maxNodos, const T& e_nulo = T()); //ctor
    void crearRaizB(const T& e);
    void insertarHijoIzqdoB(nodo n, const T& e);
    void insertarHijoDrchoB(nodo n, const T& e);
    void eliminarHijoIzqdoB(nodo n);
    void eliminarHijoDrchoB(nodo n);
    void eliminarHijo(nodo n,int i);
    ~Abin(); // destructor
    bool arbolVacioB() const;
    void eliminarRaizB();
    T elemento(nodo n) const; // acceso a elto, lectura
    T& elemento(nodo n); // acceso a elto, lectura/escritura
    nodo raizB() const;
    nodo padreB(nodo n) const;
    nodo hijoIzqdoB(nodo n) const;
    nodo hijoDrchoB(nodo n) const;
    Abin(const Abin<T>& a); // ctor. de copia
    int profundidadB(nodo n);
    Abin<T>& operator =(const Abin<T>& a); //asignación de árboles
private:
    T* nodos; // vector de nodos
    int maxNodos; // tamaño del vector
    T ELTO_NULO; // marca celdas vacías
};

template <typename T> int profundidadB(Abin<T>::nodo n)
{
    return profundidadBRec(n,0,maxNodos-1);
}

template <typename T> int profundidadBRec(Abin<T>::nodo n,int ini,int fin)
{
    int medio = (ini+fin)/2;

    if(n == medio)
        return 0;
    else
        if(n < medio)
            return 1 + profundidadBRec(n, ini, medio - 1);
        else // n > (ini+fin)/2
            return 1 + profundidadBRec(n, medio + 1, fin);
}

/* Definición del nodo nulo */
template <typename T> const typename Abin<T>::nodo Abin<T>::NODO_NULO(-1);

template <typename T> Abin<T>::Abin(size_t maxNodos, const T& e_nulo) :
    nodos(new T[maxNodos]), maxNodos(maxNodos), ELTO_NULO(e_nulo)
{/* marcar todas las celdas libres: */ for (nodo n = 0; n < maxNodos; n++) nodos[n] = ELTO_NULO; }

template <typename T> inline void Abin<T>::crearRaizB(const T& e)
{   assert(nodos[(maxNodos-1)/2] == ELTO_NULO); /* árbol vacío */ nodos[maxNodos-1] = e;}

template <typename T> inline void Abin<T>::insertarHijoIzqdoB(Abin<T>::nodo n,const T& e)
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    int pos = n-(maxNodos+1)/pow(2,profundidadB(n)+2);
    assert(pos>=0 && pos < maxNodos); // hijo izqdo. cabe en el árbol
    assert(nodos[pos] == ELTO_NULO); // n no tiene hijo izqdo.
    nodos[pos] = e;
}

template <typename T> inline void Abin<T>::insertarHijoDrchoB(Abin<T>::nodo n,const T& e)
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    int pos = n+(maxNodos+1)/pow(2,profundidadB(n)+2);
    assert(pos>=0 && pos < maxNodos); // hijo izqdo. cabe en el árbol
    assert(nodos[pos] == ELTO_NULO); // n no tiene hijo izqdo.
    nodos[pos] = e;
}

template <typename T> inline void Abin<T>::eliminarHijoIzqdoB(Abin<T>::nodo n)
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    int pos = n-(maxNodos+1)/pow(2,profundidadB(n)+2);
    int nietoIzq = pos-(maxNodos+1)/pow(2,profundidadB(pos)+2);
    int nietoDer = pos+(maxNodos+1)/pow(2,profundidadB(pos)+2);
/*Si el hijo que queremos eliminar tiene espacio para un hizq, éste debe ser nulo*/
    if(nietoIzq >= 0 && nietoIzq < maxNodos);
        assert(nodos[nietoIzq] == ELTO_NULO);
/*Si el hijo que queremos eliminar tiene espacio para un hder, éste debe ser nulo*/
    if(nietoDer >= 0 && nietoDer < maxNodos);
        assert(nodos[nietoDer] == ELTO_NULO);
    nodos[pos] = ELTO_NULO;
}

template <typename T> inline void Abin<T>::eliminarHijoDrchoB(Abin<T>::nodo n)
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    int pos = n+(maxNodos+1)/pow(2,profundidadB(n)+2);
    int nietoIzq = pos-(maxNodos+1)/pow(2,profundidadB(pos)+2);
    int nietoDer = pos+(maxNodos+1)/pow(2,profundidadB(pos)+2);
/*Si el hijo que queremos eliminar tiene espacio para un hizq, éste debe ser nulo*/
    if(nietoIzq >= 0 && nietoIzq < maxNodos);
        assert(nodos[nietoIzq] == ELTO_NULO);
/*Si el hijo que queremos eliminar tiene espacio para un hder, éste debe ser nulo*/
    if(nietoDer >= 0 && nietoDer < maxNodos);
        assert(nodos[nietoDer] == ELTO_NULO);
    nodos[pos] = ELTO_NULO;
}

template <typename T> inline void Abin<T>::eliminarRaizB()
{   assert(nodos[(maxNodos-1)/2] != ELTO_NULO); // árbol no vacío
    assert( nodos[n-(maxNodos+1)/pow(2,profundidadB(n)+2)] == ELTO_NULO &&
            nodos[n+(maxNodos+1)/pow(2,profundidadB(n)+2)] == ELTO_NULO); // la raíz es hoja
    nodos[(maxNodos-1)/2] = ELTO_NULO;
}

template <typename T> inline Abin<T>::~Abin()
{ delete[] nodos; }

template <typename T> inline bool Abin<T>::arbolVacioB() const
{ return (nodos[(maxNodos-1)/2] == ELTO_NULO); }

template <typename T> inline T Abin<T>::elemento(Abin<T>::nodo n) const
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    return nodos[n];
}

template <typename T> inline T& Abin<T>::elemento(Abin<T>::nodo n)
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    return nodos[n];
}

template <typename T> inline typename Abin<T>::nodo Abin<T>::raizB() const
{ return nodos[(maxNodos-1)/2 == ELTO_NULO ? NODO_NULO : 0; }

template <typename T> inline typename Abin<T>::nodo Abin<T>::padreB(Abin<T>::nodo n) const
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    int posPadre=0;
    if(n==hijoIzqdoB(padreB(n)))
        posPadre = n + (maxNodos+1)/pow(2,profundidadB(n)+1);
    else //n es hijo derecho
        posPadre = n - (maxNodos+1)/pow(2,profundidadB(n)+1);
    assert(posPadre >= 0 && posPadre < maxNodos); // nodo válido
    return nodos[posPadre];
}

template <typename T> inline typename Abin<T>::nodo Abin<T>::hijoIzqdoB(Abin<T>::nodo n) const
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    if( n-(maxNodos+1)/pow(2,profundidadB(n)+2) >= maxNodos ||
            nodos[n-(maxNodos+1)/pow(2,profundidadB(n)+2)] == ELTO_NULO)
     return NODO_NULO;
        else return n-(maxNodos+1)/pow(2,profundidadB(n)+2);
}

template <typename T> inline typename Abin<T>::nodo Abin<T>::hijoDrchoB(Abin<T>::nodo n) const
{   assert(n >= 0 && n < maxNodos); // nodo válido
    assert(nodos[n] != ELTO_NULO); // nodo del árbol
    if( n+(maxNodos+1)/pow(2,profundidadB(n)+2) >= maxNodos ||
            nodos[n+(maxNodos+1)/pow(2,profundidadB(n)+2)] == ELTO_NULO)
     return NODO_NULO;
        else return n+(maxNodos+1)/pow(2,profundidadB(n)+2);
}

template <typename T> Abin<T>::Abin(const Abin<T>& a) :
    nodos(new T[a.maxNodos]), maxNodos(a.maxNodos), ELTO_NULO(a.ELTO_NULO)
{   // copiar el vector
    for (nodo n = 0; n < maxNodos; n++) nodos[n] = a.nodos[n];
}

template <typename T> Abin<T>& Abin<T>::operator =(const Abin<T>& a)
{   if (this != &a)   // evitar autoasignación
    {
        // Destruir el vector y crear uno nuevo si es necesario
        if (maxNodos != a.maxNodos)
        { delete[] nodos; maxNodos = a.maxNodos; nodos = new T[maxNodos]; }
        ELTO_NULO = a.ELTO_NULO;
        // Copiar el vector
        for (nodo n = 0; n < maxNodos; n++) nodos[n] = a.nodos[n];
    }
    return *this;
}
#endif // ABIN_VEC1_H
