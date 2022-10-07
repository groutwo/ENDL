/*
    9. Se dispone de dos grafos que representan la matriz de costes para viajes en un
    determinado país, pero por diferentes medios de transporte (tren y autobús, por
    ejemplo). Por supuesto ambos grafos tendrán el mismo número de nodos, N. Dados
    ambos grafos, una ciudad de origen, una ciudad de destino y el coste del taxi para
    cambiar de una estación a otra dentro de cualquier ciudad (se supone constante e igual
    para todas las ciudades), implementa un subprograma que calcule el camino y el coste
    mínimo para ir de la ciudad origen a la ciudad destino.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

template <typename tCoste> tCoste ejercicio9(const GrafoP<tCoste>& Tren,
		const GrafoP<tCoste>& Bus, typename GrafoP<tCoste>::vertice origen,
		typename GrafoP<tCoste>::vertice destino, tCoste taxi);

int main()
{
    GrafoP<int> tren ("matriz7.09Tren.txt");
    GrafoP<int> bus_ ("matriz7.09Bus.txt");

    int taxi = 15;
    typename GrafoP<GrafoP<int>::tCoste>::vertice vOrigen = 0, vDestino = 3;

    cout << "El coste minimo para viajar entre "<<vOrigen<<" y "<< vDestino;
    cout << " es "<<ejercicio9(tren,bus_,vOrigen,vDestino,taxi)<< endl;
}

template <typename tCoste> tCoste ejercicio9(const GrafoP<tCoste>& Tren,
		const GrafoP<tCoste>& Bus, typename GrafoP<tCoste>::vertice origen,
		typename GrafoP<tCoste>::vertice destino, tCoste taxi)
{
    typedef Grafo::vertice vertice;
    const size_t n = Tren.numVert();  //tb se puede con el bus,...
    vector<vertice> P1, P2;
    vector<tCoste> D1, D2;

    GrafoP<tCoste> TB = GrafoTrenBus(Tren, Bus, taxi);

    D1 = Dijkstra(TB, origen, P1);
    D2 = Dijkstra(TB, origen+n, P2);

    return min(D1[destino], D2[destino]);
}

template <typename tCoste> GrafoP<tCoste> GrafoTrenBus(const GrafoP<tCoste>& Tren,
		const GrafoP<tCoste>& Bus, tCoste taxi)
{
    const size_t n = Tren.numVert();  //tb se puede con el bus,...
	GrafoP<tCoste> A(2*n);

    //Primero voy a inicializar con el grafo del Tren y precio taxi el 1er y 2º cuadrante
    for(int i=0; i< n; ++i)
    {
        for(int j=0; j<n; ++j) //1er cuadrante
            A[i][j] = Tren[i][j];
        for(int j=n; j<2*n; ++j) //2º cuadrante
            if(i == j-n) A[i][j] = taxi;
            //else A[i][j] = GrafoP<tCoste>::INFINITO;//->el ctor ya lo hace
    }
    //Luego voy a inicializar con el grafo del Bus y precio taxi el 3er y 4º cuadrante
    for(int i=n; i<2*n; ++i)
    {
        for(int j=0; j<n; ++j) //3er cuadrante
            if(i-n == j) A[i][j] = taxi;
            //else A[i][j] = GrafoP<tCoste>::INFINITO;//->el ctor ya lo hace
        for(int j=n; j<2*n; ++j) //4º cuadrante
            A[i][j] = Bus[i-n][j-n];
    }
	return A;
}
