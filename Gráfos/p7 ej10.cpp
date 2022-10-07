/*
    10. Se dispone de tres grafos que representan la matriz de costes para viajes en un
    determinado país, pero por diferentes medios de transporte (tren, autobús y avión). Por
    supuesto los tres grafos tendrán el mismo número de nodos, N. Dados los siguientes datos:
    · los tres grafos,
    · una ciudad de origen,
    · una ciudad de destino,
    · el coste del taxi para cambiar, dentro de una ciudad, de la estación de tren a la
            de autobús o viceversa (taxi-tren-bus) y
    · el coste del taxi desde el aeropuerto a la estación de tren o la de autobús, o
            viceversa (taxi-aeropuerto-tren/bus)
    y asumiendo que ambos costes de taxi (distintos entre sí, son dos costes diferentes) son
    constantes e iguales para todas las ciudades, implementa un subprograma que calcule el
    camino y el coste mínimo para ir de la ciudad origen a la ciudad destino.
*/

#include "../alg_grafo_E-S.h"
#include "../alg_grafoPMC.h" //Dijkstra
#include <iostream>

using namespace std;

template <typename tCoste> tCoste ejercicio10(const GrafoP<tCoste>& Tren, const GrafoP<tCoste>& Bus,
        const GrafoP<tCoste>& Avion, typename GrafoP<tCoste>::vertice origen,
        typename GrafoP<tCoste>::vertice destino, tCoste t1, tCoste t2);

int main()
{
    GrafoP<int> T ("matriz7.10Tren.txt");
    GrafoP<int> B ("matriz7.10Bus.txt");
    GrafoP<int> A  ("matriz7.10Avion.txt");

    int Taxi_urb, Taxi_inturb = 15;

    typename GrafoP<GrafoP<int>::tCoste>::vertice O = 2, D = 0;

    cout << "El coste minimo para viajar entre " << O << " y " << D << " es: ";
    cout<< ejercicio10(T, B, A, O, D, Taxi_urb, Taxi_inturb) << endl;

}

template <typename tCoste> tCoste ejercicio10(const GrafoP<tCoste>& Tren, const GrafoP<tCoste>& Bus,
        const GrafoP<tCoste>& Avion, typename GrafoP<tCoste>::vertice origen,
        typename GrafoP<tCoste>::vertice destino, tCoste t1, tCoste t2)
{
    typedef Grafo::vertice vertice;

    const size_t n = Tren.numVert();  //tb se puede con el bus,...
    vector<vertice> P1, P2, P3;
    vector<tCoste> D1, D2, D3;

    GrafoP<tCoste> TBA = GrafoTrenBusAvion(Tren, Bus, Avion, t1, t2);

    D1 = Dijkstra(TBA, origen,      P1);
    D2 = Dijkstra(TBA, origen+n,    P2);
    D3 = Dijkstra(TBA, origen+2*n,  P3);

    return min(D1[destino], min(D2[destino], D3[destino]));
}

template <typename tCoste> GrafoP<tCoste> GrafoTrenBusAvion(const GrafoP<tCoste>& Tren,
    const GrafoP<tCoste>& Bus, const GrafoP<tCoste>& Avion, tCoste t1, tCoste t2)
{
    const size_t n = Tren.numVert();  //tb se puede con el bus,...
	GrafoP<tCoste> A(3*n);
    ///Primero voy a inicializar con el grafo del Tren (1er cuadrante) y precio t1 (2º) y t2 (3º)
    for(int i=0; i< n; ++i)
    {   for(int j=0; j<n; ++j) //1er cuadrante
            A[i][j] = Tren[i][j];
        for(int j=n; j<2*n; ++j) //2º cuadrante
            if(i == j-n) A[i][j] = t1;
        for(int j=2*n; j<3*n; ++j) //3º cuadrante
            if(i == j-2*n) A[i][j] = t2;
    }
    ///Luego voy a inicializar con el grafo del Bus (5º)  y precio taxi1 (4º)  y taxi 2 (6º)
    for(int i=n; i<2*n; ++i)
    {   for(int j=0; j<n; ++j) //4º cuadrante
            if(i-n == j) A[i][j] = t1;
        for(int j=n; j<2*n; ++j) //5º cuadrante
            A[i][j] = Bus[i-n][j-n];
        for(int j=2*n; j<3*n; ++j) //6º cuadrante
            if(i-n == j-2*n) A[i][j] = t2;
    }
    ///Por ultimo voy a inicializar con el grafo del Avion (9º)  y precio taxi2 (7º)  y taxi 2 (8º)
    for(int i=2*n; i<3*n; ++i)
    {   for(int j=0; j<n; ++j) //7º cuadrante
            if(i-2*n == j) A[i][j] = t2;
        for(int j=n; j<2*n; ++j) //8º cuadrante
            if(i-2*n == j-2*n) A[i][j] = t2;
        for(int j=2*n; j<3*n; ++j) //9º cuadrante
            A[i][j] = Avion[i-2*n][j-2*n];
    }
	return A;
}
