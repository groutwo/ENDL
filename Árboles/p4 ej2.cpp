/*Añade al TAD Abb un operador de conversión para obtener un árbol binario a partir
de un ABB, template <typename T> Abb<T>::operator Abin<T>() const;. Es necesario de-
clararlo como amigo de la clase Abin. Este operador nos permitirá obtener una copia
de un ABB y tratarlo como un Abin, p ej para realizar un recorrido del mismo.*/

#include "06 ABB.hpp"
#ifndef DE_ABB_A_ABIN
#define DE_ABB_A_ABIN

template <typename T> Abb<T>::operator Abin<T>() const
{
    Abin<T> a;

    if(r)
    {
        a.r = new typename Abin<T>::celda(r->elto);
        if(r->izq.r)
        {
            Abin<T> ai (r->izq); //Abb<T> -> Abin<T>
            a.r->hizq = ai.r;    //enlazar el subarbol izq
             ai.r->padre = a.r;  //con la raiz
            ai.r = Abin<T>::NODO_NULO;//impide destruir el subarbol
        }
        if(r->der.r)
        {
            Abin<T> ad (r->der);
            a.r->hder = ad.r;
            ad.r->padre = a.r;
            ad.r = Abin<T>::NODO_NULO;
        }
    }
    return a;
}
#endif
