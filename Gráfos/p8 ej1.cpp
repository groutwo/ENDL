/*
    1. El archipiélago de Tombuctú, está formado por un número indeterminado de islas,
    cada una de las cuales tiene, a su vez, un número indeterminado de ciudades. En
    cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo N,
    por ejemplo).
    Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
    las ciudades de la isla. Se dispone de las coordenadas cartesianas (x, y) de todas y cada
    una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en
    el que se indica si existe carretera directa entre cualesquiera dos ciudades del
    archipiélago. El objetivo de nuestro problema es encontrar qué ciudades de Tombuctú
    pertenecen a cada una de las islas del mismo y cuál es el coste mínimo de viajar entre
    cualesquiera dos ciudades de una misma isla de Tombuctú.
    Así pues, dados los siguientes datos:
        - Lista de ciudades de Tombuctú representada cada una de ellas por sus
            coordenadas cartesianas.
        - Matriz de adyacencia de Tombuctú, que indica las carreteras existentes en
            dicho archipiélago.
    Implementen un subprograma que calcule y devuelva la distribución en islas de las
    ciudades de Tombuctú, así como el coste mínimo de viajar entre cualesquiera dos
    ciudades de una misma isla del archipiélago.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h"
#include "../particion.h"
#include "cmath"
#include <iostream>

using namespace std;

struct ciudad
{
    typename GrafoP<GrafoP<int>::tCoste>::vertice v;  double x, y;
    ciudad(typename GrafoP<int>::vertice vvv , double xxx,  double yyy): v(vvv),x(xxx),y(yyy){}
};

template <typename T> size_t elementosLista(Lista<T>& L)
{
    typename Lista<T>::posicion p = L.primera();
    size_t num = 0;

    while(p != L.fin())
        num++, p = L.siguiente(p);
    return num;
}

double distanciaCiudades(ciudad& A, ciudad& B)
{ return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)); }

template <typename tCoste> Particion ejercicio1(vector<ciudad>& ciudades,
    Grafo& carreteras, matriz<tCoste>& matrizCostes, size_t tam);

int main()
{
    const size_t tam = 6;
    vector<ciudad> ciudades={{0,2,5},{1,3,3},{2,5,5},{3,10,4},{4,12,7},{5,13,5}};
    Grafo grafo(tam);
    matriz<double> matrizDoubles(tam);
    Particion particion(tam);


    grafo[0][1] = grafo[1][0] = grafo[0][2] = grafo[2][0] = grafo[1][2] = grafo[2][1] = true;
    grafo[3][4] = grafo[4][3] = grafo[3][5] = grafo[5][3] = grafo[4][5] = grafo[5][4] = true;

    particion = ejercicio1(ciudades, grafo, matrizDoubles, tam);

    cout << "Coste minimo de viajar entre cualesquiera dos ciudades ";
    cout << "de una misma isla del archipielago\n" << matrizDoubles <<endl;

    cout << "\nDistribucion en islas de las ciudades de Tombuctu" << endl;
    for(int i=0; i<tam; ++i)
        cout <<"Representante de ciudad "<<i<<" es la ciudad "<<particion.encontrar(i)<<endl;
}

template <typename tCoste> Particion ejercicio1(vector<ciudad>& ciudades,
    Grafo& carreteras, matriz<tCoste>& matrizCostes, size_t tam)
{
    typedef Grafo::vertice vertice;
    Particion particion(tam);
    GrafoP<tCoste> grafoCostes(tam);
    matriz<vertice> matrizVertices(tam);

    for(int i=0; i<tam; ++i)
        for(int j=0; j<tam; ++j)
            if(carreteras[i][j])
            {   grafoCostes[i][j] = distanciaCiudades(ciudades[i], ciudades[j]);
                if(particion.encontrar(i) != particion.encontrar(j))
                    particion.unir(i, j);
            }

    matrizCostes = Floyd(grafoCostes, matrizVertices);
    return particion;
}
