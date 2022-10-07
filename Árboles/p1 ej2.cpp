/*2. Implementa un subprograma que calcule la altura de un árbol binario.*/
#include <iostream>
#include "01 abin.hpp"
#include "0 abin_E-S.hpp"

///La altura de un árbol es la altura del nodo raíz
template <typename T> void calculaAlturaRec (const Abin<T>& arbol, typename Abin<T>::nodo n,int& alturaActual)
{
    if(n!=Abin<T>::NODO_NULO)
    {
        if( arbol.hijoIzqdoB(n) == Abin<T>::NODO_NULO && arbol.hijoDrchoB(n) == Abin<T>::NODO_NULO)
        {
            //Si no es nodo hoja, su hijo será más profundo
            int alturaTemporal = 0;
            while(n!= Abin<T>::NODO_NULO)
                n = arbol.padreB(n), alturaTemporal++;
            if(alturaTemporal > alturaActual)
                alturaActual = alturaTemporal;
        }
        else
        {
            calculaAlturaRec(arbol,arbol.hijoIzqdoB(n),alturaActual);
            calculaAlturaRec(arbol,arbol.hijoDrchoB(n),alturaActual);
        }
    }
}

template <typename T> int calculaAltura(const Abin<T>& arbol)
{
    int altura = -1;
    calculaAlturaRec(arbol, arbol.raizB(), altura);
    return altura;
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    Abin<char> arbol;
    rellenarAbin(arbol, '#');
    int altura = calculaAltura(arbol);
    std::cout<<"La altura del árbol en cuestion es de "<<altura<<std::endl;

    system("pause");
    return 0;
}
