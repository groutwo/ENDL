/*Una forma de representar una figura plana en blanco y negro consiste en utilizar un
árbol cuaternario en el que cada nodo o tiene exactamente cuatro hijos, o bien es una
hoja. Un nodo hoja puede ser blanco o negro y un nodo interno no tiene color.
Una figura dibujada dentro de un cuadrado de lado 2k se representa de la forma
siguiente: Se divide el cuadrado en cuatro cuadrantes y cada uno se representa como un
hijo del nodo raíz. Si un cuadrante está completamente negro corresponde a una hoja
negra; si, por el contrario, el cuadrante está completamente blanco, éste corresponde a
una hoja blanca; y si un cuadrante está parcialmente ocupado por negro y blanco,
entonces corresponde a un nodo interno del árbol y este cuadrante se representa
siguiendo el mismo método subdividiéndolo en otros cuatro cuadrantes. Como ejemplo
se muestra una figura en blanco y negro y su árbol asociado, tomando los cuadrantes en
el sentido de las agujas del reloj a partir del cuadrante superior izquierdo.

Implementa una función que dado un árbol de esta clase, con k+1 niveles,
devuelva la figura asociada, representada como una matriz cuadrada de tamaño 2k en la
que cada celda representa un punto blanco o negro.
Nota: Por simplificar el problema, se asume que en cada nodo del árbol se
incluyen las coordenadas de la esquina superior izquierda y de la esquina inferior
derecha del cuadrante que representa.*/

/*  enunciado
3 4 2 0 2 0 8 2 0 2 0 1 0 1 0 0 2 0 0 5 2 0 2 0 2 0 9 1 0 2 0 2 0 1 0 0 0 6 1 0 2 0 3 1 0 2 0 1 0 1 0 0 1 0 0 7 1 0 1 0 2 0 2 0 0 0 4
*/

/* ejemplo a probar

6 7 1 0 2 0 1 0 2 0 0 3 1 0 2 0 1 0 2 0 0 4 1 0 2 0 1 0 1 0 0 5 1 0 2 0 1 0 2 0 0 0 3

*/

#include "09 Acuat.hpp"
#include "09 Acuat_E-S.hpp"
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
//nodo y arbol
template <typename T> void rellenaMatrizRec(Agen<T> A, typename Agen<T>::nodo n, int** matriz,/* int x1, int x2, int y1,int y2*/)
{
    if(A.elemento(n) == 1 or A.elemento(n) == 2)
    {
        for(int i=x1 ; i<x2 ; ++i)
            for(int j=y1 ; j<y2; ++j)
               matriz[i][j] = A.elemento(n);
    }
    else
    {
        rellenaMatrizRec(A,A.hijoIzqdo(n),matriz,
                            x1,     (x2/2),   y1,     (y2/2));
        rellenaMatrizRec(A,A.hermDrcho(A.hijoIzqdo(n)),matriz,
                            (x2/2),   x2,     y1,     (y2/2));
        rellenaMatrizRec(A,A.hermDrcho(A.hermDrcho(A.hijoIzqdo(n))),matriz,
                            (x2/2),   x2,     (y2/2),   y2);
        rellenaMatrizRec(A,A.hermDrcho(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(n)))),matriz,
                            x1,    (x2/2),   (y2/2),   y2);
    }
}

template <typename T> int** rellenaMatriz(Agen<T> A, int niveles)
{
    int dim = sqrt(pow(4,niveles-1));
    int** matriz = (int **)malloc (dim*sizeof(int*));
    for (int i=0;i<dim;i++)
        if ((matriz[i] = (int *) malloc (dim*sizeof(int))) == nullptr)
            cout<<"NO MEMORY";
    cout<<"dim:"<<dim<<endl;
    rellenaMatrizRec(A, A.raiz(), matriz, 0, dim, 0, dim);
    return matriz;
}

int main()
{
    Agen<int> A;
    int niveles;
    int** matriz;

    cout<<"1=negro, 2=blanco; otro valor=vacio"<<endl;
    rellenarAgen(A,0);
    cout<<"Niveles?"; cin>>niveles;
    cout<<endl;
    matriz = rellenaMatriz(A, niveles);

    int dim = sqrt(pow(4,niveles-1));


    cout<<endl<<" ";
    for(int i=1; i<dim+1; ++i)
        cout<<"_";
    cout<<endl;
    for(int i=0; i<dim; ++i)
    {  cout<<"|";
        for(int j=0 ; j<dim; ++j)
            if(matriz[i][j]==1)
                cout<<" ";
            else
                cout<<char(219);
        cout<<"|"<<endl;
    }
    for(int i=0; i<dim+2; ++i)
        cout<<char(238);

    return 0;
}
