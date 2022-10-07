/*Un montículo min-max tiene una estructura similar a la de un montículo ordinario
(árbol parcialmente ordenado), pero la ordenación parcial consiste en que los elementos
que se encuentran en un nivel par (0, 2, 4,...) son menores o iguales que sus elementos
descendientes, mientras que los elementos que se encuentran en un nivel impar (1, 3, ..)
son mayores o iguales que sus descendientes. Esto quiere decir que para cualquier
elemento e de un nivel par se cumple abuelo <= e <= padre y para cualquier elemento e de
un nivel impar padre <= e <= abuelo.
Implementa una operación de orden logarítmico para añadir un elemento a un
montículo min-max almacenado en un vector de posiciones relativas.*/

//#include "04 agen.hpp"
#include <iostream>
#include <cmath>
using namespace std;

int PosicionMaximoNivel(int* elementos, int nivel)
{
    int maximo = -1, posMax;
    for(int i = pow(2,nivel)-1; i<pow(2,nivel+1)-1;++i)
        if(elementos[i]>maximo)
            maximo = elementos[i],posMax = i;
    return posMax;
}

int PosicionMinimoNivel(int* elementos, int nivel)
{
    int minimo = 99999,posMin;
    for(int i = pow(2,nivel)-1; i<pow(2,nivel+1)-1;++i)
        if(elementos[i]<minimo)
            minimo = elementos[i],posMin = i;
    return posMin;
}

void annadirElemento(int* elementos,int& cantidadDeElementos,int nuevoElemento)
{       ///niveles = 5
    int niveles = log(cantidadDeElementos+1)/log(2);
    int aux;
    for( int nivelActual=0; nivelActual<niveles; ++nivelActual)
        if(nivelActual&0 && nuevoElemento<(aux=elementos[PosicionMaximoNivel(elementos,nivelActual)]))
            elementos[PosicionMaximoNivel(elementos,nivelActual)] = nuevoElemento,
            annadirElemento(elementos,niveles,aux) ,++cantidadDeElementos;

        else if(nivelActual&1 && nuevoElemento>(aux=elementos[PosicionMinimoNivel(elementos,nivelActual)]))
            elementos[PosicionMinimoNivel(elementos,nivelActual)] = nuevoElemento,
            annadirElemento(elementos,niveles,aux) ,++cantidadDeElementos;

        else if(nivelActual == niveles-1)
            elementos[(int)pow(2,nivelActual+1)-1] = aux;
}

int main()
{
    int niveles, nuevoElemento;
    niveles = 5;
    nuevoElemento=75;

    //    cout<<"Introduce la cantidad de niveles "; cin>>niveles;
    //    cout<<"Introduce elemento para annadirlo al monticulo "; cin>>nuevoElemento;

    int cantidadDeElementos = (int)pow(2,niveles)-1;
    int* elementos = new int[cantidadDeElementos]  {1, 120,110, 2,3,4,5, 100,90,80,70,60,50,40,30, 6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};

    cout<<"Inicialmente, el vector es: "<<endl;
    bool flag=true;
    for(int i=0; i<cantidadDeElementos;++i,flag=true)
    {
        for(int j=1; j<6 ;j++)
            if(i==int(pow(2,j))-2 && i!=cantidadDeElementos-1 )
                cout<<elementos[i]<<" - ",flag=false;
        if(flag)
                cout<<elementos[i]<<" ";
    }

        annadirElemento(elementos,cantidadDeElementos,nuevoElemento);

    cout<<"\n\nTras annadir el "<<nuevoElemento<<" queda: "<<endl;
    flag=true;
    for(int i=0; i<cantidadDeElementos;++i,flag=true)
    {
        for(int j=1; j<6 ;j++)
            if(i==int(pow(2,j))-2 && i!=cantidadDeElementos)
                cout<<elementos[i]<<" - ",flag=false;
        if(flag)
                cout<<elementos[i]<<" ";
    }
    puts("");
}
