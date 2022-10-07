#ifndef Acuat_E_S_H
#define Acuat_E_S_H

#include <cassert>
#include <iostream>
#include <fstream>
#include "09 Acuat.hpp"
using namespace std;

template <typename T> void rellenarAcuat(Acuat<T>& A, const T& fin)
// Pre: A está vacío.
// Post: Rellena el árbol A con la estructura y elementos leídos en preorden de la
// entrada estándar, usando fin como elemento especial para introducir nodos nulos.
{
    setlocale(LC_CTYPE, "Spanish");
    T e;
    assert(A.arbolVacioB());
    cout << "Raíz (Fin = " << fin << "): "; cin >> e;
    if (e != fin)
    {   A.insertarRaizB(e);
        rellenarDescendientes(A.raizB(), A, fin);
    }
}

template <typename T> void rellenarDescendientes(typename Acuat<T>::nodo r, Acuat<T>& A, const T& fin)
// Pre: r es un nodo hoja de A.
// Post: Lee de la entrada estándar y en preorden los descendientes de r, usando fin para introducir nodos nulos.
{
   T eh1, eh2, eh3, eh4;
   assert(A.hijo1C(r) == Acuat<T>::NODO_NULO && A.hijo2C(r) == Acuat<T>::NODO_NULO &&
          A.hijo3C(r) == Acuat<T>::NODO_NULO && A.hijo4C(r) == Acuat<T>::NODO_NULO);
   cout << "Hijo 1 de " << A.elemento(r) << " (Fin = " << fin << "): ";
   cin >> eh1;
   if (eh1 != fin) {
      A.insertarHijo1C(r, eh1);
      rellenarDescendientes(A.hijo1C(r), A, fin);
   }

   cout << "Hijo 2 de " << A.elemento(r) << " (Fin = " << fin << "): ";
   cin >> eh2;
   if (eh2 != fin) {
      A.insertarHijo2C(r, eh2);
      rellenarDescendientes(A.hijo2C(r), A, fin);
   }

   cout << "Hijo 3 de " << A.elemento(r) << " (Fin = " << fin << "): ";
   cin >> eh3;
   if (eh3 != fin) {
      A.insertarHijo3C(r, eh3);
      rellenarDescendientes(A.hijo3C(r), A, fin);
   }

   cout << "Hijo 4 de " << A.elemento(r) << " (Fin = " << fin << "): ";
   cin >> eh4;
   if (eh4 != fin) {
      A.insertarHijo4C(r, eh4);
      rellenarDescendientes(A.hijo4C(r), A, fin);
   }
}

template <typename T> void rellenarAcuat(istream& is, Acuat<T>& A)
// Pre: A está vacío.
// Post: Extrae los nodos de A del flujo de entrada is, que contendrá el elemento especial que denota
// un nodo nulo seguido de los elementos en preorden, incluyendo los correspondientes a nodos nulos.
{
   T e, fin;
   assert(A.arbolVacioB());
   if (is >> fin && is >> e && e != fin) {
      A.insertarRaizB(e);
      rellenarDescendientes(is, A.raizB(), A, fin);
   }
}

template <typename T> void rellenarDescendientes(istream& is, typename Acuat<T>::nodo r, Acuat<T>& A, const T& fin)
// Pre: r es un nodo hoja de A.
// Post: Lee del flujo de entrada is y en preorden los descendientes de r, usando fin para los nodos nulos.
{
   T eh1, eh2, eh3, eh4;
   assert(A.hijo1C(r) == Acuat<T>::NODO_NULO && A.hijo2C(r) == Acuat<T>::NODO_NULO &&
          A.hijo3C(r) == Acuat<T>::NODO_NULO && A.hijo4C(r) == Acuat<T>::NODO_NULO);

   if (is >> eh1 && eh1 != fin) {
      A.insertarHijo1C(r, eh1);
      rellenarDescendientes(is, A.hijo1C(r), A, fin);
   }
   if (is >> eh2 && eh2 != fin) {
      A.insertarHijo2C(r, eh2);
      rellenarDescendientes(is, A.hijo2C(r), A, fin);
   }
    if (is >> eh3 && eh3 != fin) {
      A.insertarHijo1C(r, eh3);
      rellenarDescendientes(is, A.hijo3C(r), A, fin);
   }
   if (is >> eh4 && eh4 != fin) {
      A.insertarHijo4C(r, eh4);
      rellenarDescendientes(is, A.hijo4C(r), A, fin);
   }
}

template <typename T> void imprimirAcuat (const Acuat<T>& A)
// Post: Muestra los nodos de A en la salida estándar
{
    setlocale(LC_CTYPE, "Spanish");

   if (!A.arbolVacioB())
   {
      cout << "Raíz del árbol: " << A.elemento(A.raizB()) << endl;
      imprimirDescendientes(A.raizB(), A);
   }
   else
      cout << "Árbol vacío\n";
}

template <typename T> void imprimirDescendientes (typename Acuat<T>::nodo r, const Acuat<T>& A)
// Post: Muestra los descendientes de r en la salida estándar.
{
   if (A.hijo1C(r) != Acuat<T>::NODO_NULO)
   {
      cout << "Hijo 1 de " << A.elemento(r) << ": " << A.elemento(A.hijo1C(r)) << endl;
      imprimirDescendientes(A.hijo1C(r), A);
   }
   if (A.hijo1C(r) != Acuat<T>::NODO_NULO)
   {
      cout << "Hijo 2 de " << A.elemento(r) << ": " << A.elemento(A.hijo1C(r)) << endl;
      imprimirDescendientes(A.hijo1C(r), A);
   }
    if (A.hijo3C(r) != Acuat<T>::NODO_NULO)
   {
      cout << "Hijo 1 de " << A.elemento(r) << ": " << A.elemento(A.hijo3C(r)) << endl;
      imprimirDescendientes(A.hijo3C(r), A);
   }
   if (A.hijo4C(r) != Acuat<T>::NODO_NULO)
   {
      cout << "Hijo 2 de " << A.elemento(r) << ": " << A.elemento(A.hijo4C(r)) << endl;
      imprimirDescendientes(A.hijo4C(r), A);
   }
}

template <typename T> void imprimirAcuat (ostream& os, const Acuat<T>& A, const T& fin)
// Post: Inserta en el flujo de salida os los nodos de A en preorden,
//       precedidos del elemento especial usado para denotar un nodo nulo.
{
   if (!A.arbolVacioB())
   {
      os << fin << endl << A.elemento(A.raizB()) << ' ';
      imprimirDescendientes(os, A.raizB(), A, fin);
      os << endl;
   }
}

template <typename T> void imprimirDescendientes (ostream& os, typename Acuat<T>::nodo r, const Acuat<T>& A, const T& fin)
// Post: Inserta en el flujo de salida os y en preorden los descendientes de r, usando fin como nodo nulo.
{
   if (A.hijo1C(r) != Acuat<T>::NODO_NULO)
   {
      os << A.elemento(A.hijo1C(r)) << ' ';
      imprimirDescendientes(os, A.hijo1C(r), A, fin);
   }
   else
      os << fin << ' ';

   if (A.hijo2C(r) != Acuat<T>::NODO_NULO)
   {
      os << A.elemento(A.hijo2C(r)) << ' ';
      imprimirDescendientes(os, A.hijo2C(r), A, fin);
   }
   else
      os << fin << ' ';

    if (A.hijo3C(r) != Acuat<T>::NODO_NULO)
   {
      os << A.elemento(A.hijo3C(r)) << ' ';
      imprimirDescendientes(os, A.hijo3C(r), A, fin);
   }
   else
      os << fin << ' ';

   if (A.hijo4C(r) != Acuat<T>::NODO_NULO)
   {
      os << A.elemento(A.hijo4C(r)) << ' ';
      imprimirDescendientes(os, A.hijo4C(r), A, fin);
   }
   else
      os << fin << ' ';
}
#endif   /// Acuat_E_S_H
