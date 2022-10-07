/* Implementa una nueva operación del TAD Abb que tomando un elemento del
mismo elimine al completo el subárbol que cuelga de él.

Ejemplo: Para el árbol binario de búsqueda de la figura se muestra la
    transformación si la entrada fuera el valor 9.


            7                    7
          /   \                /   \
        5      12             5     12
              /  \                    \
             9    17 -->               17
            / \
           8  11
             /
            10

*/

#include "06 ABB.hpp"
#include "iostream"
#include "0 abin_E-S.hpp"

using namespace std;
template <typename T> void Abb<T>::eliminarAPartirDe(const T& e)
{
    //Buscamos el subarbol que tiene como nodo raiz el elemento e
    if (e < r->elto)
        r->izq.eliminarAPartirDe(e);
    else if (r->elto < e)
        r->der.eliminarAPartirDe(e);
    else // r->elto == e
        ~Abb();
}
