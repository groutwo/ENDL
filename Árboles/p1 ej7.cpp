/*7. Implementa un subprograma que determine si un árbol binario es o no
pseudocompleto. En este problema entenderemos que un árbol lo es si en el
penúltimo nivel del mismo cada uno de los nodos tiene dos hijos o ninguno*/
#include <iostream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

template <typename T> void pseudocompletoRec(typename Abin<T>::nodo n, const Abin<T>& A, bool& esPseudocompleto )
{
	if(n!= Abin<T>::NODO_NULO)
	{
		if(A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO //n es un nodo hoja; nos encontramos en el ultimo nivel
        	&& esPseudocompleto //Si no lo es, da igual el resto de condiciones; el arbol directamente no es pseudocompleto
	        //Para que sea pseudocompleto, el hermano de un un nodo hoja debe ser nulo
	        && (A.hijoIzqdoB(A.padreB(n)) == Abin<T>::NODO_NULO || A.hijoDrchoB(A.padreB(n)) == Abin<T>::NODO_NULO))
	        esPseudocompleto = false;
	    else
	    	pseudocompletoRec(A.hijoIzqdoB(n), A, esPseudocompleto ), pseudocompletoRec(A.hijoDrchoB(n), A, esPseudocompleto );
	}
}

template <typename T> bool pseudocompleto(const Abin<T>& A)
{
	bool esPseudocompleto = true;
	pseudocompletoRec(A.raizB(), A, esPseudocompleto);
	return esPseudocompleto;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<char> arbol;
    rellenarAbin(arbol, 'q');
	bool esPseudocompleto = pseudocompleto(arbol);

	if(esPseudocompleto)
		std::cout<<"El arbol SI es pseudocompleto"<<std::endl;
	else
		std::cout<<"El arbol NO es pseudocompleto"<<std::endl;
}
