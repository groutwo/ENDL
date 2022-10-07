/*Implementa una operación de orden logarítmico para eliminar el elemento máximo de
un montículo min-max definido como en el problema anterior*/

///Intercambiar el maximo del segundo nivel(1) con el del cuatro nivel
///Intercambiar el maximo del cuatro nivel(3) con el del sexto nivel(5)
/// ....
///Eliminar el maximo del ultimo nivel par

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

void eliminarMaximo(int* elementos,int& cantidadDeElementos,int nuevoElemento)
{       ///niveles = 5
    int niveles = log(cantidadDeElementos+1)/log(2);
    int nivelActual;
    for(nivelActual = 2; nivelActual <=niveles-2; nivelActual+=2)
            swap(elementos[PosicionMaximoNivel(elementos,nivelActual-1)],elementos[PosicionMaximoNivel(elementos,nivelActual+1)]);
    int posElementoMaximoAELiminar = elementos[PosicionMaximoNivel(elementos,nivelActual)];
    nivelActual-=2;
    if(nivelActual==niveles-1)//hay más elementos debajo
        elementos[PosicionMaximoNivel(elementos,nivelActual+1)] = elementos[PosicionMaximoNivel(elementos,niveles)-1];
    else
        elementos[PosicionMaximoNivel(elementos,nivelActual+1)] = elementos[cantidadDeElementos-1];
    --cantidadDeElementos;
}

int main()
{
    int niveles;
    niveles = 5;

    int cantidadDeElementos = (int)pow(2,niveles)-1;
    int* elementos = new int[cantidadDeElementos]  {1, 120,110, 2,3,4,5, 100,90,80,70,60,50,40,30, 6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    int* elementos1 = new int[cantidadDeElementos]  {1, 120,110, 2,3,4,5, 100,90,80,70,60,50,40,30};

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

        eliminarMaximo(elementos,cantidadDeElementos,niveles);
        /*
        eliminarMaximo(elementos1,cantidadDeElementos,niveles);
        */

    cout<<"\n\nTras eliminar el maximo, queda: "<<endl;
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
