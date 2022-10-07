/*6. Implementa un subprograma que determine el nivel de desequilibrio de un árbol
binario, definido como el máximo desequilibrio de todos sus nodos. El desequilibrio
de un nodo se define como la diferencia entre las alturas de los subárboles del mismo.*/
#include <iostream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

int maximo(int a, int b, int c)
{
    return std::max(a,std::max(b,c));
}

template <typename T> int desequilibrioRec(typename Abin<T>::nodo n,const Abin<T>& a)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else
    {
	    int desequilibrioRamaIzq = desequilibrioRec(a.hijoIzqdoB(n), a);
	    int desequilibrioRamaDer = desequilibrioRec(a.hijoDrchoB(n), a);
	    int desequilibrioN = abs( a.alturaB(a.hijoIzqdoB(n)) - (a.alturaB(a.hijoDrchoB(n))) );
        return maximo(desequilibrioRamaIzq, desequilibrioRamaDer, desequilibrioN);
    }
}

template <typename T> int desequilibrio(const Abin<T>& a)
{
    return desequilibrioRec(a.raizB(), a);
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<char> arbol;
    rellenarAbin(arbol, 'q');
	int desequilibrio_del_arbol = desequilibrio(arbol);
    std::cout<<"El desequilibrio del árbol es: "<<desequilibrio_del_arbol<<std::endl;
}
