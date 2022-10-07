#ifndef ACUAT_H
#define ACUAT_H
#include <cassert>
//Ejercicio5.5
template <typename T> class Acuat{
    struct celda; // declaración adelantada privada

public:
    typedef celda* nodo;
    static const nodo NODO_NULO; //atributo de clase
    Acuat(); // constructor
    void crearRaizT(const T& e);
    void insertarHijo1C(nodo n, const T& e);
    void insertarHijo2C(nodo n, const T& e);
    void insertarHijo3C(nodo n, const T& e);
    void insertarHijo4C(nodo n, const T& e);
    void eliminarHijo1C(nodo n);
    void eliminarHijo2C(nodo n);
    void eliminarHijo3C(nodo n);
    void eliminarHijo4C(nodo n);
    void eliminarRaizC();
    ~Acuat(); // destructor. No sirve el destructor por defecto pq solo destruye el puntero
    bool arbolVacioC() const;
    const T& elemento(nodo n) const; // acceso a elto, lectura
    T& elemento(nodo n); // acceso a elto, lectura/escritura
    nodo raizC() const;
    nodo padreC(nodo n) const;
    nodo hijo1C(nodo n) const;
    nodo hijo2C(nodo n) const;
    nodo hijo3C(nodo n) const;
    nodo hijo4C(nodo n) const;
    Acuat(const Acuat<T>& a); // ctor. de copia
    Acuat<T>& operator =(const Acuat<T>& a); //asignación de árboles

private:
    struct celda {
        T elto;
        nodo padre, h1, h2, h3,h4;
        celda(const T& e, nodo p = NODO_NULO):
        elto(e), padre(p), h1(NODO_NULO), h2(NODO_NULO), h3(NODO_NULO), h4(NODO_NULO) {} // Ctor. NODO
    };
    nodo r; // nodo raíz del árbol
    void destruirNodos(nodo& n);
    nodo copiar(nodo n);

}; //Fin definición de la clase


/* Definición del nodo nulo */
template <typename T>
const typename Acuat<T>::nodo Acuat<T>::NODO_NULO(0);


/* CONSTRUCTOR */
template <typename T>
inline Acuat<T>::Acuat() : r(NODO_NULO) {}


template <typename T>
inline void Acuat<T>::crearRaizT (const T& e)
{
    assert(r == NODO_NULO); // árbol vacío
    r = new celda(e); //omitimos el nodo padre
}


template <typename T>
inline void Acuat<T>::insertarHijo1C(Acuat<T>::nodo n, const T& e)
{
    // No comprobamos la existencia del nodo n, ya que hacer esa comprobación es muy costosa
    // eso lo debe hacer el usuario, pq habría que llegar hasta el nodo raiz para saberlo
    assert(n != NODO_NULO); //que al menos n no sea nulo, q al menos pertenezca al arbol
    assert(n->h1 == NODO_NULO); // no existe hijo
    n->h1 = new celda(e, n); //ahora si pasamos el padre, n
}


template <typename T> inline
void Acuat<T>::insertarHijo2C(Acuat<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->h2 == NODO_NULO); // no existe hijo
    n->h2 = new celda(e, n);
}


template <typename T> inline
void Acuat<T>::insertarHijo3C(Acuat<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->h3 == NODO_NULO); // no existe hijo
    n->h3 = new celda(e, n);
}
template <typename T> inline
void Acuat<T>::insertarHijo4C(Acuat<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->h4 == NODO_NULO); // no existe hijo
    n->h4 = new celda(e, n);
}


template <typename T>
inline void Acuat<T>::eliminarHijo1C(Acuat<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->h1 != NODO_NULO); // existe hijo izqdo.
    assert(n->h1->h1 == NODO_NULO && // hijo izqdo.
           n->h1->h2 == NODO_NULO &&
           n->h1->h3 == NODO_NULO &&
           n->h1->h4 == NODO_NULO);  // es hoja
    delete(n->h1);
    n->h1 = NODO_NULO; //nos aseguramos no obstante que el valor quede NODO_NULO
}


template <typename T>
inline void Acuat<T>::eliminarHijo2C(Acuat<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->h2 != NODO_NULO); // existe hijo drcho.
    assert(n->h2->h1 == NODO_NULO && // hijo drcho.
           n->h2->h2 == NODO_NULO &&
           n->h2->h3 == NODO_NULO &&
           n->h2->h4 == NODO_NULO);  // es hoja
    delete(n->h2);
    n->h2 = NODO_NULO;
}


template <typename T>
inline void Acuat<T>::eliminarHijo3C(Acuat<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->h3 != NODO_NULO); // existe hijo drcho.
    assert(n->h3->h1 == NODO_NULO && // hijo medio.
           n->h3->h2 == NODO_NULO &&
           n->h3->h3 == NODO_NULO&&
           n->h3->h4 == NODO_NULO);  // es hoja
    delete(n->h3);
    n->h3 = NODO_NULO;
}


template <typename T>
inline void Acuat<T>::eliminarHijo4C(Acuat<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->h4 != NODO_NULO); // existe hijo drcho.
    assert(n->h4->h1 == NODO_NULO && // hijo medio.
           n->h4->h2 == NODO_NULO &&
           n->h4->h3 == NODO_NULO&&
           n->h4->h4 == NODO_NULO);  // es hoja
    delete(n->h3);
    n->h4 = NODO_NULO;
}


template <typename T>
inline void Acuat<T>::eliminarRaizC()
{
    assert(r != NODO_NULO); // árbol no vacío
    assert(r->h1 == NODO_NULO &&
           r->h2 == NODO_NULO &&
           r->h3 == NODO_NULO &&
           r->h4 == NODO_NULO);  // la raíz es hoja
    delete(r);
    r = NODO_NULO; //y queda el arbol vacío, igual que tras el Ctor.
}


template <typename T> inline Acuat<T>::~Acuat()
{
    destruirNodos(r); // vacía el árbol, el objeto árbol en sí lo destruye luego el compilador
}


template <typename T> inline bool Acuat<T>::arbolVacioC() const
{
    return (r == NODO_NULO);
}


template <typename T>
inline const T& Acuat<T>::elemento(Acuat<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}


template <typename T>
inline T& Acuat<T>::elemento(Acuat<T>::nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}


template <typename T>
inline typename Acuat<T>::nodo Acuat<T>::raizC() const
{
    return r;
}


template <typename T> inline
typename Acuat<T>::nodo Acuat<T>::padreC(Acuat<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}


template <typename T> inline
typename Acuat<T>::nodo Acuat<T>::hijo1C(Acuat<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->h1;
}


template <typename T> inline
typename Acuat<T>::nodo Acuat<T>::hijo2C(Acuat<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->h2;
}


template <typename T> inline
typename Acuat<T>::nodo Acuat<T>::hijo3C(Acuat<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->h3;
}


template <typename T> inline
typename Acuat<T>::nodo Acuat<T>::hijo4C(Acuat<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->h4;
}


template <typename T>
inline Acuat<T>::Acuat(const Acuat<T>& a)
{
    r = copiar(a.r);
}


template <typename T>
Acuat<T>& Acuat<T>::operator =(const Acuat<T>& a)
{
    if (this != &a){ // evitar autoasignación
        this->~Acuat(); // vaciar el árbol (destino)
        r = copiar(a.r); //y ahora lo copiamos con los nodos del otro arbol.
    }
    return *this;
}


// Métodos privados. LOS MAS INTERESANTES DE LA IMPLEMENTACION

// Destruye un nodo y todos sus descendientes
template <typename T>
void Acuat<T>::destruirNodos(Acuat<T>::nodo& n) //MÉTODO RECURSIVO
{
    if (n != NODO_NULO){ //CASO GENERAL: Si nodo n no es nulo, entonces destruye a sus descendientes y al propio nodo
        destruirNodos(n->h1);
        destruirNodos(n->h2);
        destruirNodos(n->h3);
        destruirNodos(n->h4);
        delete n;
        n = NODO_NULO;
    }
    //CASE BASE: No se indica pq no hay que hacer nada en caso de que el nodo n sea nulo.
}


// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Acuat<T>::nodo Acuat<T>::copiar(Acuat<T>::nodo n)//MÉTODO RECURSIVO
{
    nodo m = NODO_NULO; //variable local que devolveremos en el return.

    if (n != NODO_NULO){ //CASO GENERAL: Copiar un árbol no vacío
        m = new celda(n->elto); // copiar n. El padre lo omitimos
        m->h1 = copiar(n->h1); // copiar subárbol 1.

        if (m->h1 != NODO_NULO) m->h1->padre = m;
        m->h2 = copiar(n->h2); // copiar subárbol 2.

        if (m->h2 != NODO_NULO) m->h2->padre = m;
        m->h3 = copiar(n->h3); // copiar subárbol 3.

        if (m->h3 != NODO_NULO) m->h3->padre = m;
        m->h4 = copiar(n->h4); // copiar subárbol 4.

        if (m->h4 != NODO_NULO) m->h4->padre = m;
    }
    //CASO BASE: Copiar arbol vacío. No se hace nada.

    return m;
}

#endif // ACUAT_H

