/* Se define el desequilibrio de un árbol general como la máxima diferencia entre
    las alturas de los subárboles más bajo y más alto de cada nivel. Implementa un
    subprograma que calcule el grado de desequilibrio de un árbol general. */
#include "04 agen.hpp"
#include "04 agen_E-S.hpp"
#include <iostream>
template <typename T> int altura(typename Agen<T>::nodo n,const Agen<T>& A)
{
	int max;
	int alturaTemporal;
	typename Agen<T>::nodo hijo;

	if(n == Agen<T>::NODO_NULO)
		return -1;
	else
	{
		max = -1;
		hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO)
		{
			alturaTemporal = altura(hijo)
			if(alturaTemporal > max)
				max = alturaTemporal;
		}
		return 1 + alturaTemporal;
	}
}

template <typename T> int desequilibrioRec(typename Agen<T>::nodo n,const Agen<T>& A)
{
    int desequilibrioActual;
    typename Agen<T>::nodo hijo;

    if( n == Agen<T>::NODO_NULO )
        return -1;
    else if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return altura(n,A);
    else
    {
        desequilibrioActual = 0;
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            desequilibrioActual = max(desequilibrioActual,desequilibrioRec(hijo, A));
            hijo = A.hermDrcho(hijo);
        }
        return desequilibrioActual;
    }
}

template <typename T> int desequilibrio(const Agen<T>& A)
{
    return desequilibrioRec(A.raiz(), A);
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Agen<char> A;
    rellenarAgen(A, 'z');
	int desequilibrio_del_arbol = desequilibrio(A);
    std::cout<<"\n\nEl desequilibrio del árbol es: "<<desequilibrio_del_arbol<<std::endl;
    return 0;
}
