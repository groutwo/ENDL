/*Un árbol es estrictamente ternario si todos sus nodos son hojas o tienen tres hijos.
Escribe una función que, dado un árbol ternario, nos indique si es o no estrictamente
ternario.*/

#include <iostream>
#include "08 Ater.hpp"
#include "08 Ater_E-S.hpp"
using namespace std;
/*
no:
q a b q q q c e g q q q h q m q q q q i q q q q f j q q q k q n q q q q l q q q d q q q

si:
q a b q q q c e g q q q h q q q i q q q o q q q f j q q q k q q q l q q q d q q q

*/

template <typename T> bool nodoHoja(Ater<T>& A,typename Ater<T>::nodo n)
{ return (A.hijoIzqdoT(n) == Ater<T>::NODO_NULO && A.hijoMedioT(n) == Ater<T>::NODO_NULO && A.hijoDrchoT(n) == Ater<T>::NODO_NULO); }

template <typename T> bool hermanosNulos(Ater<T>& A,typename Ater<T>::nodo n)
{ return (A.hijoIzqdoT(A.padreT(n)) == Ater<T>::NODO_NULO || A.hijoMedioT(A.padreT(n)) == Ater<T>::NODO_NULO || A.hijoDrchoT(A.padreT(n)) == Ater<T>::NODO_NULO ); }

template <typename T>
bool estrictamenteTerciario(Ater<T>& A)
{
    bool esTerciario = true;
    estrictamenteTerciarioRec(A.raizT(), A, esTerciario);
    return esTerciario;
}

template <typename T>
bool estrictamenteTerciarioRec(typename Ater<T>::nodo n, Ater<T>& A,bool& esTerciario)
{
	if(n!= Ater<T>::NODO_NULO)
	{
		if(nodoHoja(A,n) && esTerciario && hermanosNulos(A,n))
	        esTerciario = false;
	    else
            estrictamenteTerciarioRec(A.hijoIzqdoT(n), A, esTerciario ),
            estrictamenteTerciarioRec(A.hijoMedioT(n), A, esTerciario ),
            estrictamenteTerciarioRec(A.hijoDrchoT(n), A, esTerciario );
    }
}

int main()
{
    char nodoNulo;
    std::cout << "Define elemento NULO para arbol: ";
    std::cin >> nodoNulo;

    Ater<char> A = leerAter(nodoNulo);

    puts("");
    (estrictamenteTerciario(A))? cout<<"\nSi":cout<<"\nNo";
        std::cout << " es estrictamente terciario" << std::endl;

}
