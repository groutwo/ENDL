#ifndef ATER_H
#define ATER_H
#include <cassert>
//Ejercicio5.5
template <typename T> class Ater{
    struct celda; // declaración adelantada privada

public:
    typedef celda* nodo;
    static const nodo NODO_NULO; //atributo de clase
    Ater(); // constructor
    void crearRaizT(const T& e);
    void insertarHijoIzqdoT(nodo n, const T& e);
    void insertarHijoMedioT(nodo n, const T& e);
    void insertarHijoDrchoT(nodo n, const T& e);
    void eliminarHijoIzqdoT(nodo n);
    void eliminarHijoMedioT(nodo n);
    void eliminarHijoDrchoT(nodo n);
    void eliminarRaizT();
    ~Ater(); // destructor. No sirve el destructor por defecto pq solo destruye el puntero
    bool arbolVacioT() const;
    const T& elemento(nodo n) const; // acceso a elto, lectura
    T& elemento(nodo n); // acceso a elto, lectura/escritura
    nodo raizT() const;
    nodo padreT(nodo n) const;
    nodo hijoIzqdoT(nodo n) const;
    nodo hijoMedioT(nodo n) const;
    nodo hijoDrchoT(nodo n) const;
    Ater(const Ater<T>& a); // ctor. de copia
    Ater<T>& operator =(const Ater<T>& a); //asignación de árboles

private:
    struct celda {
        T elto;
        nodo padre, hizq, hder, hmed;
        celda(const T& e, nodo p = NODO_NULO): elto(e), padre(p), hizq(NODO_NULO), hder(NODO_NULO), hmed(NODO_NULO) {} // Ctor. NODO
    };
    nodo r; // nodo raíz del árbol
    void destruirNodos(nodo& n);
    nodo copiar(nodo n);

}; //Fin definición de la clase


/* Definición del nodo nulo */
template <typename T>
const typename Ater<T>::nodo Ater<T>::NODO_NULO(0);


/* CONSTRUCTOR */
template <typename T>
inline Ater<T>::Ater() : r(NODO_NULO) {}


template <typename T>
inline void Ater<T>::crearRaizT (const T& e)
{
    assert(r == NODO_NULO); // árbol vacío
    r = new celda(e); //omitimos el nodo padre
}


template <typename T>
inline void Ater<T>::insertarHijoIzqdoT(Ater<T>::nodo n, const T& e)
{
    // No comprobamos la existencia del nodo n, ya que hacer esa comprobación es muy costosa
    // eso lo debe hacer el usuario, pq habría que llegar hasta el nodo raiz para saberlo
    assert(n != NODO_NULO); //que al menos n no sea nulo, q al menos pertenezca al arbol
    assert(n->hizq == NODO_NULO); // no existe hijo
    n->hizq = new celda(e, n); //ahora si pasamos el padre, n
}


template <typename T> inline
void Ater<T>::insertarHijoDrchoT(Ater<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO); // no existe hijo
    n->hder = new celda(e, n);
}


template <typename T> inline
void Ater<T>::insertarHijoMedioT(Ater<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hmed == NODO_NULO); // no existe hijo
    n->hmed = new celda(e, n);
}


template <typename T>
inline void Ater<T>::eliminarHijoIzqdoT(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO); // existe hijo izqdo.
    assert(n->hizq->hizq == NODO_NULO && // hijo izqdo.
           n->hizq->hder == NODO_NULO &&
           n->hizq->hmed == NODO_NULO);  // es hoja
    delete(n->hizq);
    n->hizq = NODO_NULO; //nos aseguramos no obstante que el valor quede NODO_NULO
}


template <typename T>
inline void Ater<T>::eliminarHijoDrchoT(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO); // existe hijo drcho.
    assert(n->hder->hizq == NODO_NULO && // hijo drcho.
           n->hder->hder == NODO_NULO &&
           n->hder->hmed == NODO_NULO);  // es hoja
    delete(n->hder);
    n->hder = NODO_NULO;
}


template <typename T>
inline void Ater<T>::eliminarHijoMedioT(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hmed != NODO_NULO); // existe hijo drcho.
    assert(n->hmed->hizq == NODO_NULO && // hijo medio.
           n->hmed->hder == NODO_NULO &&
           n->hmed->hmed == NODO_NULO);  // es hoja
    delete(n->hmed);
    n->hmed = NODO_NULO;
}


template <typename T>
inline void Ater<T>::eliminarRaizT()
{
    assert(r != NODO_NULO); // árbol no vacío
    assert(r->hizq == NODO_NULO &&
           r->hder == NODO_NULO &&
           r->hmed == NODO_NULO);  // la raíz es hoja
    delete(r);
    r = NODO_NULO; //y queda el arbol vacío, igual que tras el Ctor.
}


template <typename T> inline Ater<T>::~Ater()
{
    destruirNodos(r); // vacía el árbol, el objeto árbol en sí lo destruye luego el compilador
}


template <typename T> inline bool Ater<T>::arbolVacioT() const
{
    return (r == NODO_NULO);
}


template <typename T>
inline const T& Ater<T>::elemento(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}


template <typename T>
inline T& Ater<T>::elemento(Ater<T>::nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}


template <typename T>
inline typename Ater<T>::nodo Ater<T>::raizT() const
{
    return r;
}


template <typename T> inline
typename Ater<T>::nodo Ater<T>::padreT(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}


template <typename T> inline
typename Ater<T>::nodo Ater<T>::hijoIzqdoT(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}


template <typename T> inline
typename Ater<T>::nodo Ater<T>::hijoDrchoT(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hder;
}


template <typename T> inline
typename Ater<T>::nodo Ater<T>::hijoMedioT(Ater<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hmed;
}


template <typename T>
inline Ater<T>::Ater(const Ater<T>& a)
{
    r = copiar(a.r);
}


template <typename T>
Ater<T>& Ater<T>::operator =(const Ater<T>& a)
{
    if (this != &a){ // evitar autoasignación
        this->~Ater(); // vaciar el árbol (destino)
        r = copiar(a.r); //y ahora lo copiamos con los nodos del otro arbol.
    }
    return *this;
}


// Métodos privados. LOS MAS INTERESANTES DE LA IMPLEMENTACION

// Destruye un nodo y todos sus descendientes
template <typename T>
void Ater<T>::destruirNodos(Ater<T>::nodo& n) //MéTODO RECURSIVO
{
    if (n != NODO_NULO){ //CASO GENERAL: Si nodo n no es nulo, entonces destruye a sus descendientes y al propio nodo
        destruirNodos(n->hizq);
        destruirNodos(n->hmed);
        destruirNodos(n->hder);
        delete n;
        n = NODO_NULO;
    }
    //CASE BASE: No se indica pq no hay que hacer nada en caso de que el nodo n sea nulo.
}


// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Ater<T>::nodo Ater<T>::copiar(Ater<T>::nodo n)//MéTODO RECURSIVO
{
    nodo m = NODO_NULO; //variable local que devolveremos en el return.

    if (n != NODO_NULO){ //CASO GENERAL: Copiar un árbol no vacío
        m = new celda(n->elto); // copiar n. El padre lo omitimos
        m->hizq = copiar(n->hizq); // copiar subárbol izqdo.

        if (m->hizq != NODO_NULO)
            m->hizq->padre = m;

        m->hmed = copiar(n->hmed); // copiar subárbol medio.

        if (m->hmed != NODO_NULO)
            m->hmed->padre = m;

        m->hder = copiar(n->hder); // copiar subárbol drcho.

        if (m->hder != NODO_NULO)
            m->hder->padre = m;
    }
    //CASO BASE: Copiar arbol vacío. No se hace nada.

    return m;
}




#endif // ATER_H

